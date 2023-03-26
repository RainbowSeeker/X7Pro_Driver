
/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-04-30     Bernard      first implementation
 * 2006-05-04     Bernard      add list_thread,
 *                                 list_sem,
 *                                 list_timer
 * 2006-05-20     Bernard      add list_mutex,
 *                                 list_mailbox,
 *                                 list_msgqueue,
 *                                 list_event,
 *                                 list_fevent,
 *                                 list_mempool
 * 2006-06-03     Bernard      display stack information in list_thread
 * 2006-08-10     Bernard      change version to invoke show_version
 * 2008-09-10     Bernard      update the list function for finsh syscall
 *                                 list and sysvar list
 * 2009-05-30     Bernard      add list_device
 * 2010-04-21     yi.qiu       add list_module
 * 2012-04-29     goprife      improve the command line auto-complete feature.
 * 2012-06-02     lgnq         add list_memheap
 * 2012-10-22     Bernard      add MS VC++ patch.
 * 2016-06-02     armink       beautify the list_thread command
 * 2018-11-22     Jesven       list_thread add smp support
 * 2018-12-27     Jesven       Fix the problem that disable interrupt too long in list_thread
 *                             Provide protection for the "first layer of objects" when list_*
 * 2020-04-07     chenhui      add clear
 */

#include "finsh.h"

#define LIST_FIND_OBJ_NR 8

long hello(void)
{
    printf("Hello Rainbow!\n");

    return 0;
}
FINSH_FUNCTION_EXPORT(hello, say hello world);

static long clear(void)
{
    printf("\x1b[2J\x1b[H");

    return 0;
}
FINSH_FUNCTION_EXPORT(clear,clear the terminal screen);
MSH_CMD_EXPORT(clear,clear the terminal screen);

extern void show_version(void);
long version(void)
{
    show_version();

    return 0;
}
FINSH_FUNCTION_EXPORT(version, show version information);

static_inline void object_split(int len)
{
    while (len--) printf("-");
}

typedef struct
{
    list_t *list;
    list_t **array;
    uint8_t type;
    int nr;             /* input: max nr, can't be 0 */
    int nr_out;         /* out: got nr */
} list_get_next_t;

static void list_find_init(list_get_next_t *p, uint8_t type, list_t **array, int nr)
{
    struct object_information *info;
    list_t *list;

    info = object_get_information((enum object_class_type)type);
    list = &info->object_list;

    p->list = list;
    p->type = type;
    p->array = array;
    p->nr = nr;
    p->nr_out = 0;
}

static list_t *list_get_next(list_t *current, list_get_next_t *arg)
{
    int first_flag = 0;
    ubase_t level;
    list_t *node, *list;
    list_t **array;
    int nr;

    arg->nr_out = 0;

    if (!arg->nr || !arg->type)
    {
        return (list_t *)NULL;
    }

    list = arg->list;

    if (!current) /* find first */
    {
        node = list;
        first_flag = 1;
    }
    else
    {
        node = current;
    }

    level = os_hw_interrupt_disable();

    if (!first_flag)
    {
        struct object *obj;
        /* The node in the list? */
        obj = list_entry(node, struct object, list);
        if ((obj->type & ~Object_Class_Static) != arg->type)
        {
            os_hw_interrupt_enable(level);
            return (list_t *)NULL;
        }
    }

    nr = 0;
    array = arg->array;
    while (1)
    {
        node = node->next;

        if (node == list)
        {
            node = (list_t *)NULL;
            break;
        }
        nr++;
        *array++ = node;
        if (nr == arg->nr)
        {
            break;
        }
    }

    os_hw_interrupt_enable(level);
    arg->nr_out = nr;
    return node;
}

