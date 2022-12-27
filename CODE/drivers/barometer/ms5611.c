// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/5.
//

#include "ms5611.h"
#include "hal/barometer/barometer.h"
#include "hal/spi/spi.h"
#include "module/workqueue/workqueue_manager.h"
#include "driver/io.h"

#define DRV_DBG(...) printf(__VA_ARGS__)
#define POW2(_x)     ((_x) * (_x))

static uint8_t CMD_CONVERT_D1_ADDR[5] = {
        0x40, // OSR=256
        0x42, // OSR=512
        0x44, // OSR=1024
        0x46, // OSR=2048
        0x48  // OSR=4096
};

static uint8_t CMD_CONVERT_D2_ADDR[5] = {
        0x50, // OSR=256
        0x52, // OSR=512
        0x54, // OSR=1024
        0x56, // OSR=2048
        0x58  // OSR=4096
};

static uint8_t CONV_TIME_INTERVAL[5] = {
        1, // OSR=256
        2, // OSR=512
        3, // OSR=1024
        5, // OSR=2048
        10 // OSR=4096
};

typedef struct {
    uint16_t factory_data;
    uint16_t c1;
    uint16_t c2;
    uint16_t c3;
    uint16_t c4;
    uint16_t c5;
    uint16_t c6;
    uint16_t crc;
} ms5611_prom_t;

/* ms5611 report read state */
enum {
    S_CONV_1 = 0,
    S_RAW_PRESS,
    S_CONV_2,
    S_RAW_TEMP,
    S_COLLECT_REPORT
};

static light_device_t spi_dev;
uint32_t _raw_temperature, _raw_pressure;
static ms5611_prom_t _prom;
static uint8_t _ms5611_state;
static baro_report_t _baro_report;
static uint8_t _updated = 0;

static err_t write_cmd(uint8_t cmd)
{
    size_t w_byte;

//    w_byte = light_device_write(spi_dev, 0, &cmd, sizeof(cmd));
//
//    return w_byte == sizeof(cmd) ? E_OK : E_RROR;
    return spi_write_reg8(spi_dev, cmd, 1);
}

static err_t read_adc(uint32_t* buff)
{
    err_t res;
    res = spi_read_multi_reg8(spi_dev, ADDR_ADC, (uint8_t *) buff, 3);
    //big-endian to little-endian
    Msb2Lsb((uint8_t*)buff, 3);

    return res;
}

static err_t read_prom_reg(uint8_t cmd, uint16_t* buff)
{
    err_t res;

    res = spi_read_multi_reg8_msk(spi_dev, cmd, (uint8_t *) buff, 2);
    //big-endian to little-endian
    Msb2Lsb((uint8_t*)buff, 2);

    return res;
}

static bool_t crc_check(uint16_t* n_prom)
{
    int16_t cnt;
    uint16_t n_rem;
    uint16_t crc_read;
    uint8_t n_bit;

    n_rem = 0x00;

    /* save the read crc */
    crc_read = n_prom[7];

    /* remove CRC byte */
    n_prom[7] = (0xFF00 & (n_prom[7]));

    for (cnt = 0; cnt < 16; cnt++) {
        /* uneven bytes */
        if (cnt & 1) {
            n_rem ^= (uint8_t)((n_prom[cnt >> 1]) & 0x00FF);

        } else {
            n_rem ^= (uint8_t)(n_prom[cnt >> 1] >> 8);
        }

        for (n_bit = 8; n_bit > 0; n_bit--) {
            if (n_rem & 0x8000) {
                n_rem = (n_rem << 1) ^ 0x3000;

            } else {
                n_rem = (n_rem << 1);
            }
        }
    }

    /* final 4 bit remainder is CRC value */
    n_rem = (0x000F & (n_rem >> 12));
    n_prom[7] = crc_read;

    /* return true if CRCs match */
    return (0x000F & crc_read) == (n_rem ^ 0x00);
}

static err_t load_prom(void)
{
    for (uint8_t i = 0; i < 8; i++) {
        ERROR_TRY(read_prom_reg(ADDR_PROM_SETUP + (i << 1), ((uint16_t*)&_prom) + i));
    }

    return crc_check((uint16_t*)&_prom) ? E_OK : E_RROR;
}

static err_t collect_data(baro_report_t* report)
{
    int32_t _dT;
    int32_t _temp;
    int32_t _pressure;

    _dT = _raw_temperature - ((int32_t)_prom.c5 << 8);
    _temp = 2000 + (int32_t)(((int64_t)_dT * _prom.c6) >> 23);

    int64_t OFF = ((int64_t)_prom.c2 << 16) + (((int64_t)_prom.c4 * _dT) >> 7);
    int64_t SENS = ((int64_t)_prom.c1 << 15) + (((int64_t)_prom.c3 * _dT) >> 8);

    /* temperature compensation */
    if (_temp < 2000) {
        int32_t T2 = POW2(_dT) >> 31;

        int64_t f = POW2((int64_t)_temp - 2000);
        int64_t OFF2 = 5 * f >> 1;
        int64_t SENS2 = 5 * f >> 2;

        if (_temp < -1500) {
            int64_t f2 = POW2(_temp + 1500);
            OFF2 += 7 * f2;
            SENS2 += 11 * f2 >> 1;
        }

        _temp -= T2;
        OFF -= OFF2;
        SENS -= SENS2;
    }

    _pressure = (((_raw_pressure * SENS) >> 21) - OFF) >> 15;

    report->temperature_deg = _temp / 100.0f; // in deg
    report->pressure_Pa = _pressure;          // in Pa

    /* tropospheric properties (0-11km) for standard atmosphere */
    const double T1 = 15.0 + 273.15; /* temperature at base height in Kelvin, [K] = [°C] + 273.15 */
    const double a = -6.5 / 1000;    /* temperature gradient in degrees per metre */
    const double g = 9.80665;        /* gravity constant in m/s/s */
    const double R = 287.05;         /* ideal gas constant in J/kg/K */

    /* current pressure at MSL in kPa */
    double p1 = 101325.0 / 1000.0;

    /* measured pressure in kPa */
    double p = _pressure / 1000.0;

    /*
	 * Solve:
	 *
	 *     /        -(aR / g)     \
	 *    | (p / p1)          . T1 | - T1
	 *     \                      /
	 * h = -------------------------------  + h1
	 *                   a
	 */
    //report->altitude = (((exp((-(a * R) / g) * log((p / p1)))) * T1) - T1) / a;
    report->altitude_m = (((pow((p / p1), (-(a * R) / g))) * T1) - T1) / a;

    report->timestamp_ms = systime_now_ms();

    return E_OK;
}

