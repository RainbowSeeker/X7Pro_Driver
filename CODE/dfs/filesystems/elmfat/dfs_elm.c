#include "ffconf.h"
#include "ff.h"
#include <string.h>
#include <time.h>

/* ELM FatFs provide a DIR struct */
#define HAVE_DIR_STRUCTURE

#define DT_UNKNOWN           0x00
#define DT_REG               0x01
#define DT_DIR               0x02

#include <dfs_fs.h>
#include <dfs_file.h>

static device_t disk[FF_VOLUMES] = {0};

static int elm_result_to_dfs(FRESULT result)
{
    int status = E_OK;

    switch (result)
    {
    case FR_OK:
        break;

    case FR_NO_FILE:
    case FR_NO_PATH:
    case FR_NO_FILESYSTEM:
        status = -ENOENT;
        break;

    case FR_INVALID_NAME:
        status = -EINVAL;
        break;

    case FR_EXIST:
    case FR_INVALID_OBJECT:
        status = -EEXIST;
        break;

    case FR_DISK_ERR:
    case FR_NOT_READY:
    case FR_INT_ERR:
        status = -E_IO;
        break;

    case FR_WRITE_PROTECTED:
    case FR_DENIED:
        status = -EROFS;
        break;

    case FR_MKFS_ABORTED:
        status = -EINVAL;
        break;

    default:
        status = -1;
        break;
    }

    return status;
}

/* results:
 *  -1, no space to install fatfs driver
 *  >= 0, there is an space to install fatfs driver
 */
static int get_disk(device_t id)
{
    int index;

    for (index = 0; index < FF_VOLUMES; index ++)
    {
        if (disk[index] == id)
            return index;
    }

    return -1;
}

int dfs_elm_mount(struct dfs_filesystem *fs, unsigned long rwflag, const void *data)
{
    FATFS *fat;
    FRESULT result;
    int index;
    struct device_blk_geometry geometry;
    char logic_nbr[3] = {'0',':', 0};

    /* get an empty position */
    index = get_disk(NULL);
    if (index == -1)
        return -ENOENT;
    logic_nbr[0] = '0' + index;

    /* save device */
    disk[index] = fs->dev_id;
    /* check sector size */
    if (device_control(fs->dev_id, DEVICE_CTRL_BLK_GETGEOME, &geometry) == E_OK)
    {
        if (geometry.bytes_per_sector > FF_MAX_SS)
        {
            printf("The sector size of device is greater than the sector size of FAT.\n");
            return -EINVAL;
        }
    }

    fat = (FATFS *)malloc(sizeof(FATFS));
    if (fat == NULL)
    {
        disk[index] = NULL;
        return -ENOMEM;
    }

    /* mount fatfs, always 0 logic driver */
    result = f_mount(fat, (const TCHAR *)logic_nbr, 1);
    if (result == FR_OK)
    {
        char drive[8];
        DIR *dir;

        snprintf(drive, sizeof(drive), "%d:/", index);
        dir = (DIR *)malloc(sizeof(DIR));
        if (dir == NULL)
        {
            f_mount(NULL, (const TCHAR *)logic_nbr, 1);
            disk[index] = NULL;
            free(fat);
            return -ENOMEM;
        }

        /* open the root directory to test whether the fatfs is valid */
        result = f_opendir(dir, drive);
        if (result != FR_OK)
            goto __err;

        /* mount succeed! */
        fs->data = fat;
        free(dir);
        return 0;
    }

__err:
    f_mount(NULL, (const TCHAR *)logic_nbr, 1);
    disk[index] = NULL;
    free(fat);
    return elm_result_to_dfs(result);
}

int dfs_elm_unmount(struct dfs_filesystem *fs)
{
    FATFS *fat;
    FRESULT result;
    int  index;
    char logic_nbr[3] = {'0',':', 0};

    fat = (FATFS *)fs->data;

    ASSERT(fat != NULL);

    /* find the device index and then umount it */
    index = get_disk(fs->dev_id);
    if (index == -1) /* not found */
        return -ENOENT;

    logic_nbr[0] = '0' + index;
    result = f_mount(NULL, logic_nbr, (BYTE)0);
    if (result != FR_OK)
        return elm_result_to_dfs(result);

    fs->data = NULL;
    disk[index] = NULL;
    free(fat);

    return E_OK;
}

