// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/10.
//

#ifndef X7PRO_DRIVER_OBJECT_H
#define X7PRO_DRIVER_OBJECT_H

#include "common_def.h"
#include "utils/list.h"


/**
 * Base structure of Kernel object
 */
struct object
{
    char    name[NAME_MAX_LEN];                       /**< name of kernel object */
    uint8_t type;                                    /**< type of kernel object */
    uint8_t flag;                                    /**< flag of kernel object */

#ifdef RT_USING_MODULE
    void      *module_id;                               /**< id of application module */
#endif
    list_t  list;                                    /**< list node of kernel object */
};
typedef struct object *object_t;                  /**< Type for kernel objects. */


/**
 *  The object type can be one of the follows with specific
 *  macros enabled:
 *  - Thread
 *  - Semaphore
 *  - Mutex
 *  - Event
 *  - MailBox
 *  - MessageQueue
 *  - MemHeap
 *  - MemPool
 *  - Device
 *  - Timer
 *  - Module
 *  - Unknown
 *  - Static
 */

enum object_class_type
{
    Object_Class_Null          = 0x00,      /**< The object is not used. */
    Object_Class_Thread        = 0x01,      /**< The object is a thread. */
    Object_Class_Semaphore     = 0x02,      /**< The object is a semaphore. */
    Object_Class_Mutex         = 0x03,      /**< The object is a mutex. */
    Object_Class_Event         = 0x04,      /**< The object is a event. */
    Object_Class_MailBox       = 0x05,      /**< The object is a mail box. */
    Object_Class_MessageQueue  = 0x06,      /**< The object is a message queue. */
    Object_Class_MemHeap       = 0x07,      /**< The object is a memory heap. */
    Object_Class_MemPool       = 0x08,      /**< The object is a memory pool. */
    Object_Class_Device        = 0x09,      /**< The object is a device. */
    Object_Class_Timer         = 0x0a,      /**< The object is a timer. */
    Object_Class_Module        = 0x0b,      /**< The object is a module. */
    Object_Class_Unknown       = 0x0c,      /**< The object is unknown. */
    Object_Class_Static        = 0x80       /**< The object is a static object. */
};


/**
 * The information of the kernel object
 */
struct object_information
{
    enum object_class_type type;                     /**< object class type */
    list_t                 object_list;              /**< object list */
    size_t                 object_size;              /**< object size */
};


struct object_information *object_get_information(enum object_class_type type);

void object_init(struct object * object,
                 enum object_class_type type,
                 const char *name);
#endif //X7PRO_DRIVER_OBJECT_H
