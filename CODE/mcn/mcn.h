// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/22.
//

#ifndef X7PRO_DRIVER_MCN_H
#define X7PRO_DRIVER_MCN_H
#include "system/common.h"
#include "cmsis_os.h"
#include "stdbool.h"

#define MCN_FREQ_EST_WINDOW_LEN     5
#define MCN_MAX_LINK_NUM            30
#define MCN_MALLOC                  MALLOC
#define MCN_FREE                    FREE




typedef struct mcn_node_s
{
    volatile uint8_t renewal;
    osSemaphoreId event;

    void (*pub_cb)(void *parameter);

    struct mcn_node_s *next;
}mcn_node_t;


typedef struct mcn_hub_s
{
    const char *obj_name;
    const uint32_t obj_size;
    void *pdata;
    mcn_node_t *link_head;
    mcn_node_t *link_tail;
    uint32_t link_num;
    uint8_t published;
    uint8_t suspend;

    int (*echo)(void *parameter);

    /* publish freq estimate */
    float freq;
    uint16_t freq_est_window[MCN_FREQ_EST_WINDOW_LEN];
    uint16_t window_index;
}mcn_hub_t;

typedef struct mcn_list_s
{
    mcn_hub_t *hub;
    struct mcn_list_s *next;
}mcn_list_t;


/******************* Helper Macro *******************/
/* Obtain uMCN hub according to name */
#define MCN_HUB(_name) (&__mcn_##_name)
/* Declare a uMCN topic. Declare the topic at places where you need use it */
#define MCN_DECLARE(_name) extern mcn_hub_t __mcn_##_name
/* Define a uMCN topic. A topic should only be defined once */
#define MCN_DEFINE(_name, _size) \
    mcn_hub_t __mcn_##_name = {  \
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
err_status_e mcn_init(void);
err_status_e mcn_advertise(mcn_hub_t *hub, int (*echo)(void* parameter));
mcn_node_t *mcn_subscribe(mcn_hub_t *hub, osSemaphoreId event, void (*pub_cb)(void* parameter));
err_status_e mcn_unsubscribe(mcn_hub_t *hub, mcn_node_t *node);
err_status_e mcn_publish(mcn_hub_t *hub, const void* data);
bool mcn_poll(mcn_node_t *node_t);
bool mcn_wait(mcn_node_t *node_t, int32_t timeout);
err_status_e mcn_copy(mcn_hub_t *hub, mcn_node_t *node_t, void* buffer);
err_status_e mcn_copy_from_hub(mcn_hub_t *hub, void* buffer);
void mcn_suspend(mcn_hub_t *hub);
void mcn_resume(mcn_hub_t *hub);
mcn_list_t *mcn_get_list(void);
mcn_hub_t *mcn_iterate(mcn_list_t **ite);
mcn_hub_t *mcn_iterate(mcn_list_t **ite);
void mcn_node_clear(mcn_node_t *node_t);
#endif //X7PRO_DRIVER_MCN_H