int dfs_elm_mkfs(device_t dev_id)
{
#define FSM_STATUS_INIT            0
#define FSM_STATUS_USE_TEMP_DRIVER 1
    FATFS *fat = NULL;
    BYTE *work;
    int flag;
    FRESULT result;
    int index;
    char logic_nbr[3] = {'0',':', 0};
    MKFS_PARM opt;

    work = malloc(FF_MAX_SS);
    if(NULL == work) {
        return -ENOMEM;
    }

    if (dev_id == NULL)
    {
        free(work); /* release memory */
        return -EINVAL;
    }

    /* if the device is already mounted, then just do mkfs to the drv,
     * while if it is not mounted yet, then find an empty drive to do mkfs
     */

    flag = FSM_STATUS_INIT;
    index = get_disk(dev_id);
    if (index == -1)
    {
        /* not found the device id */
        index = get_disk(NULL);
        if (index == -1)
        {
            /* no space to store an temp driver */
            printf("sorry, there is no space to do mkfs! \n");
            free(work); /* release memory */
            return -ENOSPC;
        }
        else
        {
            fat = (FATFS *)malloc(sizeof(FATFS));
            if (fat == NULL)
            {
                free(work); /* release memory */
                return -ENOMEM;
            }

            flag = FSM_STATUS_USE_TEMP_DRIVER;

            disk[index] = dev_id;
            /* try to open device */
            device_open(dev_id, DEVICE_OFLAG_RDWR);

            /* just fill the FatFs[vol] in ff.c, or mkfs will failded!
             * consider this condition: you just umount the elm fat,
             * then the space in FatFs[index] is released, and now do mkfs
             * on the disk, you will get a failure. so we need f_mount here,
             * just fill the FatFS[index] in elm fatfs to make mkfs work.
             */
            logic_nbr[0] = '0' + index;
            f_mount(fat, logic_nbr, (BYTE)index);
        }
    }
    else
    {
        logic_nbr[0] = '0' + index;
    }

    /* [IN] Logical drive number */
    /* [IN] Format options */
    /* [-]  Working buffer */
    /* [IN] Size of working buffer */
    memset(&opt, 0, sizeof(opt));
    opt.fmt = FM_ANY|FM_SFD;
    result = f_mkfs(logic_nbr, &opt, work, FF_MAX_SS);
    free(work); work = NULL;

    /* check flag status, we need clear the temp driver stored in disk[] */
    if (flag == FSM_STATUS_USE_TEMP_DRIVER)
    {
        free(fat);
        f_mount(NULL, logic_nbr, (BYTE)index);
        disk[index] = NULL;
        /* close device */
        device_close(dev_id);
    }

    if (result != FR_OK)
    {
        printf("format error, result=%d\n", result);
        return elm_result_to_dfs(result);
    }

    return E_OK;
}

int dfs_elm_statfs(struct dfs_filesystem *fs, struct statfs *buf)
{
    FATFS *f;
    FRESULT res;
    char driver[4];
    DWORD fre_clust, fre_sect, tot_sect;

    ASSERT(fs != NULL);
    ASSERT(buf != NULL);

    f = (FATFS *)fs->data;

    snprintf(driver, sizeof(driver), "%d:", f->pdrv);
    res = f_getfree(driver, &fre_clust, &f);
    if (res)
        return elm_result_to_dfs(res);

    /* Get total sectors and free sectors */
    tot_sect = (f->n_fatent - 2) * f->csize;
    fre_sect = fre_clust * f->csize;

    buf->f_bfree = fre_sect;
    buf->f_blocks = tot_sect;
#if FF_MAX_SS != 512
    buf->f_bsize = f->ssize;
#else
    buf->f_bsize = 512;
#endif

    return 0;
}

