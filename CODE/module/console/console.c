
//#include <finsh.h>

#include "console.h"
#include "finsh.h"

#include <string.h>


//#include "hal/serial/serial.h"

#define CONSOLE_BUFF_SIZE 1024

/* console write hook function, can be reimplemented by other modules. */
__WEAK void console_write_hook(const char *content, uint32_t len);

static device_t console_dev;
static char console_buffer[CONSOLE_BUFF_SIZE];

/**
 * Write raw data to console device.
 *
 * @param content data to be written
 * @param len length of data
 *
 * @return length has been written.
 */
int console_write(const char *content, uint32_t len)
{
    if (console_dev == NULL)
    {
        return 0;
    }

    /* write content into console device */
    uint32_t size = device_write(console_dev, 0, (void *) content, len);

    /* call write hook */
    if (console_write_hook)
        console_write_hook(content, len);

    return size;
}

/**
 * Console print arguments.
 *
 * @param fmt string format
 * @param args arguments list
 *
 * @return length of output.
 */
int console_print_args(const char *fmt, va_list args)
{
    int length;

    length = vsnprintf(console_buffer, CONSOLE_BUFF_SIZE, fmt, args);

    return console_write(console_buffer, length);
}

/**
 * Console printf.
 *
 * @param fmt string format
 *
 * @return length of output.
 */
int console_printf(const char *fmt, ...)
{
    va_list args;
    int length;

    va_start(args, fmt);
    length = vsnprintf(console_buffer, CONSOLE_BUFF_SIZE, fmt, args);
    va_end(args);

    return console_write(console_buffer, length);
}

/**
 * Console print line.
 *
 * @param fmt string format
 * @return length of output.
 */
int console_println(const char *fmt, ...)
{
    va_list args;
    int length;

    va_start(args, fmt);
    length = vsnprintf(console_buffer, CONSOLE_BUFF_SIZE - 1, fmt, args);
    va_end(args);

    console_buffer[length++] = '\n';

    return console_write(console_buffer, length);
}

/**
 * Format string into the buffer.
 */
void console_format(char *buffer, const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);
}

/**
 * Get current console device.
 *
 * @return current console device. NULL indicates no device.
 */
device_t console_get_device(void)
{
    return console_dev;
}

/**
 * Set console to a specific device.
 * @note console input/output will be enabled as well
 *
 * @return Errors Status.
 */
err_t console_set_device(const char *device_name)
{
    device_t new;
    err_t err;

    new = device_find(device_name);
    if (new == NULL)
    {
        /* can not find console device */
        return E_INVAL;
    }

    /* switch console to new device */
    console_dev = new;
    /* enable console */
    err = console_enable_input();

    return err;
}

/**
 * Enable console input and output.
 * @note console_dev should be set already
 *
 * @return Errors Status.
 */
err_t console_enable_input(void)
{
    uint16_t oflag = DEVICE_OFLAG_RDWR | DEVICE_FLAG_INT_RX | DEVICE_FLAG_STREAM;

    if (console_dev == NULL)
    {
        return E_INVAL;
    }

    if ((console_dev->open_flag & DEVICE_OFLAG_OPEN)
        && (console_dev->open_flag != oflag))
    {
        /* reopen console device */
        device_close(console_dev);
    }
    /* open console device */
    if (device_open(console_dev, oflag) != E_OK)
    {
        /* fail to open */
        return E_RROR;
    }

    /* mount finsh to current console device */
    finsh_set_device_without_open(console_dev->name);

    return E_OK;
}

/**
 * Initialize the console device.
 * @note only console output is enabled
 *
 * @return Errors Status.
 */
err_t console_init(void)
{
    /* console use serial0 by default */
    console_dev = device_find("serial0");
    if (console_dev == NULL)
    {
        /* can not find console device */
        return E_EMPTY;
    }

    /* here we only enable console output, the console input should be enabled specifically */
    if (device_open(console_dev, DEVICE_OFLAG_WRONLY | DEVICE_FLAG_STREAM) != E_OK)
    {
        return E_RROR;
    }

    return E_OK;
}