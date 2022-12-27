
#ifndef USBD_CDC_H__
#define USBD_CDC_H__

#include <common.h>

#include "module/utils/ringbuffer.h"

#ifdef __cplusplus
extern "C" {
#endif

#define USBD_CDC_TX_BUFSIZE 1280
#define USBD_CDC_RX_BUFSIZE 1280

#define USBD_STATUS_DISCONNECT  0
#define USBD_STATUS_CONNECT     1
#define USBD_STATUS_TX_COMPLETE 2
#define USBD_STATUS_RX          3

struct usbd_cdc_dev {
    struct device parent;
    struct usbd_cdc_ops* ops;
    ringbuffer* rx_rb;
    struct completion tx_cplt;
    os_mutex_t tx_lock;
    int status;
};
typedef struct usbd_cdc_dev* usbd_cdc_dev_t;

struct usbd_cdc_ops {
    err_t (*dev_init)(usbd_cdc_dev_t usbd);
    size_t (*dev_read)(usbd_cdc_dev_t usbd, off_t pos, void* buf, size_t size);
    size_t (*dev_write)(usbd_cdc_dev_t usbd, off_t pos, const void* buf, size_t size);
    err_t (*dev_control)(usbd_cdc_dev_t usbd, int cmd, void* arg);
};

err_t hal_usbd_cdc_register(usbd_cdc_dev_t usbd, const char* name, uint16_t flag, void* data);
void hal_usbd_cdc_notify_status(usbd_cdc_dev_t usbd, int status);

#ifdef __cplusplus
}
#endif

#endif