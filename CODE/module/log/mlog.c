#include <common.h>
#include <string.h>

#include "model/control/control_interface.h"
#include "model/fms/fms_interface.h"
#include "model/ins/ins_interface.h"
#include "module/file_manager/file_manager.h"
#include "module/utils/list.h"


#define LOG_TAG "mlog"
#define LOG_LVL LOG_LVL_INFO

#include "ulog.h"


#ifdef FMT_USING_SIH
#include "model/plant/plant_interface.h"
#endif

#define WRITE_PAYLOAD(_payload, _len) write(mlog_handle.fid, _payload, _len);

struct mlog_cb
{
    void (*func)(void);

    struct list_node link;
};

typedef struct
{
    uint32_t total_msg;
    uint32_t lost_msg;
} mlog_stats_t;

struct mlog
{
    int fid;
    uint8_t is_open;
    char file_name[50];
    uint8_t log_status;
    mlog_header_t header;
    mlog_buffer_t buffer;
    struct mutex lock;
    mlog_stats_t *stats;
};

#if defined(__CC_ARM) || defined(__CLANG_ARM)          /* ARM C Compiler */
extern const int MlogTab$$Base;
extern const int MlogTab$$Limit;

#elif defined (__GNUC__) || defined(__TI_COMPILER_VERSION__)
/* GNU GCC Compiler and TI CCS */
extern const int __mlog_start;
extern const int __mlog_end;
#endif

static uint8_t __mlog_data_buffer[MLOG_BUFFER_SIZE];
static mlog_bus_t *__mlog_table;
static uint8_t __mlog_bus_num;
static struct mlog mlog_handle;
static LIST_HEAD(__start_cb_list_head);
static LIST_HEAD(__stop_cb_list_head);
static LIST_HEAD(__update_cb_list_head);

static void invoke_callback_func(mlog_cb_type type)
{
    struct mlog_cb *pos;

    if (type == MLOG_CB_START)
    {
        list_for_each_entry(pos, struct mlog_cb, &__start_cb_list_head, link)
        {
            /* invoke registered callback function */
            pos->func();
        }
    }
    else if (type == MLOG_CB_STOP)
    {
        list_for_each_entry(pos, struct mlog_cb, &__stop_cb_list_head, link)
        {
            /* invoke registered callback function */
            pos->func();
        }
    }
    else if (type == MLOG_CB_UPDATE)
    {
        list_for_each_entry(pos, struct mlog_cb, &__update_cb_list_head, link)
        {
            /* invoke registered callback function */
            pos->func();
        }
    }
}

static void buffer_putc(uint8_t ch)
{
    uint32_t free_space_in_sector = MLOG_SECTOR_SIZE - mlog_handle.buffer.index;

    if (free_space_in_sector < 1)
    {
        // move head point to next sector
        mlog_handle.buffer.head = (mlog_handle.buffer.head + 1) % mlog_handle.buffer.num_sector;
        mlog_handle.buffer.index = 0;

        /* we have a new sector data, inform callback functions */
        invoke_callback_func(MLOG_CB_UPDATE);
    }

    mlog_handle.buffer.data[mlog_handle.buffer.head * MLOG_SECTOR_SIZE + mlog_handle.buffer.index] = ch;
    mlog_handle.buffer.index += 1;
}

static void buffer_write(const uint8_t *data, uint16_t len)
{
    uint32_t free_space_in_sector = MLOG_SECTOR_SIZE - mlog_handle.buffer.index;

    // TODO: add support with len larger than MLOG_SECTOR_SIZE

    if (free_space_in_sector < len)
    {
        memcpy(&mlog_handle.buffer.data[mlog_handle.buffer.head * MLOG_SECTOR_SIZE + mlog_handle.buffer.index], data,
               free_space_in_sector);

        // move head point to next sector
        mlog_handle.buffer.head = (mlog_handle.buffer.head + 1) % mlog_handle.buffer.num_sector;
        mlog_handle.buffer.index = 0;

        memcpy(&mlog_handle.buffer.data[mlog_handle.buffer.head * MLOG_SECTOR_SIZE + mlog_handle.buffer.index],
               &data[free_space_in_sector], len - free_space_in_sector);
        mlog_handle.buffer.index += len - free_space_in_sector;

        /* we have a new sector data, inform callback functions */
        invoke_callback_func(MLOG_CB_UPDATE);
    }
    else
    {
        memcpy(&mlog_handle.buffer.data[mlog_handle.buffer.head * MLOG_SECTOR_SIZE + mlog_handle.buffer.index], data,
               len);
        mlog_handle.buffer.index += len;
    }
}

