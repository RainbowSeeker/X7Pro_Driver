// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#include "mem.h"
#include "common.h"

static inline void *_malloc(size_t size)
{
    return MALLOC(size);
}

static inline void _free(void *mem)
{
    FREE(mem);
}

void *_calloc(size_t count, size_t size)
{
    void *p;

    /* allocate 'count' objects of size 'size' */
    p = malloc(count * size);
    if (p) {
        /* zero the memory */
        memset(p, 0, count * size);
    }
    return p;
}

void *_realloc(void *mem, size_t newsize)
{
    if (newsize == 0) {
        free(mem);
        return NULL;
    }

    void *p;
    p = malloc(newsize);
    if (p) {
        /* zero the memory */
        if (mem != NULL) {
            memcpy(p, mem, newsize);
            free(mem);
        }
    }
    return p;
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
void *_memset(void *s, int c, size_t count)
{
#ifdef USING_TINY_SIZE
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
void *_memcpy(void *dst, const void *src, size_t count)
{
#ifdef USING_TINY_SIZE
    char *tmp = (char *)dst, *s = (char *)src;
    size_t len;

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
void *_memmove(void *dest, const void *src, size_t n)
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
int32_t _memcmp(const void *cs, const void *ct, size_t count)
{
    const unsigned char *su1, *su2;
    int res = 0;

    for (su1 = (const unsigned char *)cs, su2 = (const unsigned char *)ct; 0 < count; ++su1, ++su2, count--)
        if ((res = *su1 - *su2) != 0)
            break;

    return res;
}


#include <sys/types.h>
void *malloc(size_t) __attribute__((weak, alias("_malloc")));
void free(void *) __attribute__((weak, alias("_free")));
void *calloc(size_t, size_t) __attribute__((weak, alias("_calloc")));
void *realloc(void *, size_t) __attribute__((weak, alias("_realloc")));

void *memset(void *, int , size_t) __attribute__((weak, alias("_memset")));
void *memcpy(void *, const void *, size_t) __attribute__((weak, alias("_memcpy")));
void *memmove(void *, const void *, size_t) __attribute__((weak, alias("_memmove")));
int   memcmp(const void *, const void *, size_t) __attribute__((weak, alias("_memcmp")));

#ifdef RT_USING_FINSH
#include <finsh.h>

static size_t mem_size = configTOTAL_HEAP_SIZE;
static size_t used_mem, max_mem;

void list_mem(void)
{
    HeapStats_t stat;
    vPortGetHeapStats(&stat);

    printf("total memory: %d\n", mem_size);
    printf("used memory : %d\n", mem_size - stat.xAvailableHeapSpaceInBytes);
    printf("maximum allocated memory: %d\n", mem_size - stat.xMinimumEverFreeBytesRemaining);
}
#endif