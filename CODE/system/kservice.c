// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/4.
//

#include "board_config.h"
#include "common_def.h"
#include "os_def.h"
/** note
*   Redefine system service function
*   ( Contains memory operation functions & Print function etc.)
*/

/* use precision */
#define PRINTF_PRECISION
//#define PRINTF_LONGLONG

/* the buffer size of console */
#define CONSOLEBUF_SIZE	256


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
char *_strncpy(char *dst, const char *src, size_t n)
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
int32_t _strncmp(const char *cs, const char *ct, size_t count)
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
size_t _strnlen(const char *s, size_t maxlen)
{
    const char *sc;

    for (sc = s; *sc != '\0' && (size_t)(sc - s) < maxlen; ++sc) /* nothing */
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

/* private function */
#define _ISDIGIT(c)  ((unsigned)((c) - '0') < 10)

static inline int divide(long *n, int base)
{
    int res;

    /* optimized for processor which does not support divide instructions. */
    if (base == 10)
    {
        res = (int)(((unsigned long)*n) % 10U);
        *n = (long)(((unsigned long)*n) / 10U);
    }
    else
    {
        res = (int)(((unsigned long)*n) % 16U);
        *n = (long)(((unsigned long)*n) / 16U);
    }

    return res;
}


static inline int skip_atoi(const char **s)
{
    register int i = 0;
    while (_ISDIGIT(**s))
        i = i * 10 + *((*s)++) - '0';

    return i;
}

#define ZEROPAD     (1 << 0)    /* pad with zero */
#define SIGN        (1 << 1)    /* unsigned/signed long */
#define PLUS        (1 << 2)    /* show plus */
#define SPACE       (1 << 3)    /* space if plus */
#define LEFT        (1 << 4)    /* left justified */
#define SPECIAL     (1 << 5)    /* 0x */
#define LARGE       (1 << 6)    /* use 'ABCDEF' instead of 'abcdef' */

#ifdef PRINTF_PRECISION
static char *print_number(char *buf,
                          char *end,
#ifdef PRINTF_LONGLONG
        long long  num,
#else
                          long  num,
#endif
                          int   base,
                          int   s,
                          int   precision,
                          int   type)
#else
static char *print_number(char *buf,
                          char *end,
#ifdef PRINTF_LONGLONG
        long long  num,
#else
                          long  num,
#endif
                          int   base,
                          int   s,
                          int   type)
#endif
{
    char c, sign;
#ifdef PRINTF_LONGLONG
    char tmp[32];
#else
    char tmp[16];
#endif
    int precision_bak = precision;
    const char *digits;
    static const char small_digits[] = "0123456789abcdef";
    static const char large_digits[] = "0123456789ABCDEF";
    register int i;
    register int size;

    size = s;

    digits = (type & LARGE) ? large_digits : small_digits;
    if (type & LEFT)
        type &= ~ZEROPAD;

    c = (type & ZEROPAD) ? '0' : ' ';

    /* get sign */
    sign = 0;
    if (type & SIGN)
    {
        if (num < 0)
        {
            sign = '-';
            num = -num;
        }
        else if (type & PLUS)
            sign = '+';
        else if (type & SPACE)
            sign = ' ';
    }

#ifdef PRINTF_SPECIAL
    if (type & SPECIAL)
    {
        if (base == 16)
            size -= 2;
        else if (base == 8)
            size--;
    }
#endif

    i = 0;
    if (num == 0)
        tmp[i++] = '0';
    else
    {
        while (num != 0)
            tmp[i++] = digits[divide(&num, base)];
    }

#ifdef PRINTF_PRECISION
    if (i > precision)
        precision = i;
    size -= precision;
#else
    size -= i;
#endif

    if (!(type & (ZEROPAD | LEFT)))
    {
        if ((sign) && (size > 0))
            size--;

        while (size-- > 0)
        {
            if (buf < end)
                *buf = ' ';
            ++ buf;
        }
    }

    if (sign)
    {
        if (buf < end)
        {
            *buf = sign;
        }
        -- size;
        ++ buf;
    }

#ifdef PRINTF_SPECIAL
    if (type & SPECIAL)
    {
        if (base == 8)
        {
            if (buf < end)
                *buf = '0';
            ++ buf;
        }
        else if (base == 16)
        {
            if (buf < end)
                *buf = '0';
            ++ buf;
            if (buf < end)
            {
                *buf = type & LARGE ? 'X' : 'x';
            }
            ++ buf;
        }
    }
#endif

    /* no align to the left */
    if (!(type & LEFT))
    {
        while (size-- > 0)
        {
            if (buf < end)
                *buf = c;
            ++ buf;
        }
    }

#ifdef PRINTF_PRECISION
    while (i < precision--)
    {
        if (buf < end)
            *buf = '0';
        ++ buf;
    }
#endif

    /* put number in the temporary buffer */
    while (i-- > 0 && (precision_bak != 0))
    {
        if (buf < end)
            *buf = tmp[i];
        ++ buf;
    }

    while (size-- > 0)
    {
        if (buf < end)
            *buf = ' ';
        ++ buf;
    }

    return buf;
}

int32_t _vsnprintf(char       *buf,
                     size_t   size,
                     const char *fmt,
                     va_list     args)
{
#ifdef PRINTF_LONGLONG
    unsigned long long num;
#else
    uint32_t num;
#endif
    int i, len;
    char *str, *end, c;
    const char *s;

    uint8_t base;            /* the base of number */
    uint8_t flags;           /* flags to print number */
    uint8_t qualifier;       /* 'h', 'l', or 'L' for integer fields */
    int32_t field_width;     /* width of output field */

#ifdef PRINTF_PRECISION
    int precision;      /* min. # of digits for integers and max for a string */
#endif

    str = buf;
    end = buf + size;

    /* Make sure end is always >= buf */
    if (end < buf)
    {
        end  = ((char *) - 1);
        size = end - buf;
    }

    for (; *fmt ; ++fmt)
    {
        if (*fmt != '%')
        {
            if (str < end)
                *str = *fmt;
            ++ str;
            continue;
        }

        /* process flags */
        flags = 0;

        while (1)
        {
            /* skips the first '%' also */
            ++ fmt;
            if (*fmt == '-') flags |= LEFT;
            else if (*fmt == '+') flags |= PLUS;
            else if (*fmt == ' ') flags |= SPACE;
            else if (*fmt == '#') flags |= SPECIAL;
            else if (*fmt == '0') flags |= ZEROPAD;
            else break;
        }

        /* get field width */
        field_width = -1;
        if (_ISDIGIT(*fmt)) field_width = skip_atoi(&fmt);
        else if (*fmt == '*')
        {
            ++ fmt;
            /* it's the next argument */
            field_width = va_arg(args, int);
            if (field_width < 0)
            {
                field_width = -field_width;
                flags |= LEFT;
            }
        }

#ifdef PRINTF_PRECISION
        /* get the precision */
        precision = -1;
        if (*fmt == '.')
        {
            ++ fmt;
            if (_ISDIGIT(*fmt)) precision = skip_atoi(&fmt);
            else if (*fmt == '*')
            {
                ++ fmt;
                /* it's the next argument */
                precision = va_arg(args, int);
            }
            if (precision < 0) precision = 0;
        }
#endif
        /* get the conversion qualifier */
        qualifier = 0;
#ifdef PRINTF_LONGLONG
        if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L')
#else
        if (*fmt == 'h' || *fmt == 'l')
#endif
        {
            qualifier = *fmt;
            ++ fmt;
#ifdef PRINTF_LONGLONG
            if (qualifier == 'l' && *fmt == 'l')
            {
                qualifier = 'L';
                ++ fmt;
            }
#endif
        }

        /* the default base */
        base = 10;

        switch (*fmt)
        {
            case 'c':
                if (!(flags & LEFT))
                {
                    while (--field_width > 0)
                    {
                        if (str < end) *str = ' ';
                        ++ str;
                    }
                }

                /* get character */
                c = (uint8_t)va_arg(args, int);
                if (str < end) *str = c;
                ++ str;

                /* put width */
                while (--field_width > 0)
                {
                    if (str < end) *str = ' ';
                    ++ str;
                }
                continue;

            case 's':
                s = va_arg(args, char *);
                if (!s) s = "(NULL)";

                len = strlen(s);
#ifdef PRINTF_PRECISION
                if (precision > 0 && len > precision) len = precision;
#endif

                if (!(flags & LEFT))
                {
                    while (len < field_width--)
                    {
                        if (str < end) *str = ' ';
                        ++ str;
                    }
                }

                for (i = 0; i < len; ++i)
                {
                    if (str < end) *str = *s;
                    ++ str;
                    ++ s;
                }

                while (len < field_width--)
                {
                    if (str < end) *str = ' ';
                    ++ str;
                }
                continue;

            case 'p':
                if (field_width == -1)
                {
                    field_width = sizeof(void *) << 1;
                    flags |= ZEROPAD;
                }
#ifdef PRINTF_PRECISION
                str = print_number(str, end,
                                   (long)va_arg(args, void *),
                16, field_width, precision, flags);
#else
                str = print_number(str, end,
                                   (long)va_arg(args, void *),
                                   16, field_width, flags);
#endif
                continue;

            case '%':
                if (str < end) *str = '%';
                ++ str;
                continue;

                /* integer number formats - set up the flags and "break" */
            case 'o':
                base = 8;
                break;

            case 'X':
                flags |= LARGE;
            case 'x':
                base = 16;
                break;

            case 'd':
            case 'i':
                flags |= SIGN;
            case 'u':
                break;

            default:
                if (str < end) *str = '%';
                ++ str;

                if (*fmt)
                {
                    if (str < end) *str = *fmt;
                    ++ str;
                }
                else
                {
                    -- fmt;
                }
                continue;
        }

#ifdef PRINTF_LONGLONG
        if (qualifier == 'L') num = va_arg(args, long long);
        else if (qualifier == 'l')
#else
        if (qualifier == 'l')
#endif
        {
            num = va_arg(args, uint32_t);
            if (flags & SIGN) num = (int32_t)num;
        }
        else if (qualifier == 'h')
        {
            num = (uint16_t)va_arg(args, int32_t);
            if (flags & SIGN) num = (int16_t)num;
        }
        else
        {
            num = va_arg(args, uint32_t);
            if (flags & SIGN) num = (int32_t)num;
        }
#ifdef PRINTF_PRECISION
        str = print_number(str, end, num, base, field_width, precision, flags);
#else
        str = print_number(str, end, num, base, field_width, flags);
#endif
    }

    if (size > 0)
    {
        if (str < end) *str = '\0';
        else
        {
            end[-1] = '\0';
        }
    }

    /* the trailing null byte doesn't count towards the total
    * ++str;
    */
    return str - buf;
}


/**
 * This function will fill a formatted string to buffer
 *
 * @param buf the buffer to save formatted string
 * @param size the size of buffer
 * @param fmt the format
 */
int32_t _snprintf(char *buf, size_t size, const char *fmt, ...)
{
    int32_t n;
    va_list args;

    va_start(args, fmt);
    n = vsnprintf(buf, size, fmt, args);
    va_end(args);

    return n;
}


/**
 * This function will fill a formatted string to buffer
 *
 * @param buf the buffer to save formatted string
 * @param arg_ptr the arg_ptr
 * @param format the format
 */
int32_t _vsprintf(char *buf, const char *format, va_list arg_ptr)
{
    return vsnprintf(buf, (size_t) - 1, format, arg_ptr);
}


/**
 * This function will fill a formatted string to buffer
 *
 * @param buf the buffer to save formatted string
 * @param format the format
 */
int32_t _sprintf(char *buf, const char *format, ...)
{
    int32_t n;
    va_list arg_ptr;

    va_start(arg_ptr, format);
    n = vsprintf(buf, format, arg_ptr);
    va_end(arg_ptr);

    return n;
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

char *strstr(const char *, const char *) __attribute__((weak, alias("_strstr")));
int strcasecmp(const char *, const char *) __attribute__((weak, alias("_strcasecmp")));
char *strncpy(char *, const char *, size_t) __attribute__((weak, alias("_strncpy")));
int strncmp(const char *, const char *, size_t) __attribute__((weak, alias("_strncmp")));
int	strcmp(const char *, const char *) __attribute__((weak, alias("_strcmp")));
size_t strnlen(const char *, size_t) __attribute__((weak, alias("_strnlen")));
size_t strlen(const char *) __attribute__((weak, alias("_strlen")));
char *strdup(const char *) __attribute__((weak, alias("_strdup")));


#ifdef USE_CONSOLE
#include "console/console.h"

int	_printf(const char *fmt, ...)
{
    va_list args;
    size_t length;
    static char log_buf[CONSOLEBUF_SIZE];

    va_start(args, fmt);
    length = vsnprintf(log_buf, sizeof(log_buf) - 1, fmt, args);
    if (length > CONSOLEBUF_SIZE - 1)
        length = CONSOLEBUF_SIZE - 1;

    console_write(log_buf, length);

    va_end(args);
    return length;
}

int	_println(const char *fmt, ...)
{
    va_list args;
    size_t length;
    static char log_buf[CONSOLEBUF_SIZE];

    va_start(args, fmt);
    length = vsnprintf(log_buf, sizeof(log_buf) - 1, fmt, args);
    if (length > CONSOLEBUF_SIZE - 1)
        length = CONSOLEBUF_SIZE - 1;

    console_write(log_buf, length);
    console_write("\n", 1);

    va_end(args);
    return length;
}
int println(const void *,...) __attribute__((weak, alias("_println")));

/**
 * 重定义 printf (GNU中)
 * @param ch
 * @return
 */
int __io_putchar(int ch)
{
    console_write((char *)&ch, 1);
    return ch;
}
/**
 * 重定义 printf (MDK中)
 * @param ch
 * @param f
 * @return
 */
int fputc(int ch, FILE *f)
{
    console_write((char *)&ch, 1);
    return ch;
}

#endif