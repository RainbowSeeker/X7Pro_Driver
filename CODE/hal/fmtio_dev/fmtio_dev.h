#ifndef FMTIO_DEV_H__
#define FMTIO_DEV_H__

#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FMTIO_SET_BAUDRATE 0x10
#define FMTIO_GET_BAUDRATE 0x11

err_t hal_fmtio_dev_register(device_t io_dev, const char* name, uint32_t flag, void* data);

#ifdef __cplusplus
}
#endif

#endif