static uint16_t get_max_write_sector(uint32_t head_p, uint32_t tail_p)
{
    uint16_t sector_to_end;
    uint16_t sector_in_buffer;
    uint16_t sector_to_write;

    sector_to_end = mlog_handle.buffer.num_sector - tail_p;
    // 2 1      18
    if (head_p >= tail_p)
    {
        sector_in_buffer = head_p - tail_p;
    }
    else
    {
        sector_in_buffer = sector_to_end + head_p;
    }

    sector_to_write = sector_in_buffer < sector_to_end ? sector_in_buffer : sector_to_end;

    return sector_to_write <= MLOG_MAX_SECTOR_TO_WRITE ? sector_to_write : MLOG_MAX_SECTOR_TO_WRITE;
}

static bool buffer_is_full(uint32_t len_to_write)
{
    uint32_t free_space_in_sector = MLOG_SECTOR_SIZE - mlog_handle.buffer.index;

    // TODO: check if write multiple sectors at once

    /* check if buffer is full */
    if (free_space_in_sector < len_to_write)
    {
        if ((mlog_handle.buffer.head + 1) % mlog_handle.buffer.num_sector == mlog_handle.buffer.tail)
        {
            return true;
        }
    }

    return false;
}

/**
 * Get current logging status
 *
 * @return mlog status: MLOG_STATUS_IDLE | MLOG_STATUS_WRITE_HEAD | MLOG_STATUS_LOGGING | MLOG_STATUS_STOPPING
 */
uint8_t mlog_get_status(void)
{
    return mlog_handle.log_status;
}

/**
 * Get current logging file name
 *
 * @return mlog logging file name
 */
char *mlog_get_file_name(void)
{
    return mlog_handle.file_name;
}

/**
 * Show the mlog logging statistics
 *
 */
void mlog_show_statistic_all(void)
{
    for (int i = 0; i < __mlog_bus_num; i++)
    {
        printf("%-10s id:%-3d record:%-8ld lost:%-5ld\n", __mlog_table[i].name, i, mlog_handle.stats[i].total_msg,
               mlog_handle.stats[i].lost_msg);
    }
}

/**
 * Show the mlog logging statistics
 *
 */
void mlog_show_statistic(uint8_t msg_id)
{
    LOG_I("%-10s id:%-3d record:%-8ld lost:%-5ld", __mlog_table[msg_id].name, msg_id,
          mlog_handle.stats[msg_id].total_msg,
          mlog_handle.stats[msg_id].lost_msg);
}

/**
 * Show the mlog logging statistics
 *
 */
void mlog_print_volume(uint8_t msg_id)
{
    size_t record_size;
    OS_ENTER_CRITICAL();
    record_size = ((mlog_handle.buffer.head - mlog_handle.buffer.tail +
                mlog_handle.buffer.num_sector) % mlog_handle.buffer.num_sector) * MLOG_SECTOR_SIZE
                + mlog_handle.buffer.index;
    OS_EXIT_CRITICAL();
    printf("\n[%lu]%s current volume:%5d / %5d (%.2f%%).", systime_now_ms(), __mlog_table[msg_id].name, record_size, MLOG_BUFFER_SIZE, (float )record_size * 100 / MLOG_BUFFER_SIZE);
}


/**
 * Register mlog callback function
 *
 * @param cb_type MLOG_CB_START | MLOG_CB_STOP | MLOG_CB_UPDATE
 * @param cb callback function
 *
 * @return FMT Error
 */
err_t mlog_register_callback(mlog_cb_type type, void (*cb_func)(void))
{
    struct mlog_cb *node;

    if (cb_func == NULL)
    {
        return E_INVAL;
    }

    node = (struct mlog_cb *) malloc(sizeof(struct mlog_cb));
    if (node == NULL)
    {
        return E_NOMEM;
    }

    list_init(&node->link);
    node->func = cb_func;

    if (type == MLOG_CB_START)
    {
        list_add_tail(&node->link, &__start_cb_list_head);
    }
    else if (type == MLOG_CB_STOP)
    {
        list_add_tail(&node->link, &__stop_cb_list_head);
    }
    else if (type == MLOG_CB_UPDATE)
    {
        list_add_tail(&node->link, &__update_cb_list_head);
    }

    return E_RROR;
}

/**
 * @brief Deregister mlog callback function
 *
 * @param type MLOG_CB_START | MLOG_CB_STOP | MLOG_CB_UPDATE
 * @param cb_func callback function
 * @return err_t
 */
