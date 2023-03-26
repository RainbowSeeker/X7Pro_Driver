// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/4.
//
#include "common.h"
#include "rtconfig.h"
#include "device.h"

/* use precision */
#define PRINTF_PRECISION

/**
 * @addtogroup KernelService
 */

/**@{*/

/* global errno */
static volatile int __os_errno;

#if defined(RT_USING_DEVICE) && defined(RT_USING_CONSOLE)
static device_t _console_device = NULL;
#endif

/*
 * This function will get errno
 *
 * @return errno
 */
err_t os_get_errno(void)
{
    os_thread_t tid;

    if (os_interrupt_get_nest() != 0)
    {
        /* it's in interrupt context */
        return __os_errno;
    }

    tid = os_thread_self();
    if (tid == NULL)
        return __os_errno;

    return tid->error;
}

/*
 * This function will set errno
 *
 * @param error the errno shall be set
 */
void os_set_errno(err_t error)
{
    os_thread_t tid = NULL;

    if (os_interrupt_get_nest() != 0)
    {
        /* it's in interrupt context */
        __os_errno = error;

        return;
    }

    tid = os_thread_self();
    if (tid == NULL)
    {
        __os_errno = error;

        return;
    }

    tid->error = error;
}

/**
 * This function returns errno.
 *
 * @return the errno in the system
 */
int *_os_errno(void)
{
    os_thread_t tid;

    if (os_interrupt_get_nest() != 0)
        return (int *)&__os_errno;

    tid = os_thread_self();
    if (tid != NULL)
        return (int *) & (tid->error);

    return (int *)&__os_errno;
}

/**
 * This function will set the content of memory to specified value
 *
 * @param s the address of source memory
 * @param c the value shall be set in content
 * @param count the copied length
 *
 * @return the address of source memory
 */
void *__memset(void *s, int c, ubase_t count)
{
#ifdef RT_USING_TINY_SIZE
    char *xs = (char *)s;

    while (count--)
        *xs++ = c;

    return s;
#else
#define LBLOCKSIZE      (sizeof(long))
#define UNALIGNED(X)    ((long)X & (LBLOCKSIZE - 1))
#define TOO_SMALL(LEN)  ((LEN) < LBLOCKSIZE)

    unsigned int i;
    char *m = (char *)s;
    unsigned long buffer;
    unsigned long *aligned_addr;
    unsigned int d = c & 0xff;  /* To avoid sign extension, copy C to an
                                unsigned variable.  */

    if (!TOO_SMALL(count) && !UNALIGNED(s))
    {
        /* If we get this far, we know that n is large and m is word-aligned. */
        aligned_addr = (unsigned long *)s;

        /* Store D into each char sized location in BUFFER so that
         * we can set large blocks quickly.
         */
        if (LBLOCKSIZE == 4)
        {
            buffer = (d << 8) | d;
            buffer |= (buffer << 16);
        }
        else
        {
            buffer = 0;
            for (i = 0; i < LBLOCKSIZE; i ++)
                buffer = (buffer << 8) | d;
        }

        while (count >= LBLOCKSIZE * 4)
        {
            *aligned_addr++ = buffer;
            *aligned_addr++ = buffer;
            *aligned_addr++ = buffer;
            *aligned_addr++ = buffer;
            count -= 4 * LBLOCKSIZE;
        }

        while (count >= LBLOCKSIZE)
        {
            *aligned_addr++ = buffer;
            count -= LBLOCKSIZE;
        }

        /* Pick up the remainder with a bytewise loop. */
        m = (char *)aligned_addr;
    }

    while (count--)
    {
        *m++ = (char)d;
    }

    return s;

#undef LBLOCKSIZE
#undef UNALIGNED
#undef TOO_SMALL
#endif
}

/**
 * This function will copy memory content from source address to destination
 * address.
 *
 * @param dst the address of destination memory
 * @param src  the address of source memory
 * @param count the copied length
 *
 * @return the address of destination memory
 */
