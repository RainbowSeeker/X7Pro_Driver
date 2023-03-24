
#ifndef PPM_H__
#define PPM_H__

#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PPM_DECODER_FREQUENCY 100000 // 100K frequency, where has the 0.01ms accurancy
#define MAX_PPM_CHANNEL       10

typedef struct {
    uint8_t chan_id;
    uint8_t total_chan; /* total ppm channel number */
    uint16_t last_ic;
    uint16_t ppm_recvd;
    uint16_t ppm_reading;
    uint16_t ppm_val[MAX_PPM_CHANNEL]; /* ppm raw value in microseconds */
} ppm_decoder_t;

__STATIC_INLINE void ppm_lock(ppm_decoder_t* decoder)
{
    decoder->ppm_reading = 1;
}

__STATIC_INLINE void ppm_unlock(ppm_decoder_t* decoder)
{
    decoder->ppm_reading = 0;
}

__STATIC_INLINE uint16_t ppm_get_recvd(ppm_decoder_t* decoder)
{
    return decoder->ppm_recvd;
}

__STATIC_INLINE void ppm_clear_recvd(ppm_decoder_t* decoder)
{
    decoder->ppm_recvd = 0;
}

void ppm_update(ppm_decoder_t* decoder, uint32_t ic_val);
err_t ppm_decoder_init(ppm_decoder_t* decoder);

#ifdef __cplusplus
}
#endif

#endif