err_t mlog_deregister_callback(mlog_cb_type type, void (*cb_func)(void))
{
    struct mlog_cb *pos;

    if (cb_func == NULL)
    {
        return E_INVAL;
    }

    if (type == MLOG_CB_START)
    {
        list_for_each_entry(pos, struct mlog_cb, &__start_cb_list_head, link)
        {
            if (pos->func == cb_func)
            {
                list_del(&pos->link);
                free(pos);
                return E_OK;
            }
        }
    }
    else if (type == MLOG_CB_STOP)
    {
        list_for_each_entry(pos, struct mlog_cb, &__stop_cb_list_head, link)
        {
            if (pos->func == cb_func)
            {
                list_del(&pos->link);
                free(pos);
                return E_OK;
            }
        }
    }
    else if (type == MLOG_CB_UPDATE)
    {
        list_for_each_entry(pos, struct mlog_cb, &__update_cb_list_head, link)
        {
            if (pos->func == cb_func)
            {
                list_del(&pos->link);
                free(pos);
                return E_OK;
            }
        }
    }

    return E_RROR;
}

/**
 * @brief Return bus id based on bus_name
 *
 * @param bus_name The bus name
 * @return int Finded bus id, -1 means not found
 */
int mlog_get_bus_id(const char *bus_name)
{
    /* this function may be called before mlog_init */
#if defined(__CC_ARM) || defined(__CLANG_ARM)          /* ARM C Compiler */
    extern const int MlogTab$$Base;
    extern const int MlogTab$$Limit;

    mlog_bus_t *mlog_table = (mlog_bus_t *) &MlogTab$$Base;
    uint8_t mlog_bus_num = (mlog_bus_t *) &MlogTab$$Limit - mlog_table;
#elif defined (__GNUC__) || defined(__TI_COMPILER_VERSION__)
    /* GNU GCC Compiler and TI CCS */
    extern const int __mlog_start;
    extern const int __mlog_end;

    mlog_bus_t *mlog_table = (mlog_bus_t *) &__mlog_start;
    uint8_t mlog_bus_num = (mlog_bus_t *) &__mlog_end - mlog_table;
#endif


    for (uint8_t n = 0; n < mlog_bus_num; n++)
    {
        if (strcmp(bus_name, mlog_table[n].name) == 0)
        {
            /* the bus id is the same as index */
            return n;
        }
    }

    return -1;
}

/**
 * Add log description into mlog header
 *
 * @param desc description text, should not longer than MLOG_DESCRIPTION_SIZE
 * @return FMT Error
 */
err_t mlog_add_desc(char *desc)
{
    if (!desc)  return E_INVAL;
    if (strlen(desc) > MLOG_DESCRIPTION_SIZE - 1)
    {
        LOG_W("description too long.");
        return E_NOMEM;
    }

    strcpy(mlog_handle.header.description, desc);

    return E_OK;
}

/**
 * Push a mlog message into buffer
 *
 * @param payload msg payload
 * @param msg_id msg id
 * @param len msg length
 *
 * @return FMT Error
 */
err_t mlog_push_msg(const uint8_t *payload, uint8_t msg_id, uint16_t len)
{
    /*                           MLOG MSG Format                                 */
    /*   ======================================================================= */
    /*   | MLOG_BEGIN_MSG1 | MLOG_BEGIN_MSG2 | MSG_ID | PAYLOAD | MLOG_END_MSG | */
    /*   ======================================================================= */

    if (msg_id + 1 > __mlog_bus_num)
    {
        /* invalid msg id */
        return E_INVAL;
    }

    /* check log status */
    if (mlog_handle.log_status != MLOG_STATUS_LOGGING)
    {
        return E_EMPTY;
    }

    /* check if buffer has enough space to store msg */
    if (buffer_is_full(len + 4))
    {
        /* do not let it print too fast */
        PERIOD_EXECUTE(mlog_buff_full, 1000, LOG_W("buffer is full!"););

        mlog_handle.stats[msg_id].lost_msg += 1;

        return E_FULL;
    }

    os_mutex_take(&mlog_handle.lock, OS_WAITING_FOREVER);

    /* write msg begin flag */
    buffer_putc(MLOG_BEGIN_MSG1);
    buffer_putc(MLOG_BEGIN_MSG2);
    /* write msg id */
    buffer_putc(msg_id);
    /* write payload */
    buffer_write(payload, len);
    /* write msg end flag */
    buffer_putc(MLOG_END_MSG);

    os_mutex_release(&mlog_handle.lock);

    mlog_handle.stats[msg_id].total_msg += 1;

    return E_OK;
}

