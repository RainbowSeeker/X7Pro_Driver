#include <common.h>
#include <string.h>

#include "module/workqueue/workqueue_manager.h"

#define MAX_WQ_SIZE 10

WorkQueue_t wq_list[MAX_WQ_SIZE] = { NULL };

WorkQueue_t workqueue_find(const char* name)
{
    for (int i = 0; i < MAX_WQ_SIZE; i++) {
        if (wq_list[i] == NULL) {
            break;
        }
        if (strcmp(wq_list[i]->thread->name, name) == 0) {
            return wq_list[i];
        }
    }
    return NULL;
}

err_t workqueue_manager_init(void)
{
    wq_list[0] = workqueue_create("wq:lp_work", 20, 10240, 6);
    ASSERT(wq_list[0] != NULL);

    wq_list[1] = workqueue_create("wq:hp_work", 20, 10240, 2);
    ASSERT(wq_list[1] != NULL);

    return E_OK;
}