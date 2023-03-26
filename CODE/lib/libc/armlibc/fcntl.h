#ifndef FCNTL_H__
#define FCNTL_H__

#include <dfs_posix.h>
#include <sys/fcntl.h>

#ifndef O_NONBLOCK
#define O_NONBLOCK   0x4000
#endif

#if defined(_WIN32)
#define O_ACCMODE   (_O_RDONLY | _O_WRONLY | _O_RDWR)
#endif

#ifndef F_GETFL
#define F_GETFL  3
#endif
#ifndef F_SETFL
#define F_SETFL  4
#endif

#ifndef O_DIRECTORY
#define O_DIRECTORY 0x200000
#endif

#ifndef O_BINARY
#ifdef  _O_BINARY
#define O_BINARY _O_BINARY
#else
#define O_BINARY	     0
#endif
#endif

#endif
