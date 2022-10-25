//
// Created by 19114 on 2022/10/10.
//

#ifndef STM32H743IIT6_LED_H
#define STM32H743IIT6_LED_H

#include "gpio.h"

#define LED0_Pin        GPIO_PIN_0
#define LED0_GPIO_Port  GPIOB
#define LED1_Pin        GPIO_PIN_1
#define LED1_GPIO_Port  GPIOB

#define BEEP_Pin        GPIO_PIN_5
#define BEEP_GPIO_Port  GPIOE

#define BEEP_ON         HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET)
#define BEEP_OFF        HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET)

typedef enum
{
    led0 = 0,
    led1,
    led_all
}led_enum_t;

void LED_BEEP_Init(void);
void LED_Toggle(led_enum_t ledn);
void Beep(uint32_t timeout);
#endif //STM32H743IIT6_LED_H
