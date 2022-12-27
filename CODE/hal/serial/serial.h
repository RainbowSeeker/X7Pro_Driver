// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/3.
//

#ifndef X7PRO_DRIVER_SERIAL_H
#define X7PRO_DRIVER_SERIAL_H

#include "stm32h743xx.h"
#include "common.h"
#include "driver/io.h"

/* serial configuration */
#define BAUD_RATE_2400    2400
#define BAUD_RATE_4800    4800
#define BAUD_RATE_9600    9600
#define BAUD_RATE_19200   19200
#define BAUD_RATE_38400   38400
#define BAUD_RATE_57600   57600
#define BAUD_RATE_115200  115200
#define BAUD_RATE_230400  230400
#define BAUD_RATE_460800  460800
#define BAUD_RATE_921600  921600
#define BAUD_RATE_2000000 2000000
#define BAUD_RATE_3000000 3000000

#define DATA_BITS_5 5
#define DATA_BITS_6 6
#define DATA_BITS_7 7
#define DATA_BITS_8 8
#define DATA_BITS_9 9

#define STOP_BITS_1 0
#define STOP_BITS_2 1
#define STOP_BITS_3 2
#define STOP_BITS_4 3

#define PARITY_NONE 0
#define PARITY_ODD  1
#define PARITY_EVEN 2

#define BIT_ORDER_LSB 0
#define BIT_ORDER_MSB 1

#define NRZ_NORMAL   0 /* Non Return to Zero : normal mode */
#define NRZ_INVERTED 1 /* Non Return to Zero : inverted mode */

#ifndef SERIAL_RB_BUFSZ
#define SERIAL_RB_BUFSZ 256
#endif

/* serial isr event */
#define SERIAL_EVENT_RX_IND     0x01 /* Rx indication */
#define SERIAL_EVENT_TX_DONE    0x02 /* Tx complete   */
#define SERIAL_EVENT_RX_DMADONE 0x03 /* Rx DMA transfer done */
#define SERIAL_EVENT_TX_DMADONE 0x04 /* Tx DMA transfer done */
#define SERIAL_EVENT_RX_TIMEOUT 0x05 /* Rx timeout    */

/* serial dma transfer direction */
#define SERIAL_DMA_RX 0x01
#define SERIAL_DMA_TX 0x02

#define SERIAL_RX_INT 0x01
#define SERIAL_TX_INT 0x02

#define SERIAL_ERR_OVERRUN 0x01
#define SERIAL_ERR_FRAMING 0x02
#define SERIAL_ERR_PARITY  0x03

/* Default config for serial_configure structure */
#define SERIAL_DEFAULT_CONFIG                     \
            DATA_BITS_8,     /* 8 databits */     \
            STOP_BITS_1,     /* 1 stopbit */      \
            PARITY_NONE,     /* No parity  */     \
            BIT_ORDER_LSB,   /* LSB first sent */ \
            NRZ_NORMAL,      /* Normal mode */    \
            SERIAL_RB_BUFSZ, /* Buffer size */    \
            0




/*
* Serial FIFO mode
*/
struct serial_rx_fifo {
    /* software fifo */
    uint8_t* buffer;
    uint16_t put_index, get_index;
    bool_t is_full;
};

struct serial_configure {
    USART_TypeDef *instance;

    struct dma
    {
        void *instance;
        uint32_t tx_stream;
        uint32_t tx_channel;   //used for dma mux
        uint32_t rx_stream;
        uint32_t rx_channel;   //used for dma mux
    }dma;

    uint32_t baud_rate;
    uint32_t data_bits;
    uint32_t stop_bits;
    uint32_t parity;
    uint32_t bit_order;
    uint32_t invert;
    uint32_t bufsz;
    uint32_t reserved;
};

struct serial_device {
    struct device parent;

    const struct uart_ops {
        err_t (*configure)(struct serial_device* serial, struct serial_configure* cfg);
        err_t (*control)(struct serial_device* serial, int cmd, void* arg);
        int (*putc)(struct serial_device* serial, char c);
        int (*getc)(struct serial_device* serial);
        size_t (*dma_transmit)(struct serial_device* serial, uint8_t* buf, size_t size);
    }*ops;
    struct serial_configure config;

    void* serial_rx;    //used for software fifo
    void* serial_tx;

    size_t setting_recv_len;
    size_t last_recv_index;
};
typedef struct serial_device* serial_dev_t;



err_t hal_serial_register(serial_dev_t serial, const char* name, uint32_t flag, void* data);

#endif //X7PRO_DRIVER_SERIAL_H
