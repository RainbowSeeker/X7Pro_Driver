///******************************************************************************
// * Copyright 2020-2021 The Firmament Authors. All Rights Reserved.
// *
// * Licensed under the Apache License, Version 2.0 (the "License");
// * you may not use this file except in compliance with the License.
// * You may obtain a copy of the License at
// *
// * http://www.apache.org/licenses/LICENSE-2.0
// *
// * Unless required by applicable law or agreed to in writing, software
// * distributed under the License is distributed on an "AS IS" BASIS,
// * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// * See the License for the specific language governing permissions and
// * limitations under the License.
// *****************************************************************************/
//#include <common.h>
//#include <string.h>
//
//#include "module/syscmd/optparse.h"
//#include "module/syscmd/syscmd.h"
//
//#define LIST_FIND_OBJ_NR 8
//
//typedef struct
//{
//    list_t* list;
//    list_t** array;
//    uint8_t type;
//    int nr;     /* input: max nr, can't be 0 */
//    int nr_out; /* out: got nr */
//} list_get_next_t;
//
//static inline void object_split(int len)
//{
//    while (len--)
//        printf("-");
//}
//
//static void list_find_init(list_get_next_t* p, uint8_t type, list_t** array, int nr)
//{
//    struct rt_object_information* info;
//    list_t* list;
//
//    info = rt_object_get_information((enum rt_object_class_type)type);
//    list = &info->object_list;
//
//    p->list = list;
//    p->type = type;
//    p->array = array;
//    p->nr = nr;
//    p->nr_out = 0;
//}
//
//static list_t* list_get_next(list_t* current, list_get_next_t* arg)
//{
//    int first_flag = 0;
//    ubase_t level;
//    list_t *node, *list;
//    list_t** array;
//    int nr;
//
//    arg->nr_out = 0;
//
//    if (!arg->nr || !arg->type) {
//        return (list_t*)NULL;
//    }
//
//    list = arg->list;
//
//    if (!current) /* find first */
//    {
//        node = list;
//        first_flag = 1;
//    } else {
//        node = current;
//    }
//
//    level = os_hw_interrupt_disable();
//
//    if (!first_flag) {
//        struct rt_object* obj;
//        /* The node in the list? */
//        obj = rt_list_entry(node, struct rt_object, list);
//        if ((obj->type & ~RT_Object_Class_Static) != arg->type) {
//            os_hw_interrupt_enable(level);
//            return (list_t*)NULL;
//        }
//    }
//
//    nr = 0;
//    array = arg->array;
//    while (1) {
//        node = node->next;
//
//        if (node == list) {
//            node = (list_t*)NULL;
//            break;
//        }
//        nr++;
//        *array++ = node;
//        if (nr == arg->nr) {
//            break;
//        }
//    }
//
//    os_hw_interrupt_enable(level);
//    arg->nr_out = nr;
//    return node;
//}
//
//static int name_maxlen(const char* title)
//{
//    list_get_next_t find_arg;
//    list_t* obj_list[LIST_FIND_OBJ_NR];
//    int max_len = strlen(title);
//
//    list_t* next = (list_t*)NULL;
//    list_find_init(&find_arg, RT_Object_Class_Thread, obj_list, sizeof(obj_list) / sizeof(obj_list[0]));
//
//    do {
//        next = list_get_next(next, &find_arg);
//        for (int i = 0; i < find_arg.nr_out; i++) {
//            struct rt_object* obj;
//            struct rt_thread thread_info, *thread;
//            ubase_t level;
//
//            obj = rt_list_entry(obj_list[i], struct rt_object, list);
//            level = os_hw_interrupt_disable();
//
//            if ((obj->type & ~RT_Object_Class_Static) != find_arg.type) {
//                os_hw_interrupt_enable(level);
//                continue;
//            }
//            /* copy info */
//            memcpy(&thread_info, obj, sizeof thread_info);
//            os_hw_interrupt_enable(level);
//
//            thread = (struct rt_thread*)obj;
//            if (strlen(thread->name) > max_len) {
//                max_len = strlen(thread->name);
//            }
//        }
//    } while (next != (list_t*)NULL);
//
//    return max_len;
//}
//
//static int list_thread(void)
//{
//    ubase_t level;
//    list_get_next_t find_arg;
//    list_t* obj_list[LIST_FIND_OBJ_NR];
//    list_t* next = (list_t*)NULL;
//    const char* item_title = "thread";
//    int maxlen = name_maxlen(item_title) + 1;
//
//    list_find_init(&find_arg, RT_Object_Class_Thread, obj_list, sizeof(obj_list) / sizeof(obj_list[0]));
//
//    printf("%-*.s pri  status      sp     stack size max used left tick  error cpu\n", maxlen, item_title);
//    object_split(maxlen);
//    printf(" ---  ------- ---------- ----------  ------  ---------- ---   -----\n");
//
//    do {
//        next = list_get_next(next, &find_arg);
//        {
//            int i;
//            for (i = 0; i < find_arg.nr_out; i++) {
//                struct rt_object* obj;
//                struct rt_thread thread_info, *thread;
//
//                obj = rt_list_entry(obj_list[i], struct rt_object, list);
//                level = os_hw_interrupt_disable();
//
//                if ((obj->type & ~RT_Object_Class_Static) != find_arg.type) {
//                    os_hw_interrupt_enable(level);
//                    continue;
//                }
//                /* copy info */
//                memcpy(&thread_info, obj, sizeof thread_info);
//                os_hw_interrupt_enable(level);
//
//                thread = (struct rt_thread*)obj;
//                {
//                    uint8_t stat;
//                    uint8_t* ptr;
//
//                    printf("%-*.*s %3d ", maxlen, RT_NAME_MAX, thread->name, thread->current_priority);
//
//                    stat = (thread->stat & RT_THREAD_STAT_MASK);
//                    if (stat == RT_THREAD_READY)
//                        printf(" ready  ");
//                    else if (stat == RT_THREAD_SUSPEND)
//                        printf(" suspend");
//                    else if (stat == RT_THREAD_INIT)
//                        printf(" init   ");
//                    else if (stat == RT_THREAD_CLOSE)
//                        printf(" close  ");
//                    else if (stat == RT_THREAD_RUNNING)
//                        printf(" running");
//
//                    cpu_usage_stats* stats = (cpu_usage_stats*)thread->user_data;
//#if defined(ARCH_CPU_STACK_GROWS_UPWARD)
//                    ptr = (uint8_t*)thread->stack_addr + thread->stack_size - 1;
//                    while (*ptr == '#')
//                        ptr--;
//
//                    printf(" 0x%08x 0x%08x    %02d%%   0x%08x %03d   %.2f%%\n",
//                           ((ubase_t)thread->sp - (ubase_t)thread->stack_addr),
//                           thread->stack_size,
//                           ((ubase_t)ptr - (ubase_t)thread->stack_addr) * 100 / thread->stack_size,
//                           thread->remaining_tick,
//                           thread->error,
//                           stats != NULL ? stats->cpu_usage : -1.0f);
//#else
//                    ptr = (uint8_t*)thread->stack_addr;
//                    while (*ptr == '#')
//                        ptr++;
//
//                    printf(" 0x%08x 0x%08x    %02d%%   0x%08x %03d   %.2f%%\n",
//                           thread->stack_size + ((ubase_t)thread->stack_addr - (ubase_t)thread->sp),
//                           thread->stack_size,
//                           (thread->stack_size - ((ubase_t)ptr - (ubase_t)thread->stack_addr)) * 100
//                               / thread->stack_size,
//                           thread->remaining_tick,
//                           thread->error,
//                           stats != NULL ? stats->cpu_usage : -1.0f);
//#endif
//                }
//            }
//        }
//    } while (next != (list_t*)NULL);
//
//    return 0;
//}
//
//int cmd_ps(int argc, char** argv)
//{
//    return list_thread();
//}
//FINSH_FUNCTION_EXPORT_ALIAS(cmd_ps, __cmd_ps, List threads in the system.);