long list_thread(void)
{
    ubase_t level;
    list_get_next_t find_arg;
    list_t *obj_list[LIST_FIND_OBJ_NR];
    list_t *next = (list_t*)NULL;
    const char *item_title = "thread";
    int maxlen;

    list_find_init(&find_arg, Object_Class_Thread, obj_list, sizeof(obj_list)/sizeof(obj_list[0]));

    maxlen = NAME_MAX_LEN;

#ifdef USING_SMP
    printf("%-*.s cpu pri  status      sp     stack size max used left tick  error\n", maxlen, item_title); object_split(maxlen);
    printf(     " --- ---  ------- ---------- ----------  ------  ---------- ---\n");
#else
    printf("%-*s  pri  status  stacksz max_used usage error\n", maxlen, item_title); object_split(maxlen);
    printf(     "  ---  ------  ------- -------- ----- -----\n");
#endif /*USING_SMP*/

    os_thread_update_info_all();
    do
    {
        next = list_get_next(next, &find_arg);
        {
            int i;
            for (i = 0; i < find_arg.nr_out; i++)
            {
                struct object *obj;
                struct thread thread_info, *thread;

                obj = list_entry(obj_list[i], struct object, list);
                level = os_hw_interrupt_disable();

                if ((obj->type & ~Object_Class_Static) != find_arg.type)
                {
                    os_hw_interrupt_enable(level);
                    continue;
                }
                /* copy info */
                memcpy(&thread_info, obj, sizeof thread_info);
                os_hw_interrupt_enable(level);

                thread = (struct thread*)obj;
                {
                    uint8_t stat;

#ifdef USING_SMP
                    if (thread->oncpu != CPU_DETACHED)
                        printf("%-*.*s %3d %3d ", maxlen, NAME_MAX_LEN, thread->name, thread->oncpu, thread->current_priority);
                    else
                        printf("%-*.*s N/A %3d ", maxlen, NAME_MAX_LEN, thread->name, thread->current_priority);

#else
                    printf("%-*.*s %3d  ", maxlen, NAME_MAX_LEN, thread->parent.name, thread->priority);
#endif /*USING_SMP*/
                    stat = (thread->stat & THREAD_STAT_MASK);
                    if (stat == THREAD_READY)        printf(" ready  ");
                    else if (stat == THREAD_SUSPEND) printf(" suspend");
                    else if (stat == THREAD_INIT)    printf(" init   ");
                    else if (stat == THREAD_CLOSE)   printf(" close  ");
                    else if (stat == THREAD_RUNNING) printf(" running");

                    cpu_usage_stats* cpu_stat = (cpu_usage_stats*)thread->user_data;
#if defined(ARCH_CPU_STACK_GROWS_UPWARD)
                    ptr = (uint8_t *)thread->stack_addr + thread->stack_size - 1;
                    while (*ptr == '#')ptr --;

                    printf(" 0x%08x 0x%08x    %02d%%   0x%08x %03d\n",
                            ((ubase_t)thread->sp - (ubase_t)thread->stack_addr),
                            thread->stack_size,
                            ((ubase_t)ptr - (ubase_t)thread->stack_addr) * 100 / thread->stack_size,
                            thread->remaining_tick,
                            thread->error);
#else
                    printf("%8lu    %02lu%%   %.2f%%   %03d\n",
                            thread->stack_size,
                            (thread->max_used) * 100
                            / thread->stack_size,
                           cpu_stat != NULL ? cpu_stat->cpu_usage : -1.0f,
                            thread->error);
#endif
                }
            }
        }
    }
    while (next != (list_t*)NULL);

    return 0;
}
FINSH_FUNCTION_EXPORT(list_thread, list thread);

//static void show_wait_queue(struct list_node *list)
//{
//    struct thread *thread;
//    struct list_node *node;
//
//    for (node = list->next; node != list; node = node->next)
//    {
//        thread = list_entry(node, struct thread, tlist);
//        printf("%s", thread->name);
//
//        if (node->next != list)
//            printf("/");
//    }
//}

