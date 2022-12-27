// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/10.
//

#include "object.h"
#include <common.h>



enum Object_info_type
{
    Object_Info_Thread = 0,                         /**< The object is a thread. */
#ifdef USING_SEMAPHORE
    Object_Info_Semaphore,                          /**< The object is a semaphore. */
#endif
#ifdef USING_MUTEX
    Object_Info_Mutex,                              /**< The object is a mutex. */
#endif
#ifdef USING_EVENT
    Object_Info_Event,                              /**< The object is a event. */
#endif
#ifdef USING_MAILBOX
    Object_Info_MailBox,                            /**< The object is a mail box. */
#endif
    Object_Info_MessageQueue,                       /**< The object is a message queue. */
#ifdef USING_MEMHEAP
    Object_Info_MemHeap,                            /**< The object is a memory heap */
#endif
#ifdef USING_MEMPOOL
    Object_Info_MemPool,                            /**< The object is a memory pool. */
#endif
#ifdef USING_DEVICE
    Object_Info_Device,                             /**< The object is a device */
#endif
    Object_Info_Timer,                              /**< The object is a timer. */
#ifdef USING_MODULE
    Object_Info_Module,                             /**< The object is a module. */
#endif
    Object_Info_Unknown,                            /**< The object is unknown. */
};

#define _OBJ_CONTAINER_LIST_INIT(c)     \
    {&(object_container[c].object_list), &(object_container[c].object_list)}
static struct object_information object_container[Object_Info_Unknown] =
        {
                /* initialize object container - thread */
                {Object_Class_Thread, _OBJ_CONTAINER_LIST_INIT(Object_Info_Thread), sizeof(struct thread)},
#ifdef USING_SEMAPHORE
                /* initialize object container - semaphore */
    {Object_Class_Semaphore, _OBJ_CONTAINER_LIST_INIT(Object_Info_Semaphore), sizeof(struct semaphore)},
#endif
#ifdef USING_MUTEX
                /* initialize object container - mutex */
    {Object_Class_Mutex, _OBJ_CONTAINER_LIST_INIT(Object_Info_Mutex), sizeof(struct mutex)},
#endif
#ifdef USING_EVENT
                /* initialize object container - event */
    {Object_Class_Event, _OBJ_CONTAINER_LIST_INIT(Object_Info_Event), sizeof(struct event)},
#endif
#ifdef USING_MAILBOX
                /* initialize object container - mailbox */
    {Object_Class_MailBox, _OBJ_CONTAINER_LIST_INIT(Object_Info_MailBox), sizeof(struct mailbox)},
#endif
                /* initialize object container - message queue */
    {Object_Class_MessageQueue, _OBJ_CONTAINER_LIST_INIT(Object_Info_MessageQueue), sizeof(struct messagequeue)},
#ifdef USING_MEMHEAP
                /* initialize object container - memory heap */
    {Object_Class_MemHeap, _OBJ_CONTAINER_LIST_INIT(Object_Info_MemHeap), sizeof(struct memheap)},
#endif
#ifdef USING_MEMPOOL
                /* initialize object container - memory pool */
    {Object_Class_MemPool, _OBJ_CONTAINER_LIST_INIT(Object_Info_MemPool), sizeof(struct mempool)},
#endif
#ifdef USING_DEVICE
                /* initialize object container - device */
    {Object_Class_Device, _OBJ_CONTAINER_LIST_INIT(Object_Info_Device), sizeof(struct device)},
#endif
                /* initialize object container - timer */
                {Object_Class_Timer, _OBJ_CONTAINER_LIST_INIT(Object_Info_Timer), sizeof(struct timer)},
#ifdef USING_MODULE
                /* initialize object container - module */
    {Object_Class_Module, _OBJ_CONTAINER_LIST_INIT(Object_Info_Module), sizeof(struct dlmodule)},
#endif
        };


/**
 * This function will return the specified type of object information.
 *
 * @param type the type of object, which can be 
 *             Object_Class_Thread/Semaphore/Mutex... etc
 *
 * @return the object type information or NULL
 */
struct object_information *object_get_information(enum object_class_type type)
{
    int index;
    for (index = 0; index < Object_Info_Unknown; index ++)
        if (object_container[index].type == type) return &object_container[index];

    return NULL;
}


void object_init(struct object *object,
                 enum object_class_type type,
                 const char *name)
{
    register base_t temp;
    struct list_node *node = NULL;
    struct object_information *information;

    /* get object information */
    information = object_get_information(type);
    ASSERT(information != NULL);

    /* check object type to avoid re-initialization */

    /* enter critical */
    OS_ENTER_CRITICAL();
    /* try to find object */
    list_for_each(node, &information->object_list)
    {
        struct object *obj;

        obj = list_entry(node, struct object, list);
        if (obj) /* skip warning when disable debug */
        {
            ASSERT(obj != object);
        }
    }
    /* leave critical */
    OS_EXIT_CRITICAL();

    /* initialize object's parameters */
    /* set object type to static */
    object->type = type | Object_Class_Static;
    /* copy name */
    strncpy(object->name, name, NAME_MAX_LEN);

    /* lock interrupt */
    temp = os_hw_interrupt_disable();

    {
        /* insert object into information object list */
        list_insert_after(&(information->object_list), &(object->list));
    }

    /* unlock interrupt */
    os_hw_interrupt_enable(temp);
}