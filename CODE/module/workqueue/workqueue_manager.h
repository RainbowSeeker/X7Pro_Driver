#ifndef WORKQUEUE_MANAGER_H__
#define WORKQUEUE_MANAGER_H__

#include <common.h>

#include "module/workqueue/work_queue.h"

#ifdef __cplusplus
extern "C" {
#endif

err_t workqueue_manager_init(void);
WorkQueue_t workqueue_find(const char* name);

#ifdef __cplusplus
}
#endif

#endif