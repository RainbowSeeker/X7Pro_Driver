// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/15.
//

#include "logger.h"
#include "file_manager/file_manager.h"

err_t logger_start_mlog(char* path)
{
    char log_name[100];
    char file_name[50];
    static uint8_t mlog_id = 0;

    if (path) {
        /* if a valid path is provided, use it for mlog */
        return mlog_start(path);
    }

    if (current_log_session(log_name) != E_OK) {
        console_printf("no available log session\n");
        return E_RROR;
    }
    sprintf(file_name, "/mlog%d.bin", ++mlog_id);
    strcat(log_name, file_name);

    return mlog_start(log_name);
}

void logger_stop_mlog(void)
{
    mlog_stop();
}