void *_memcpy(void *dst, const void *src, ubase_t count)
{
#ifdef RT_USING_TINY_SIZE
    char *tmp = (char *)dst, *s = (char *)src;
    ubase_t len;

    if (tmp <= s || tmp > (s + count))
    {
        while (count--)
            *tmp ++ = *s ++;
    }
    else
    {
        for (len = count; len > 0; len --)
            tmp[len - 1] = s[len - 1];
    }

    return dst;
#else

#define UNALIGNED(X, Y) \
    (((long)X & (sizeof (long) - 1)) | ((long)Y & (sizeof (long) - 1)))
#define BIGBLOCKSIZE    (sizeof (long) << 2)
#define LITTLEBLOCKSIZE (sizeof (long))
#define TOO_SMALL(LEN)  ((LEN) < BIGBLOCKSIZE)

    char *dst_ptr = (char *)dst;
    char *src_ptr = (char *)src;
    long *aligned_dst;
    long *aligned_src;
    int len = count;

    /* If the size is small, or either SRC or DST is unaligned,
    then punt into the byte copy loop.  This should be rare. */
    if (!TOO_SMALL(len) && !UNALIGNED(src_ptr, dst_ptr))
    {
        aligned_dst = (long *)dst_ptr;
        aligned_src = (long *)src_ptr;

        /* Copy 4X long words at a time if possible. */
        while (len >= BIGBLOCKSIZE)
        {
            *aligned_dst++ = *aligned_src++;
            *aligned_dst++ = *aligned_src++;
            *aligned_dst++ = *aligned_src++;
            *aligned_dst++ = *aligned_src++;
            len -= BIGBLOCKSIZE;
        }

        /* Copy one long word at a time if possible. */
        while (len >= LITTLEBLOCKSIZE)
        {
            *aligned_dst++ = *aligned_src++;
            len -= LITTLEBLOCKSIZE;
        }

        /* Pick up any residual with a byte copier. */
        dst_ptr = (char *)aligned_dst;
        src_ptr = (char *)aligned_src;
    }

    while (len--)
        *dst_ptr++ = *src_ptr++;

    return dst;
#undef UNALIGNED
#undef BIGBLOCKSIZE
#undef LITTLEBLOCKSIZE
#undef TOO_SMALL
#endif
}

/**
 * This function will move memory content from source address to destination
 * address.
 *
 * @param dest the address of destination memory
 * @param src  the address of source memory
 * @param n the copied length
 *
 * @return the address of destination memory
 */
void *_memmove(void *dest, const void *src, ubase_t n)
{
    char *tmp = (char *)dest, *s = (char *)src;

    if (s < tmp && tmp < s + n)
    {
        tmp += n;
        s += n;

        while (n--)
            *(--tmp) = *(--s);
    }
    else
    {
        while (n--)
            *tmp++ = *s++;
    }

    return dest;
}

/**
 * This function will compare two areas of memory
 *
 * @param cs one area of memory
 * @param ct another area of memory
 * @param count the size of the area
 *
 * @return the result
 */
int32_t _memcmp(const void *cs, const void *ct, ubase_t count)
{
    const unsigned char *su1, *su2;
    int res = 0;

    for (su1 = (const unsigned char *)cs, su2 = (const unsigned char *)ct; 0 < count; ++su1, ++su2, count--)
        if ((res = *su1 - *su2) != 0)
            break;

    return res;
}

/**
 * This function will return the first occurrence of a string.
 *
 * @param s1 the source string
 * @param s2 the find string
 *
 * @return the first occurrence of a s2 in s1, or NULL if no found.
 */
char *_strstr(const char *s1, const char *s2)
{
    int l1, l2;

    l2 = strlen(s2);
    if (!l2)
        return (char *)s1;
    l1 = strlen(s1);
    while (l1 >= l2)
    {
        l1 --;
        if (!memcmp(s1, s2, l2))
            return (char *)s1;
        s1 ++;
    }

    return NULL;
}

