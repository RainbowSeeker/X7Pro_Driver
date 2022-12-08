

#include <common.h>

#include "module/file_manager/file_manager.h"
#include "module/syscmd/syscmd.h"
#include "task/logger/task_logger.h"

static void _show_mlog_status(void)
{
    if (mlog_get_status() == MLOG_STATUS_IDLE) {
        console_printf("no working log file.\n");
        return;
    }

    console_printf("log file: %s\n", mlog_get_file_name());
    mlog_show_statistic();
}

static void show_usage(void)
{
}

static int handle_cmd(int argc, char** argv, int optc, optv_t* optv)
{
    if (argc < 2) {
        show_usage();
        return 0;
    }

    for (uint16_t i = 0; i < optc; i++) {

        if (STRING_COMPARE(optv[i].opt, "-m") || STRING_COMPARE(optv[i].opt, "--msg")) {
            mlog_add_desc(optv[i].val);
        }
    }

    if (strcmp(argv[1], "start") == 0) {
        if (argc >= 3) {
            logger_start_mlog(argv[2]);
        } else {
            logger_start_mlog(NULL);
        }
    } else if (strcmp(argv[1], "stop") == 0) {
        logger_stop_mlog();
    } else if (strcmp(argv[1], "status") == 0) {
        _show_mlog_status();
    } else if (strcmp(argv[1], "ws") == 0) {
        char path[100];
        current_log_session(path);
        console_printf("working log session: %s\n", path);
    } else {
        show_usage();
    }

    return 0;
}

int cmd_mlog(int argc, char** argv)
{
    return syscmd_process(argc, argv, handle_cmd);
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_mlog, __cmd_mlog, start / stop mlog);