#ifdef USING_SEMAPHORE
long list_sem(void)
{
    ubase_t level;
    list_get_next_t find_arg;
    list_t *obj_list[LIST_FIND_OBJ_NR];
    list_t *next = (list_t*)NULL;

    int maxlen;
    const char *item_title = "semaphore";

    list_find_init(&find_arg, Object_Class_Semaphore, obj_list, sizeof(obj_list)/sizeof(obj_list[0]));

    maxlen = NAME_MAX_LEN;

    printf("%-*.s v   suspend thread\n", maxlen, item_title); object_split(maxlen);
    printf(     " --- --------------\n");

    do
    {
        next = list_get_next(next, &find_arg);
        {
            int i;
            for (i = 0; i < find_arg.nr_out; i++)
            {
                struct object *obj;
                struct semaphore *sem;

                obj = list_entry(obj_list[i], struct object, list);
                level = os_hw_interrupt_disable();
                if ((obj->type & ~Object_Class_Static) != find_arg.type)
                {
                    os_hw_interrupt_enable(level);
                    continue;
                }
                os_hw_interrupt_enable(level);

                sem = (struct semaphore*)obj;
                if (!list_isempty(&sem->parent.suspend_thread))
                {
                    printf("%-*.*s %03d %d:",
                            maxlen, NAME_MAX_LEN,
                            sem->parent.parent.name,
                            sem->value,
                            list_len(&sem->parent.suspend_thread));
                    show_wait_queue(&(sem->parent.suspend_thread));
                    printf("\n");
                }
                else
                {
                    printf("%-*.*s %03d %d\n",
                            maxlen, NAME_MAX_LEN,
                            sem->parent.parent.name,
                            sem->value,
                            list_len(&sem->parent.suspend_thread));
                }
            }
        }
    }
    while (next != (list_t*)NULL);

    return 0;
}
FINSH_FUNCTION_EXPORT(list_sem, list semaphore in system);
#endif

#ifdef USING_EVENT
long list_event(void)
{
    ubase_t level;
    list_get_next_t find_arg;
    list_t *obj_list[LIST_FIND_OBJ_NR];
    list_t *next = (list_t*)NULL;

    int maxlen;
    const char *item_title = "event";

    list_find_init(&find_arg, Object_Class_Event, obj_list, sizeof(obj_list)/sizeof(obj_list[0]));

    maxlen = NAME_MAX_LEN;

    printf("%-*.s      set    suspend thread\n", maxlen, item_title); object_split(maxlen);
    printf(     "  ---------- --------------\n");

    do
    {
        next = list_get_next(next, &find_arg);
        {
            int i;
            for (i = 0; i < find_arg.nr_out; i++)
            {
                struct object *obj;
                struct event *e;

                obj = list_entry(obj_list[i], struct object, list);
                level = os_hw_interrupt_disable();
                if ((obj->type & ~Object_Class_Static) != find_arg.type)
                {
                    os_hw_interrupt_enable(level);
                    continue;
                }

                os_hw_interrupt_enable(level);

                e = (struct event *)obj;
                if (!list_isempty(&e->parent.suspend_thread))
                {
                    printf("%-*.*s  0x%08x %03d:",
                            maxlen, NAME_MAX_LEN,
                            e->parent.parent.name,
                            e->set,
                            list_len(&e->parent.suspend_thread));
                    show_wait_queue(&(e->parent.suspend_thread));
                    printf("\n");
                }
                else
                {
                    printf("%-*.*s  0x%08x 0\n",
                            maxlen, NAME_MAX_LEN, e->parent.parent.name, e->set);
                }
            }
        }
    }
    while (next != (list_t*)NULL);

    return 0;
}
FINSH_FUNCTION_EXPORT(list_event, list event in system);
#endif

#ifdef USING_MUTEX
long list_mutex(void)
{
    ubase_t level;
    list_get_next_t find_arg;
    list_t *obj_list[LIST_FIND_OBJ_NR];
    list_t *next = (list_t*)NULL;

    int maxlen;
    const char *item_title = "mutex";

    list_find_init(&find_arg, Object_Class_Mutex, obj_list, sizeof(obj_list)/sizeof(obj_list[0]));

    maxlen = NAME_MAX_LEN;

    printf("%-*.s   owner  hold suspend thread\n", maxlen, item_title); object_split(maxlen);
    printf(     " -------- ---- --------------\n");

    do
    {
        next = list_get_next(next, &find_arg);
        {
            int i;
            for (i = 0; i < find_arg.nr_out; i++)
            {
                struct object *obj;
                struct mutex *m;

                obj = list_entry(obj_list[i], struct object, list);
                level = os_hw_interrupt_disable();
                if ((obj->type & ~Object_Class_Static) != find_arg.type)
                {
                    os_hw_interrupt_enable(level);
                    continue;
                }

                os_hw_interrupt_enable(level);

                m = (struct mutex *)obj;
                printf("%-*.*s %-8.*s %04d %d\n",
                        maxlen, NAME_MAX_LEN,
                        m->parent.parent.name,
                        NAME_MAX_LEN,
                        m->owner->name,
                        m->hold,
                        list_len(&m->parent.suspend_thread));

            }
        }
    }
    while (next != (list_t*)NULL);

    return 0;
}
FINSH_FUNCTION_EXPORT(list_mutex, list mutex in system);
#endif