/**
 * This function will compare two strings while ignoring differences in case
 *
 * @param a the string to be compared
 * @param b the string to be compared
 *
 * @return the result
 */
int32_t _strcasecmp(const char *a, const char *b)
{
    int ca, cb;

    do
    {
        ca = *a++ & 0xff;
        cb = *b++ & 0xff;
        if (ca >= 'A' && ca <= 'Z')
            ca += 'a' - 'A';
        if (cb >= 'A' && cb <= 'Z')
            cb += 'a' - 'A';
    }
    while (ca == cb && ca != '\0');

    return ca - cb;
}

/**
 * This function will copy string no more than n bytes.
 *
 * @param dst the string to copy
 * @param src the string to be copied
 * @param n the maximum copied length
 *
 * @return the result
 */
char *_strncpy(char *dst, const char *src, ubase_t n)
{
    if (n != 0)
    {
        char *d = dst;
        const char *s = src;

        do
        {
            if ((*d++ = *s++) == 0)
            {
                /* NUL pad the remaining n-1 bytes */
                while (--n != 0)
                    *d++ = 0;
                break;
            }
        } while (--n != 0);
    }

    return (dst);
}

/**
 * This function will compare two strings with specified maximum length
 *
 * @param cs the string to be compared
 * @param ct the string to be compared
 * @param count the maximum compare length
 *
 * @return the result
 */
int32_t _strncmp(const char *cs, const char *ct, ubase_t count)
{
    register signed char __res = 0;

    while (count)
    {
        if ((__res = *cs - *ct++) != 0 || !*cs++)
            break;
        count --;
    }

    return __res;
}

/**
 * This function will compare two strings without specified length
 *
 * @param cs the string to be compared
 * @param ct the string to be compared
 *
 * @return the result
 */
int32_t _strcmp(const char *cs, const char *ct)
{
    while (*cs && *cs == *ct)
    {
        cs++;
        ct++;
    }

    return (*cs - *ct);
}


/**
 * The  strnlen()  function  returns the number of characters in the
 * string pointed to by s, excluding the terminating null byte ('\0'),
 * but at most maxlen.  In doing this, strnlen() looks only at the
 * first maxlen characters in the string pointed to by s and never
 * beyond s+maxlen.
 *
 * @param s the string
 * @param maxlen the max size
 * @return the length of string
 */
size_t _strnlen(const char *s, ubase_t maxlen)
{
    const char *sc;

    for (sc = s; *sc != '\0' && (ubase_t)(sc - s) < maxlen; ++sc) /* nothing */
        ;

    return sc - s;
}

/**
 * This function will return the length of a string, which terminate will
 * null character.
 *
 * @param s the string
 *
 * @return the length of string
 */
size_t _strlen(const char *s)
{
    const char *sc;

    for (sc = s; *sc != '\0'; ++sc) /* nothing */
        ;

    return sc - s;
}

#ifdef RT_USING_HEAP
/**
 * This function will duplicate a string.
 *
 * @param s the string to be duplicated
 *
 * @return the duplicated string pointer
 */
char *_strdup(const char *s)
{
    size_t len = strlen(s) + 1;
    char *tmp = (char *)malloc(len);

    if (!tmp)
        return NULL;

    memcpy(tmp, s, len);

    return tmp;
}

#if defined(__CC_ARM) || defined(__CLANG_ARM)
char *strdup(const char *s) __attribute__((alias("_strdup")));
#endif
#endif

/**
 * This function will show the version of rt-thread rtos
 */
void show_version(void)
{
    printf("\n >> Rain << \n\t\t  --- build %s\n", __DATE__);
}

#ifdef RT_USING_HEAP
/**
 * This function allocates a memory block, which address is aligned to the
 * specified alignment size.
 *
 * @param size the allocated memory block size
 * @param align the alignment size
 *
 * @return the allocated memory block on successful, otherwise returns NULL
 */
