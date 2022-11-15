// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/14.
//
#include "board_config.h"
#ifdef USE_SENSOR_SPI_MS5611
#include "barometer_ms5611.h"
#include "bus_spi.h"
#include "sensor.h"

static uint32_t ms5611_ut;  // static result of temperature measurement
static uint32_t ms5611_up;  // static result of pressure measurement
static uint16_t ms5611_c[PROM_NB];  // on-chip ROM
static uint8_t ms5611_osr = CMD_ADC_4096;
#define MS5611_DATA_FRAME_SIZE 3
static DMA_DATA_ZERO_INIT uint8_t sensor_data[MS5611_DATA_FRAME_SIZE];

static void MS5611_Reset(const device_t *dev)
{
    Bus_RawWriteRegister(dev, CMD_RESET, 1);

    delay_us(2800);
}

static uint16_t MS5611_Prom(const device_t *dev, int8_t coef_num)
{
    uint8_t rxbuf[2] = {0, 0};

    Bus_RawReadRegisterBuffer(dev, CMD_PROM_RD + coef_num * 2, rxbuf, 2); // send PROM READ command

    return rxbuf[0] << 8 | rxbuf[1];
}

static int8_t MS5611_CRC(uint16_t *prom)
{
    int32_t i, j;
    uint32_t res = 0;
    uint8_t crc = prom[7] & 0xF;
    prom[7] &= 0xFF00;

    bool blankEeprom = true;

    for (i = 0; i < 16; i++)
    {
        if (prom[i >> 1])
        {
            blankEeprom = false;
        }
        if (i & 1)
            res ^= ((prom[i >> 1]) & 0x00FF);
        else
            res ^= (prom[i >> 1] >> 8);
        for (j = 8; j > 0; j--)
        {
            if (res & 0x8000)
                res ^= 0x1800;
            res <<= 1;
        }
    }
    prom[7] |= crc;
    if (!blankEeprom && crc == ((res >> 12) & 0xF))
        return 0;

    return -1;
}

uint8_t MS5611_Detect(const device_t *dev)
{
    uint8_t sig;
    uint16_t remainingTime = 20;
    delay_ms(10);
    SPI_SetClkDivisor(dev, SPI_CalculateDivider(MS5611_MAX_SPI_CLK_HZ));

    MS5611_Reset(dev);
    while (remainingTime--)
    {
        if (!Bus_RawReadRegisterBuffer(dev, CMD_PROM_RD, &sig, 1) || sig == 0xFF)
        {
            continue;
        }

        // read all coefficients
        for (int i = 0; i < PROM_NB; i++)
            ms5611_c[i] = MS5611_Prom(dev, i);

        // check crc, bail out if wrong - we are probably talking to BMP085 w/o XCLR line!
        if (MS5611_CRC(ms5611_c) == 0)
        {
            return MS5611_SPI;
        }
    }

    return SENSOR_NONE;

}


static void MS5611_ReadAdc(const device_t *dev)
{

    SPI_ReadRegBuf(dev, CMD_ADC_READ, sensor_data, MS5611_DATA_FRAME_SIZE); // read ADC
//    Bus_RawReadRegisterBufferStart(dev, CMD_ADC_READ, sensor_data, MS5611_DATA_FRAME_SIZE); // read ADC
}

static void MS5611_StartUT(baro_t *baro)
{
    SPI_WriteReg(&baro->dev, CMD_ADC_CONV + CMD_ADC_D2 + ms5611_osr, 1); // D2 (temperature) conversion start!
//    Bus_RawWriteRegisterStart(&baro->dev, CMD_ADC_CONV + CMD_ADC_D2 + ms5611_osr, 1); // D2 (temperature) conversion start!
}

static bool MS5611_ReadUT(baro_t *baro)
{
    if (Bus_Busy(&baro->dev, NULL)) {
        return false;
    }

    MS5611_ReadAdc(&baro->dev);

    return true;
}

static bool MS5611_GetUT(baro_t *baro)
{
    if (Bus_Busy(&baro->dev, NULL)) {
        return false;
    }

    ms5611_ut = sensor_data[0] << 16 | sensor_data[1] << 8 | sensor_data[2];

    return true;
}

static void MS5611_StartUP(baro_t *baro)
{
    SPI_WriteReg(&baro->dev, CMD_ADC_CONV + CMD_ADC_D1 + ms5611_osr, 1); // D1 (pressure) conversion start!
//    Bus_RawWriteRegisterStart(&baro->dev, CMD_ADC_CONV + CMD_ADC_D1 + ms5611_osr, 1); // D1 (pressure) conversion start!
}

static bool MS5611_ReadUP(baro_t *baro)
{
    if (Bus_Busy(&baro->dev, NULL)) {
        return false;
    }

    MS5611_ReadAdc(&baro->dev);

    return true;
}

static bool MS5611_GetUP(baro_t *baro)
{
    if (Bus_Busy(&baro->dev, NULL)) {
        return false;
    }

    ms5611_up = sensor_data[0] << 16 | sensor_data[1] << 8 | sensor_data[2];

    return true;
}

static void MS5611_Calculate(int32_t *pressure, int32_t *temperature)
{
    uint32_t press;
    int64_t temp;
    int64_t delt;
    int64_t dT = (int64_t)ms5611_ut - ((uint64_t)ms5611_c[5] * 256);
    int64_t off = ((int64_t)ms5611_c[2] << 16) + (((int64_t)ms5611_c[4] * dT) >> 7);
    int64_t sens = ((int64_t)ms5611_c[1] << 15) + (((int64_t)ms5611_c[3] * dT) >> 8);
    temp = 2000 + ((dT * (int64_t)ms5611_c[6]) >> 23);

    if (temp < 2000) { // temperature lower than 20degC
        delt = temp - 2000;
        delt = 5 * delt * delt;
        off -= delt >> 1;
        sens -= delt >> 2;
        if (temp < -1500) { // temperature lower than -15degC
            delt = temp + 1500;
            delt = delt * delt;
            off -= 7 * delt;
            sens -= (11 * delt) >> 1;
        }
        temp -= ((dT * dT) >> 31);
    }
    press = ((((int64_t)ms5611_up * sens) >> 21) - off) >> 15;


    if (pressure)
        *pressure = press;
    if (temperature)
        *temperature = temp;
}

bool MS5611_Init(baro_t *baro)
{
    baro->ut_delay = 10000;
    baro->up_delay = 10000;
    baro->start_ut = MS5611_StartUT;
    baro->read_ut = MS5611_ReadUT;
    baro->get_ut = MS5611_GetUT;
    baro->start_up = MS5611_StartUP;
    baro->read_up = MS5611_ReadUP;
    baro->get_up = MS5611_GetUP;
    baro->calculate = MS5611_Calculate;
    baro->combined_read = false;
    return true;
}

#endif