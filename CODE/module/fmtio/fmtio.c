#include "module/fmtio/fmtio.h"
#include "hal/actuator/actuator.h"
#include "hal/fmtio_dev/fmtio_dev.h"
#include "hal/rc/rc.h"
#include "hal/serial/serial.h"
#include "protocol/sbus/sbus.h"

#define EVENT_FMTIO_RX (1) // 1 << 0

#define FMTIO_MOTOR_CHANNEL_NUM 8
#define FMTIO_RC_CHANNEL_NUM    16

/* default config for rc device */
#define RC_CONFIG_DEFAULT               \
    {                                   \
        1,         /* sbus */           \
            6,     /* 6 channel */      \
            0.05f, /* sample time */    \
            1000,  /* minimal 1000us */ \
            2000,  /* maximal 2000us */ \
    }

typedef struct {
    uint32_t timestamp_ms;
    uint16_t rc_chan_val[FMTIO_RC_CHANNEL_NUM];
} rc_data_t;

static struct IOPacket io_tx_pkt;
static struct IOPacket io_rx_pkt;
static struct IOPacket* io_tx_pkt_ptr = &io_tx_pkt;
static device_t fmtio_dev;
static struct event fmtio_event;
static os_mutex_t tx_lock;
static rc_data_t rc_data;
static uint8_t rc_updated;
/* suspend io package transfer */
static uint8_t io_comm_suspend;
/* io default configuration */
static IO_ActuatorConfig actuator_config = { .pwm_freq = 50 };
static IO_RCConfig rc_config = { .protocol = 1, .sample_time = 0.05 };

static err_t rc_configure(rc_dev_t rc, struct rc_configure* cfg);
static err_t rc_control(rc_dev_t rc, int cmd, void* arg);
static uint16_t rc_read(rc_dev_t rc, uint16_t chan_mask, uint16_t* chan_val);

static err_t pwm_config(actuator_dev_t dev, const struct actuator_configure* cfg);
static err_t pwm_control(actuator_dev_t dev, int cmd, void* arg);
static size_t pwm_read(actuator_dev_t dev, uint16_t chan_sel, uint16_t* chan_val, size_t size);
static size_t pwm_write(actuator_dev_t dev, uint16_t chan_sel, const uint16_t* chan_val, size_t size);

const static struct rc_ops _rc_ops = {
    rc_configure,
    rc_control,
    rc_read,
};

static struct rc_device rc_dev = {
    .config = RC_CONFIG_DEFAULT,
    .ops = &_rc_ops
};

const static struct actuator_ops _act_ops = {
    .dev_config = pwm_config,
    .dev_control = pwm_control,
    .dev_read = pwm_read,
    .dev_write = pwm_write
};

static struct actuator_device act_dev = {
    .chan_mask = 0xFF,
    .range = { 1000, 2000 },
    .config = {
        .protocol = ACT_PROTOCOL_PWM,
        .chan_num = FMTIO_MOTOR_CHANNEL_NUM,
        .pwm_config = { .pwm_freq = 50 },
        .dshot_config = { 0 } },
    .ops = &_act_ops
};

static err_t io_rx_ind(device_t dev, size_t size)
{
    /* wakeup thread to handle received data */
    return os_event_send(&fmtio_event, EVENT_FMTIO_RX);
}

static err_t io_actuator_config(IO_ActuatorConfig config)
{
    return send_io_cmd(IO_CODE_CONFIG_ACTUATOR, &config, sizeof(IO_ActuatorConfig));
}

static err_t io_rc_config(IO_RCConfig config)
{
    return send_io_cmd(IO_CODE_CONFIG_RC, &config, sizeof(IO_RCConfig));
}

static err_t io_default_config(void)
{
    ERROR_TRY(io_actuator_config(actuator_config));
    ERROR_TRY(io_rc_config(rc_config));

    return E_OK;
}

static err_t handle_rc_pkt(struct IOPacket* pkt)
{
    uint16_t* index = (uint16_t*)pkt->data;

    rc_data.timestamp_ms = systime_now_ms();
    for (uint8_t i = 0; i < pkt->len / 2; i++) {
        rc_data.rc_chan_val[i] = *(index++);
    }

    rc_updated = 1;
    hal_rc_rx_ind(&rc_dev, pkt->len);

    return E_OK;
}