void *malloc_align(size_t size, size_t align)
{
    void *ptr;
    void *align_ptr;
    int uintptr_size;
    size_t align_size;

    /* sizeof pointer */
    uintptr_size = sizeof(void*);
    uintptr_size -= 1;

    /* align the alignment size to uintptr size byte */
    align = ((align + uintptr_size) & ~uintptr_size);

    /* get total aligned size */
    align_size = ((size + uintptr_size) & ~uintptr_size) + align;
    /* allocate memory block from heap */
    ptr = malloc(align_size);
    if (ptr != NULL)
    {
        /* the allocated memory block is aligned */
        if (((ubase_t)ptr & (align - 1)) == 0)
        {
            align_ptr = (void *)((ubase_t)ptr + align);
        }
        else
        {
            align_ptr = (void *)(((ubase_t)ptr + (align - 1)) & ~(align - 1));
        }

        /* set the pointer before alignment pointer to the real pointer */
        *((ubase_t *)((ubase_t)align_ptr - sizeof(void *))) = (ubase_t)ptr;

        ptr = align_ptr;
    }

    return ptr;
}

/**
 * This function release the memory block, which is allocated by
 * malloc_align function and address is aligned.
 *
 * @param ptr the memory block pointer
 */
void free_align(void *ptr)
{
    void *real_ptr;

    real_ptr = (void *) * (ubase_t *)((ubase_t)ptr - sizeof(void *));
    free(real_ptr);
}
#endif

#ifndef RT_USING_CPU_FFS
const uint8_t __lowest_bit_bitmap[] =
        {
                /* 00 */ 0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                /* 10 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                /* 20 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                /* 30 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                /* 40 */ 6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                /* 50 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                /* 60 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                /* 70 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                /* 80 */ 7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                /* 90 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                /* A0 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                /* B0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                /* C0 */ 6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                /* D0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                /* E0 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
                /* F0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
        };

/**
 * This function finds the first bit set (beginning with the least significant bit)
 * in value and return the index of that bit.
 *
 * Bits are numbered starting at 1 (the least significant bit).  A return value of
 * zero from any of these functions means that the argument was zero.
 *
 * @return return the index of the first bit set. If value is 0, then this function
 * shall return 0.
 */
int __ffs(int value)
{
    if (value == 0) return 0;

    if (value & 0xff)
        return __lowest_bit_bitmap[value & 0xff] + 1;

    if (value & 0xff00)
        return __lowest_bit_bitmap[(value & 0xff00) >> 8] + 9;

    if (value & 0xff0000)
        return __lowest_bit_bitmap[(value & 0xff0000) >> 16] + 17;

    return __lowest_bit_bitmap[(value & 0xff000000) >> 24] + 25;
}
#endif

#if defined (__GNUC__)
#include <sys/types.h>
void *memcpy(void *dest, const void *src, size_t n) __attribute__((weak, alias("_memcpy")));
void *memset(void *s, int c, size_t n) __attribute__((weak, alias("__memset")));
void *memmove(void *dest, const void *src, size_t n) __attribute__((weak, alias("_memmove")));
int   memcmp(const void *s1, const void *s2, size_t n) __attribute__((weak, alias("_memcmp")));

size_t strlen(const char *s) __attribute__((weak, alias("_strlen")));
size_t strnlen(const char *s, size_t maxlen) __attribute__((weak, alias("_strnlen")));
char *strstr(const char *s1, const char *s2) __attribute__((weak, alias("_strstr")));
int strcasecmp(const char *a, const char *b) __attribute__((weak, alias("_strcasecmp")));
char *strncpy(char *dest, const char *src, size_t n) __attribute__((weak, alias("_strncpy")));
int strncmp(const char *cs, const char *ct, size_t count) __attribute__((weak, alias("_strncmp")));
int strcmp(const char *cs, const char *ct) __attribute__((weak, alias("_strcmp")));
#ifdef RT_USING_HEAP
char *strdup(const char *s) __attribute__((weak, alias("_strdup")));
#endif
#endif




/**@}*/
