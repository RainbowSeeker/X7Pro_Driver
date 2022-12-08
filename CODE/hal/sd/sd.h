#ifndef SD_H__
#define SD_H__

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

struct sd_device {
    struct light_device parent;
    const struct sd_ops* ops;
    os_event_t event;
};
typedef struct sd_device* sd_dev_t;

/* sd driver opeations */
struct sd_ops {
    err_t (*init)(sd_dev_t sd);
    err_t (*write_disk)(sd_dev_t sd, uint8_t* buffer, uint32_t sector, uint32_t count);
    err_t (*read_disk)(sd_dev_t sd, uint8_t* buffer, uint32_t sector, uint32_t count);
    err_t (*io_control)(sd_dev_t sd, int cmd, void* arg);
};

err_t hal_sd_register(sd_dev_t sd, const char* name, uint32_t flag, void* data);

#ifdef __cplusplus
}
#endif

#endif
