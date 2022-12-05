
#ifndef INS_INTERFACE_H__
#define INS_INTERFACE_H__
#include <common.h>
#include "base_ins/lib/INS.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    union {
        struct {
            uint32_t imu1_available : 1;
            uint32_t imu2_available : 1;
            uint32_t mag_available : 1;
            uint32_t baro_available : 1;
            uint32_t gps_available : 1;
            uint32_t sonar_available : 1;
            uint32_t optFlow_available : 1;
            uint32_t reserved : 25;
        } bit;
        uint32_t val;
    } status;
} INS_Status;

typedef struct {
    union {
        struct {
            uint32_t ready : 1;
            uint32_t standstill : 1;
            uint32_t att_valid : 1;
            uint32_t head_valid : 1;
            uint32_t vel_valid : 1;
            uint32_t WGS84_pos_valid : 1;
            uint32_t xy_R_valid : 1;
            uint32_t h_R_valid : 1;
            uint32_t h_AGL_valid : 1;
            uint32_t reserved : 23;
        } bit;
        uint32_t val;
    } flag;
} INS_Flag;

extern model_info_t ins_model_info;

void ins_interface_init(void);
void ins_interface_step(uint32_t timestamp);

#ifdef __cplusplus
}
#endif

#endif
