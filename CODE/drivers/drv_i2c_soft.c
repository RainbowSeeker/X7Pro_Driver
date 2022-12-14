//// Copyright (c) 2022 By RainbowSeeker.
//
//#include <common.h>
//
//#include "drv_i2c_soft.h"
//#include "hal/i2c/i2c.h"
//#include "hal/i2c/i2c_bit_ops.h"
//#include "hal/pin/pin.h"
//
//#define BSP_I2C1_SDA_PORT GPIOB
//#define BSP_I2C2_SDA_PORT GPIOB
//
//#define BSP_I2C1_SCL_PORT GPIOB
//#define BSP_I2C2_SCL_PORT GPIOB
//
//#define BSP_I2C1_SDA_PIN GPIO_Pin_9
//#define BSP_I2C2_SDA_PIN GPIO_Pin_11
//
//#define BSP_I2C1_SCL_PIN GPIO_Pin_8
//#define BSP_I2C2_SCL_PIN GPIO_Pin_10
//
//#define I2C_DELAY_US      (10)
//#define I2C_TIMEOUT_TICKS TICKS_FROM_MS(1)
//
//#define FMU_I2C1_PIN_SCL 95
//#define FMU_I2C1_PIN_SDA 96
//#define FMU_I2C2_PIN_SCL 47
//#define FMU_I2C2_PIN_SDA 48
//
//static struct rt_i2c_bus i2c1_dev;
//static struct rt_i2c_bus i2c2_dev;
//
//void stm32_set_sda(void* data, int32_t state)
//{
//    struct rt_i2c_bus* i2c_bus = (struct rt_i2c_bus*)data;
//
//    if (i2c_bus == &i2c1_dev) {
//        if (state == 1)
//            GPIO_SetBits(BSP_I2C1_SDA_PORT, BSP_I2C1_SDA_PIN);
//        else if (state == 0)
//            GPIO_ResetBits(BSP_I2C1_SDA_PORT, BSP_I2C1_SDA_PIN);
//    } else if (i2c_bus == &i2c2_dev) {
//        if (state == 1)
//            GPIO_SetBits(BSP_I2C2_SDA_PORT, BSP_I2C2_SDA_PIN);
//        else if (state == 0)
//            GPIO_ResetBits(BSP_I2C2_SDA_PORT, BSP_I2C2_SDA_PIN);
//    }
//}
//
//void stm32_set_scl(void* data, int32_t state)
//{
//    struct rt_i2c_bus* i2c_bus = (struct rt_i2c_bus*)data;
//
//    if (i2c_bus == &i2c1_dev) {
//        if (state == 1)
//            GPIO_SetBits(BSP_I2C1_SCL_PORT, BSP_I2C1_SCL_PIN);
//        else if (state == 0)
//            GPIO_ResetBits(BSP_I2C1_SCL_PORT, BSP_I2C1_SCL_PIN);
//    } else if (i2c_bus == &i2c2_dev) {
//        if (state == 1)
//            GPIO_SetBits(BSP_I2C2_SCL_PORT, BSP_I2C2_SCL_PIN);
//        else if (state == 0)
//            GPIO_ResetBits(BSP_I2C2_SCL_PORT, BSP_I2C2_SCL_PIN);
//    }
//}
//
//int32_t stm32_get_sda(void* data)
//{
//    int32_t val;
//    struct rt_i2c_bus* i2c_bus = (struct rt_i2c_bus*)data;
//
//    if (i2c_bus == &i2c1_dev) {
//        //set input mode
//        BSP_I2C1_SDA_PORT->MODER &= ~(GPIO_MODER_MODER0 << (9 * 2));
//        val = GPIO_ReadInputDataBit(BSP_I2C1_SDA_PORT, BSP_I2C1_SDA_PIN);
//        //set output mode
//        BSP_I2C1_SDA_PORT->MODER |= ((uint32_t)GPIO_Mode_OUT << (9 * 2));
//    } else if (i2c_bus == &i2c2_dev) {
//        //set input mode
//        BSP_I2C2_SDA_PORT->MODER &= ~(GPIO_MODER_MODER0 << (11 * 2));
//        val = GPIO_ReadInputDataBit(BSP_I2C2_SDA_PORT, BSP_I2C2_SDA_PIN);
//        //set output mode
//        BSP_I2C2_SDA_PORT->MODER |= ((uint32_t)GPIO_Mode_OUT << (11 * 2));
//    }
//
//    return val;
//}
//
//int32_t stm32_get_scl(void* data)
//{
//    int32_t val;
//    struct rt_i2c_bus* i2c_bus = (struct rt_i2c_bus*)data;
//
//    if (i2c_bus == &i2c1_dev) {
//        //set input mode
//        BSP_I2C1_SCL_PORT->MODER &= ~(GPIO_MODER_MODER0 << (8 * 2));
//        val = GPIO_ReadInputDataBit(BSP_I2C1_SCL_PORT, BSP_I2C1_SCL_PIN);
//        //set output mode
//        BSP_I2C1_SCL_PORT->MODER |= ((uint32_t)GPIO_Mode_OUT << (8 * 2));
//    } else if (i2c_bus == &i2c2_dev) {
//        //set input mode
//        BSP_I2C2_SCL_PORT->MODER &= ~(GPIO_MODER_MODER0 << (10 * 2));
//        val = GPIO_ReadInputDataBit(BSP_I2C2_SCL_PORT, BSP_I2C2_SCL_PIN);
//        //set output mode
//        BSP_I2C2_SCL_PORT->MODER |= ((uint32_t)GPIO_Mode_OUT << (10 * 2));
//    }
//
//    return val;
//}
//
//static inline void stm32_udelay(uint32_t us)
//{
//    systime_udelay(us);
//}
//
//err_t stm32_i2c_pin_init(struct rt_i2c_bus* i2c_bus)
//{
//    light_device_t pin_dev;
//    struct device_pin_mode mode;
//
//    pin_dev = light_device_find("pin");
//    if (pin_dev == NULL) {
//        return E_EMPTY;
//    }
//
//    if (i2c_bus == &i2c1_dev) {
//        mode.pin = FMU_I2C1_PIN_SCL;
//        mode.mode = PIN_MODE_OUTPUT;
//        mode.otype = PIN_OUT_TYPE_PP;
//        pin_dev->control(pin_dev, 0, &mode);
//
//        mode.pin = FMU_I2C1_PIN_SDA;
//        mode.mode = PIN_MODE_OUTPUT;
//        mode.otype = PIN_OUT_TYPE_PP;
//        pin_dev->control(pin_dev, 0, &mode);
//    } else if (i2c_bus == &i2c2_dev) {
//        mode.pin = FMU_I2C2_PIN_SCL;
//        mode.mode = PIN_MODE_OUTPUT;
//        mode.otype = PIN_OUT_TYPE_PP;
//        pin_dev->control(pin_dev, 0, &mode);
//
//        mode.pin = FMU_I2C2_PIN_SDA;
//        mode.mode = PIN_MODE_OUTPUT;
//        mode.otype = PIN_OUT_TYPE_PP;
//        pin_dev->control(pin_dev, 0, &mode);
//    } else {
//        return E_INVAL;
//    }
//
//    return E_OK;
//}
//
//struct rt_i2c_bit_ops stm32_i2c1_bit_ops = {
//    (void*)NULL,
//    stm32_set_sda,
//    stm32_set_scl,
//    stm32_get_sda,
//    stm32_get_scl,
//    stm32_udelay,
//    I2C_DELAY_US,
//    I2C_TIMEOUT_TICKS
//};
//
//struct rt_i2c_bit_ops stm32_i2c2_bit_ops = {
//    (void*)NULL,
//    stm32_set_sda,
//    stm32_set_scl,
//    stm32_get_sda,
//    stm32_get_scl,
//    stm32_udelay,
//    I2C_DELAY_US,
//    I2C_TIMEOUT_TICKS
//};
//
//err_t drv_i2c_soft_init(void)
//{
//    stm32_i2c1_bit_ops.data = &i2c1_dev;
//    i2c1_dev.priv = (void*)&stm32_i2c1_bit_ops;
//    i2c1_dev.retries = 3;
//
//    stm32_i2c_pin_init(&i2c1_dev);
//    rt_i2c_soft_bus_register(&i2c1_dev, "i2c1");
//
//    stm32_i2c2_bit_ops.data = &i2c2_dev;
//    i2c2_dev.priv = (void*)&stm32_i2c2_bit_ops;
//    i2c2_dev.retries = 3;
//
//    stm32_i2c_pin_init(&i2c2_dev);
//    rt_i2c_soft_bus_register(&i2c2_dev, "i2c2");
//
//    return E_OK;
//}
