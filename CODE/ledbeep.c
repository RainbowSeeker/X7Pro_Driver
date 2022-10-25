//
// Created by 19114 on 2022/10/10.
//

#include "ledbeep.h"
#include "gpio.h"


void LED_BEEP_Init(void)
{

}

void LED_Toggle(led_enum_t ledn)
{
    switch (ledn)
    {
        case led0:
            HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
            break;
        case led1:
            HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
            break;
        case led_all:
            HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin|LED1_Pin);
            break;
        default:
            break;
    }
}


void Beep(uint32_t timeout)
{
    BEEP_ON;
    delay_ms(timeout);
    BEEP_OFF;
}
