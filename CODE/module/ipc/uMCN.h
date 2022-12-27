
#ifndef UMCN_H__
#define UMCN_H__

#include <common_def.h>
#include "system/os_def.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MCN_MALLOC(size)            malloc(size)
#define MCN_FREE(ptr)               free(ptr)
#define MCN_ENTER_CRITICAL          OS_ENTER_CRITICAL
#define MCN_EXIT_CRITICAL           OS_EXIT_CRITICAL
#define MCN_EVENT_HANDLE            osSemaphoreId
#define MCN_SEND_EVENT(event)       osSemaphoreRelease(event)
#define MCN_WAIT_EVENT(event, time) osSemaphoreWait(event, time)
#define MCN_ASSERT(EX)              ASSERT(EX)

#define MCN_MAX_LINK_NUM        30
#define MCN_FREQ_EST_WINDOW_LEN 5

typedef struct mcn_node McnNode;
typedef struct mcn_node* McnNode_t;
struct mcn_node {
    volatile uint8_t renewal;
    MCN_EVENT_HANDLE event;
    void (*pub_cb)(void* parameter);
    McnNode_t next;
};

typedef struct mcn_hub McnHub;
typedef struct mcn_hub* McnHub_t;
struct mcn_hub {
    const char* obj_name;
    const uint32_t obj_size;
    void* pdata;
    McnNode_t link_head;
    McnNode_t link_tail;
    uint32_t link_num;
    uint8_t published;
    uint8_t suspend;
    int (*echo)(void* parameter);
    /* publish freq estimate */
    float freq;
    uint16_t freq_est_window[MCN_FREQ_EST_WINDOW_LEN];
    uint16_t window_index;
};

typedef struct mcn_list McnList;
typedef struct mcn_list* McnList_t;
struct mcn_list {
    McnHub_t hub;
    McnList_t next;
};

/******************* Helper Macro *******************/
/* Obtain uMCN hub according to name */
#define MCN_HUB(_name) (&__mcn_##_name)
/* Declare a uMCN topic. Declare the topic at places where you need use it */
#define MCN_DECLARE(_name) extern McnHub __mcn_##_name
/* Define a uMCN topic. A topic should only be defined once */
#define MCN_DEFINE(_name, _size) \
    McnHub __mcn_##_name = {     \
        .obj_name = #_name,      \
        .obj_size = _size,       \
        .pdata = NULL,           \
        .link_head = NULL,       \
        .link_tail = NULL,       \
        .link_num = 0,           \
        .published = 0,          \
        .suspend = 0,            \
        .freq = 0.0f             \
    }

/******************* API *******************/
err_t mcn_init(void);
err_t mcn_advertise(McnHub_t hub, int (*echo)(void* parameter));
McnNode_t mcn_subscribe(McnHub_t hub, MCN_EVENT_HANDLE event, void (*pub_cb)(void* parameter));
err_t mcn_unsubscribe(McnHub_t hub, McnNode_t node);
err_t mcn_publish(McnHub_t hub, const void* data);
bool mcn_poll(McnNode_t node_t);
bool mcn_wait(McnNode_t node_t, int32_t timeout);
err_t mcn_copy(McnHub_t hub, McnNode_t node_t, void* buffer);
err_t mcn_copy_from_hub(McnHub_t hub, void* buffer);
void mcn_suspend(McnHub_t hub);
void mcn_resume(McnHub_t hub);
McnList_t mcn_get_list(void);
McnHub_t mcn_iterate(McnList_t* ite);
void mcn_node_clear(McnNode_t node_t);

#ifdef __cplusplus
}
#endif

#endif