static void ms5611_measure(void* parameter)
{
    switch (_ms5611_state) {

        case S_CONV_1: {
            if (write_cmd(CMD_CONVERT_D1_ADDR[DEFAULT_OSR]) == E_OK) {
                _ms5611_state = S_CONV_2;
            }
        } break;

        case S_CONV_2: {
            _ms5611_state = S_CONV_1;

            /* read raw pressure */
            if (read_adc(&_raw_pressure) == E_OK) {
                /* trigger D2 conversion immediately */
                if (write_cmd(CMD_CONVERT_D2_ADDR[DEFAULT_OSR]) == E_OK) {
                    _ms5611_state = S_COLLECT_REPORT;
                }
            }
        } break;

        case S_COLLECT_REPORT: {
            _ms5611_state = S_CONV_1;

            /* read raw temperature */
            if (read_adc(&_raw_temperature) == E_OK) {
                if (collect_data(&_baro_report) == E_OK) {
                    /* trigger D1 conversion immediately */
                    if (write_cmd(CMD_CONVERT_D1_ADDR[DEFAULT_OSR]) == E_OK) {
                        _ms5611_state = S_CONV_2;
                    }

                    /* set updated flag, baro report is ready */
                    _updated = 1;
                }
            }
        } break;

        default:
            break;
    }
}

static err_t lowlevel_init(void)
{
    uint8_t retry = 0;
    ERROR_TRY(light_device_open(spi_dev, DEVICE_OFLAG_RDWR));


    do {
        /* reset first */
        ERROR_TRY(write_cmd(ADDR_RESET_CMD));

        /* device need 2.8ms reload time */
        systime_mdelay(10);
    } while (load_prom() != E_OK && ++retry < 20);  /* load prom */

    if(retry >= 20)
    {
        DRV_DBG("\nms5611 load_prom error!\n");
    }

    _raw_temperature = _raw_pressure = 0;
    _updated = 0;
    _ms5611_state = S_CONV_1;

    return E_OK;
}

static err_t baro_control(baro_dev_t baro, int cmd, void* arg)
{
    switch (cmd) {
        case BARO_CMD_CHECK_READY: {
            *(uint8_t*)arg = _updated;
        } break;

        default:
            break;
    }

    return E_OK;
}

static size_t baro_read(baro_dev_t baro, baro_report_t* report)
{
    if (!_updated)
        return 0;

    *report = _baro_report;

    /* read will reset updated flag */
    _updated = 0;

    return sizeof(baro_report_t);
}

static struct baro_ops _baro_ops = {
        baro_control,
        baro_read
};

static struct WorkItem ms5611_work = {
        .name = "ms5611",
        .period = 0,
        .schedule_time = 0,
        .run = ms5611_measure
};

static struct baro_device baro_device = {
        .ops = &_baro_ops
};

static void ms5611_thread(void *param)
{
    while (1)
    {
        ms5611_work.run(param);
        os_delay(ms5611_work.period);
    }
}
err_t drv_ms5611_init(const char* baro_device_name)
{
    /* Initialize baro */
    static struct spi_device spi_device;
    static io_tag cs = PI8;
    io_init(cs, CS_CONFIG);
    ERROR_TRY(spi_bus_attach_device(&spi_device,
                                    "ms5611",
                                    "spi6",
                                    (void *) &cs));

    /* config spi */
    struct spi_configuration cfg = {
            .data_width = 8,
            .mode = SPI_MODE_3 | SPI_MSB,
            .max_hz = MS5611_MAX_SPI_CLK_HZ
    };
    ERROR_TRY(spi_configure_device(&spi_device, &cfg));

    spi_dev = light_device_find("ms5611");
    ASSERT(spi_dev != NULL);

    /* driver internal init */
    ERROR_TRY(lowlevel_init());

    /* find high-priority workqueue */
    WorkQueue_t hp_wq = workqueue_find("wq:hp_work");
    /* set period based on osr */
    ms5611_work.period = CONV_TIME_INTERVAL[DEFAULT_OSR];
    /* schedule the work */
//    SELF_CHECK(workqueue_schedule_work(hp_wq, &ms5611_work));
    os_thread_create("ms5611",
                     ms5611_thread,
                     NULL,
                     6,
                     256);

    ERROR_TRY(hal_baro_register(&baro_device, baro_device_name, DEVICE_FLAG_RDWR, NULL));

    return E_OK;
}