int dfs_elm_open(struct dfs_fd *file)
{
    FIL *fd;
    BYTE mode;
    FRESULT result;
    char *drivers_fn;

#if (FF_VOLUMES > 1)
    int vol;
    struct dfs_filesystem *fs = (struct dfs_filesystem *)file->data;
    extern int elm_get_vol(FATFS * fat);

    if (fs == NULL)
        return -ENOENT;

    /* add path for ELM FatFS driver support */
    vol = elm_get_vol((FATFS *)fs->data);
    if (vol < 0)
        return -ENOENT;
    drivers_fn = (char *)malloc(256);
    if (drivers_fn == NULL)
        return -ENOMEM;

    snprintf(drivers_fn, 256, "%d:%s", vol, file->path);
#else
    drivers_fn = file->path;
#endif

    if (file->flags & O_DIRECTORY)
    {
        DIR *dir;

        if (file->flags & O_CREAT)
        {
            result = f_mkdir(drivers_fn);
            if (result != FR_OK)
            {
#if FF_VOLUMES > 1
                free(drivers_fn);
#endif
                return elm_result_to_dfs(result);
            }
        }

        /* open directory */
        dir = (DIR *)malloc(sizeof(DIR));
        if (dir == NULL)
        {
#if FF_VOLUMES > 1
            free(drivers_fn);
#endif
            return -ENOMEM;
        }

        result = f_opendir(dir, drivers_fn);
#if FF_VOLUMES > 1
        free(drivers_fn);
#endif
        if (result != FR_OK)
        {
            free(dir);
            return elm_result_to_dfs(result);
        }

        file->data = dir;
        return E_OK;
    }
    else
    {
        mode = FA_READ;

        if (file->flags & O_WRONLY)
            mode |= FA_WRITE;
        if ((file->flags & O_ACCMODE) & O_RDWR)
            mode |= FA_WRITE;
        /* Opens the file, if it is existing. If not, a new file is created. */
        if (file->flags & O_CREAT)
            mode |= FA_OPEN_ALWAYS;
        /* Creates a new file. If the file is existing, it is truncated and overwritten. */
        if (file->flags & O_TRUNC)
            mode |= FA_CREATE_ALWAYS;
        /* Creates a new file. The function fails if the file is already existing. */
        if (file->flags & O_EXCL)
            mode |= FA_CREATE_NEW;

        /* allocate a fd */
        fd = (FIL *)malloc(sizeof(FIL));
        if (fd == NULL)
        {
#if FF_VOLUMES > 1
            free(drivers_fn);
#endif
            return -ENOMEM;
        }

        result = f_open(fd, drivers_fn, mode);
#if FF_VOLUMES > 1
        free(drivers_fn);
#endif
        if (result == FR_OK)
        {
            file->pos  = fd->fptr;
            file->size = f_size(fd);
            file->data = fd;

            if (file->flags & O_APPEND)
            {
                /* seek to the end of file */
                f_lseek(fd, f_size(fd));
                file->pos = fd->fptr;
            }
        }
        else
        {
            /* open failed, return */
            free(fd);
            return elm_result_to_dfs(result);
        }
    }

    return E_OK;
}

int dfs_elm_close(struct dfs_fd *file)
{
    FRESULT result;

    result = FR_OK;
    if (file->type == FT_DIRECTORY)
    {
        DIR *dir;

        dir = (DIR *)(file->data);
        ASSERT(dir != NULL);

        /* release memory */
        free(dir);
    }
    else if (file->type == FT_REGULAR)
    {
        FIL *fd;
        fd = (FIL *)(file->data);
        ASSERT(fd != NULL);

        result = f_close(fd);
        if (result == FR_OK)
        {
            /* release memory */
            free(fd);
        }
    }

    return elm_result_to_dfs(result);
}

int dfs_elm_ioctl(struct dfs_fd *file, int cmd, void *args)
{
    switch (cmd)
    {
    case RT_FIOFTRUNCATE:
        {
            FIL *fd;
            FSIZE_t fptr, length;
            FRESULT result = FR_OK;
            fd = (FIL *)(file->data);
            ASSERT(fd != NULL);

            /* save file read/write point */
            fptr = fd->fptr;
            length = *(off_t*)args;
            if (length <= fd->obj.objsize)
            {
                fd->fptr = length;
                result = f_truncate(fd);
            }
            else
            {
                result = f_lseek(fd, length);
            }
            /* restore file read/write point */
            fd->fptr = fptr;
            return elm_result_to_dfs(result);
        }
    }
    return -ENOSYS;
}

int dfs_elm_read(struct dfs_fd *file, void *buf, size_t len)
{
    FIL *fd;
    FRESULT result;
    UINT byte_read;

    if (file->type == FT_DIRECTORY)
    {
        return -EISDIR;
    }

    fd = (FIL *)(file->data);
    ASSERT(fd != NULL);

    result = f_read(fd, buf, len, &byte_read);
    /* update position */
    file->pos  = fd->fptr;
    if (result == FR_OK)
        return byte_read;

    return elm_result_to_dfs(result);
}

