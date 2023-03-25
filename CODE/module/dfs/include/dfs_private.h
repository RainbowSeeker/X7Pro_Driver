// Copyright (c) 2006-2022 By RainbowSeeker.

#ifndef DFS_PRIVATE_H__
#define DFS_PRIVATE_H__

#include <dfs_fs.h>

#define LOG_TAG    "DFS"
#define LOG_LVL    LOG_LVL_INFO

#define NO_WORKING_DIR  "system does not support working directory\n"

/* extern variable */
extern const struct dfs_filesystem_ops *filesystem_operation_table[];
extern struct dfs_filesystem filesystem_table[];
extern const struct dfs_mount_tbl mount_table[];

extern char working_directory[];

#endif
