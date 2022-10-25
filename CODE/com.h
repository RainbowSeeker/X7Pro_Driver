//
// Created by 19114 on 2022/10/10.
//

#ifndef STM32H743IIT6_COM_H
#define STM32H743IIT6_COM_H

#include "main.h"
#include "usart.h"

#define COM_UART        (huart7)

#define RXBUFFERSIZE    1                   //HAL库使用的串口接收缓冲大小
extern uint8_t aRxBuffer[RXBUFFERSIZE];     //HAL库使用的串口接收缓冲

#define UART_REC_LEN    100                 //接收字节大小
extern uint16_t UART_RX_STA;                //接收状态标记
extern uint8_t UART_RX_BUF[UART_REC_LEN];   //接收缓冲,最大USART_REC_LEN个字节.


#if USE_FREERTOS
extern osSemaphoreId uart1Sem;
#else





#endif


void COM_Init(void);
void UART_HandleMsg(void);


#endif //STM32H743IIT6_COM_H
