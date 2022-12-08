#ifndef FILE_MANAGER_H__
#define FILE_MANAGER_H__

#include <dfs_posix.h>
#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif

err_t file_manager_init(const struct dfs_mount_tbl* mnt_table);
err_t current_log_session(char* path);

/* file extended operation */
int fm_fprintf(int fd, const char* fmt, ...);
int fm_deldir(const char* path);

#ifdef __cplusplus
}
#endif

#endif
