// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/7.
//

#ifndef ADIS16470_H
#define ADIS16470_H
#include "bus_spi.h"

#define SENSORS_ON_Port         GPIOE
#define SENSORS_ON_Pin          GPIO_PIN_3

#define ADI_CS_Port             GPIOF
#define ADI_CS_Pin              GPIO_PIN_10


typedef struct
{
    int16_t noUse1;             //just for occupy postion
    int16_t stat;
    int16_t gyro[3];
    int16_t accl[3];
    int16_t temp;
    int16_t cntr;
    int16_t checknum;
    int16_t noUse2;             //just for occupy postion
}acc_value_t;

#define ADIS_ID                     0x4056     //ADIS16470

#define DIAG_STAT	      	  		0x0200
#define X_GYRO_LOW	      	  		0x0400
#define X_GYRO_OUT	      	  		0x0600
#define Y_GYRO_LOW	      	  		0x0800
#define Y_GYRO_OUT	      	  		0x0A00
#define Z_GYRO_LOW	      	  		0x0C00
#define Z_GYRO_OUT	      	  		0x0E00
#define X_ACCL_LOW	      	  		0x1000
#define X_ACCL_OUT	      	  		0x1200
#define Y_ACCL_LOW	      	  		0x1400
#define Y_ACCL_OUT	      	  		0x1600
#define Z_ACCL_LOW	      	 		0x1800
#define Z_ACCL_OUT	      	  		0x1A00
#define TEMP_OUT	      	  	 	0x1C00
#define TIME_STAMP	      	  		0x1E00
#define DATA_CNTR	      	  		0x2200
#define X_DELTANG_LOW	      		0x2400
#define X_DELTANG_OUT	      	    0x2600
#define Y_DELTANG_LOW	      	    0x2800
#define Y_DELTANG_OUT  	      	    0x2A00
#define Z_DELTANG_LOW	      	    0x2C00
#define Z_DELTANG_OUT	      	    0x2E00
#define X_DELTVEL_LOW	      	    0x3000
#define X_DELTVEL_OUT	      	    0x3200
#define Y_DELTVEL_LOW 	      	    0x3400
#define Y_DELTVEL_OUT	      	    0x3600
#define Z_DELTVEL_LOW	      	    0x3800
#define Z_DELTVEL_OUT	      	    0x3A00
#define XG_BIAS_LOW	      	  		0x4000
#define XG_BIAS_HIGH	      	  	0x4200
#define YG_BIAS_LOW	      	  		0x4400
#define YG_BIAS_HIGH	      	  	0x4600
#define ZG_BIAS_LOW	      	  		0x4800
#define ZG_BIAS_HIGH	      	  	0x4A00
#define XA_BIAS_LOW	      	  		0x4C00
#define XA_BIAS_HIGH	      	  	0x4E00
#define YA_BIAS_LOW	      	  		0x5000
#define YA_BIAS_HIGH	      	  	0x5200
#define ZA_BIAS_LOW	      	  		0x5400
#define ZA_BIAS_HIGH	      	    0x5600
#define FILT_CTRL	      	  		0x5C00
#define RANG_MDL	      	  		0x5E00
#define MSC_CTRL	  	      	    0x6000
#define UP_SCALE	      	  		0x6200
#define DEC_RATE	      	  		0x6400
#define NULL_CNFG	      	  		0x6600
#define GLOB_CMD	      	  		0x6800
#define FIRM_REV	      	  		0x6C00
#define FIRM_DM	      	  			0x6E00
#define FIRM_Y		  	      	    0x7000
#define PROD_ID	      				0x7200
#define SERIAL_NUM      		  	0x7400
#define USER_SCR_1	      		    0x7600
#define USER_SCR_2	      		    0x7800
#define USER_SCR_3	  	      	    0x7A00
#define FLSHCNT_LOW		      	    0x7C00
#define FLSHCNT_HIGH  		      	0x7E00

#define BURST_READ        			0x6800
#define Dummy_Byte                  0x0FFF


//      Global Commands (GLOB_CMD)命令
#define SOFTWARE_RESET            	 0x0080
#define FLASH_MEMORY_TEST            0x0010
#define FLASH_MEMORY_UPDATE          0x0008
#define SENSOR_SELF_TEST             0x0004
#define FACTORY_CALIBRATION_RESTORE  0x0002       //工厂校准恢复
#define BIAS_CORRECTION_UPDATE       0x0001       //偏差纠正更新

extern spi_device_t adis16470;
extern acc_value_t accValue;

void ADIS_Init(void);
void ADIS_Brust_Read(void);
#endif //ADIS16470_H
