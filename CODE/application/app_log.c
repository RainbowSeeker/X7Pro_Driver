// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/2.
//
#include "common.h"
#include "module_common.h"
#include "module/file_manager/file_manager.h"
#include "sys.h"
#include "logger.h"


#define LOG_TAG    "Logger"
#include <ulog.h>

#define ULOG_FILE_NAME    "ulog.txt"
#define EVENT_MLOG_UPDATE (1 << 0)
#define EVENT_ULOG_UPDATE (1 << 1)

static os_event_t _log_event = NULL;

#ifdef ENABLE_ULOG_CONSOLE_BACKEND

static void ulog_console_backend_output(struct ulog_backend *backend, uint32_t level, const char *tag, bool_t is_raw,
                                        const char *log, size_t len)
{
    console_write(log, len);
}

#endif /* ENABLE_ULOG_CONSOLE_BACKEND */

#ifdef ENABLE_ULOG_FS_BACKEND
static int _ulog_fd = -1;
static void ulog_fs_backend_init(struct ulog_backend* backend)
{
    char file_name[50];
    char log_session[50];

    if (current_log_session(log_session) == E_OK) {
        sprintf(file_name, "%s/%s", log_session, ULOG_FILE_NAME);

        _ulog_fd = open(file_name, O_CREAT | O_WRONLY);

        if (_ulog_fd < 0) {
            printf("ulog fs backend init fail\n");
        }
    }
}

static void ulog_fs_backend_output(struct ulog_backend* backend, uint32_t level, const char* tag, bool_t is_raw,
                                   const char* log, size_t len)
{
    if (_ulog_fd >= 0) {
        write(_ulog_fd, log, len);
    }
}

static void ulog_fs_backend_deinit(struct ulog_backend* backend)
{
    if (_ulog_fd >= 0) {
        close(_ulog_fd);
        _ulog_fd = -1;
    }
}
#endif /* ENABLE_ULOG_FS_BACKEND */

static void mlog_update_cb(void)
{
    os_event_send(_log_event, EVENT_MLOG_UPDATE);
}

static void ulog_update_cb(void)
{
    os_event_send(_log_event, EVENT_ULOG_UPDATE);
}


void App_Log_Main(void *argument)
{
    err_t err;
    uint32_t recv_set = 0;

    if (os_event_init(&_log_event, 10) != E_OK)
    {
        printf("log event create fail\n");
        return;
    }

    /* init binary log */
    mlog_init();

    /* init ulog */
    ulog_init();

#ifdef ENABLE_ULOG_CONSOLE_BACKEND
    static struct ulog_backend console;
    /* register ulog console backend */
    console.output = ulog_console_backend_output;
    ulog_backend_register(&console, "console", FALSE);
#endif

#ifdef ENABLE_ULOG_FS_BACKEND
    static struct ulog_backend fs;
    /* register ulog filesystem backend */
    fs.init = ulog_fs_backend_init;
    fs.output = ulog_fs_backend_output;
    fs.deinit = ulog_fs_backend_deinit;
    ulog_backend_register(&fs, "filesystem", FALSE);
#endif

    if (PARAM_GET_INT32(SYSTEM, MLOG_MODE) == 2 || PARAM_GET_INT32(SYSTEM, MLOG_MODE) == 3)
    {
        logger_start_mlog(NULL);
    }

    mlog_register_callback(MLOG_CB_UPDATE, mlog_update_cb);
    ulog_register_callback(ulog_update_cb);

    while (1)
    {
        err = os_event_recv(_log_event, 20, &recv_set);
        if (err == E_OK)
        {
            if (recv_set & EVENT_MLOG_UPDATE)
            {
                mlog_async_output();
            }
            if (recv_set & EVENT_ULOG_UPDATE)
            {
                ulog_async_output();
            }
        }
        else if (err == E_TIMEOUT)
        {
            /* if timeout, check if there are log data need to send */
            mlog_async_output();
            ulog_async_output();
#ifdef ENABLE_ULOG_FS_BACKEND
            fsync(_ulog_fd);
#endif
        }
        else
        {
            /* some other error happen */
        }
    }
}
