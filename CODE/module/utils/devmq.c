
#include <common.h>
#include <string.h>

#include "module/utils/devmq.h"
#include "module/workqueue/workqueue_manager.h"

#define DEVMQ_MAX_HANDLER  10
#define DEVMQ_MAX_MSG_SIZE 128

struct devmq_handler {
    os_mq_t mq;
    uint32_t msg_size;
    uint32_t max_msgs;
    light_device_t device;
    void (*handler)(light_device_t dev, void* msg);
};
typedef struct devmq_handler* devmq_handler_t;

typedef struct devmq_node* devmq_node_t;
struct devmq_node {
    devmq_handler_t handle;
    devmq_node_t next;
};

static struct devmq_node devmq_list = { .handle = NULL, .next = NULL };

static devmq_node_t find_last_node(void)
{
    devmq_node_t nod = &devmq_list;

    while (nod->next != NULL) {
        nod = nod->next;
    }
    return nod;
}

static devmq_node_t find_device_node(light_device_t device)
{
    for (devmq_node_t nod = &devmq_list; nod != NULL && nod->handle != NULL; nod = nod->next) {
        if (nod->handle->device == device) {
            return nod;
        }
    }
    return NULL;
}

err_t devmq_create(light_device_t device, uint32_t msg_size, uint32_t max_msgs)
{
    ASSERT(device != NULL);
    ASSERT(msg_size > 0);
    ASSERT(max_msgs > 0);

    if (msg_size > DEVMQ_MAX_MSG_SIZE) {
        console_printf("devmq create fail, exceed max msg size: %d %d\n", msg_size, DEVMQ_MAX_MSG_SIZE);
        return E_INVAL;
    }

    if (find_device_node(device) != NULL) {
        console_printf("devmq is already created for %s\n", device->name);
        return E_BUSY;
    }

    devmq_node_t new_nod = find_last_node();
    if (new_nod->handle != NULL) {
        new_nod->next = (devmq_node_t)malloc(sizeof(struct devmq_node));
        if (new_nod->next == NULL) {
            return E_NOMEM;
        }
        new_nod = new_nod->next;
    }

    new_nod->handle = (devmq_handler_t)malloc(sizeof(struct devmq_handler));
    if (new_nod->handle == NULL) {
        console_printf("devmq malloc fail for %s\n", device->name);
        return E_NOMEM;
    }
    new_nod->next = NULL;

    memset(new_nod->handle, 0, sizeof(struct devmq_handler));

    new_nod->handle->device = device;
    new_nod->handle->msg_size = msg_size;
    new_nod->handle->max_msgs = max_msgs;
    new_nod->handle->mq = os_mq_create(device->name, msg_size, max_msgs);
    if (new_nod->handle->mq == NULL) {
        console_printf("create devmq fail for %s\n", device->name);
        return E_RROR;
    }

    return E_OK;
}

err_t devmq_register(light_device_t device, void (*handler)(light_device_t dev, void* msg))
{
    ASSERT(device != NULL);
    ASSERT(handler != NULL);

    devmq_node_t nod = find_device_node(device);
    if (nod == NULL) {
        console_printf("%s devmq is not created\n", device->name);
        return E_NOSYS;
    }

    nod->handle->handler = handler;
    return E_OK;
}

err_t devmq_deregister(light_device_t device)
{
    ASSERT(device != NULL);

    devmq_node_t nod = find_device_node(device);
    if (nod == NULL) {
        console_printf("%s devmq is not created\n", device->name);
        return E_NOSYS;
    }

    nod->handle->handler = NULL;
    return E_OK;
}

err_t devmq_notify(light_device_t device, void* msg)
{
    ASSERT(device != NULL);
    ASSERT(msg != NULL);

    devmq_node_t nod = find_device_node(device);
    if (nod == NULL) {
        console_printf("%s devmq is not created\n", device->name);
        return E_NOSYS;
    }

    err_t err = os_mq_send(nod->handle->mq, msg, nod->handle->msg_size);
    return (err == E_OK) ? E_OK : E_RROR;
}

void devmq_distribute_msg(void* parameter)
{
    static uint8_t msg_buffer[DEVMQ_MAX_MSG_SIZE];

    /* traverse all device nodes */
    for (devmq_node_t nod = &devmq_list; nod != NULL; nod = nod->next) {
        if (nod->handle) {
            /* check if handler is registered */
            if (nod->handle->handler == NULL) {
                continue;
            }
            /* now distribute messages to handler */
            while (os_mq_recv(nod->handle->mq, msg_buffer, nod->handle->msg_size, 0) == E_OK) {
                nod->handle->handler(nod->handle->device, msg_buffer);
            }
        }
    }
}

err_t devmq_start_work(void)
{
    static struct WorkItem item = {
        .name = "devmq",
        .period = 50,
        .schedule_time = 0,
        .run = devmq_distribute_msg
    };
    WorkQueue_t wq = workqueue_find("wq:lp_work");
    if (wq == NULL) {
        return E_NOSYS;
    }

    if (workqueue_schedule_work(wq, &item) != E_OK) {
        return E_RROR;
    }
    return E_OK;
}
