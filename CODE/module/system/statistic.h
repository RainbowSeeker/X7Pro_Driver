#ifndef STATISTIC_H__
#define STATISTIC_H__

#include <common_def.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint64_t exec_time;
    uint64_t total_exec_time;
    float cpu_usage;
} cpu_usage_stats;

err_status_e sys_stat_init(void);
float get_cpu_usage(void);

#ifdef __cplusplus
}
#endif

#endif
