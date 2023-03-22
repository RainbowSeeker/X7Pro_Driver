////
//// Created by 19114 on 2022/10/10.
////
//
//#include "com.h"
//
//
//uint8_t aRxBuffer[RXBUFFERSIZE];                //HAL库使用的串口接收缓冲
//uint16_t UART_RX_STA = 0;                      //接收状态标记
//uint8_t UART_RX_BUF[UART_REC_LEN];             //接收缓冲,最大USART_REC_LEN个字节.
//
//#if USE_FREERTOS
//osSemaphoreId uart1Sem;
//#endif
//
//uint32_t rxcount = 0;
//uint32_t txcount = 0;
//void COM_Init(void)
//{
//    HAL_UART_Receive_IT(&COM_UART, (uint8_t *)aRxBuffer, RXBUFFERSIZE);
//#if USE_FREERTOS
//    osSemaphoreDef(uart1Sem);
//    uart1Sem = osSemaphoreCreate(osSemaphore(uart1Sem),1);
//#endif
//}
//void UART_HandleMsg(void)
//{
//#if USE_FREERTOS
//    osStatus res = osSemaphoreWait(uart1Sem, OS_WAIT_FOREVER);
//    if (res == osOK)            //successfully reveiced a Byte
//    {
//#endif
//        static uint16_t times=0;
//        if(UART_RX_STA&0x8000)
//        {
//            print("\nReceived your message:\t%s\n",UART_RX_BUF);
//            print("\nRxcount:\t\t\t%d\n",rxcount);
//            print("\nTxcount:\t\t\t%d\n",txcount);
//            memset(UART_RX_BUF, 0 ,UART_REC_LEN);
//            UART_RX_STA=0;
//        }
//        else
//        {
//            times++;
//            if (times%10==0) LED_Toggle(led0);
//        }
//#if USE_FREERTOS
//    }
//#endif
//}
//
//void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
//{
//    if(huart->Instance==USART1)//如果是串口1
//    {
//    }
//}
//
////void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
////{
////    if(huart->Instance==UART7)//如果是串口1
////    {
////        if((UART_RX_STA&0x8000)==0)//接收未完成
////        {
////            if(UART_RX_STA&0x4000)//接收到了0x0d
////            {
////                if(aRxBuffer[0]!=0x0a)  UART_RX_STA=0;   //接收错误,重新开始
////                else
////                {
////                    UART_RX_STA|=0x8000;	    //接收完成了
////                }
////
////            }
////            else //还没收到0X0D
////            {
////                if(aRxBuffer[0]==0x0d)  UART_RX_STA |= 0x4000;
////                else
////                {
////                    UART_RX_BUF[UART_RX_STA&0X3FFF]=aRxBuffer[0] ;
////                    UART_RX_STA++;
////                    if(UART_RX_STA>(UART_REC_LEN-1))  UART_RX_STA=0;//接收数据错误,重新开始接收
////                }
////            }
////        }
////    }
////#if SUPPORT_OS
////    osSemaphoreRelease(uart1Sem);  //由于是中断里发送，等待时间直接填 0
////#endif
////}
//
//void USART1_IRQHandler(void)
//{
//#if USE_UCOS
//    OSIntEnter();
//#endif
//    if (__HAL_UART_GET_IT(&huart7, UART_IT_RXNE) == SET)
//    {
//        HAL_UART_IRQHandler(&huart7);
//
//        uint32_t timeout=0;
//        uint32_t maxDelay=0x1FFFF;
//        while (HAL_UART_GetState(&huart7)!=HAL_UART_STATE_READY)//等待就绪
//        {
//            timeout++;  //超时处理
//            if(timeout>maxDelay) break;
//        }
//
//        timeout=0;
//        while(HAL_UART_Receive_IT(&huart7,(uint8_t *)aRxBuffer, RXBUFFERSIZE)!=HAL_OK)//每次处理完成之后，重新开启中断并设置aRxBuffer
//        {
//            timeout++; //超时处理
//            if(timeout>maxDelay) break;
//        }
//    }
//    else  HAL_UART_IRQHandler(&huart7);
//
//#if USE_UCOS
//    OSIntExit();
//#endif
//    /* USER CODE END USART1_IRQn 1 */
//}