/**
 * Call this function to start the binary log
 *
 * @param file_name mlog_handle file name with full path
 * @return FMT Error
 */
err_t mlog_start(char *file_name)
{
    if (mlog_handle.log_status != MLOG_STATUS_IDLE)
    {
        LOG_W("%s is logging, stop it first", mlog_handle.file_name);
        return E_BUSY;
    }

    /* create log file */
    mlog_handle.fid = open(file_name, O_CREAT | O_WRONLY);

    if (mlog_handle.fid < 0)
    {
        LOG_E("%s open fail", file_name);
        return E_RROR;
    }
    /* set log file open flag */
    mlog_handle.is_open = 1;
    /* get current time stamp */
    mlog_handle.header.timestamp = systime_now_ms();

    /* init log buffer */
    mlog_handle.buffer.head = mlog_handle.buffer.tail = 0;
    mlog_handle.buffer.index = 0;

    /* write log header */
    mlog_handle.log_status = MLOG_STATUS_WRITE_HEAD;

    /* write log info */
    WRITE_PAYLOAD(&mlog_handle.header.version, sizeof(mlog_handle.header.version));
    WRITE_PAYLOAD(&mlog_handle.header.timestamp, sizeof(mlog_handle.header.timestamp));
    WRITE_PAYLOAD(&mlog_handle.header.max_name_len, sizeof(mlog_handle.header.max_name_len));
    WRITE_PAYLOAD(&mlog_handle.header.max_desc_len, sizeof(mlog_handle.header.max_desc_len));
    WRITE_PAYLOAD(&mlog_handle.header.max_model_info_len, sizeof(mlog_handle.header.max_model_info_len));
    WRITE_PAYLOAD(mlog_handle.header.description, MLOG_DESCRIPTION_SIZE);
    /* clear the description after it has been written */
    memset(mlog_handle.header.description, 0, MLOG_DESCRIPTION_SIZE);

    /* write model information */
#ifdef FMT_USING_SIH
    sprintf(mlog_handle.header.model_info, "%s\n%s\n%s\n%s", ins_model_info.info, fms_model_info.info, control_model_info.info, plant_model_info.info);
#else
    memset(mlog_handle.header.model_info, 0, MLOG_MODEL_INFO_SIZE);
//    sprintf(mlog_handle.header.model_info, "%s\n%s\n%s", ins_model_info.info, fms_model_info.info,
//            control_model_info.info);
#endif
    WRITE_PAYLOAD(mlog_handle.header.model_info, MLOG_MODEL_INFO_SIZE);

    /* write bus information */
    WRITE_PAYLOAD(&mlog_handle.header.num_bus, sizeof(mlog_handle.header.num_bus));
    for (uint8_t n = 0; n < mlog_handle.header.num_bus; n++)
    {
        uint8_t msg_id = n;

        /* write bus list */
        WRITE_PAYLOAD(mlog_handle.header.bus_list[n].name, MLOG_NAME_MAX_LEN);
        WRITE_PAYLOAD(&msg_id, sizeof(msg_id));
        WRITE_PAYLOAD(&mlog_handle.header.bus_list[n].num_elem, sizeof(mlog_handle.header.bus_list[n].num_elem));
        /* write bus element */
        for (int k = 0; k < mlog_handle.header.bus_list[n].num_elem; k++)
        {
            WRITE_PAYLOAD(mlog_handle.header.bus_list[n].elem_list[k].name, MLOG_NAME_MAX_LEN);
            WRITE_PAYLOAD(&mlog_handle.header.bus_list[n].elem_list[k].type,
                          sizeof(mlog_handle.header.bus_list[n].elem_list[k].type));
            WRITE_PAYLOAD(&mlog_handle.header.bus_list[n].elem_list[k].number,
                          sizeof(mlog_handle.header.bus_list[n].elem_list[k].number));
        }
    }

    /* write parameter information */
    char name_buffer[MLOG_NAME_MAX_LEN + 1];

    WRITE_PAYLOAD(&mlog_handle.header.num_param_group, sizeof(mlog_handle.header.num_param_group));
    for (int n = 0; n < mlog_handle.header.num_param_group; n++)
    {
        memset(name_buffer, 0, MLOG_NAME_MAX_LEN);
        strncpy(name_buffer, mlog_handle.header.param_group_list[n].name, MLOG_NAME_MAX_LEN);

        WRITE_PAYLOAD(name_buffer, MLOG_NAME_MAX_LEN);
        WRITE_PAYLOAD(&mlog_handle.header.param_group_list[n].param_num,
                      sizeof(mlog_handle.header.param_group_list[n].param_num));

        for (int k = 0; k < mlog_handle.header.param_group_list[n].param_num; k++)
        {
            memset(name_buffer, 0, MLOG_NAME_MAX_LEN);
            strncpy(name_buffer, mlog_handle.header.param_group_list[n].param_list[k].name, MLOG_NAME_MAX_LEN);

            WRITE_PAYLOAD(name_buffer, MLOG_NAME_MAX_LEN);
            WRITE_PAYLOAD(&mlog_handle.header.param_group_list[n].param_list[k].type,
                          sizeof(mlog_handle.header.param_group_list[n].param_list[k].type));

            int type = mlog_handle.header.param_group_list[n].param_list[k].type;

            if (type == PARAM_TYPE_INT8)
            {
                WRITE_PAYLOAD(&mlog_handle.header.param_group_list[n].param_list[k].val.i8, sizeof(int8_t));
            }
            else if (type == PARAM_TYPE_UINT8)
            {
                WRITE_PAYLOAD(&mlog_handle.header.param_group_list[n].param_list[k].val.u8, sizeof(uint8_t));
            }
            else if (type == PARAM_TYPE_INT16)
            {
                WRITE_PAYLOAD(&mlog_handle.header.param_group_list[n].param_list[k].val.i16, sizeof(int16_t));
            }
            else if (type == PARAM_TYPE_UINT16)
            {
                WRITE_PAYLOAD(&mlog_handle.header.param_group_list[n].param_list[k].val.u16, sizeof(uint16_t));
            }
            else if (type == PARAM_TYPE_INT32)
            {
                WRITE_PAYLOAD(&mlog_handle.header.param_group_list[n].param_list[k].val.i32, sizeof(int32_t));
            }
            else if (type == PARAM_TYPE_UINT32)
            {
                WRITE_PAYLOAD(&mlog_handle.header.param_group_list[n].param_list[k].val.u32, sizeof(uint32_t));
            }
            else if (type == PARAM_TYPE_FLOAT)
            {
                WRITE_PAYLOAD(&mlog_handle.header.param_group_list[n].param_list[k].val.f, sizeof(float));
            }
            else if (type == PARAM_TYPE_DOUBLE)
            {
                WRITE_PAYLOAD(&mlog_handle.header.param_group_list[n].param_list[k].val.lf, sizeof(double));
            }
            else
            {
                LOG_W("unknown parameter type:%d", type);
            }
        }
    }

    /* set log status */
    strncpy(mlog_handle.file_name, file_name, sizeof(mlog_handle.file_name) - 1);

    for (uint8_t i = 0; i < __mlog_bus_num; i++)
    {
        mlog_handle.stats[i].total_msg = 0;
        mlog_handle.stats[i].lost_msg = 0;
    }

    /* start logging, set flag */
    mlog_handle.log_status = MLOG_STATUS_LOGGING;

    /* invoke callback function */
    invoke_callback_func(MLOG_CB_START);

    LOG_I("start logging:%s", file_name);

    return E_OK;
}