int dfs_elm_write(struct dfs_fd *file, const void *buf, size_t len)
{
    FIL *fd;
    FRESULT result;
    UINT byte_write;

    if (file->type == FT_DIRECTORY)
    {
        return -EISDIR;
    }

    fd = (FIL *)(file->data);
    ASSERT(fd != NULL);

    result = f_write(fd, buf, len, &byte_write);
    /* update position and file size */
    file->pos  = fd->fptr;
    file->size = f_size(fd);
    if (result == FR_OK)
        return byte_write;

    return elm_result_to_dfs(result);
}

int dfs_elm_flush(struct dfs_fd *file)
{
    FIL *fd;
    FRESULT result;

    fd = (FIL *)(file->data);
    ASSERT(fd != NULL);

    result = f_sync(fd);
    return elm_result_to_dfs(result);
}

int dfs_elm_lseek(struct dfs_fd *file, off_t offset)
{
    FRESULT result = FR_OK;
    if (file->type == FT_REGULAR)
    {
        FIL *fd;

        /* regular file type */
        fd = (FIL *)(file->data);
        ASSERT(fd != NULL);

        result = f_lseek(fd, offset);
        if (result == FR_OK)
        {
            /* return current position */
            file->pos = fd->fptr;
            return fd->fptr;
        }
    }
    else if (file->type == FT_DIRECTORY)
    {
        /* which is a directory */
        DIR *dir;

        dir = (DIR *)(file->data);
        ASSERT(dir != NULL);

        result = f_seekdir(dir, offset / sizeof(struct dirent));
        if (result == FR_OK)
        {
            /* update file position */
            file->pos = offset;
            return file->pos;
        }
    }

    return elm_result_to_dfs(result);
}

int dfs_elm_getdents(struct dfs_fd *file, struct dirent *dirp, uint32_t count)
{
    DIR *dir;
    FILINFO fno;
    FRESULT result;
    uint32_t index;
    struct dirent *d;

    dir = (DIR *)(file->data);
    ASSERT(dir != NULL);

    /* make integer count */
    count = (count / sizeof(struct dirent)) * sizeof(struct dirent);
    if (count == 0)
        return -EINVAL;

    index = 0;
    while (1)
    {
        char *fn;

        d = dirp + index;

        result = f_readdir(dir, &fno);
        if (result != FR_OK || fno.fname[0] == 0)
            break;

#if FF_USE_LFN
        fn = *fno.fname ? fno.fname : fno.altname;
#else
        fn = fno.fname;
#endif

        d->d_type = DT_UNKNOWN;
        if (fno.fattrib & AM_DIR)
            d->d_type = DT_DIR;
        else
            d->d_type = DT_REG;

        d->d_namlen = (uint8_t)strlen(fn);
        d->d_reclen = (uint16_t)sizeof(struct dirent);
        strncpy(d->d_name, fn, strlen(fn) + 1);

        index ++;
        if (index * sizeof(struct dirent) >= count)
            break;
    }

    if (index == 0)
        return elm_result_to_dfs(result);

    file->pos += index * sizeof(struct dirent);

    return index * sizeof(struct dirent);
}

int dfs_elm_unlink(struct dfs_filesystem *fs, const char *path)
{
    FRESULT result;

#if FF_VOLUMES > 1
    int vol;
    char *drivers_fn;
    extern int elm_get_vol(FATFS * fat);

    /* add path for ELM FatFS driver support */
    vol = elm_get_vol((FATFS *)fs->data);
    if (vol < 0)
        return -ENOENT;
    drivers_fn = (char *)malloc(256);
    if (drivers_fn == NULL)
        return -ENOMEM;

    snprintf(drivers_fn, 256, "%d:%s", vol, path);
#else
    const char *drivers_fn;
    drivers_fn = path;
#endif

    result = f_unlink(drivers_fn);
#if FF_VOLUMES > 1
    free(drivers_fn);
#endif
    return elm_result_to_dfs(result);
}

int dfs_elm_rename(struct dfs_filesystem *fs, const char *oldpath, const char *newpath)
{
    FRESULT result;

#if FF_VOLUMES > 1
    char *drivers_oldfn;
    const char *drivers_newfn;
    int vol;
    extern int elm_get_vol(FATFS * fat);

    /* add path for ELM FatFS driver support */
    vol = elm_get_vol((FATFS *)fs->data);
    if (vol < 0)
        return -ENOENT;

    drivers_oldfn = (char *)malloc(256);
    if (drivers_oldfn == NULL)
        return -ENOMEM;
    drivers_newfn = newpath;

    snprintf(drivers_oldfn, 256, "%d:%s", vol, oldpath);
#else
    const char *drivers_oldfn, *drivers_newfn;

    drivers_oldfn = oldpath;
    drivers_newfn = newpath;
#endif

    result = f_rename(drivers_oldfn, drivers_newfn);
#if FF_VOLUMES > 1
    free(drivers_oldfn);
#endif
    return elm_result_to_dfs(result);
}

