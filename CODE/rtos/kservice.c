// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/4.
//
#include "os_common.h"


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



char *strstr(const char *, const char *) __attribute__((weak, alias("_strstr")));
int strcasecmp(const char *, const char *) __attribute__((weak, alias("_strcasecmp")));
char *strncpy(char *, const char *, size_t) __attribute__((weak, alias("_strncpy")));
int strncmp(const char *, const char *, size_t) __attribute__((weak, alias("_strncmp")));
int	strcmp(const char *, const char *) __attribute__((weak, alias("_strcmp")));
size_t strnlen(const char *, size_t) __attribute__((weak, alias("_strnlen")));
size_t strlen(const char *) __attribute__((weak, alias("_strlen")));
char *strdup(const char *) __attribute__((weak, alias("_strdup")));


/**
 * This function will show the version of rt-thread rtos
 */
void show_version(void)
{
    printf("\n >> Rain << \n\t\t  --- build %s\n", __DATE__);
}

#ifdef RT_USING_CONSOLE
#include "console/console.h"

int	_println(const char *fmt, ...)
{
    va_list args;
    size_t length;
    static char log_buf[RT_CONSOLEBUF_SIZE];

    va_start(args, fmt);
    length = vsnprintf(log_buf, sizeof(log_buf) - 1, fmt, args);
    if (length > RT_CONSOLEBUF_SIZE - 1)
        length = RT_CONSOLEBUF_SIZE - 1;

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


#ifndef _gettimeofday
/* Dummy function when hardware do not have RTC */
int _gettimeofday( struct timeval *tv, void *ignore)
{
    tv->tv_sec = 0;  // convert to seconds
    tv->tv_usec = 0;  // get remaining microseconds
    return 0;  // return non-zero for error
}
#endif