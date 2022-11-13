// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/7.
//

#ifndef ADIS16470_H
#define ADIS16470_H
#include "bus_spi.h"
#include "mpu.h"
#include "accgyro.h"

#define ADI_ID                     0x4056     //ADIS16470

// 1 MHz max SPI frequency
#define ADI_MAX_SPI_CLK_HZ          1000000

#define ADIS16470_DIAG_STAT	      	0x02
#define ADI_X_GYRO_LOW	      	  	0x04
#define ADI_X_GYRO_OUT	      	  	0x06
#define ADI_Y_GYRO_LOW	      	  	0x08
#define ADI_Y_GYRO_OUT	      	  	0x0A
#define ADI_Z_GYRO_LOW	      	  	0x0C
#define ADI_Z_GYRO_OUT	      	  	0x0E
#define ADI_X_ACCL_LOW	      	  	0x10
#define ADI_X_ACCL_OUT	      	  	0x12
#define ADI_Y_ACCL_LOW	      	  	0x14
#define ADI_Y_ACCL_OUT	      	  	0x16
#define ADI_Z_ACCL_LOW	      	 	0x18
#define ADI_Z_ACCL_OUT	      	  	0x1A
#define ADI_TEMP_OUT	      	  	0x1C
#define ADI_TIME_STAMP	      	  	0x1E
#define ADI_DATA_CNTR	      	  	0x22
#define ADI_X_DELTANG_LOW	      	0x24
#define ADI_X_DELTANG_OUT	      	0x26
#define ADI_Y_DELTANG_LOW	      	0x28
#define ADI_Y_DELTANG_OUT  	      	0x2A
#define ADI_Z_DELTANG_LOW	      	0x2C
#define ADI_Z_DELTANG_OUT	      	0x2E
#define ADI_X_DELTVEL_LOW	      	0x30
#define ADI_X_DELTVEL_OUT	      	0x32
#define ADI_Y_DELTVEL_LOW 	      	0x34
#define ADI_Y_DELTVEL_OUT	      	0x36
#define ADI_Z_DELTVEL_LOW	      	0x38
#define ADI_Z_DELTVEL_OUT	      	0x3A
#define ADI_XG_BIAS_LOW	      	    0x40
#define ADI_XG_BIAS_HIGH	      	0x42
#define ADI_YG_BIAS_LOW	      	    0x44
#define ADI_YG_BIAS_HIGH	      	0x46
#define ADI_ZG_BIAS_LOW	      	  	0x48
#define ADI_ZG_BIAS_HIGH	      	0x4A
#define ADI_XA_BIAS_LOW	      	  	0x4C
#define ADI_XA_BIAS_HIGH	      	0x4E
#define ADI_YA_BIAS_LOW	      	  	0x50
#define ADI_YA_BIAS_HIGH	      	0x52
#define ADI_ZA_BIAS_LOW	      	  	0x54
#define ADI_ZA_BIAS_HIGH	      	0x56
#define ADI_FILT_CTRL	      	  	0x5C
#define ADI_RANG_MDL	      	  	0x5E
#define ADI_MSC_CTRL	  	      	0x60
#define ADI_UP_SCALE	      	  	0x62
#define ADI_DEC_RATE	      	  	0x64
#define ADI_NULL_CNFG	      	  	0x66
#define ADI_GLOB_CMD	      	  	0x68
#define ADI_FIRM_REV	      	  	0x6C
#define ADI_FIRM_DM	      	  		0x6E
#define ADI_FIRM_Y		  	      	0x70
#define ADI_PROD_ID	      			0x72
#define ADI_SERIAL_NUM      		0x74
#define ADI_USER_SCR_1	      		0x76
#define ADI_USER_SCR_2	      		0x78
#define ADI_USER_SCR_3	  	      	0x7A
#define ADI_FLSHCNT_LOW		      	0x7C
#define ADI_FLSHCNT_HIGH  		    0x7E

#define BURST_READ        			        0x68
#define Dummy_Byte                          0x0FFF

//    Global Commands (GLOB_CMD)命令
#define SOFTWARE_RESET            	 0x0080
#define FLASH_MEMORY_TEST            0x0010
#define FLASH_MEMORY_UPDATE          0x0008
#define SENSOR_SELF_TEST             0x0004
#define FACTORY_CALIBRATION_RESTORE  0x0002       //工厂校准恢复
#define BIAS_CORRECTION_UPDATE       0x0001       //偏差纠正更新


#define ADI_BUF_SIZE       48

typedef struct
{
    int16_t noUse1;             //just for occupy postion
    int16_t stat;
    int16_t gyro[3];
    int16_t acc[3];
    int16_t temp;
    int16_t cntr;
    int16_t checknum;
    int16_t noUse2;             //just for occupy postion
}adi_value_t;


extern adi_value_t adiValue;
extern const gyro_config_t adi_config;

uint8_t ADIS16470_Detect(const device_t *dev);
void ADI_Revise(adi_value_t *pValue);
#endif //ADIS16470_H