int dfs_elm_stat(struct dfs_filesystem *fs, const char *path, struct stat *st)
{
    FILINFO file_info;
    FRESULT result;

#if FF_VOLUMES > 1
    int vol;
    char *drivers_fn;
    extern int elm_get_vol(FATFS * fat);

    /* add path for ELM FatFS driver support */
    vol = elm_get_vol((FATFS *)fs->data);
    if (vol < 0)
        return -ENOENT;
    drivers_fn = (char *)malloc(256);
    if (drivers_fn == NULL)
        return -ENOMEM;

    snprintf(drivers_fn, 256, "%d:%s", vol, path);
#else
    const char *drivers_fn;
    drivers_fn = path;
#endif

    result = f_stat(drivers_fn, &file_info);
#if FF_VOLUMES > 1
    free(drivers_fn);
#endif
    if (result == FR_OK)
    {
        /* convert to dfs stat structure */
        st->st_dev = 0;

        st->st_mode = S_IFREG | S_IRUSR | S_IRGRP | S_IROTH |
                      S_IWUSR | S_IWGRP | S_IWOTH;
        if (file_info.fattrib & AM_DIR)
        {
            st->st_mode &= ~S_IFREG;
            st->st_mode |= S_IFDIR | S_IXUSR | S_IXGRP | S_IXOTH;
        }
        if (file_info.fattrib & AM_RDO)
            st->st_mode &= ~(S_IWUSR | S_IWGRP | S_IWOTH);

        st->st_size  = file_info.fsize;

        /* get st_mtime. */
        {
            struct tm tm_file;
            int year, mon, day, hour, min, sec;
            WORD tmp;

            tmp = file_info.fdate;
            day = tmp & 0x1F;           /* bit[4:0] Day(1..31) */
            tmp >>= 5;
            mon = tmp & 0x0F;           /* bit[8:5] Month(1..12) */
            tmp >>= 4;
            year = (tmp & 0x7F) + 1980; /* bit[15:9] Year origin from 1980(0..127) */

            tmp = file_info.ftime;
            sec = (tmp & 0x1F) * 2;     /* bit[4:0] Second/2(0..29) */
            tmp >>= 5;
            min = tmp & 0x3F;           /* bit[10:5] Minute(0..59) */
            tmp >>= 6;
            hour = tmp & 0x1F;          /* bit[15:11] Hour(0..23) */

            memset(&tm_file, 0, sizeof(tm_file));
            tm_file.tm_year = year - 1900; /* Years since 1900 */
            tm_file.tm_mon  = mon - 1;     /* Months *since* january: 0-11 */
            tm_file.tm_mday = day;         /* Day of the month: 1-31 */
            tm_file.tm_hour = hour;        /* Hours since midnight: 0-23 */
            tm_file.tm_min  = min;         /* Minutes: 0-59 */
            tm_file.tm_sec  = sec;         /* Seconds: 0-59 */

            st->st_mtime = mktime(&tm_file);
        } /* get st_mtime. */
    }

    return elm_result_to_dfs(result);
}

static const struct dfs_file_ops dfs_elm_fops =
{
    dfs_elm_open,
    dfs_elm_close,
    dfs_elm_ioctl,
    dfs_elm_read,
    dfs_elm_write,
    dfs_elm_flush,
    dfs_elm_lseek,
    dfs_elm_getdents,
    NULL, /* poll interface */
};

static const struct dfs_filesystem_ops dfs_elm =
{
    "elm",
    DFS_FS_FLAG_DEFAULT,
    &dfs_elm_fops,

    dfs_elm_mount,
    dfs_elm_unmount,
    dfs_elm_mkfs,
    dfs_elm_statfs,

    dfs_elm_unlink,
    dfs_elm_stat,
    dfs_elm_rename,
};

int elm_init(void)
{
    /* register fatfs file system */
    dfs_register(&dfs_elm);

    return 0;
}

/*
 * RT-Thread Device Interface for ELM FatFs
 */
#include "diskio.h"

/* Initialize a Drive */
 DSTATUS disk_initialize(BYTE drv)
{
    return 0;
}