#ifdef USING_MAILBOX
long list_mailbox(void)
{
    ubase_t level;
    list_get_next_t find_arg;
    list_t *obj_list[LIST_FIND_OBJ_NR];
    list_t *next = (list_t*)NULL;

    int maxlen;
    const char *item_title = "mailbox";

    list_find_init(&find_arg, Object_Class_MailBox, obj_list, sizeof(obj_list)/sizeof(obj_list[0]));

    maxlen = NAME_MAX_LEN;

    printf("%-*.s entry size suspend thread\n", maxlen, item_title); object_split(maxlen);
    printf(     " ----  ---- --------------\n");

    do
    {
        next = list_get_next(next, &find_arg);
        {
            int i;
            for (i = 0; i < find_arg.nr_out; i++)
            {
                struct object *obj;
                struct mailbox *m;

                obj = list_entry(obj_list[i], struct object, list);
                level = os_hw_interrupt_disable();
                if ((obj->type & ~Object_Class_Static) != find_arg.type)
                {
                    os_hw_interrupt_enable(level);
                    continue;
                }

                os_hw_interrupt_enable(level);

                m = (struct mailbox *)obj;
                if (!list_isempty(&m->parent.suspend_thread))
                {
                    printf("%-*.*s %04d  %04d %d:",
                            maxlen, NAME_MAX_LEN,
                            m->parent.parent.name,
                            m->entry,
                            m->size,
                            list_len(&m->parent.suspend_thread));
                    show_wait_queue(&(m->parent.suspend_thread));
                    printf("\n");
                }
                else
                {
                    printf("%-*.*s %04d  %04d %d\n",
                            maxlen, NAME_MAX_LEN,
                            m->parent.parent.name,
                            m->entry,
                            m->size,
                            list_len(&m->parent.suspend_thread));
                }

            }
        }
    }
    while (next != (list_t*)NULL);

    return 0;
}
FINSH_FUNCTION_EXPORT(list_mailbox, list mail box in system);
#endif

#ifdef USING_MESSAGEQUEUE
long list_msgqueue(void)
{
    ubase_t level;
    list_get_next_t find_arg;
    list_t *obj_list[LIST_FIND_OBJ_NR];
    list_t *next = (list_t*)NULL;

    int maxlen;
    const char *item_title = "msgqueue";

    list_find_init(&find_arg, Object_Class_MessageQueue, obj_list, sizeof(obj_list)/sizeof(obj_list[0]));

    maxlen = NAME_MAX_LEN;

    printf("%-*.s entry suspend thread\n", maxlen, item_title); object_split(maxlen);
    printf(     " ----  --------------\n");
    do
    {
        next = list_get_next(next, &find_arg);
        {
            int i;
            for (i = 0; i < find_arg.nr_out; i++)
            {
                struct object *obj;
                struct messagequeue *m;

                obj = list_entry(obj_list[i], struct object, list);
                level = os_hw_interrupt_disable();
                if ((obj->type & ~Object_Class_Static) != find_arg.type)
                {
                    os_hw_interrupt_enable(level);
                    continue;
                }

                os_hw_interrupt_enable(level);

                m = (struct messagequeue *)obj;
                if (!list_isempty(&m->parent.suspend_thread))
                {
                    printf("%-*.*s %04d  %d:",
                            maxlen, NAME_MAX_LEN,
                            m->parent.parent.name,
                            m->entry,
                            list_len(&m->parent.suspend_thread));
                    show_wait_queue(&(m->parent.suspend_thread));
                    printf("\n");
                }
                else
                {
                    printf("%-*.*s %04d  %d\n",
                            maxlen, NAME_MAX_LEN,
                            m->parent.parent.name,
                            m->entry,
                            list_len(&m->parent.suspend_thread));
                }
            }
        }
    }
    while (next != (list_t*)NULL);

    return 0;
}
FINSH_FUNCTION_EXPORT(list_msgqueue, list message queue in system);
#endif

