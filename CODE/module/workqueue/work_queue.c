// Copyright (c) 2022 By RainbowSeeker.

#include "work_queue.h"

#define work_lock(_wq)      os_mutex_take(_wq->lock, OS_WAIT_FOREVER)
#define work_unlock(_wq)    os_mutex_release(_wq->lock)

static void __swap_item(WorkItem_t* a, WorkItem_t* b)
{
    WorkItem_t temp = *b;
    *b = *a;
    *a = temp;
}

void __heapify(WorkItem_t* queue, uint8_t size, int idx)
{
    if (size == 1) {
        /* single element in the heap */
        return;
    }

    /* Find the smallest among root, left child and right child */
    int smallest = idx;
    int l = 2 * idx + 1;
    int r = 2 * idx + 2;
    if (l < size && queue[l]->schedule_time < queue[smallest]->schedule_time)
        smallest = l;
    if (r < size && queue[r]->schedule_time < queue[smallest]->schedule_time)
        smallest = r;

    /* Swap and continue heapifying if root is not smallest */
    if (smallest != idx) {
        __swap_item(&queue[idx], &queue[smallest]);
        __heapify(queue, size, smallest);
    }
}

/**
 * @brief Pop the latest work from workqueue
 * 
 * @param work_queue The target workqueue
 * @return WorkItem_t The latest work item
 */
static WorkItem_t workqueue_pop(WorkQueue_t work_queue)
{
    ASSERT(work_queue != NULL);

    work_lock(work_queue);

    if (work_queue->size == 0) {
        work_unlock(work_queue);
        return NULL;
    }
    WorkItem_t dq_item = work_queue->queue[0];

    work_unlock(work_queue);

    if (workqueue_cancel_work(work_queue, dq_item) != E_OK) {
        return NULL;
    }

    return dq_item;
}


/**
 * @brief Workqueue execution thread
 * 
 * @param parameter the pointer of workqueue
 */
static void workqueue_executor(void* parameter)
{
    ASSERT(parameter != NULL);

    WorkQueue_t work_queue = (WorkQueue_t)parameter;
    WorkItem_t work_item;
    uint32_t time_now, schedule_time;

    while (1) {
        if (work_queue->size == 0){
            /* no work scheduled, suspend itself */
            os_thread_suspend(os_thread_self());
            os_schedule();
        }

        time_now = systime_now_ms();
        schedule_time = work_queue->queue[0]->schedule_time;
        if (schedule_time > time_now) {
            systime_msleep(schedule_time - time_now);
            continue;
        }

        work_item = workqueue_pop(work_queue);
        if (work_item != NULL) {
            /* do work */
            work_item->run(work_item->parameter);
            /* if period is set, push work item back to queue */
            if (work_item->period > 0) {
                work_item->schedule_time = SCHEDULE_DELAY(work_item->period);
                workqueue_schedule_work(work_queue, work_item);
            }
        }
    }
}

/**
 * @brief Schedule a work for workqueue
 * @note  schedule_time of item indicates when the work should be executed.
 *        0 means it should be executed immediately.
 *
 * @param work_queue The target workqueue
 * @param item The work item to be scheduled
 * @return err_t E_OK on OK
 */
err_t workqueue_schedule_work(WorkQueue_t work_queue, WorkItem_t item)
{
    ASSERT(work_queue != NULL);
    ASSERT(item != NULL);
    ASSERT(item->run != NULL);

    /* first cancel old work if any */
    workqueue_cancel_work(work_queue, item);

    work_lock(work_queue);

    if (work_queue->size >= work_queue->qsize - 1) {
        work_unlock(work_queue);
        return E_FULL;
    }

    work_queue->queue[work_queue->size++] = item;
    for (int i = work_queue->size / 2 - 1; i >= 0; i--) {
        __heapify(work_queue->queue, work_queue->size, i);
    }

    work_unlock(work_queue);

    /* wakeup workqueue thread */
    os_thread_resume(work_queue->thread);
    /* perform a schedule */
    os_schedule();

    return E_OK;
}

/**
 * @brief Cancel a work from workqueue
 * 
 * @param work_queue The target workqueue
 * @param item The work item to be canceled
 * @return err_t E_OK on OK
 */
err_t workqueue_cancel_work(WorkQueue_t work_queue, WorkItem_t item)
{
    ASSERT(work_queue != NULL);
    ASSERT(item != NULL);

    int idx = -1;

    work_lock(work_queue);

    for (int i = 0; i < work_queue->size; i++) {
        if (item == work_queue->queue[i]) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        work_unlock(work_queue);
        return E_EMPTY;
    }

    if (work_queue->size > 1)   __swap_item(&work_queue->queue[idx], &work_queue->queue[work_queue->size - 1]);

    work_queue->size -= 1;
    for (int i = work_queue->size / 2 - 1; i >= 0; i--) {
        __heapify(work_queue->queue, work_queue->size, i);
    }

    work_unlock(work_queue);

    return E_OK;
}

/**
 * @brief Delete a workqueue
 * 
 * @param work_queue Workqueue to be deleted
 * @return err_t E_OK on OK
 */
err_t workqueue_delete(WorkQueue_t work_queue)
{
    ASSERT(work_queue != NULL);

    if (os_thread_delete(work_queue->thread) != E_OK) {
        return E_RROR;
    }

    if (os_mutex_delete(work_queue->lock) != E_OK) {
        return E_RROR;
    }

    free(work_queue->queue);
    free(work_queue);

    return E_OK;
}

/**
 * @brief Create a workqueue
 * 
 * @param name Name of workqueue
 * @param size Size of workqueue
 * @param stack_size Stack size of workqueue thread
 * @param priority Priority of workqueue thread
 * @return WorkQueue_t Workqueue pointer
 */
WorkQueue_t workqueue_create(const char* name, uint8_t size, uint16_t stack_size, uint8_t priority)
{
    ASSERT(size > 0);
    ASSERT(stack_size > 0);

    WorkQueue_t work_queue = (WorkQueue_t)malloc(sizeof(struct WorkQueue));
    if (work_queue == NULL) {
        return NULL;
    }

    work_queue->queue = (WorkItem_t*)malloc(size * sizeof(WorkItem_t));
    if (work_queue->queue == NULL) {
        goto _exit;
    }
    work_queue->qsize = size;
    work_queue->size = 0;


    os_mutex_init(&work_queue->lock);
    if (work_queue->lock == NULL) {
        goto _exit;
    }

    work_queue->thread = os_thread_create(name,
                                          workqueue_executor,
                                          work_queue,
                                          priority,
                                          stack_size);

    if (work_queue->thread == NULL) {
        goto _exit;
    }

    if (os_thread_startup(work_queue->thread) != E_OK) {
        os_thread_delete(work_queue->thread);
        goto _exit;
    }

    return work_queue;

_exit:
    free(work_queue);
    return NULL;
}