static err_t local_rx_handler(struct IOPacket* pkt)
{
    uint8_t crc = pkt->crc;
    err_t ret = E_OK;

    pkt->crc = 0;
    if (crc != crc_packet(pkt)) {
        return E_INVAL;
    }

    switch (pkt->code) {
    case IO_CODE_SYNC: {
        send_io_cmd(IO_CODE_SYNC, NULL, 0);
        /* get io sync message, configure it */
        ret = io_default_config();
    } break;

    case IO_CODE_RC_DATA: {
        ret = handle_rc_pkt(pkt);
    } break;

    case IO_CODE_DBG_TEXT: {
        console_printf("[IO]:");
        console_write((char*)pkt->data, pkt->len);
    } break;

    default:
        ret = E_NOTHANDLE;
        break;
    }

    return ret;
}

static err_t handle_rx_packet(void)
{
    uint8_t c;
    err_t ret = E_OK;

    if (io_comm_suspend) {
        return E_BUSY;
    }

    while (device_read(fmtio_dev, 0, &c, 1)) {
//        if (io_parse_char(&io_rx_pkt, c) == E_OK) {
//            /* handle rx pkg locally */
//            ret = local_rx_handler(&io_rx_pkt);
//        }
        sbus_putc(c);
        {
            static struct IOPacket pkt = {.len = 32};
            static uint16_t rc_count = 0;
            static bool sbus_failsafe, sbus_frame_drop;

            if (sbus_input((uint16_t *)pkt.data, &rc_count, &sbus_failsafe, &sbus_frame_drop,
                           16))
            {
                handle_rc_pkt(&pkt);
            }
        }
    }

    return ret;
}

static err_t rc_configure(rc_dev_t rc, struct rc_configure* cfg)
{
    IO_RCConfig new_config = { .protocol = cfg->protocol, .sample_time = cfg->sample_time };

    if (rc_config.protocol == new_config.protocol
        && rc_config.sample_time == new_config.sample_time) {
        /* it's same configuration already */
        return E_OK;
    }

    if (io_rc_config(new_config) == E_OK) {
        /* update default configuration */
        rc_config = new_config;
        /* update rc device configuration */
        rc->config = *cfg;
        return E_OK;
    } else {
        return ERROR;
    }
}

static err_t rc_control(rc_dev_t rc, int cmd, void* arg)
{
    switch (cmd) {
    case RC_CMD_CHECK_UPDATE: {
        *(uint8_t*)arg = rc_updated;
    } break;

    default:
        break;
    }

    return E_OK;
}

static uint16_t rc_read(rc_dev_t rc, uint16_t chan_mask, uint16_t* chan_val)
{
    uint16_t* index = chan_val;
    uint16_t rb = 0;

    if (!rc_updated)
        return 0;

    for (uint8_t i = 0; i < FMTIO_RC_CHANNEL_NUM; i++) {
        if (chan_mask & (1 << i)) {
            *(index++) = rc_data.rc_chan_val[i];
            rb += 2;
        }
    }

    rc_updated = 0;

    return rb;
}

static err_t pwm_config(actuator_dev_t dev, const struct actuator_configure* cfg)
{
    IO_ActuatorConfig new_config = { .pwm_freq = cfg->pwm_config.pwm_freq };

    if (actuator_config.pwm_freq == new_config.pwm_freq) {
        /* it's same configuration already */
        return E_OK;
    }

    if (io_actuator_config(new_config) != E_OK) {
        return ERROR;
    }

    /* update default configuration */
    actuator_config = new_config;
    /* update device configuration */
    dev->config = *cfg;

    return E_OK;
}

static err_t pwm_control(actuator_dev_t dev, int cmd, void* arg)
{
    err_t ret = E_OK;

    switch (cmd) {
    case ACT_CMD_CHANNEL_ENABLE: {
        uint8_t enable = 1;

        err_t err = send_io_cmd(IO_CODE_CTRL_ACTUATOR, &enable, sizeof(enable));
        ret = (err == E_OK) ? E_OK : ERROR;
    } break;

    case ACT_CMD_CHANNEL_DISABLE: {
        uint8_t enable = 0;

        err_t err = send_io_cmd(IO_CODE_CTRL_ACTUATOR, &enable, sizeof(enable));
        ret = (err == E_OK) ? E_OK : ERROR;
    } break;

    default:
        ret = EINVAL;
        break;
    }

    return ret;
}

static size_t pwm_read(actuator_dev_t dev, uint16_t chan_sel, uint16_t* chan_val, size_t size)
{
    // TODO
    return 0;
}

