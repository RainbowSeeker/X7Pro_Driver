#ifndef CAN_H_
#define CAN_H_

#include <common.h>


#ifndef RT_CANMSG_BOX_SZ
#define RT_CANMSG_BOX_SZ    16
#endif
#ifndef RT_CANSND_BOX_NUM
#define RT_CANSND_BOX_NUM   1
#endif

enum CANBAUD
{
    CAN1MBaud   = 1000UL * 1000,/* 1 MBit/sec   */
    CAN800kBaud = 1000UL * 800, /* 800 kBit/sec */
    CAN500kBaud = 1000UL * 500, /* 500 kBit/sec */
    CAN250kBaud = 1000UL * 250, /* 250 kBit/sec */
    CAN125kBaud = 1000UL * 125, /* 125 kBit/sec */
    CAN100kBaud = 1000UL * 100, /* 100 kBit/sec */
    CAN50kBaud  = 1000UL * 50,  /* 50 kBit/sec  */
    CAN20kBaud  = 1000UL * 20,  /* 20 kBit/sec  */
    CAN10kBaud  = 1000UL * 10   /* 10 kBit/sec  */
};

#define CAN_MODE_NORMAL              0
#define CAN_MODE_LISEN               1
#define CAN_MODE_LOOPBACK            2
#define CAN_MODE_LOOPBACKANLISEN     3

#define CAN_MODE_PRIV                0x01
#define CAN_MODE_NOPRIV              0x00

struct can_filter_item
{
    uint32_t id  : 29;
    uint32_t ide : 1;
    uint32_t rtr : 1;
    uint32_t mode : 1;
    uint32_t mask;
    int32_t hdr;
#ifdef RT_CAN_USING_HDR
    err_t (*ind)(light_device_t dev, void *args , int32_t hdr, size_t size);
    void *args;
#endif /*RT_CAN_USING_HDR*/
};

#ifdef RT_CAN_USING_HDR
#define RT_CAN_FILTER_ITEM_INIT(id,ide,rtr,mode,mask,ind,args) \
     {(id), (ide), (rtr), (mode), (mask), -1, (ind), (args)}
#define RT_CAN_FILTER_STD_INIT(id,ind,args) \
     RT_CAN_FILTER_ITEM_INIT(id,0,0,0,0xFFFFFFFF,ind,args)
#define RT_CAN_FILTER_EXT_INIT(id,ind,args) \
     RT_CAN_FILTER_ITEM_INIT(id,1,0,0,0xFFFFFFFF,ind,args)
#define RT_CAN_STD_RMT_FILTER_INIT(id,ind,args) \
     RT_CAN_FILTER_ITEM_INIT(id,0,1,0,0xFFFFFFFF,ind,args)
#define RT_CAN_EXT_RMT_FILTER_INIT(id,ind,args) \
     RT_CAN_FILTER_ITEM_INIT(id,1,1,0,0xFFFFFFFF,ind,args)
#define RT_CAN_STD_RMT_DATA_FILTER_INIT(id,ind,args) \
     RT_CAN_FILTER_ITEM_INIT(id,0,0,1,0xFFFFFFFF,ind,args)
#define RT_CAN_EXT_RMT_DATA_FILTER_INIT(id,ind,args) \
     RT_CAN_FILTER_ITEM_INIT(id,1,0,1,0xFFFFFFFF,ind,args)
#else

#define RT_CAN_FILTER_ITEM_INIT(id,ide,rtr,mode,mask) \
     {(id), (ide), (rtr), (mode), (mask), -1, }
#define RT_CAN_FILTER_STD_INIT(id) \
     RT_CAN_FILTER_ITEM_INIT(id,0,0,0,0xFFFFFFFF)
#define RT_CAN_FILTER_EXT_INIT(id) \
     RT_CAN_FILTER_ITEM_INIT(id,1,0,0,0xFFFFFFFF)
#define RT_CAN_STD_RMT_FILTER_INIT(id) \
     RT_CAN_FILTER_ITEM_INIT(id,0,1,0,0xFFFFFFFF)
#define RT_CAN_EXT_RMT_FILTER_INIT(id) \
     RT_CAN_FILTER_ITEM_INIT(id,1,1,0,0xFFFFFFFF)
#define RT_CAN_STD_RMT_DATA_FILTER_INIT(id) \
     RT_CAN_FILTER_ITEM_INIT(id,0,0,1,0xFFFFFFFF)
#define RT_CAN_EXT_RMT_DATA_FILTER_INIT(id) \
     RT_CAN_FILTER_ITEM_INIT(id,1,0,1,0xFFFFFFFF)
#endif

struct can_filter_config
{
    uint32_t count;
    uint32_t actived;
    struct can_filter_item *items;
};

struct can_configure
{
    uint32_t baud_rate;
    uint32_t msgboxsz;
    uint32_t sndboxnumber;
    uint32_t mode      : 8;
    uint32_t privmode  : 8;
    uint32_t reserved  : 16;
    uint32_t ticks;
#ifdef RT_CAN_USING_HDR
    uint32_t maxhdr;
#endif
};