#ifdef USING_MEMHEAP
long list_memheap(void)
{
    ubase_t level;
    list_get_next_t find_arg;
    list_t *obj_list[LIST_FIND_OBJ_NR];
    list_t *next = (list_t*)NULL;

    int maxlen;
    const char *item_title = "memheap";

    list_find_init(&find_arg, Object_Class_MemHeap, obj_list, sizeof(obj_list)/sizeof(obj_list[0]));

    maxlen = NAME_MAX_LEN;

    printf("%-*.s  pool size  max used size available size\n", maxlen, item_title); object_split(maxlen);
    printf(      " ---------- ------------- --------------\n");
    do
    {
        next = list_get_next(next, &find_arg);
        {
            int i;
            for (i = 0; i < find_arg.nr_out; i++)
            {
                struct object *obj;
                struct memheap *mh;

                obj = list_entry(obj_list[i], struct object, list);
                level = os_hw_interrupt_disable();
                if ((obj->type & ~Object_Class_Static) != find_arg.type)
                {
                    os_hw_interrupt_enable(level);
                    continue;
                }

                os_hw_interrupt_enable(level);

                mh = (struct memheap *)obj;

                printf("%-*.*s %-010d %-013d %-05d\n",
                        maxlen, NAME_MAX_LEN,
                        mh->parent.name,
                        mh->pool_size,
                        mh->max_used_size,
                        mh->available_size);

            }
        }
    }
    while (next != (list_t*)NULL);

    return 0;
}
FINSH_FUNCTION_EXPORT(list_memheap, list memory heap in system);
FINSH_FUNCTION_EXPORT(list_memheap, list memory heap in system);
#endif

#ifdef USING_MEMPOOL
long list_mempool(void)
{
    ubase_t level;
    list_get_next_t find_arg;
    list_t *obj_list[LIST_FIND_OBJ_NR];
    list_t *next = (list_t*)NULL;

    int maxlen;
    const char *item_title = "mempool";

    list_find_init(&find_arg, Object_Class_MemPool, obj_list, sizeof(obj_list)/sizeof(obj_list[0]));

    maxlen = NAME_MAX_LEN;

    printf("%-*.s block total free suspend thread\n", maxlen, item_title); object_split(maxlen);
    printf(     " ----  ----  ---- --------------\n");
    do
    {
        next = list_get_next(next, &find_arg);
        {
            int i;
            for (i = 0; i < find_arg.nr_out; i++)
            {
                struct object *obj;
                struct mempool *mp;
                int suspend_thread_count;
                list_t *node;

                obj = list_entry(obj_list[i], struct object, list);
                level = os_hw_interrupt_disable();
                if ((obj->type & ~Object_Class_Static) != find_arg.type)
                {
                    os_hw_interrupt_enable(level);
                    continue;
                }

                os_hw_interrupt_enable(level);

                mp = (struct mempool *)obj;

                suspend_thread_count = 0;
                list_for_each(node, &mp->suspend_thread)
                {
                    suspend_thread_count++;
                }

                if (suspend_thread_count > 0)
                {
                    printf("%-*.*s %04d  %04d  %04d %d:",
                            maxlen, NAME_MAX_LEN,
                            mp->parent.name,
                            mp->block_size,
                            mp->block_total_count,
                            mp->block_free_count,
                            suspend_thread_count);
                    show_wait_queue(&(mp->suspend_thread));
                    printf("\n");
                }
                else
                {
                    printf("%-*.*s %04d  %04d  %04d %d\n",
                            maxlen, NAME_MAX_LEN,
                            mp->parent.name,
                            mp->block_size,
                            mp->block_total_count,
                            mp->block_free_count,
                            suspend_thread_count);
                }
            }
        }
    }
    while (next != (list_t*)NULL);

    return 0;
}
FINSH_FUNCTION_EXPORT(list_mempool, list memory pool in system)
#endif

