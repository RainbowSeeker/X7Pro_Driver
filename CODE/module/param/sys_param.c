
#include <common.h>

#include "module/param/param.h"

/* define parameters */
static param_t __param_list[] = {
    /* Mavlink system ID */
    PARAM_UINT8(MAV_SYS_ID, 1),
    /* Mavlink component ID */
    PARAM_UINT8(MAV_COMP_ID, 1),
    /* Determines when to start and stop logging.
	0: disabled
	1: when armed until disarm
	2: from boot until disarm
	3: from boot until shutdown  */
    PARAM_INT32(MLOG_MODE, 0),
    /* Endless mission mode, when mission complete, 
	it will start from the first mission data again */
    PARAM_UINT8(LOOP_MISSION, 1),
};
PARAM_GROUP_DEFINE(SYSTEM, __param_list);