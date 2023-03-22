#ifndef WORK_QUEUE_H__
#define WORK_QUEUE_H__

#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCHEDULE_DELAY(_delay_ms) (systime_now_ms() + _delay_ms)

struct WorkItem {
    const char* name;
    uint32_t schedule_time; /* work scheduled time */
    uint16_t period;        /* period of work, 0 means only execute once */
    void* parameter;
    void (*run)(void* parameter);
};
typedef struct WorkItem* WorkItem_t;

struct WorkQueue {
    os_thread_t thread;
    uint8_t qsize;
    uint8_t size;
    WorkItem_t* queue;
    os_mutex_t lock;
};
typedef struct WorkQueue* WorkQueue_t;

WorkQueue_t workqueue_create(const char* name, uint8_t size, uint16_t stack_size, uint8_t priority);
err_t workqueue_delete(WorkQueue_t work_queue);
err_t workqueue_schedule_work(WorkQueue_t work_queue, WorkItem_t item);
err_t workqueue_cancel_work(WorkQueue_t work_queue, WorkItem_t item);

#ifdef __cplusplus
}
#endif

#endif