#ifdef USING_TIMER
long list_timer(void)
{
    ubase_t level;
    list_get_next_t find_arg;
    list_t *obj_list[LIST_FIND_OBJ_NR];
    list_t *next = (list_t*)NULL;

    int maxlen;
    const char *item_title = "timer";

    list_find_init(&find_arg, Object_Class_Timer, obj_list, sizeof(obj_list)/sizeof(obj_list[0]));

    maxlen = NAME_MAX_LEN;

    printf("%-*.s  periodic   timeout       flag\n", maxlen, item_title); object_split(maxlen);
    printf(     " ---------- ---------- -----------\n");
    do {
        next = list_get_next(next, &find_arg);
        {
            int i;
            for (i = 0; i < find_arg.nr_out; i++)
            {
                struct object *obj;
                struct timer *timer;

                obj = list_entry(obj_list[i], struct object, list);
                level = os_hw_interrupt_disable();
                if ((obj->type & ~Object_Class_Static) != find_arg.type)
                {
                    os_hw_interrupt_enable(level);
                    continue;
                }

                os_hw_interrupt_enable(level);

                timer = (struct timer *)obj;
                printf("%-*.*s 0x%08x 0x%08x ",
                        maxlen, NAME_MAX_LEN,
                        timer->parent.name,
                        timer->init_tick,
                        timer->timeout_tick);
                if (timer->parent.flag & TIMER_FLAG_ACTIVATED)
                    printf("activated\n");
                else
                    printf("deactivated\n");

            }
        }
    }
    while (next != (list_t*)NULL);

    printf("current tick:0x%08x\n", tick_get());

    return 0;
}
FINSH_FUNCTION_EXPORT(list_timer, list timer in system);
#endif


static char *const device_type_str[] =
{
    "Character Device",
    "Block Device",
    "Network Interface",
    "MTD Device",
    "CAN Device",
    "RTC",
    "Sound Device",
    "Graphic Device",
    "I2C Bus",
    "I2C Device",
    "USB Slave Device",
    "USB Host Bus",
    "SPI Bus",
    "SPI Device",
    "SDIO Bus",
    "PM Pseudo Device",
    "Pipe",
    "Portal Device",
    "Timer Device",
    "Miscellaneous Device",
    "Sensor Device",
    "Touch Device",
    "Phy Device",
    "Unknown"
};

long list_device(void)
{
    ubase_t level;
    list_get_next_t find_arg;
    list_t *obj_list[LIST_FIND_OBJ_NR];
    list_t *next = (list_t*)NULL;

    int maxlen;
    const char *item_title = "device";

    list_find_init(&find_arg, Object_Class_Device, obj_list, sizeof(obj_list)/sizeof(obj_list[0]));

    maxlen = NAME_MAX_LEN;

    printf("%-*.s         type         ref count\n", maxlen, item_title); object_split(maxlen);
    printf(     " -------------------- ----------\n");
    do
    {
        next = list_get_next(next, &find_arg);
        {
            int i;
            for (i = 0; i < find_arg.nr_out; i++)
            {
                struct object *obj;
                struct device *device;

                obj = list_entry(obj_list[i], struct object, list);
                level = os_hw_interrupt_disable();
                if ((obj->type & ~Object_Class_Static) != find_arg.type)
                {
                    os_hw_interrupt_enable(level);
                    continue;
                }

                os_hw_interrupt_enable(level);

                device = (struct device *)obj;
                printf("%-*.*s %-20s %-8d\n",
                        maxlen, NAME_MAX_LEN,
                        device->name,
                        (device->type <= Device_Class_Unknown) ?
                        device_type_str[device->type] :
                        device_type_str[Device_Class_Unknown],
                        device->ref_count);

            }
        }
    }
    while (next != (list_t*)NULL);

    return 0;
}
FINSH_FUNCTION_EXPORT(list_device, list device in system);


#ifndef FINSH_USING_MSH_ONLY
static int str_is_prefix(const char *prefix, const char *str)
{
    while ((*prefix) && (*prefix == *str))
    {
        prefix ++;
        str ++;
    }

    if (*prefix == 0)
        return 0;

    return -1;
}

static int str_common(const char *str1, const char *str2)
{
    const char *str = str1;

    while ((*str != 0) && (*str2 != 0) && (*str == *str2))
    {
        str ++;
        str2 ++;
    }

    return (str - str1);
}

