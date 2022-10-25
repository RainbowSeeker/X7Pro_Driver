/*
*********************************************************************************************************
*                                            EXAMPLE CODE
*
*               This file is provided as an example on how to use Micrium products.
*
*               Please feel free to use any application code labeled as 'EXAMPLE CODE' in
*               your application products.  Example code may be used as is, in whole or in
*               part, or may be used as a reference only. This file can be modified as
*               required to meet the end-product requirements.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can find our product's user manual, API reference, release notes and
*               more information at https://doc.micrium.com.
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                    MICRIUM BOARD SUPPORT PACKAGE
*                                         STM32H743ZI NUCLEO
*
* Filename : bsp_led.c
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  "bsp_led.h"

#include  <lib_def.h>
#include  <stm32h7xx_hal.h>


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

#define  USER_LD1_GPIOB_PIN             DEF_BIT_00
#define  USER_LD2_GPIOB_PIN             DEF_BIT_01
#define  USER_LD3_GPIOB_PIN             DEF_BIT_14
#define  USER_LED_ALL_GPIOB_PIN        (USER_LD1_GPIOB_PIN  |  \
                                        USER_LD2_GPIOB_PIN  |  \
                                        USER_LD3_GPIOB_PIN)

#define  USER_LED_GPIO_PORT             GPIOB


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
**                                         GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           BSP_LED_Init()
*
* Description : Initializes the required pins that control the LEDs.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_Init (void)
{
    GPIO_InitTypeDef  gpio_init;


    __HAL_RCC_GPIOB_CLK_ENABLE();                               /* Enable GPIO clock for USER LEDs                      */

                                                                /* ----------- CONFIGURE GPIOB FOR USER LEDS ---------- */
    gpio_init.Pin   = USER_LD1_GPIOB_PIN  |
                      USER_LD2_GPIOB_PIN  |
                      USER_LD3_GPIOB_PIN;
    gpio_init.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio_init.Pull  = GPIO_NOPULL;
    gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(USER_LED_GPIO_PORT, &gpio_init);
}


/*
*********************************************************************************************************
*                                            BSP_LED_On()
*
* Description : Turn ON a specific LED.
*
* Argument(s) : led    The ID of the LED to control.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_On (BSP_LED  led)
{
    switch (led) {
        case USER_LED_ALL:
             HAL_GPIO_WritePin(USER_LED_GPIO_PORT, USER_LED_ALL_GPIOB_PIN, GPIO_PIN_SET);
             break;


        case USER_LD1:
             HAL_GPIO_WritePin(USER_LED_GPIO_PORT, USER_LD1_GPIOB_PIN, GPIO_PIN_SET);
             break;


        case USER_LD2:
             HAL_GPIO_WritePin(USER_LED_GPIO_PORT, USER_LD2_GPIOB_PIN, GPIO_PIN_SET);
             break;


        case USER_LD3:
             HAL_GPIO_WritePin(USER_LED_GPIO_PORT, USER_LD3_GPIOB_PIN, GPIO_PIN_SET);
             break;


        default:
             break;
    }
}


/*
*********************************************************************************************************
*                                            BSP_LED_Off()
*
* Description : Turn OFF a specific LED.
*
* Argument(s) : led    The ID of the LED to control.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_Off (BSP_LED  led)
{
    switch (led) {
        case USER_LED_ALL:
             HAL_GPIO_WritePin(USER_LED_GPIO_PORT, USER_LED_ALL_GPIOB_PIN, GPIO_PIN_RESET);
             break;


        case USER_LD1:
             HAL_GPIO_WritePin(USER_LED_GPIO_PORT, USER_LD1_GPIOB_PIN, GPIO_PIN_RESET);
             break;


        case USER_LD2:
             HAL_GPIO_WritePin(USER_LED_GPIO_PORT, USER_LD2_GPIOB_PIN, GPIO_PIN_RESET);
             break;


        case USER_LD3:
             HAL_GPIO_WritePin(USER_LED_GPIO_PORT, USER_LD3_GPIOB_PIN, GPIO_PIN_RESET);
             break;


        default:
             break;
    }
}


/*
*********************************************************************************************************
*                                          BSP_LED_Toggle()
*
* Description : Toggles a specific LED.
*
* Argument(s) : led    The ID of the LED to control.
*
* Return(s)   : none.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_Toggle (BSP_LED  led)
{
    switch (led) {
        case USER_LED_ALL:
             HAL_GPIO_TogglePin(USER_LED_GPIO_PORT, USER_LED_ALL_GPIOB_PIN);
             break;


        case USER_LD1:
             HAL_GPIO_TogglePin(USER_LED_GPIO_PORT, USER_LD1_GPIOB_PIN);
             break;


        case USER_LD2:
             HAL_GPIO_TogglePin(USER_LED_GPIO_PORT, USER_LD2_GPIOB_PIN);
             break;


        case USER_LD3:
             HAL_GPIO_TogglePin(USER_LED_GPIO_PORT, USER_LD3_GPIOB_PIN);
             break;


        default:
             break;
    }
}
