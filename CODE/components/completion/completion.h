#ifndef COMPLETION_H_
#define COMPLETION_H_

#include <common.h>

/**
 * Completion
 */

struct completion
{
    uint32_t flag;

    /* suspended list */
    list_t suspended_list;
};

void completion_init(struct completion *completion);
err_t completion_wait(struct completion *completion, int32_t timeout);
void completion_done(struct completion *completion);

#endif
