
#include <common.h>

#include "hal/serial/serial.h"

static device_t mavproxy_dev = NULL;
static struct completion tx_cplt, rx_cplt;

static err_t (*mav_rx_indicate)(uint32_t size) = NULL;

static err_t mavproxy_dev_tx_done(device_t dev, void* buffer)
{
    completion_done(&tx_cplt);
    return E_OK;
}

static err_t mavproxy_dev_rx_ind(device_t dev, size_t size)
{
    completion_done(&rx_cplt);

    if (mav_rx_indicate) {
        mav_rx_indicate(size);
    }

    return E_OK;
}

size_t mavproxy_dev_write(const void* buffer, uint32_t len, int32_t timeout)
{
    size_t size;

    if (mavproxy_dev == NULL) {
        /* mavproxy device not initialized */
        return 0;
    }
    /* write data to device */
    size = device_write(mavproxy_dev, 0, buffer, len);
    if (size > 0) {
        /* wait write complete (synchronized write) */
        if (completion_wait(&tx_cplt, timeout) != E_OK) {
            return 0;
        }
    }

    return size;
}

size_t mavproxy_dev_read(void* buffer, uint32_t len, int32_t timeout)
{
    size_t cnt = 0;

    if (mavproxy_dev == NULL) {
        /* mavproxy device not initialized */
        return 0;
    }

    /* try to read data */
    cnt = device_read(mavproxy_dev, 0, buffer, len);

    /* sync mode */
    if (timeout != 0) {
        uint32_t time_start, elapse_time;
        /* if not enough data reveived, wait it */
        while (cnt < len) {
            time_start = systime_now_ms();
            /* wait until something reveived (synchronized read) */
            if (completion_wait(&rx_cplt, timeout) != E_OK) {
                break;
            }
            if (timeout != OS_WAITING_FOREVER) {
                elapse_time = systime_now_ms() - time_start;
                timeout -= elapse_time;
                if (timeout <= 0) {
                    /* timeout */
                    break;
                }
            }
            /* read rest data */
            cnt += device_read(mavproxy_dev, 0, (void*)((uint32_t)buffer + cnt), len - cnt);
        }
    }

    return cnt;
}

void mavproxy_dev_set_rx_indicate(err_t (*rx_ind)(uint32_t size))
{
    mav_rx_indicate = rx_ind;
}

err_t mavproxy_set_device(const char* dev_name)
{
    device_t new_dev;

    new_dev = device_find(dev_name);

    if (new_dev == NULL) {
        return E_EMPTY;
    }

    if (new_dev != mavproxy_dev) {
        uint16_t flag = DEVICE_OFLAG_RDWR | DEVICE_FLAG_INT_RX;
        if (new_dev->flag & (DEVICE_FLAG_DMA_RX | DEVICE_FLAG_DMA_TX)) {
            /* if device support DMA, then use it */
            flag = DEVICE_OFLAG_RDWR | DEVICE_FLAG_DMA_RX | DEVICE_FLAG_DMA_TX;
        }
        err_t err = device_open(new_dev, flag);
        if (err != E_OK) {
            return E_RROR;
        }
        mavproxy_dev = new_dev;
    }

    /* set callback functions */
    device_set_tx_complete(new_dev, mavproxy_dev_tx_done);
    device_set_rx_indicate(new_dev, mavproxy_dev_rx_ind);

    return E_OK;
}

device_t mavproxy_get_device(void)
{
    return mavproxy_dev;
}

err_t mavproxy_dev_init(void)
{
    completion_init(&tx_cplt);
    completion_init(&rx_cplt);

    return E_OK;
}