static size_t pwm_write(actuator_dev_t dev, uint16_t chan_sel, const uint16_t* chan_val, size_t size)
{
    uint16_t data[FMTIO_MOTOR_CHANNEL_NUM + 1];
    uint8_t chan_num = 0;

    for (int i = 0; i < 16; i++) {
        if (chan_sel & (1 << i)) {
            chan_num++;
        }
    }

    /* construct io data: <chan_sel> [chan val1] [chan val2] ... */
    data[0] = chan_sel;
    memcpy(&data[1], chan_val, chan_num * sizeof(uint16_t));

    if (send_io_cmd(IO_CODE_W_ACTUATOR, data, chan_num * sizeof(uint16_t) + sizeof(chan_sel)) != E_OK) {
        return 0;
    }

    return size;
}

/**
 * @brief Send command to io processor
 * 
 * @param code command code
 * @param data command data
 * @param len data length
 * @return err_t E_OK for success
 */
err_t send_io_cmd(uint8_t code, void* data, uint16_t len)
{
    err_t ret = ERROR;

    if (io_comm_suspend) {
        return E_BUSY;
    }

    os_mutex_take(tx_lock, OS_WAITING_FOREVER);

    if (set_io_pkt(io_tx_pkt_ptr, code, data, len) == E_OK) {
        size_t w_size = PKT_SIZE(io_tx_pkt_ptr);
        if (device_write(fmtio_dev, -1, io_tx_pkt_ptr, w_size) == w_size) {
            ret = E_OK;
        }
    }

    os_mutex_release(tx_lock);

    return ret;
}

/**
 * @brief Suspend fmtio communication
 * 
 * @param suspend 1: suspend 0: resume
 */
void fmtio_suspend_comm(uint8_t suspend)
{
    io_comm_suspend = suspend;

    if (suspend == 0) {
        /* wakeup thread to handle TX/RX event */
        os_event_send(&fmtio_event, EVENT_FMTIO_RX);
    }
}

/**
 * @brief Get fmtio device
 * 
 * @return device_t fmtio handler
 */
device_t fmtio_get_device(void)
{
    return fmtio_dev;
}

/**
 * @brief FMTIO main loop
 * 
 */
void fmtio_loop(void)
{
    err_t err;
    uint32_t recv_set = 0;
    /* try to re-configure io at the beginning, this is needed in case that fmu's configuration has changed
     * and then reboot. */
//    io_default_config();
    sbus_init();

    while (1) {
        /* wait event happen or timeout */
        err = os_event_recv(&fmtio_event, EVENT_FMTIO_RX, 10, &recv_set);

        if (err == E_OK) {
            if (recv_set & EVENT_FMTIO_RX) {
                handle_rx_packet();
            }
        } else if (err == E_TIMEOUT) {
            handle_rx_packet();
        } else {
            console_printf("fmtio event err:%d\n", err);
        }
    }
}

/**
 * @brief Initialize fmtio module
 * 
 * @param dev_name io device name
 * @return err_t E_OK for success
 */
err_t fmtio_init(const char* dev_name)
{
    device_t io_dev = device_find(dev_name);

    /* setup fmtio device */
    SELF_CHECK(hal_fmtio_dev_register(io_dev, "fmtio_dev", io_dev->flag, NULL));

    fmtio_dev = device_find("fmtio_dev");
    ASSERT(fmtio_dev != NULL);

    /* create event */
    SELF_CHECK(os_event_init(&fmtio_event, "fmtio"));

    /* Find best capacity for fmtio device */
    uint16_t oflag = DEVICE_OFLAG_RDWR;
    if (io_dev->flag & DEVICE_FLAG_DMA_TX) {
        oflag |= DEVICE_FLAG_DMA_TX;
    }
    if (io_dev->flag & DEVICE_FLAG_DMA_RX) {
        oflag |= DEVICE_FLAG_DMA_RX;
    } else {
        oflag |= DEVICE_FLAG_INT_RX;
    }
    SELF_CHECK(device_open(fmtio_dev, oflag));

    SELF_CHECK(device_set_rx_indicate(fmtio_dev, io_rx_ind));

    /* init io tx lock */
    tx_lock = os_mutex_create("io_tx");
    ASSERT(tx_lock != NULL);

    /* init io packet */
    init_io_pkt(&io_tx_pkt);
    init_io_pkt(&io_rx_pkt);

    /* register motor hal device */
    SELF_CHECK(hal_actuator_register(&act_dev, "main_out", DEVICE_FLAG_RDWR, NULL));

    /* register rc hal device */
    SELF_CHECK(hal_rc_register(&rc_dev, "rc", DEVICE_FLAG_RDWR, NULL));

    return E_OK;
}