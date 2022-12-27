// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/1.
//

#ifndef X7PRO_DRIVER_DEVICE_H
#define X7PRO_DRIVER_DEVICE_H

#include "common_def.h"
#include "module/utils/list.h"

/**
 * device flags defitions
 */
#define DEVICE_FLAG_DEACTIVATE       0x000           /**< device is not not initialized */

#define DEVICE_FLAG_RDONLY           0x001           /**< read only */
#define DEVICE_FLAG_WRONLY           0x002           /**< write only */
#define DEVICE_FLAG_RDWR             0x003           /**< read and write */

#define DEVICE_FLAG_REMOVABLE        0x004           /**< removable device */
#define DEVICE_FLAG_STANDALONE       0x008           /**< standalone device */
#define DEVICE_FLAG_ACTIVATED        0x010           /**< device is activated */
#define DEVICE_FLAG_SUSPENDED        0x020           /**< device is suspended */
#define DEVICE_FLAG_STREAM           0x040           /**< stream mode */

#define DEVICE_FLAG_INT_RX           0x100           /**< INT mode on Rx */
#define DEVICE_FLAG_DMA_RX           0x200           /**< DMA mode on Rx */
#define DEVICE_FLAG_INT_TX           0x400           /**< INT mode on Tx */
#define DEVICE_FLAG_DMA_TX           0x800           /**< DMA mode on Tx */

#define DEVICE_OFLAG_CLOSE           0x000           /**< device is closed */
#define DEVICE_OFLAG_RDONLY          0x001           /**< read only access */
#define DEVICE_OFLAG_WRONLY          0x002           /**< write only access */
#define DEVICE_OFLAG_RDWR            0x003           /**< read and write */
#define DEVICE_OFLAG_OPEN            0x008           /**< device is opened */
#define DEVICE_OFLAG_MASK            0xf0f           /**< mask of open flag */

/**
 * general device commands
 */
#define DEVICE_CTRL_RESUME           0x01            /**< resume device */
#define DEVICE_CTRL_SUSPEND          0x02            /**< suspend device */
#define DEVICE_CTRL_CONFIG           0x03            /**< configure device */
#define DEVICE_CTRL_CLOSE            0x04            /**< close device */

#define DEVICE_CTRL_SET_INT          0x10            /**< set interrupt */
#define DEVICE_CTRL_CLR_INT          0x11            /**< clear interrupt */
#define DEVICE_CTRL_GET_INT          0x12            /**< get interrupt status */

/**
 * special device commands
 */
#define DEVICE_CTRL_CHAR_STREAM      0x10            /**< stream mode on char device */
#define DEVICE_CTRL_BLK_GETGEOME     0x10            /**< get geometry information   */
#define DEVICE_CTRL_BLK_SYNC         0x11            /**< flush data to block device */
#define DEVICE_CTRL_BLK_ERASE        0x12            /**< erase block on block device */
#define DEVICE_CTRL_BLK_AUTOREFRESH  0x13            /**< block device : enter/exit auto refresh mode */
#define DEVICE_CTRL_NETIF_GETMAC     0x10            /**< get mac address */
#define DEVICE_CTRL_MTD_FORMAT       0x10            /**< format a MTD device */
#define DEVICE_CTRL_RTC_GET_TIME     0x10            /**< get time */
#define DEVICE_CTRL_RTC_SET_TIME     0x11            /**< set time */
#define DEVICE_CTRL_RTC_GET_ALARM    0x12            /**< get alarm */
#define DEVICE_CTRL_RTC_SET_ALARM    0x13            /**< set alarm */


/**
 * device (I/O) class type
 */
enum device_class
{
    Device_Class_Char = 0,                           /**< character device */
    Device_Class_Block,                              /**< block device */
    Device_Class_NetIf,                              /**< net interface */
    Device_Class_MTD,                                /**< memory device */
    Device_Class_CAN,                                /**< CAN device */
    Device_Class_RTC,                                /**< RTC device */
    Device_Class_Sound,                              /**< Sound device */
    Device_Class_Graphic,                            /**< Graphic device */
    Device_Class_I2CBUS,                             /**< I2C bus device */
    Device_Class_I2CDevice,                          /**< I2C device */
    Device_Class_USBDevice,                          /**< USB slave device */
    Device_Class_USBHost,                            /**< USB host bus */
    Device_Class_SPIBUS,                             /**< SPI bus device */
    Device_Class_SPIDevice,                          /**< SPI device */
    Device_Class_SDIO,                               /**< SDIO bus device */
    Device_Class_PM,                                 /**< PM pseudo device */
    Device_Class_Pipe,                               /**< Pipe device */
    Device_Class_Portal,                             /**< Portal device */
    Device_Class_Timer,                              /**< Timer device */
    Device_Class_Miscellaneous,                      /**< Miscellaneous device */
    Device_Class_Sensor,                             /**< Sensor device */
    Device_Class_Touch,                              /**< Touch device */
    Device_Class_PHY,                                /**< PHY device */
    Device_Class_Unknown                             /**< unknown device */
};


/**
 * Device structure
 */
typedef struct device *light_device_t;
struct device
{
    char                   name[NAME_MAX_LEN];       /* device name */
    list_t                 list;                     /* associate the next and prev device*/

    enum device_class      type;                     /* device type */
    uint16_t               flag;                     /* device flag */
    uint16_t               open_flag;                /* device open flag */

