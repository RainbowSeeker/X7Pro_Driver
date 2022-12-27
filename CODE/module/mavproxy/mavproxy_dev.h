

#ifndef MAVPROXY_DEV_H__
#define MAVPROXY_DEV_H__

#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif

err_t mavproxy_dev_init(void);
size_t mavproxy_dev_write(const void* buffer, uint32_t len, int32_t timeout);
size_t mavproxy_dev_read(void* buffer, uint32_t len, int32_t timeout);
void mavproxy_dev_set_rx_indicate(err_t (*rx_ind)(uint32_t size));
err_t mavproxy_set_device(const char* dev_name);
light_device_t mavproxy_get_device(void);

#ifdef __cplusplus
}
#endif

#endif