/* Return Disk Status */
 DSTATUS disk_status(BYTE drv)
{
    return 0;
}

/* Read Sector(s) */
 DRESULT disk_read(BYTE drv, BYTE *buff, DWORD sector, UINT count)
{
    size_t result;
    device_t device = disk[drv];

    result = device_read(device, sector, buff, count);
    if (result == count)
    {
        return RES_OK;
    }

    return RES_ERROR;
}

/* Write Sector(s) */
 DRESULT disk_write(BYTE drv, const BYTE *buff, DWORD sector, UINT count)
{
    size_t result;
    device_t device = disk[drv];

    result = device_write(device, sector, buff, count);
    if (result == count)
    {
        return RES_OK;
    }

    return RES_ERROR;
}

/* Miscellaneous Functions */
 DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void *buff)
{
    device_t device = disk[drv];

    if (device == NULL)
        return RES_ERROR;

    if (ctrl == GET_SECTOR_COUNT)
    {
        struct device_blk_geometry geometry;

        memset(&geometry, 0, sizeof(geometry));
        device_control(device, DEVICE_CTRL_BLK_GETGEOME, &geometry);

        *(DWORD *)buff = geometry.sector_count;
        if (geometry.sector_count == 0)
            return RES_ERROR;
    }
    else if (ctrl == GET_SECTOR_SIZE)
    {
        struct device_blk_geometry geometry;

        memset(&geometry, 0, sizeof(geometry));
        device_control(device, DEVICE_CTRL_BLK_GETGEOME, &geometry);

        *(WORD *)buff = (WORD)(geometry.bytes_per_sector);
    }
    else if (ctrl == GET_BLOCK_SIZE) /* Get erase block size in unit of sectors (DWORD) */
    {
        struct device_blk_geometry geometry;

        memset(&geometry, 0, sizeof(geometry));
        device_control(device, DEVICE_CTRL_BLK_GETGEOME, &geometry);

        *(DWORD *)buff = geometry.block_size / geometry.bytes_per_sector;
    }
    else if (ctrl == CTRL_SYNC)
    {
        device_control(device, DEVICE_CTRL_BLK_SYNC, NULL);
    }
    else if (ctrl == CTRL_TRIM)
    {
        device_control(device, DEVICE_CTRL_BLK_ERASE, buff);
    }

    return RES_OK;
}

 DWORD get_fattime(void)
{
    DWORD fat_time = 0;

#ifdef RT_USING_LIBC
    time_t now;
    struct tm *p_tm;
    struct tm tm_now;

    /* get current time */
    now = time(NULL);

    /* lock scheduler. */
    OS_ENTER_CRITICAL();
    /* converts calendar time time into local time. */
    p_tm = localtime(&now);
    /* copy the statically located variable */
    memcpy(&tm_now, p_tm, sizeof(struct tm));
    /* unlock scheduler. */
    OS_EXIT_CRITICAL();

    fat_time = (DWORD)(tm_now.tm_year - 80) << 25 |
               (DWORD)(tm_now.tm_mon + 1)   << 21 |
               (DWORD)tm_now.tm_mday        << 16 |
               (DWORD)tm_now.tm_hour        << 11 |
               (DWORD)tm_now.tm_min         <<  5 |
               (DWORD)tm_now.tm_sec / 2 ;
#endif /* RT_USING_LIBC  */

    return fat_time;
}

#if FF_FS_REENTRANT
 int ff_cre_syncobj(BYTE drv, FF_SYNC_t *m)
{
    char name[8];
    os_mutex_t mutex;

    snprintf(name, sizeof(name), "fat%d", drv);
    os_mutex_init(&mutex);
    if (mutex != NULL)
    {
        *m = mutex;
        return TRUE;
    }

    return FALSE;
}

 int ff_del_syncobj(FF_SYNC_t m)
{
    if (m != NULL)
        os_mutex_delete(m);

    return TRUE;
}

 int ff_req_grant(FF_SYNC_t m)
{
    if (os_mutex_take(m, FF_FS_TIMEOUT) == E_OK)
        return TRUE;

    return FALSE;
}

 void ff_rel_grant(FF_SYNC_t m)
{
    os_mutex_release(m);
}

#endif

/* Memory functions */
#if FF_USE_LFN == 3
/* Allocate memory block */
 void *ff_memalloc(UINT size)
{
    return malloc(size);
}

/* Free memory block */
 void ff_memfree(void *mem)
{
    free(mem);
}
#endif /* FF_USE_LFN == 3 */