void list_prefix(char *prefix)
{
    struct finsh_syscall_item *syscall_item;
    struct finsh_sysvar_item *sysvar_item;
    uint16_t func_cnt, var_cnt;
    int length, min_length;
    const char *name_ptr;

    func_cnt = 0;
    var_cnt  = 0;
    min_length = 0;
    name_ptr = NULL;

    /* checks in system function call */
    {
        struct finsh_syscall *index;
        for (index = _syscall_table_begin;
                index < _syscall_table_end;
                FINSH_NEXT_SYSCALL(index))
        {
            /* skip internal command */
            if (str_is_prefix("__", index->name) == 0) continue;

            if (str_is_prefix(prefix, index->name) == 0)
            {
                if (func_cnt == 0)
                {
                    printf("--function:\n");

                    if (*prefix != 0)
                    {
                        /* set name_ptr */
                        name_ptr = index->name;

                        /* set initial length */
                        min_length = strlen(name_ptr);
                    }
                }

                func_cnt ++;

                if (*prefix != 0)
                {
                    length = str_common(name_ptr, index->name);
                    if (length < min_length)
                        min_length = length;
                }

#ifdef FINSH_USING_DESCRIPTION
                printf("%-16s -- %s\n", index->name, index->desc);
#else
                printf("%s\n", index->name);
#endif
            }
        }
    }

    /* checks in dynamic system function call */
    syscall_item = global_syscall_list;
    while (syscall_item != NULL)
    {
        if (str_is_prefix(prefix, syscall_item->syscall.name) == 0)
        {
            if (func_cnt == 0)
            {
                printf("--function:\n");
                if (*prefix != 0 && name_ptr == NULL)
                {
                    /* set name_ptr */
                    name_ptr = syscall_item->syscall.name;

                    /* set initial length */
                    min_length = strlen(name_ptr);
                }
            }

            func_cnt ++;

            if (*prefix != 0)
            {
                length = str_common(name_ptr, syscall_item->syscall.name);
                if (length < min_length)
                    min_length = length;
            }

            printf("[l] %s\n", syscall_item->syscall.name);
        }
        syscall_item = syscall_item->next;
    }

    /* checks in system variable */
    {
        struct finsh_sysvar *index;
        for (index = _sysvar_table_begin;
                index < _sysvar_table_end;
                FINSH_NEXT_SYSVAR(index))
        {
            if (str_is_prefix(prefix, index->name) == 0)
            {
                if (var_cnt == 0)
                {
                    printf("--variable:\n");

                    if (*prefix != 0 && name_ptr == NULL)
                    {
                        /* set name_ptr */
                        name_ptr = index->name;

                        /* set initial length */
                        min_length = strlen(name_ptr);

                    }
                }

                var_cnt ++;

                if (*prefix != 0)
                {
                    length = str_common(name_ptr, index->name);
                    if (length < min_length)
                        min_length = length;
                }

#ifdef FINSH_USING_DESCRIPTION
                printf("%-16s -- %s\n", index->name, index->desc);
#else
                printf("%s\n", index->name);
#endif
            }
        }
    }

    /* checks in dynamic system variable */
    sysvar_item = global_sysvar_list;
    while (sysvar_item != NULL)
    {
        if (str_is_prefix(prefix, sysvar_item->sysvar.name) == 0)
        {
            if (var_cnt == 0)
            {
                printf("--variable:\n");
                if (*prefix != 0 && name_ptr == NULL)
                {
                    /* set name_ptr */
                    name_ptr = sysvar_item->sysvar.name;

                    /* set initial length */
                    min_length = strlen(name_ptr);
                }
            }

            var_cnt ++;

            if (*prefix != 0)
            {
                length = str_common(name_ptr, sysvar_item->sysvar.name);
                if (length < min_length)
                    min_length = length;
            }

            printf("[v] %s\n", sysvar_item->sysvar.name);
        }
        sysvar_item = sysvar_item->next;
    }

    /* only one matched */
    if (name_ptr != NULL)
    {
        strncpy(prefix, name_ptr, min_length);
    }
}
#endif

#if defined(FINSH_USING_SYMTAB) && !defined(FINSH_USING_MSH_ONLY)
static int dummy = 0;
FINSH_VAR_EXPORT(dummy, finsh_type_int, dummy variable for finsh)
#endif
