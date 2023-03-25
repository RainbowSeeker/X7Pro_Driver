#include "drv_usbd_cdc.h"
#include "hal/usb/usbd_cdc.h"
#include "module/utils/ringbuffer.h"

#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "usbd_conf.h"
#include "usbd_desc.h"


extern PCD_HandleTypeDef hpcd_USB_OTG_FS;

static struct usbd_cdc_dev usbd_dev;

void OTG_FS_IRQHandler(void)
{
    os_interrupt_enter();

    HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
    /* leave interrupt */
    os_interrupt_leave();
}

static size_t usbd_cdc_read(usbd_cdc_dev_t usbd, off_t pos, void* buf, size_t size)
{
    size_t rb;

    ASSERT(usbd->rx_rb != NULL);

    rb = ringbuffer_get(usbd->rx_rb, buf, size);
    return rb;
}

static size_t usbd_cdc_write(usbd_cdc_dev_t usbd, off_t pos, const void* buf, size_t size)
{
    if (CDC_Transmit_FS((uint8_t*)buf, size) != USBD_OK) {
        return 0;
    }
    return size;
}

void drv_usbd_cdc_connect_cb(PCD_HandleTypeDef* hpcd)
{
    //Note: Must be same with !!!HAL_PCD_ConnectCallback!!!
    USBD_LL_DevConnected((USBD_HandleTypeDef*)hpcd->pData);
    hal_usbd_cdc_notify_status(&usbd_dev, USBD_STATUS_CONNECT);
}

void drv_usbd_cdc_disconnect_cb(PCD_HandleTypeDef* hpcd)
{
    //Note: Must be same with !!!HAL_PCD_DisconnectCallback!!!
    USBD_LL_DevDisconnected((USBD_HandleTypeDef*)hpcd->pData);
    hal_usbd_cdc_notify_status(&usbd_dev, USBD_STATUS_DISCONNECT);
}

void drv_usbd_cdc_receive(uint8_t* buffer, uint32_t size)
{
    if (usbd_dev.rx_rb == NULL) {
        /* usbd is not initialized */
        return;
    }
    (void)ringbuffer_put(usbd_dev.rx_rb, buffer, size);
    hal_usbd_cdc_notify_status(&usbd_dev, USBD_STATUS_RX);
}

void drv_usbd_cdc_transmist_complete(uint8_t* buffer, uint32_t size)
{
    hal_usbd_cdc_notify_status(&usbd_dev, USBD_STATUS_TX_COMPLETE);
}

struct usbd_cdc_ops usbd_ops = {
    .dev_init = NULL,
    .dev_read = usbd_cdc_read,
    .dev_write = usbd_cdc_write,
    .dev_control = NULL
};

err_t drv_usb_cdc_init(void)
{
    err_t err;
    usbd_dev.ops = &usbd_ops;

    err = hal_usbd_cdc_register(&usbd_dev, "usbd0", DEVICE_FLAG_RDWR | DEVICE_FLAG_STANDALONE | DEVICE_FLAG_DMA_RX | DEVICE_FLAG_DMA_TX, NULL);
    if (err != E_OK) {
        return err;
    }

    MX_USB_DEVICE_Init();
    return E_OK;
}