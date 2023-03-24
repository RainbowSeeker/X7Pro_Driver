#include <common.h>

#include "module/mavproxy/mavproxy.h"
#include "module/utils/ringbuffer.h"

#define MAV_CONSOLE_DEVICE_NAME    "mav_console"
#define MAV_CONSOLE_RX_BUFFER_SIZE 128
#define MAV_CONSOLE_TX_BUFFER_SIZE 256

static struct device* device;
static struct device mavlink_console_dev;
static ringbuffer* _mav_console_rx_rb = NULL;
static ringbuffer* _mav_console_tx_rb = NULL;
static uint8_t _mav_console_rx_buffer[MAV_CONSOLE_RX_BUFFER_SIZE];
static uint8_t _mav_console_tx_buffer[MAV_CONSOLE_TX_BUFFER_SIZE];
static mavlink_serial_control_t _serial_control;
static struct timer timer_mav_console;

static void mav_console_timeout(void* parameter)
{
    mavproxy_send_event(EVENT_MAVCONSOLE_TIMEOUT);
}

static void send_serial_control_msg(mavlink_serial_control_t* serial_control)
{
    bool sync = true;
    mavlink_message_t msg;
    mavlink_system_t mavlink_system = mavproxy_get_system();

    mavlink_msg_serial_control_encode(mavlink_system.sysid, mavlink_system.compid, &msg, serial_control);

    if (os_interrupt_get_nest() != 0) {
        /* if we are in the interrupt context, we can not send data via usb,
			since usb driver doesn't support that. Therefore, we will push this
			message into immediate msg queue, and let mavproxy send it out.
		*/

        /* we use async send for all msg in interrupt context,
			in order to do not influence the real-time performance */
        sync = false;
    }

    mavproxy_send_immediate_msg(&msg, sync);
}

void mavlink_console_handle_timeout(void)
{
    mavlink_serial_control_t serial_control;

    serial_control.baudrate = 0;
    serial_control.device = SERIAL_CONTROL_DEV_SHELL;
    serial_control.flags = SERIAL_CONTROL_FLAG_REPLY;

    while (ringbuffer_getlen(_mav_console_tx_rb) >= 70) {

        serial_control.count = 70;
        ringbuffer_get(_mav_console_tx_rb, serial_control.data, serial_control.count);

        send_serial_control_msg(&serial_control);
    }

    uint32_t len = ringbuffer_getlen(_mav_console_tx_rb);

    if (len) {
        serial_control.count = len;

        ringbuffer_get(_mav_console_tx_rb, serial_control.data, serial_control.count);

        send_serial_control_msg(&serial_control);
    }
}

/* RT-Thread Device Interface */
/*
 * This function initializes mavlink_console device.
 */
static err_t _init(struct device* dev)
{
    err_t result = E_OK;
    ASSERT(dev != NULL);

    return result;
}

static err_t _open(struct device* dev, uint16_t oflag)
{
    ASSERT(dev != NULL);

    /* do not check oflag, since mav_console based on mavproxy device, which should be opened properly */

    /* get open flags */
    dev->open_flag = oflag & 0xFFFF;

    /* initialize the Rx/Tx structure according to open flag */
    if (oflag & DEVICE_FLAG_DMA_RX) {
        dev->open_flag |= DEVICE_FLAG_DMA_RX;
    } else if (oflag & DEVICE_FLAG_INT_RX) {
        dev->open_flag |= DEVICE_FLAG_INT_RX;
    }

    if (oflag & DEVICE_FLAG_DMA_TX) {
        dev->open_flag |= DEVICE_FLAG_DMA_TX;
    } else if (oflag & DEVICE_FLAG_INT_TX) {
        dev->open_flag |= DEVICE_FLAG_INT_TX;
    }

    /* init serial control object */
    _serial_control.baudrate = 0;
    _serial_control.count = 0;
    _serial_control.device = SERIAL_CONTROL_DEV_SHELL;
    _serial_control.flags = SERIAL_CONTROL_FLAG_REPLY;

    return E_OK;
}

static err_t _close(struct device* dev)
{
    ASSERT(dev != NULL);

    /* this device has more reference count */
    if (dev->ref_count > 1)
        return E_BUSY;

    dev->rx_indicate = NULL;
    dev->tx_complete = NULL;

    return E_OK;
}

static size_t _read(struct device* dev,
                       off_t pos,
                       void* buffer,
                       size_t size)
{
    uint16_t len;

    ASSERT(dev != NULL);

    if (size == 0)
        return 0;

    len = ringbuffer_getlen(_mav_console_rx_rb);

    if (!len)
        return 0;

    size = size > len ? len : size;
    return ringbuffer_get(_mav_console_rx_rb, buffer, size);
}

