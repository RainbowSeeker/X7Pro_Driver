
#include <common.h>
#include <string.h>

#include "module/console/console.h"
#include "module/utils/ringbuffer.h"

#undef OS_ENTER_CRITICAL()
#undef OS_EXIT_CRITICAL()

#define OS_ENTER_CRITICAL() base_t level = os_hw_interrupt_disable()
#define OS_EXIT_CRITICAL() os_hw_interrupt_enable(level)

ringbuffer* ringbuffer_create(uint32_t size)
{
    ringbuffer* rb = (ringbuffer*)malloc(sizeof(ringbuffer));
    if (rb == NULL) {
        return NULL;
    }

    rb->buff = (uint8_t*)malloc(size);
    if (rb->buff == NULL) {
        free(rb);
        return NULL;
    }

    rb->size = size;
    rb->head = 0;
    rb->tail = 0;
    rb->static_flag = 0;

    return rb;
}

ringbuffer* ringbuffer_static_create(uint32_t size, uint8_t* buffer)
{
    ringbuffer* rb = (ringbuffer*)malloc(sizeof(ringbuffer));
    if (rb == NULL) {
        return rb;
    }

    rb->buff = buffer;
    rb->size = size;
    rb->head = 0;
    rb->tail = 0;
    rb->static_flag = 1;

    return rb;
}

void ringbuffer_delete(ringbuffer* rb)
{
    if (rb->static_flag != 0)
        free(rb->buff);

    free(rb);
}

uint32_t ringbuffer_getlen(ringbuffer* rb)
{
    uint32_t len;

    OS_ENTER_CRITICAL();


    if (rb->head >= rb->tail)
        len = rb->head - rb->tail;
    else
        len = rb->head + (rb->size - rb->tail);
    OS_EXIT_CRITICAL();

    return len;
}

uint8_t ringbuffer_putc(ringbuffer* rb, uint8_t c)
{
    OS_ENTER_CRITICAL();
    if ((rb->head + 1) % rb->size == rb->tail) {
        OS_EXIT_CRITICAL();
        return 0;
    }

    rb->buff[rb->head] = c;
    rb->head = (rb->head + 1) % rb->size;
    OS_EXIT_CRITICAL();

    return 1;
}

uint8_t ringbuffer_getc(ringbuffer* rb)
{
    uint8_t c;

    OS_ENTER_CRITICAL();
    c = rb->buff[rb->tail];
    rb->tail = (rb->tail + 1) % rb->size;
    OS_EXIT_CRITICAL();

    return c;
}

uint32_t ringbuffer_get(ringbuffer* rb, uint8_t* ptr, uint32_t len)
{
    uint32_t r_len, buffer_len;

    /* check if there are enough data to read */
    buffer_len = ringbuffer_getlen(rb);
    r_len = buffer_len < len ? buffer_len : len;

    OS_ENTER_CRITICAL();
    for (uint32_t i = 0; i < r_len; i++) {
        ptr[i] = rb->buff[rb->tail];
        rb->tail = (rb->tail + 1) % rb->size;
    }
    OS_EXIT_CRITICAL();

    return r_len;
}

uint32_t ringbuffer_put(ringbuffer* rb, const uint8_t* ptr, uint32_t len)
{
    uint32_t w_len, buffer_len;
    uint32_t free_space;
    uint32_t space_to_end;

    /* check if there are enough space to write */
    buffer_len = ringbuffer_getlen(rb);
    free_space = rb->size - buffer_len;
    w_len = (len <= free_space) ? len : free_space;

    OS_ENTER_CRITICAL();
    space_to_end = rb->size - rb->head;

    if (w_len <= space_to_end) {
        memcpy(&rb->buff[rb->head], ptr, w_len);
    } else {
        memcpy(&rb->buff[rb->head], ptr, space_to_end);
        memcpy(rb->buff, &ptr[space_to_end], w_len - space_to_end);
    }

    rb->head = (rb->head + w_len) % rb->size;
    OS_EXIT_CRITICAL();

    return w_len;
}

void ringbuffer_flush(ringbuffer* rb)
{
    OS_ENTER_CRITICAL();
    rb->head = rb->tail = 0;
    OS_EXIT_CRITICAL();
}
