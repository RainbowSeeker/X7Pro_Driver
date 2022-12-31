#include <common.h>

#include "module/console/console.h"
#include "module/system/statistic.h"
#include "module/system/systime.h"

#define CPU_USAGE_CALC_INTERVAL 1000

static uint64_t prev_schedule_time = 0;
static uint64_t prev_usage_cal_time = 0;

static void thread_idle_hook(void)
{
    uint64_t time_now;

    OS_ENTER_CRITICAL();

    time_now = systime_now_us();
    /* time_now could less than prev_usage_cal_time, this is because systick isr
     * is preempted by higher priority isr, which triggers thread schedule. At that
     * moment, the systime is not updated yet */
    if (time_now > prev_usage_cal_time && time_now - prev_usage_cal_time >= CPU_USAGE_CALC_INTERVAL * 1000)
    {
        struct list_node* list;
        struct thread* thread;
        cpu_usage_stats* stats;

        list = &(object_get_information(Object_Class_Thread)->object_list);

        for (struct list_node* node = list->next; node != list; node = node->next)
        {
            thread = (os_thread_t)list_entry(node, struct object, list);
            stats = (cpu_usage_stats*)thread->user_data;

            if (stats != NULL)
            {
                stats->cpu_usage = (stats->exec_time * 100.0f) / (time_now - prev_usage_cal_time);
                stats->exec_time = 0;
            }
        }
        /* update previous cpu usage calculate time */
        prev_usage_cal_time = time_now;
    }

    OS_EXIT_CRITICAL();
}

static void scheduler_hook(os_thread_t from, os_thread_t to)
{
    uint64_t time_now;
    cpu_usage_stats* stats = (cpu_usage_stats*)from->user_data;
    ASSERT(stats != NULL);

    time_now = systime_now_us();

    if (time_now < prev_schedule_time) {
        /* This could happen, because higher priority isr preempt systick isr,
         * so the systick time is not updated yet.
         */
        time_now += 1000000 / TICK_PER_SECOND;
    }
    /* from thread execution time = current time - last scheduled time */
    stats->exec_time += time_now - prev_schedule_time;
    stats->total_exec_time += stats->exec_time;

    /* update previous schedule time */
    prev_schedule_time = time_now;
}

static void thread_inited_hook(os_thread_t thread)
{
    cpu_usage_stats* stats = (cpu_usage_stats*)malloc(sizeof(cpu_usage_stats));
    ASSERT(stats != NULL);

    stats->exec_time = 0;
    stats->total_exec_time = 0;
    stats->cpu_usage = 0.0;

    thread->user_data = (uint32_t)stats;
}

static void thread_deleted_hook(os_thread_t thread)
{
    free((void*)thread->user_data);
}

/**
 * @brief Get the cpu usage consumption
 *
 * @return float The cpu usage in percent. e.g, 50.0 means 50%
 */
float get_cpu_usage(void)
{
    os_thread_t idle = os_thread_idle_gethandler();
    ASSERT(idle != NULL);
    cpu_usage_stats* stats = (cpu_usage_stats*)idle->user_data;
    float cpu_usage = -1.0f;

    if (stats != NULL) {
        cpu_usage = 100.0f - stats->cpu_usage;
    }

    return cpu_usage;
}

/**
 * @brief Initialize system statistic module
 *
 * @return err_t E_OK if successful
 */
err_t sys_stat_init(void)
{
    os_thread_inited_sethook(thread_inited_hook);
    os_thread_deleted_sethook(thread_deleted_hook);
    os_scheduler_sethook(scheduler_hook);
    os_thread_idle_sethook(thread_idle_hook);

    return E_OK;
}