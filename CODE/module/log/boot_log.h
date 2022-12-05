#ifndef BOOT_LOG_H__
#define BOOT_LOG_H__

#include <common_def.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t boot_log_push(const char* content, uint32_t len);
err_status_e boot_log_dump(void);
err_status_e boot_log_init(void);

#ifdef __cplusplus
}
#endif

#endif