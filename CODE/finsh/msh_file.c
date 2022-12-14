/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-09-25     Bernard      the first verion for FinSH
 */

#include <common.h>

#if defined(FINSH_USING_MSH) && defined(RT_USING_DFS)

#include <finsh.h>
#include "msh.h"
#include <dfs_posix.h>

#define DT_UNKNOWN           0x00
#define DT_REG               0x01
#define DT_DIR               0x02

static int msh_readline(int fd, char *line_buf, int size)
{
    char ch;
    int index = 0;

    do
    {
        if (read(fd, &ch, 1) != 1)
        {
            /* nothing in this file */
            return 0;
        }
    }
    while (ch == '\n' || ch == '\r');

    /* set the first character */
    line_buf[index ++] = ch;

    while (index < size)
    {
        if (read(fd, &ch, 1) == 1)
        {
            if (ch == '\n' || ch == '\r')
            {
                line_buf[index] = '\0';
                break;
            }

            line_buf[index++] = ch;
        }
        else
        {
            line_buf[index] = '\0';
            break;
        }
    }

    return index;
}

int msh_exec_script(const char *cmd_line, int size)
{
    int ret;
    int fd = -1;
    char *pg_name;
    int length, cmd_length = 0;

    if (size == 0) return -E_RROR;

    /* get the length of command0 */
    while ((cmd_line[cmd_length] != ' ' && cmd_line[cmd_length] != '\t') && cmd_length < size)
        cmd_length ++;

    /* get name length */
    length = cmd_length + 32;

    /* allocate program name memory */
    pg_name = (char *) malloc(length);
    if (pg_name == NULL) return -E_NOMEM;

    /* copy command0 */
    memcpy(pg_name, cmd_line, cmd_length);
    pg_name[cmd_length] = '\0';

    if (strstr(pg_name, ".sh") != NULL || strstr(pg_name, ".SH") != NULL)
    {
        /* try to open program */
        fd = open(pg_name, O_RDONLY, 0);

        /* search in /bin path */
        if (fd < 0)
        {
            snprintf(pg_name, length - 1, "/bin/%.*s", cmd_length, cmd_line);
            fd = open(pg_name, O_RDONLY, 0);
        }
    }

    free(pg_name);
    if (fd >= 0)
    {
        /* found script */
        char *line_buf;
        int length;

        line_buf = (char *) malloc(RT_CONSOLEBUF_SIZE);
        if (line_buf == NULL)
        {
            close(fd);
            return -E_NOMEM;
        }

        /* read line by line and then exec it */
        do
        {
            length = msh_readline(fd, line_buf, RT_CONSOLEBUF_SIZE);
            if (length > 0)
            {
                char ch = '\0';
                int index;

                for (index = 0; index < length; index ++)
                {
                    ch = line_buf[index];
                    if (ch == ' ' || ch == '\t') continue;
                    else break;
                }

                if (ch != '#') /* not a comment */
                    msh_exec(line_buf, length);
            }
        }
        while (length > 0);

        close(fd);
        free(line_buf);

        ret = 0;
    }
    else
    {
        ret = -1;
    }

    return ret;
}

#ifdef DFS_USING_WORKDIR
extern char working_directory[];
#endif

