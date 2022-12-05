#ifndef __DFS_POSIX_H__
#define __DFS_POSIX_H__

#include "dfs_file.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DIR dfs_dir_t

typedef struct
{
    int fd;     /* directory file */
    char buf[512];
    int num;
    int cur;
} DIR;

/* directory api*/
int mkdir(const char *path, mode_t mode);
DIR *opendir(const char *name);
struct dirent *readdir(DIR *d);
long telldir(DIR *d);
void seekdir(DIR *d, off_t offset);
void rewinddir(DIR *d);
int closedir(DIR *d);

/* file api*/
int open(const char *file, int flags, ...);
int close(int d);

#if defined(RT_USING_NEWLIB) && defined(_EXFUN)
_READ_WRITE_RETURN_TYPE _EXFUN(read, (int __fd, void *__buf, size_t __nbyte));
_READ_WRITE_RETURN_TYPE _EXFUN(write, (int __fd, const void *__buf, size_t __nbyte));
#else
int read(int fd, void *buf, size_t len);
int write(int fd, const void *buf, size_t len);
#endif

off_t lseek(int fd, off_t offset, int whence);
int rename(const char *from, const char *to);
int unlink(const char *pathname);
int stat(const char *file, struct stat *buf);
int fstat(int fildes, struct stat *buf);
int fsync(int fildes);
int fcntl(int fildes, int cmd, ...);
int ioctl(int fildes, int cmd, ...);
int ftruncate(int fd, off_t length);

/* directory api*/
int rmdir(const char *path);
int chdir(const char *path);
char *getcwd(char *buf, size_t size);

/* file system api */
int statfs(const char *path, struct statfs *buf);

int access(const char *path, int amode);
int pipe(int fildes[2]);
int mkfifo(const char *path, mode_t mode);

#ifdef __cplusplus
}
#endif

#endif