#define CANDEFAULTCONFIG \
{\
        CAN1MBaud,\
        RT_CANMSG_BOX_SZ,\
        RT_CANSND_BOX_NUM,\
        CAN_MODE_NORMAL,\
};

struct can_ops;
#define CAN_CMD_SET_FILTER       0x13
#define CAN_CMD_SET_BAUD         0x14
#define CAN_CMD_SET_MODE         0x15
#define CAN_CMD_SET_PRIV         0x16
#define CAN_CMD_GET_STATUS       0x17
#define CAN_CMD_SET_STATUS_IND   0x18
#define CAN_CMD_SET_BUS_HOOK     0x19

#define DEVICE_CAN_INT_ERR       0x1000

enum can_status_mode
{
    NORMAL = 0,
    ERRWARNING = 1,
    ERRPASSIVE = 2,
    BUSOFF = 4,
};
enum can_bus_err
{
    CAN_BUS_NO_ERR = 0,
    CAN_BUS_BIT_PAD_ERR = 1,
    CAN_BUS_FORMAT_ERR = 2,
    CAN_BUS_ACK_ERR = 3,
    CAN_BUS_IMPLICIT_BIT_ERR = 4,
    CAN_BUS_EXPLICIT_BIT_ERR = 5,
    CAN_BUS_CRC_ERR = 6,
};

struct can_status
{
    uint32_t rcverrcnt;
    uint32_t snderrcnt;
    uint32_t errcode;
    uint32_t rcvpkg;
    uint32_t dropedrcvpkg;
    uint32_t sndpkg;
    uint32_t dropedsndpkg;
    uint32_t bitpaderrcnt;
    uint32_t formaterrcnt;
    uint32_t ackerrcnt;
    uint32_t biterrcnt;
    uint32_t crcerrcnt;
    uint32_t rcvchange;
    uint32_t sndchange;
    uint32_t lasterrtype;
};

#ifdef RT_CAN_USING_HDR
struct can_hdr
{
    uint32_t connected;
    uint32_t msgs;
    struct can_filter_item filter;
    struct list_node list;
};
#endif
struct can_device;
typedef err_t (*canstatus_ind)(struct can_device *, void *);
typedef struct can_status_ind_type
{
    canstatus_ind ind;
    void *args;
} *can_status_ind_type_t;
typedef void (*can_bus_hook)(struct can_device *);
struct can_device
{
    struct device parent;

    const struct can_ops *ops;
    struct can_configure config;
    struct can_status status;

    uint32_t timerinitflag;
    os_timer_t timer;


    struct can_status_ind_type status_indicate;
#ifdef RT_CAN_USING_HDR
    struct can_hdr *hdr;
#endif
#ifdef RT_CAN_USING_BUS_HOOK
    can_bus_hook bus_hook;
#endif /*RT_CAN_USING_BUS_HOOK*/
    os_mutex_t lock;
    void *can_rx;
    void *can_tx;
};
typedef struct can_device *can_t;

#define CAN_STDID 0
#define CAN_EXTID 1
#define CAN_DTR   0
#define CAN_RTR   1

typedef struct can_status *can_status_t;
struct can_msg
{
    uint32_t id  : 29;
    uint32_t ide : 1;
    uint32_t rtr : 1;
    uint32_t rsv : 1;
    uint32_t len : 8;
    uint32_t priv : 8;
    int32_t hdr : 8;
    uint32_t reserved : 8;
    uint8_t data[8];
};
typedef struct can_msg *can_msg_t;

struct can_msg_list
{
    struct list_node list;
#ifdef RT_CAN_USING_HDR
    struct list_node hdrlist;
    struct can_hdr *owner;
#endif
    struct can_msg data;
};

struct can_rx_fifo
{
    /* software fifo */
    struct can_msg_list *buffer;
    uint32_t freenumbers;
    struct list_node freelist;
    struct list_node uselist;
};

#define CAN_SND_RESULT_OK        0
#define CAN_SND_RESULT_ERR       1
#define CAN_SND_RESULT_WAIT      2

#define CAN_EVENT_RX_IND         0x01    /* Rx indication */
#define CAN_EVENT_TX_DONE        0x02    /* Tx complete   */
#define CAN_EVENT_TX_FAIL        0x03    /* Tx fail   */
#define CAN_EVENT_RX_TIMEOUT     0x05    /* Rx timeout    */
#define CAN_EVENT_RXOF_IND       0x06    /* Rx overflow */

struct can_sndbxinx_list
{
    struct list_node list;
    struct completion completion;
    uint32_t result;
};

struct can_tx_fifo
{
    struct can_sndbxinx_list *buffer;
    os_sem_t sem;
    struct list_node freelist;
};

struct can_ops
{
    err_t (*configure)(struct can_device *can, struct can_configure *cfg);
    err_t (*control)(struct can_device *can, int cmd, void *arg);
    int (*sendmsg)(struct can_device *can, const void *buf, uint32_t boxno);
    int (*recvmsg)(struct can_device *can, void *buf, uint32_t boxno);
};

err_t hw_can_register(struct can_device    *can,
                            const char              *name,
                            const struct can_ops *ops,
                            void                    *data);
void hw_can_isr(struct can_device *can, int event);
#endif /*_CAN_H*/

