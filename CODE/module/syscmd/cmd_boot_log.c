#include <common.h>

#include <dfs_posix.h>
#include "optparse.h"
#include "syscmd.h"

#define LOG_SESSION_FILE "/log/session_id"

extern void cat(const char* filename);

int cmd_boot_log(int argc, char** argv)
{
    struct optparse options;
    int option;
    char id_buffer[5] = { 0 };
    int id = -1;
    struct optparse_long longopts[] = {
        { "id", 'i', OPTPARSE_REQUIRED },
        { NULL } /* Don't remove this line */
    };

    optparse_init(&options, argv);

    while ((option = optparse_long(&options, longopts, NULL)) != -1) {
        switch (option) {
        case 'i':
            id = atoi(options.optarg);
            break;
        case '?':
            printf("%s: %s\n", "mcn echo", options.errmsg);
            return EXIT_FAILURE;
        }
    }

    if (id < 0) {
        /* read current work id */
        int fd = open(LOG_SESSION_FILE, O_WRONLY);
        if (fd < 0) {
            printf("open %s fail!\n", LOG_SESSION_FILE);
            return EXIT_FAILURE;
        }

        if (read(fd, id_buffer, sizeof(id_buffer) - 1) > 0) {
            id = atoi(id_buffer);
        }
        close(fd);
    }

    if (id > 0) {
        char filename[20];
        console_format(filename, "/log/session_%d/boot_log.txt", id);
        printf("content of %s:\n", filename);
        cat(filename);
    }

    return EXIT_SUCCESS;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_boot_log, __cmd_boot_log, display boot log);
