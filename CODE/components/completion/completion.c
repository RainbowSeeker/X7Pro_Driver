#include "completion.h"
#include <rtdebug.h>

#define COMPLETED    1
#define UNCOMPLETED  0

/**
 * @brief This function will initialize a completion object.
 *
 * @param completion is a pointer to a completion object.
 */
void completion_init(struct completion *completion)
{
    base_t level;
    ASSERT(completion != NULL);

    level = os_hw_interrupt_disable();
    completion->flag = UNCOMPLETED;
    list_init(&completion->suspended_list);
    os_hw_interrupt_enable(level);
}

/**
 * @brief This function will wait for a completion, if the completion is unavailable, the thread shall wait for
 *        the completion up to a specified time.
 *
 * @param completion is a pointer to a completion object.
 *
 * @param timeout is a timeout period (unit: OS ticks). If the completion is unavailable, the thread will wait for
 *                the completion done up to the amount of time specified by the argument.
 *                NOTE: Generally, we use the macro RT_WAITING_FOREVER to set this parameter, which means that when the
 *                completion is unavailable, the thread will be waitting forever.
 *
 * @return Return the operation status. ONLY when the return value is RT_EOK, the operation is successful.
 *         If the return value is any other values, it means that the completion wait failed.
 *
 * @warning This function can ONLY be called in the thread context. It MUST NOT be called in interrupt context.
 */
err_t completion_wait(struct completion *completion,
                                 int32_t timeout)
{
    err_t result;
    base_t level;
    os_thread_t thread;
    ASSERT(completion != NULL);

    result = E_OK;
    thread = os_thread_self();
    level = os_hw_interrupt_disable();
    if (completion->flag != COMPLETED)
    {
        /* only one thread can suspend on complete */
        ASSERT(list_isempty(&(completion->suspended_list)));

        if (timeout == 0)
        {
            result = -E_TIMEOUT;
            goto __exit;
        }
        else
        {
            /* current context checking */
            if (os_interrupt_get_nest() != 0)
            {
                printf("Function[%s] shall not be used in ISR\n", __FUNCTION__);
                goto __exit;
            }

            /* reset thread error number */
            thread->error = E_OK;

            /* add to suspended list */
            list_insert_before(&completion->suspended_list,
                                  &thread->tlist);

            /* start timer */
            if (timeout > 0)
            {
                /* reset the timeout of thread timer and start it */
//                thread->thread_timer = os_timer_create("",
//                                os_thread_timeout,
//                                thread,
//                                timeout,
//                                TIMER_TYPE_ONE_SHOT);
//
//                os_timer_start(thread->thread_timer);
            }

            /* suspend thread */
            os_thread_suspend(thread);

            /* enable interrupt */
            os_hw_interrupt_enable(level);

            /* do schedule */
            os_schedule();

            /* thread is waked up */
            result = thread->error;

            level = os_hw_interrupt_disable();
        }
    }
    /* clean completed flag */
    completion->flag = UNCOMPLETED;

__exit:
    os_hw_interrupt_enable(level);

    return result;
}

void completion_done(struct completion *completion)
{
    base_t level;
    ASSERT(completion != NULL);

    if (completion->flag == COMPLETED)
        return;

    level = os_hw_interrupt_disable();
    completion->flag = COMPLETED;

    if (!list_isempty(&(completion->suspended_list)))
    {
        /* there is one thread in suspended list */
        struct thread *thread;

        /* get thread entry */
        thread = list_entry(completion->suspended_list.next, struct thread, tlist);

        os_hw_interrupt_enable(level);

        /* resume it */
        os_thread_resume(thread);
        /* perform a schedule */
        os_schedule();
    }
    else
    {
        os_hw_interrupt_enable(level);
    }
}

