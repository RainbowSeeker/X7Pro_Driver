
#ifndef CONVERSION_H__
#define CONVERSION_H__

#include <common_def.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RAD2DEG(u) ((u)*180.0f / PI)
#define DEG2RAD(u) ((u)*PI / 180.0f)

void Msb2Lsb(uint8_t* data, uint8_t bytes);
int16_t int16_t_from_bytes(uint8_t bytes[]);

#ifdef __cplusplus
}
#endif

#endif