/**
 * Call this function to stop the binary log
 *
 */
void mlog_stop(void)
{
    /* here we just set log status to stopping, it actually stops
       when the mlog_async_output() is called later */
    if (mlog_handle.log_status == MLOG_STATUS_LOGGING)
    {
        mlog_handle.log_status = MLOG_STATUS_STOPPING;
    }
}

/**
 * Asynchronous binary logs to storage device
 *
 * @note you must call this function periodically
 */
void mlog_async_output(void)
{
    uint32_t head_p, tail_p;
    uint8_t need_sync = 0;

    if (!mlog_handle.is_open)
    {
        /* no log file is opened */
        return;
    }

    OS_ENTER_CRITICAL();
    head_p = mlog_handle.buffer.head;
    tail_p = mlog_handle.buffer.tail;
    OS_EXIT_CRITICAL();

    /* check if we need synchronous the output */
    need_sync = (head_p != tail_p);
    /* write log buffer sector into storage device */
    while (head_p != tail_p)
    {
        /* check how many sectors that we can write at once */
        uint16_t sector_to_write = get_max_write_sector(head_p, tail_p);
        /* write data to the storage device */
        write(mlog_handle.fid, &mlog_handle.buffer.data[tail_p * MLOG_SECTOR_SIZE], sector_to_write * MLOG_SECTOR_SIZE);
        /* update buffer pointer */
        tail_p = (tail_p + sector_to_write) % mlog_handle.buffer.num_sector;
        OS_ENTER_CRITICAL();
        mlog_handle.buffer.tail = tail_p;
        OS_EXIT_CRITICAL();
    }

    /* synchronous the disk to make sure data have been written */
    if (need_sync)
    {
        fsync(mlog_handle.fid);
    }

    /* if logging is off, clean up the buffer. */
    if (mlog_handle.log_status == MLOG_STATUS_STOPPING)
    {
        /* dump rest data in buffer */
        if (mlog_handle.buffer.index)
        {
            write(mlog_handle.fid, &mlog_handle.buffer.data[tail_p * MLOG_SECTOR_SIZE], mlog_handle.buffer.index);
            fsync(mlog_handle.fid);
        }
        /* close the file if needed */
        if (mlog_handle.is_open)
        {
            close(mlog_handle.fid);
            mlog_handle.fid = -1;
            mlog_handle.is_open = 0;
        }

        /* set log status to idle */
        mlog_handle.log_status = MLOG_STATUS_IDLE;

        /* invoke callback function */
        invoke_callback_func(MLOG_CB_STOP);

        LOG_I("stop logging:%s", mlog_handle.file_name);
        for (uint8_t i = 0; i < __mlog_bus_num; i++)
        {
            LOG_I("%-20s id:%-3d record:%-8d lost:%-5d", __mlog_table[i].name, i, mlog_handle.stats[i].total_msg,
                  mlog_handle.stats[i].lost_msg);
        }
    }
}