    uint8_t                ref_count;                /* reference count */
    uint8_t                device_id;                /* 0 - 255 */

    /* device call back */
    err_t (*rx_indicate)(light_device_t dev, size_t size);
    err_t (*tx_complete)(light_device_t dev, void *buffer);

    /* common device interface */
    err_t  (*init)   (light_device_t dev);
    err_t  (*open)   (light_device_t dev, uint16_t oflag);
    err_t  (*close)  (light_device_t dev);
    size_t (*read)   (light_device_t dev, off_t pos, void *buffer, size_t size);
    size_t (*write)  (light_device_t dev, off_t pos, const void *buffer, size_t size);
    err_t  (*control)(light_device_t dev, int cmd, void *args);

    void                     *user_data;            /* device private data */
};


/**
 * block device geometry structure
 */
struct device_blk_geometry
{
    uint32_t sector_count;                           /**< count of sectors */
    uint32_t bytes_per_sector;                       /**< number of bytes per sector */
    uint32_t block_size;                             /**< number of bytes to erase one block */
};

/**
 * sector arrange struct on block device
 */
struct device_blk_sectors
{
    uint32_t sector_begin;                           /**< begin sector */
    uint32_t sector_end;                             /**< end sector   */
};

/**
 * cursor control command
 */
#define DEVICE_CTRL_CURSOR_SET_POSITION  0x10
#define DEVICE_CTRL_CURSOR_SET_TYPE      0x11

/**
 * graphic device control command
 */
#define RTGRAPHIC_CTRL_RECT_UPDATE      0
#define RTGRAPHIC_CTRL_POWERON          1
#define RTGRAPHIC_CTRL_POWEROFF         2
#define RTGRAPHIC_CTRL_GET_INFO         3
#define RTGRAPHIC_CTRL_SET_MODE         4
#define RTGRAPHIC_CTRL_GET_EXT          5

/* graphic deice */
enum
{
    RTGRAPHIC_PIXEL_FORMAT_MONO = 0,
    RTGRAPHIC_PIXEL_FORMAT_GRAY4,
    RTGRAPHIC_PIXEL_FORMAT_GRAY16,
    RTGRAPHIC_PIXEL_FORMAT_RGB332,
    RTGRAPHIC_PIXEL_FORMAT_RGB444,
    RTGRAPHIC_PIXEL_FORMAT_RGB565,
    RTGRAPHIC_PIXEL_FORMAT_RGB565P,
    RTGRAPHIC_PIXEL_FORMAT_BGR565 = RTGRAPHIC_PIXEL_FORMAT_RGB565P,
    RTGRAPHIC_PIXEL_FORMAT_RGB666,
    RTGRAPHIC_PIXEL_FORMAT_RGB888,
    RTGRAPHIC_PIXEL_FORMAT_ARGB888,
    RTGRAPHIC_PIXEL_FORMAT_ABGR888,
    RTGRAPHIC_PIXEL_FORMAT_ARGB565,
    RTGRAPHIC_PIXEL_FORMAT_ALPHA,
    RTGRAPHIC_PIXEL_FORMAT_COLOR,
};

/**
 * build a pixel position according to (x, y) coordinates.
 */
#define RTGRAPHIC_PIXEL_POSITION(x, y)  ((x << 16) | y)

/**
 * graphic device information structure
 */
struct device_graphic_info
{
    uint8_t  pixel_format;                           /**< graphic format */
    uint8_t  bits_per_pixel;                         /**< bits per pixel */
    uint16_t reserved;                               /**< reserved field */

    uint16_t width;                                  /**< width of graphic device */
    uint16_t height;                                 /**< height of graphic device */

    uint8_t *framebuffer;                            /**< frame buffer */
};

/**
 * rectangle information structure
 */
struct device_rect_info
{
    uint16_t x;                                      /**< x coordinate */
    uint16_t y;                                      /**< y coordinate */
    uint16_t width;                                  /**< width */
    uint16_t height;                                 /**< height */
};

/**
 * graphic operations
 */
struct device_graphic_ops
{
    void (*set_pixel) (const char *pixel, int x, int y);
    void (*get_pixel) (char *pixel, int x, int y);

    void (*draw_hline)(const char *pixel, int x1, int x2, int y);
    void (*draw_vline)(const char *pixel, int x, int y1, int y2);

    void (*blit_line) (const char *pixel, int x, int y, size_t size);
};
#define graphix_ops(device)          ((struct device_graphic_ops *)(device->user_data))


err_t light_device_register(light_device_t dev, const char *name, uint16_t flags);
err_t light_device_unregister(light_device_t dev);
light_device_t light_device_find(const char *name);
light_device_t light_device_create(int type, int attach_size);
void light_device_destroy(light_device_t dev);
err_t light_device_init(light_device_t dev);
err_t light_device_open(light_device_t dev, uint16_t oflag);
err_t light_device_close(light_device_t dev);
size_t light_device_read(light_device_t dev, off_t pos, void *buffer, size_t size);
size_t light_device_write(light_device_t dev, off_t pos, const void *buffer, size_t size);
err_t light_device_control(light_device_t dev, int cmd, void *arg);
err_t light_device_set_rx_indicate(light_device_t dev, err_t (*rx_ind)(light_device_t dev, size_t size));
err_t light_device_set_tx_complete(light_device_t dev, err_t (*tx_done)(light_device_t dev, void *buffer));
#endif //X7PRO_DRIVER_DEVICE_H