static size_t _write(struct device* dev,
                        off_t pos,
                        const void* buffer,
                        size_t size)
{
    size_t len;
    size_t left;
    size_t free_space;
    size_t data_in_buffer;
    size_t sent_cnt;

    ASSERT(dev != NULL);

    if (size == 0)
        return 0;

    /* left data to be sent */
    left = size;

    while (left) {
        /* get data length in buffer */
        data_in_buffer = ringbuffer_getlen(_mav_console_tx_rb);
        /* get buffer free space */
        free_space = MAV_CONSOLE_TX_BUFFER_SIZE - data_in_buffer;
        /* data that already be sent */
        sent_cnt = size - left;
        /* fill buffer up to it's size */
        len = left <= free_space ? left : free_space;
        ringbuffer_put(_mav_console_tx_rb, buffer + sent_cnt, len);

        /* if buffer has enough data, send it now */
        while (ringbuffer_getlen(_mav_console_tx_rb) >= 70) {

            mavlink_serial_control_t serial_control;

            serial_control.baudrate = 0;
            serial_control.count = 70;
            serial_control.device = SERIAL_CONTROL_DEV_SHELL;
            serial_control.flags = SERIAL_CONTROL_FLAG_REPLY;

            /* read data from buffer */
            ringbuffer_get(_mav_console_tx_rb, serial_control.data, serial_control.count);

            send_serial_control_msg(&serial_control);
        }

        /* update left data to be sent */
        left -= len;
    }

    /* if there are some data in buffer but buffer is not full,
		setup a timer. If no more data coming before timer expired,
		send data out. otherwise, reset timer */
    if (ringbuffer_getlen(_mav_console_tx_rb)) {
        os_timer_start(&timer_mav_console);
    }

    if (dev->tx_complete) {
        dev->tx_complete(dev, NULL);
    }

    return size;
}

static err_t _control(struct device* dev,
                         int cmd,
                         void* args)
{
    ASSERT(dev != NULL);

    switch (cmd) {
    case DEVICE_CTRL_SUSPEND:
        /* suspend device */
        dev->flag |= DEVICE_FLAG_SUSPENDED;
        break;

    case DEVICE_CTRL_RESUME:
        /* resume device */
        dev->flag &= ~DEVICE_FLAG_SUSPENDED;
        break;

    case DEVICE_CTRL_CONFIG:
        /* configure device */
        break;

    case DEVICE_CTRL_GET_INT:
        break;

    default:
        break;
    }

    return E_OK;
}

void mavlink_console_process_rx_msg(const mavlink_serial_control_t* serial_control)
{
    /* push data to ring buffer */
    for (uint8_t i = 0; i < serial_control->count; i++) {
        if (!ringbuffer_putc(_mav_console_rx_rb, serial_control->data[i]))
            break;
    }

    /* call indicator if exist */
    if (device->rx_indicate) {
        device->rx_indicate(device, serial_control->count);
    }
}

/*
 * mavlink console register
 */
err_t mavlink_console_init(void)
{
    device = &mavlink_console_dev;

    device->type = Device_Class_Char;
    device->rx_indicate = NULL;
    device->tx_complete = NULL;

    device->init = _init;
    device->open = _open;
    device->close = _close;
    device->read = _read;
    device->write = _write;
    device->control = _control;
    device->user_data = NULL;

    if (_mav_console_rx_rb == NULL) {
        _mav_console_rx_rb = ringbuffer_static_create(MAV_CONSOLE_RX_BUFFER_SIZE, _mav_console_rx_buffer);

        if (_mav_console_rx_rb == NULL) {
            console_printf("mav console ringbuffer create fail\n");
            return E_RROR;
        }
    }

    if (_mav_console_tx_rb == NULL) {
        _mav_console_tx_rb = ringbuffer_static_create(MAV_CONSOLE_TX_BUFFER_SIZE, _mav_console_tx_buffer);

        if (_mav_console_tx_rb == NULL) {
            console_printf("mav console ringbuffer create fail\n");
            return E_RROR;
        }
    }

    /* register timer event */
    os_timer_init(&timer_mav_console, "mav_console", mav_console_timeout, NULL, 50, TIMER_TYPE_ONE_SHOT);
    /* open flag doesn't matter, since open function will not check open flag */
    return device_register(device, MAV_CONSOLE_DEVICE_NAME, DEVICE_FLAG_RDWR);
}