int cmd_ls(int argc, char **argv)
{
    extern void ls(const char *pathname);

    if (argc == 1)
    {
#ifdef DFS_USING_WORKDIR
        ls(working_directory);
#else
        ls("/");
#endif
    }
    else
    {
        ls(argv[1]);
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_ls, __cmd_ls, List information about the FILEs.);

int cmd_cp(int argc, char **argv)
{
    void copy(const char *src, const char *dst);

    if (argc != 3)
    {
        printf("Usage: cp SOURCE DEST\n");
        printf("Copy SOURCE to DEST.\n");
    }
    else
    {
        copy(argv[1], argv[2]);
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_cp, __cmd_cp, Copy SOURCE to DEST.);

int cmd_mv(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Usage: mv SOURCE DEST\n");
        printf("Rename SOURCE to DEST, or move SOURCE(s) to DIRECTORY.\n");
    }
    else
    {
        int fd;
        char *dest = NULL;

        printf("%s => %s\n", argv[1], argv[2]);

        fd = open(argv[2], O_DIRECTORY, 0);
        if (fd >= 0)
        {
            char *src;

            close(fd);

            /* it's a directory */
            dest = (char *)malloc(DFS_PATH_MAX);
            if (dest == NULL)
            {
                printf("out of memory\n");
                return -E_NOMEM;
            }

            src = argv[1] + strlen(argv[1]);
            while (src != argv[1])
            {
                if (*src == '/') break;
                src --;
            }

            snprintf(dest, DFS_PATH_MAX - 1, "%s/%s", argv[2], src);
        }
        else
        {
            fd = open(argv[2], O_RDONLY, 0);
            if (fd >= 0)
            {
                close(fd);

                unlink(argv[2]);
            }

            dest = argv[2];
        }

        rename(argv[1], dest);
        if (dest != NULL && dest != argv[2]) free(dest);
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_mv, __cmd_mv, Rename SOURCE to DEST.);

int cmd_cat(int argc, char **argv)
{
    int index;
    extern void cat(const char *filename);

    if (argc == 1)
    {
        printf("Usage: cat [FILE]...\n");
        printf("Concatenate FILE(s)\n");
        return 0;
    }

    for (index = 1; index < argc; index ++)
    {
        cat(argv[index]);
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_cat, __cmd_cat, Concatenate FILE(s));

static void directory_delete_for_msh(const char *pathname, char f, char v)
{
    DIR *dir = NULL;
    struct dirent *dirent = NULL;
    char *full_path;

    if (pathname == NULL)
        return;

    full_path = (char *)malloc(DFS_PATH_MAX);
    if (full_path == NULL)
        return;

    dir = opendir(pathname);
    if (dir == NULL)
    {
        if (f == 0)
        {
            printf("cannot remove '%s'\n", pathname);
        }
        free(full_path);
        return;
    }

    while (1)
    {
        dirent = readdir(dir);
        if (dirent == NULL)
            break;
        if (strcmp(".", dirent->d_name) != 0 &&
            strcmp("..", dirent->d_name) != 0)
        {
            sprintf(full_path, "%s/%s", pathname, dirent->d_name);
            if (dirent->d_type == DT_REG)
            {
                if (unlink(full_path) != 0)
                {
                    if (f == 0)
                        printf("cannot remove '%s'\n", full_path);
                }
                else if (v)
                {
                    printf("removed '%s'\n", full_path);
                }
            }
            else if (dirent->d_type == DT_DIR)
            {
                directory_delete_for_msh(full_path, f, v);
            }
        }
    }
    closedir(dir);
    free(full_path);
    if (unlink(pathname) != 0)
    {
        if (f == 0)
            printf("cannot remove '%s'\n", pathname);
    }
    else if (v)
    {
        printf("removed directory '%s'\n", pathname);
    }
}

int cmd_rm(int argc, char **argv)
{
    int index, n;
    char f = 0, r = 0, v = 0;

    if (argc == 1)
    {
        printf("Usage: rm option(s) FILE...\n");
        printf("Remove (unlink) the FILE(s).\n");
        return 0;
    }

    if (argv[1][0] == '-')
    {
        for (n = 0; argv[1][n]; n++)
        {
            switch (argv[1][n])
            {
                case 'f': f = 1; break;
                case 'r': r = 1; break;
                case 'v': v = 1; break;
                case '-': break;
                default:
                    printf("Error: Bad option: %c\n", argv[1][n]);
                    return 0;
            }
        }
        argc -= 1;
        argv = argv + 1;
    }

    for (index = 1; index < argc; index ++)
    {
        struct stat s;
        if (stat (argv[index], &s) == 0)
        {
            if (s.st_mode & S_IFDIR)
            {
                if (r == 0)
                    printf("cannot remove '%s': Is a directory\n", argv[index]);
                else
                    directory_delete_for_msh(argv[index], f, v);
            }
            else if (s.st_mode & S_IFREG)
            {
                if (unlink(argv[index]) != 0)
                {
                    if (f == 0)
                        printf("cannot remove '%s'\n", argv[index]);
                }
                else if (v)
                {
                    printf("removed '%s'\n", argv[index]);
                }
            }
        }
        else if (f == 0)
        {
            printf("cannot remove '%s': No such file or directory\n", argv[index]);
        }
    }
    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_rm, __cmd_rm, Remove(unlink) the FILE(s).);

#ifdef DFS_USING_WORKDIR
int cmd_cd(int argc, char **argv)
{
    if (argc == 1)
    {
        printf("%s\n", working_directory);
    }
    else if (argc == 2)
    {
        if (chdir(argv[1]) != 0)
        {
            printf("No such directory: %s\n", argv[1]);
        }
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_cd, __cmd_cd, Change the shell working directory.);

int cmd_pwd(int argc, char **argv)
{
    printf("%s\n", working_directory);
    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_pwd, __cmd_pwd, Print the name of the current working directory.);
#endif

int cmd_mkdir(int argc, char **argv)
{
    if (argc == 1)
    {
        printf("Usage: mkdir [OPTION] DIRECTORY\n");
        printf("Create the DIRECTORY, if they do not already exist.\n");
    }
    else
    {
        mkdir(argv[1], 0);
    }

    return 0;
}

int cmd_mkfs(int argc, char **argv)
{
    int result = 0;
    char *type = "elm"; /* use the default file system type as 'fatfs' */

    if (argc == 2)
    {
        result = dfs_mkfs(type, argv[1]);
    }
    else if (argc == 4)
    {
        if (strcmp(argv[1], "-t") == 0)
        {
            type = argv[2];
            result = dfs_mkfs(type, argv[3]);
        }
    }
    else
    {
        printf("Usage: mkfs [-t type] device\n");
        return 0;
    }

    if (result != E_OK)
    {
        printf("mkfs failed, result=%d\n", result);
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_mkfs, __cmd_mkfs, format disk with file system);

extern int df(const char *path);
int cmd_df(int argc, char** argv)
{
    if (argc != 2)
    {
        df("/");
    }
    else
    {
        if ((strcmp(argv[1], "--help") == 0) || (strcmp(argv[1], "-h") == 0))
        {
            printf("df [path]\n");
        }
        else
        {
            df(argv[1]);
        }
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_df, __cmd_df, disk free);

int cmd_echo(int argc, char** argv)
{
    if (argc == 2)
    {
        printf("%s\n", argv[1]);
    }
    else if (argc == 3)
    {
        int fd;

        fd = open(argv[2], O_RDWR | O_APPEND | O_CREAT, 0);
        if (fd >= 0)
        {
            write (fd, argv[1], strlen(argv[1]));
            close(fd);
        }
        else
        {
            printf("open file:%s failed!\n", argv[2]);
        }
    }
    else
    {
        printf("Usage: echo \"string\" [filename]\n");
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_echo, __cmd_echo, echo string to file);

#endif /* defined(FINSH_USING_MSH) && defined(RT_USING_DFS) */

