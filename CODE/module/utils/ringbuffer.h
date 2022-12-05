
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t static_flag;
    unsigned head;
    unsigned tail;
    unsigned size;
    uint8_t* buff;
} ringbuffer;

ringbuffer* ringbuffer_create(uint32_t size);
ringbuffer* ringbuffer_static_create(uint32_t size, uint8_t* buffer);
uint32_t ringbuffer_getlen(ringbuffer* rb);
uint8_t ringbuffer_putc(ringbuffer* rb, uint8_t c);
uint8_t ringbuffer_getc(ringbuffer* rb);
uint32_t ringbuffer_get(ringbuffer* rb, uint8_t* ptr, uint32_t len);
uint32_t ringbuffer_put(ringbuffer* rb, const uint8_t* ptr, uint32_t len);
void ringbuffer_flush(ringbuffer* rb);
void ringbuffer_delete(ringbuffer* rb);

#ifdef __cplusplus
}
#endif