/**
 * Initialize mat log module.
 *
 * @return Errors Status.
 */
err_t mlog_init(void)
{
#if defined(__CC_ARM) || defined(__CLANG_ARM)          /* ARM C Compiler */
    extern const int MlogTab$$Base;
    extern const int MlogTab$$Limit;

    __mlog_table = (mlog_bus_t *) &MlogTab$$Base;
    __mlog_bus_num = (mlog_bus_t *) &MlogTab$$Limit - __mlog_table;
#elif defined (__GNUC__) || defined(__TI_COMPILER_VERSION__)
    /* GNU GCC Compiler and TI CCS */
    extern const int __mlog_start;
    extern const int __mlog_end;

    __mlog_table = (mlog_bus_t *) &__mlog_start;
    __mlog_bus_num = (mlog_bus_t *) &__mlog_end - __mlog_table;
#endif

    /* initialize mlog_handle status */
    mlog_handle.is_open = 0;
    mlog_handle.log_status = MLOG_STATUS_IDLE;
    /* initialize log header */
    mlog_handle.header.version = MLOG_VERSION;
    mlog_handle.header.timestamp = 0;
    mlog_handle.header.max_name_len = MLOG_NAME_MAX_LEN;
    mlog_handle.header.max_desc_len = MLOG_DESCRIPTION_SIZE;
    mlog_handle.header.max_model_info_len = MLOG_MODEL_INFO_SIZE;
    mlog_handle.header.num_bus = __mlog_bus_num;
    mlog_handle.header.bus_list = __mlog_table;
    mlog_handle.header.num_param_group = param_get_group_count();
    mlog_handle.header.param_group_list = param_get_table();
    memset(mlog_handle.header.description, 0, MLOG_DESCRIPTION_SIZE);

    /* initialize mlog_handle buffer */
    mlog_handle.buffer.data = __mlog_data_buffer;

    mlog_handle.stats = (mlog_stats_t *) malloc(__mlog_bus_num * sizeof(mlog_stats_t));
    if (mlog_handle.stats == NULL)
    {
        return E_NOMEM;
    }

    if (mlog_handle.buffer.data == NULL)
    {
        console_printf("mlog_handle buffer malloc fail!\n");
        return E_NOMEM;
    }
    else
    {
        /* initialize buffer */
        mlog_handle.buffer.num_sector = MLOG_BUFFER_SIZE / MLOG_SECTOR_SIZE;
        mlog_handle.buffer.head = 0;
        mlog_handle.buffer.tail = 0;
        mlog_handle.buffer.index = 0;
    }

    /* create write lock */
    if (os_mutex_init(&mlog_handle.lock, "mlog_lock") != E_OK)
    {
        console_printf("fail to create mlog lock!\n");
        return E_RROR;
    }

    return E_OK;
}