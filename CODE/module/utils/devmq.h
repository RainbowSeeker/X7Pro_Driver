
#ifndef DEVMQ_H__
#define DEVMQ_H__

#ifdef __cplusplus
extern "C" {
#endif
#include <common.h>
/* device status msg */
#define DEVICE_STATUS_CONNECT    (1)
#define DEVICE_STAUTS_DISCONNECT (2)
#define DEVICE_STATUS_RX         (3)
#define DEVICE_STATUS_TX         (4)

typedef int device_status;

err_t devmq_create(device_t device, uint32_t msg_size, uint32_t max_msgs);
err_t devmq_register(device_t device, void (*handler)(device_t dev, void* msg));
err_t devmq_deregister(device_t device);
err_t devmq_notify(device_t device, void* msg);
void devmq_distribute_msg(void* parameter);
err_t devmq_start_work(void);

#ifdef __cplusplus
}
#endif

#endif /* DEVMQ_H__ */
