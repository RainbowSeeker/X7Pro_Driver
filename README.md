# X7Pro_Driver
主控：STM32H743XIH6，请使用  CLion 或 Stm32CubeIDE 打开工程

目前：

1. 移植 UCOSIII 系统
2. 增加 SD + FATFS 功能。
3. 增加 SPI + DMA / BDMA ，实现 Devcie Bus 读写 ADIS16470, ICM42688, ICM20689, RM3100, MS5611, FRAM 设备。
4. 实现数据软总线 uMcn， 日志记录 mlog。
5. 增加串口设备驱动， 实现 Finsh 控制台以及 GPS 以 ubox 协议读写。 
6. 增加 usbd_cdc 驱动，用于 mavlink 交互。

