#include <common.h>
#include <stdarg.h>

#include "ipc/ringblk_buf.h"
#include "ulog.h"

#ifdef ULOG_USING_SYSLOG
#include <syslog.h>
#endif

#ifdef ULOG_OUTPUT_FLOAT

#include <stdio.h>

#endif

#ifdef ULOG_TIME_USING_TIMESTAMP
#include <sys/time.h>
#endif


#ifdef RT_USING_ULOG

/* the number which is max stored line logs */
#ifndef ULOG_ASYNC_OUTPUT_STORE_LINES
#define ULOG_ASYNC_OUTPUT_STORE_LINES (ULOG_ASYNC_OUTPUT_BUF_SIZE * 3 / 2 / ULOG_LINE_BUF_SIZE)
#endif

#ifdef ULOG_USING_COLOR
/**
* CSI(Control Sequence Introducer/Initiator) sign
* more information on https://en.wikipedia.org/wiki/ANSI_escape_code
*/
#define CSI_START "\033["
#define CSI_END   "\033[0m"
/* output log front color */
#define F_BLACK   "30m"
#define F_RED     "31m"
#define F_GREEN   "32m"
#define F_YELLOW  "33m"
#define F_BLUE    "34m"
#define F_MAGENTA "35m"
#define F_CYAN    "36m"
#define F_WHITE   "37m"

/* output log default color definition */
#ifndef ULOG_COLOR_DEBUG
#define ULOG_COLOR_DEBUG NULL
#endif
#ifndef ULOG_COLOR_INFO
#define ULOG_COLOR_INFO (F_GREEN)
#endif
#ifndef ULOG_COLOR_WARN
#define ULOG_COLOR_WARN (F_YELLOW)
#endif
#ifndef ULOG_COLOR_ERROR
#define ULOG_COLOR_ERROR (F_RED)
#endif
#ifndef ULOG_COLOR_ASSERT
#define ULOG_COLOR_ASSERT (F_MAGENTA)
#endif
#endif /* ULOG_USING_COLOR */

#if ULOG_LINE_BUF_SIZE < 80
#error "the log line buffer size must more than 80"
#endif

struct ulog
{
    bool_t init_ok;
    mutex_t output_locker;
    /* all backends */
    slist_t backend_list;
    /* the thread log's line buffer */
    char log_buf_th[ULOG_LINE_BUF_SIZE + 1];

#ifdef ULOG_USING_ISR_LOG
    /* the ISR log's line buffer */
    base_t output_locker_isr_lvl;
    char log_buf_isr[ULOG_LINE_BUF_SIZE + 1];
#endif /* ULOG_USING_ISR_LOG */

#ifdef ULOG_USING_ASYNC_OUTPUT
    rbb_t async_rbb;
#endif

#ifdef ULOG_USING_FILTER
    struct {
        /* all tag's level filter */
        slist_t tag_lvl_list;
        /* global filter level, tag and keyword */
        uint32_t level;
        char tag[ULOG_FILTER_TAG_MAX_LEN + 1];
        char keyword[ULOG_FILTER_KW_MAX_LEN + 1];
    } filter;
#endif /* ULOG_USING_FILTER */
};

/* level output info */
static const char *const level_output_info[] = {
        "A/",
        NULL,
        NULL,
        "E/",
        "W/",
        NULL,
        "I/",
        "D/",
};

#ifdef ULOG_USING_COLOR
/* color output info */
static const char* const color_output_info[] = {
    ULOG_COLOR_ASSERT,
    NULL,
    NULL,
    ULOG_COLOR_ERROR,
    ULOG_COLOR_WARN,
    NULL,
    ULOG_COLOR_INFO,
    ULOG_COLOR_DEBUG,
};
#endif /* ULOG_USING_COLOR */

/* ulog local object */
static struct ulog ulog = {0};

static void (*ulog_cb)(void) = NULL;

size_t ulog_strcpy(size_t cur_len, char *dst, const char *src)
{
    const char *src_old = src;

    ASSERT(dst);
    ASSERT(src);

    while (*src != 0)
    {
        /* make sure destination has enough space */
        if (cur_len++ < ULOG_LINE_BUF_SIZE)
        {
            *dst++ = *src++;
        }
        else
        {
            break;
        }
    }

    return src - src_old;
}

size_t ulog_ultoa(char *s, unsigned long int n)
{
    size_t i = 0, j = 0, len = 0;
    char swap;

    do
    {
        s[len++] = n % 10 + '0';
    } while (n /= 10);

    s[len] = '\0';

    /* reverse string */
    for (i = 0, j = len - 1; i < j; ++i, --j)
    {
        swap = s[i];
        s[i] = s[j];
        s[j] = swap;
    }

    return len;
}

static void output_unlock(void)
{
    /* is in thread context */
    if (os_interrupt_get_nest() == 0)
    {
        mutex_release(ulog.output_locker);
    }
    else
    {
#ifdef ULOG_USING_ISR_LOG
        os_hw_interrupt_enable(ulog.output_locker_isr_lvl);
#endif
    }
}

static void output_lock(void)
{
    /* is in thread context */
    if (os_interrupt_get_nest() == 0)
    {
        mutex_take(ulog.output_locker, osWaitForever);
    }
    else
    {
#ifdef ULOG_USING_ISR_LOG
        ulog.output_locker_isr_lvl = os_hw_interrupt_disable();
#endif
    }
}

static char *get_log_buf(void)
{
    /* is in thread context */
    if (os_interrupt_get_nest() == 0)
    {
        return ulog.log_buf_th;
    }
    else
    {
#ifdef ULOG_USING_ISR_LOG
        return ulog.log_buf_isr;
#else
        printf("Error: Current mode not supported run in ISR. Please enable ULOG_USING_ISR_LOG.\n");
        return NULL;
#endif
    }
}

__WEAK size_t ulog_formater(char *log_buf, uint32_t level, const char *tag, bool_t newline,
                              const char *format, va_list args)
{
    /* the caller has locker, so it can use static variable for reduce stack usage */
    static size_t log_len, newline_len;
    static int fmt_result;

    ASSERT(log_buf);
    ASSERT(level <= LOG_LVL_DBG);
    ASSERT(tag);
    ASSERT(format);

    log_len = 0;
    newline_len = strlen(ULOG_NEWLINE_SIGN);

#ifdef ULOG_USING_COLOR

    /* add CSI start sign and color info */
    if (color_output_info[level]) {
        log_len += ulog_strcpy(log_len, log_buf + log_len, CSI_START);
        log_len += ulog_strcpy(log_len, log_buf + log_len, color_output_info[level]);
    }

#endif /* ULOG_USING_COLOR */

#ifdef ULOG_OUTPUT_TIME
    /* add time info */
    {
#ifdef ULOG_TIME_USING_TIMESTAMP
        static time_t now;
        static struct tm *tm, tm_tmp;

        now = time(NULL);
        tm = gmtime_r(&now, &tm_tmp);

#ifdef RT_USING_SOFT_RTC
        snprintf(log_buf + log_len, ULOG_LINE_BUF_SIZE - log_len, "%02d-%02d %02d:%02d:%02d.%03d", tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, rt_tick_get() % 1000);
#else
        snprintf(log_buf + log_len, ULOG_LINE_BUF_SIZE - log_len, "%02d-%02d %02d:%02d:%02d", tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
#endif /* USING_SOFT_RTC */

#else
        static size_t tick_len = 0;

        log_buf[log_len] = '[';
        tick_len = ulog_ultoa(log_buf + log_len + 1, os_tick_get());
        log_buf[log_len + 1 + tick_len] = ']';
        log_buf[log_len + 1 + tick_len + 1] = '\0';
#endif /* ULOG_TIME_USING_TIMESTAMP */

        log_len += strlen(log_buf + log_len);
    }
#endif /* ULOG_OUTPUT_TIME */

#ifdef ULOG_OUTPUT_LEVEL

#ifdef ULOG_OUTPUT_TIME
    log_len += ulog_strcpy(log_len, log_buf + log_len, " ");
#endif

    /* add level info */
    log_len += ulog_strcpy(log_len, log_buf + log_len, level_output_info[level]);
#endif /* ULOG_OUTPUT_LEVEL */

#ifdef ULOG_OUTPUT_TAG

#if !defined(ULOG_OUTPUT_LEVEL) && defined(ULOG_OUTPUT_TIME)
    log_len += ulog_strcpy(log_len, log_buf + log_len, " ");
#endif

    /* add tag info */
    log_len += ulog_strcpy(log_len, log_buf + log_len, tag);
#endif /* ULOG_OUTPUT_TAG */

#ifdef ULOG_OUTPUT_THREAD_NAME
    /* add thread info */
    {

#if defined(ULOG_OUTPUT_TIME) || defined(ULOG_OUTPUT_LEVEL) || defined(ULOG_OUTPUT_TAG)
        log_len += ulog_strcpy(log_len, log_buf + log_len, " ");
#endif

        /* is not in interrupt context */
        if (os_interrupt_get_nest() == 0) {
            size_t name_len = strnlen(os_thread_self()->name, NAME_MAX_LEN);

            strncpy(log_buf + log_len, os_thread_self()->name, name_len);
            log_len += name_len;
        } else {
            log_len += ulog_strcpy(log_len, log_buf + log_len, "ISR");
        }
    }
#endif /* ULOG_OUTPUT_THREAD_NAME */

    log_len += ulog_strcpy(log_len, log_buf + log_len, ": ");

#ifdef ULOG_OUTPUT_FLOAT
    fmt_result = vsnprintf(log_buf + log_len, ULOG_LINE_BUF_SIZE - log_len, format, args);
#else
    fmt_result = vsnprintf(log_buf + log_len, ULOG_LINE_BUF_SIZE - log_len, format, args);
#endif /* ULOG_OUTPUT_FLOAT */

    /* calculate log length */
    if ((log_len + fmt_result <= ULOG_LINE_BUF_SIZE) && (fmt_result > -1))
    {
        log_len += fmt_result;
    }
    else
    {
        /* using max length */
        log_len = ULOG_LINE_BUF_SIZE;
    }

    /* overflow check and reserve some space for CSI end sign and newline sign */
#ifdef ULOG_USING_COLOR

    if (log_len + (sizeof(CSI_END) - 1) + newline_len > ULOG_LINE_BUF_SIZE) {
        /* using max length */
        log_len = ULOG_LINE_BUF_SIZE;
        /* reserve some space for CSI end sign */
        log_len -= (sizeof(CSI_END) - 1);
#else

    if (log_len + newline_len > ULOG_LINE_BUF_SIZE)
    {
        /* using max length */
        log_len = ULOG_LINE_BUF_SIZE;
#endif /* ULOG_USING_COLOR */
        /* reserve some space for newline sign */
        log_len -= newline_len;
    }

    /* package newline sign */
    if (newline)
    {
        log_len += ulog_strcpy(log_len, log_buf + log_len, ULOG_NEWLINE_SIGN);
    }

#ifdef ULOG_USING_COLOR

    /* add CSI end sign  */
    if (color_output_info[level]) {
        log_len += ulog_strcpy(log_len, log_buf + log_len, CSI_END);
    }

#endif /* ULOG_USING_COLOR */

    return log_len;
}

void ulog_output_to_all_backend(uint32_t level, const char *tag, bool_t is_raw, const char *log, size_t size)
{
    slist_t *node;
    ulog_backend_t backend;

    if (!ulog.init_ok)
        return;

    /* output for all backends */
    for (node = slist_first(&ulog.backend_list); node; node = slist_next(node))
    {
        backend = slist_entry(node, struct ulog_backend, list);
#if !defined(ULOG_USING_COLOR) || defined(ULOG_USING_SYSLOG)
        backend->output(backend, level, tag, is_raw, log, size);
#else

        if (backend->support_color || is_raw) {
            backend->output(backend, level, tag, is_raw, log, size);
        } else {
            /* recalculate the log start address and log size when backend not supported color */
            size_t color_info_len = strlen(color_output_info[level]), output_size = size;

            if (color_info_len) {
                size_t color_hdr_len = strlen(CSI_START) + color_info_len;

                log += color_hdr_len;
                output_size -= (color_hdr_len + (sizeof(CSI_END) - 1));
            }

            backend->output(backend, level, tag, is_raw, log, output_size);
        }

#endif /* !defined(ULOG_USING_COLOR) || defined(ULOG_USING_SYSLOG) */
    }
}

static void do_output(uint32_t level, const char *tag, bool_t is_raw, const char *log_buf, size_t log_len)
{
#ifdef ULOG_USING_ASYNC_OUTPUT
    rbb_blk_t log_blk;
    ulog_frame_t log_frame;

    /* allocate log frame */
    log_blk = rbb_blk_alloc(ulog.async_rbb, ALIGN(sizeof(struct ulog_frame) + log_len, ALIGN_SIZE));

    if (log_blk)
    {
        /* package the log frame */
        log_frame = (ulog_frame_t) log_blk->buf;
        log_frame->magic = ULOG_FRAME_MAGIC;
        log_frame->is_raw = is_raw;
        log_frame->level = level;
        log_frame->log_len = log_len;
        log_frame->tag = tag;
        log_frame->log = (const char *) log_blk->buf + sizeof(struct ulog_frame);
        /* copy log data */
        memcpy(log_blk->buf + sizeof(struct ulog_frame), log_buf, log_len);
        /* put the block */
        rbb_blk_put(log_blk);
        /* send a notice */
        if (ulog_cb != NULL)
        {
            ulog_cb();
        }
    }
    else
    {
        static bool_t already_output = FALSE;

        if (already_output == FALSE)
        {
            printf("Warning: There is no enough buffer for saving async log,"
                   " please increase the ULOG_ASYNC_OUTPUT_BUF_SIZE option.\n");
            already_output = TRUE;
        }
    }

#else

    /* is in thread context */
    if (os_interrupt_get_nest() == 0) {
        /* output to all backends */
        ulog_output_to_all_backend(level, tag, is_raw, log_buf, log_len);
    } else {
#ifdef ULOG_BACKEND_USING_CONSOLE
        /* We can't ensure that all backends support ISR context output.
         * So only using printf when context is ISR */
        extern void ulog_console_backend_output(struct ulog_backend * backend, uint32_t level, const char* tag, bool_t is_raw, const char* log, size_t len);
        ulog_console_backend_output(NULL, level, tag, is_raw, log_buf, log_len);
#endif /* ULOG_BACKEND_USING_CONSOLE */
    }

#endif /* ULOG_USING_ASYNC_OUTPUT */
}

/**
 * output the log by variable argument list
 *
 * @param level level
 * @param tag tag
 * @param newline has_newline
 * @param format output format
 * @param args variable argument list
 */
void ulog_voutput(uint32_t level, const char *tag, bool_t newline, const char *format, va_list args)
{
    char *log_buf = NULL;
    size_t log_len = 0;

#ifndef ULOG_USING_SYSLOG
    ASSERT(level <= LOG_LVL_DBG);
#else
    ASSERT(LOG_PRI(level) <= LOG_DEBUG);
#endif /* ULOG_USING_SYSLOG */

    ASSERT(tag);
    ASSERT(format);

    if (!ulog.init_ok)
    {
        return;
    }

#ifdef ULOG_USING_FILTER
    /* level filter */
#ifndef ULOG_USING_SYSLOG

if (level > ulog.filter.level || level > ulog_tag_lvl_filter_get(tag)) {
    return;
}

#else

if (((LOG_MASK(LOG_PRI(level)) & ulog.filter.level) == 0)
    || ((LOG_MASK(LOG_PRI(level)) & ulog_tag_lvl_filter_get(tag)) == 0)) {
    return;
}

#endif /* ULOG_USING_SYSLOG */
else if (!strstr(tag, ulog.filter.tag)) {
    /* tag filter */
    return;
}

#endif /* ULOG_USING_FILTER */

    /* get log buffer */
    log_buf = get_log_buf();

    /* lock output */
    output_lock();

#ifndef ULOG_USING_SYSLOG
    log_len = ulog_formater(log_buf, level, tag, newline, format, args);
#else
    extern size_t syslog_formater(char* log_buf, uint8_t level, const char* tag, bool_t newline, const char* format, va_list args);
    log_len = syslog_formater(log_buf, level, tag, newline, format, args);
#endif /* ULOG_USING_SYSLOG */

#ifdef ULOG_USING_FILTER

    /* keyword filter */
    if (ulog.filter.keyword[0] != '\0') {
        /* add string end sign */
        log_buf[log_len] = '\0';

        /* find the keyword */
        if (!strstr(log_buf, ulog.filter.keyword)) {
            /* unlock output */
            output_unlock();
            return;
        }
    }

#endif /* ULOG_USING_FILTER */
    /* do log output */
    do_output(level, tag, FALSE, log_buf, log_len);

    /* unlock output */
    output_unlock();
}

/**
 * output the log
 *
 * @param level level
 * @param tag tag
 * @param newline has newline
 * @param format output format
 * @param ... args
 */
void ulog_output(uint32_t level, const char *tag, bool_t newline, const char *format, ...)
{
    va_list args;

    /* args point to the first variable parameter */
    va_start(args, format);

    ulog_voutput(level, tag, newline, format, args);

    va_end(args);
}

/**
 * output RAW string format log
 *
 * @param format output format
 * @param ... args
 */
void ulog_raw(const char *format, ...)
{
    size_t log_len = 0;
    char *log_buf = NULL;
    va_list args;
    int fmt_result;

    ASSERT(ulog.init_ok);

    /* get log buffer */
    log_buf = get_log_buf();

    /* lock output */
    output_lock();
    /* args point to the first variable parameter */
    va_start(args, format);

#ifdef ULOG_OUTPUT_FLOAT
    fmt_result = vsnprintf(log_buf, ULOG_LINE_BUF_SIZE, format, args);
#else
    fmt_result = vsnprintf(log_buf, ULOG_LINE_BUF_SIZE, format, args);
#endif /* ULOG_OUTPUT_FLOAT */

    va_end(args);

    /* calculate log length */
    if ((fmt_result > -1) && (fmt_result <= ULOG_LINE_BUF_SIZE))
    {
        log_len = fmt_result;
    }
    else
    {
        log_len = ULOG_LINE_BUF_SIZE;
    }

    /* do log output */
    do_output(LOG_LVL_DBG, NULL, TRUE, log_buf, log_len);

    /* unlock output */
    output_unlock();
}

/**
 * dump the hex format data to log
 *
 * @param tag name for hex object, it will show on log header
 * @param width hex number for every line, such as: 16, 32
 * @param buf hex buffer
 * @param size buffer size
 */
void ulog_hexdump(const char *tag, size_t width, uint8_t *buf, size_t size)
{
#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127u - ' ')

    size_t i, j;
    size_t log_len = 0, name_len = strlen(tag);
    char *log_buf = NULL, dump_string[8];
    int fmt_result;

    ASSERT(ulog.init_ok);

#ifdef ULOG_USING_FILTER
    /* level filter */
#ifndef ULOG_USING_SYSLOG

if (LOG_LVL_DBG > ulog.filter.level || LOG_LVL_DBG > ulog_tag_lvl_filter_get(tag)) {
    return;
}

#else

if ((LOG_MASK(LOG_DEBUG) & ulog.filter.level) == 0) {
    return;
}

#endif /* ULOG_USING_SYSLOG */
else if (!strstr(tag, ulog.filter.tag)) {
    /* tag filter */
    return;
}

#endif /* ULOG_USING_FILTER */

    /* get log buffer */
    log_buf = get_log_buf();

    /* lock output */
    output_lock();

    for (i = 0, log_len = 0; i < size; i += width)
    {
        /* package header */
        if (i == 0)
        {
            log_len += ulog_strcpy(log_len, log_buf + log_len, "D/HEX ");
            log_len += ulog_strcpy(log_len, log_buf + log_len, tag);
            log_len += ulog_strcpy(log_len, log_buf + log_len, ": ");
        }
        else
        {
            log_len = 6 + name_len + 2;
            memset(log_buf, ' ', log_len);
        }

        fmt_result = snprintf(log_buf + log_len, ULOG_LINE_BUF_SIZE, "%04X-%04X: ", i, i + width - 1);

        /* calculate log length */
        if ((fmt_result > -1) && (fmt_result <= ULOG_LINE_BUF_SIZE))
        {
            log_len += fmt_result;
        }
        else
        {
            log_len = ULOG_LINE_BUF_SIZE;
        }

        /* dump hex */
        for (j = 0; j < width; j++)
        {
            if (i + j < size)
            {
                snprintf(dump_string, sizeof(dump_string), "%02X ", buf[i + j]);
            }
            else
            {
                strncpy(dump_string, "   ", sizeof(dump_string));
            }

            log_len += ulog_strcpy(log_len, log_buf + log_len, dump_string);

            if ((j + 1) % 8 == 0)
            {
                log_len += ulog_strcpy(log_len, log_buf + log_len, " ");
            }
        }

        log_len += ulog_strcpy(log_len, log_buf + log_len, "  ");

        /* dump char for hex */
        for (j = 0; j < width; j++)
        {
            if (i + j < size)
            {
                snprintf(dump_string, sizeof(dump_string), "%c", __is_print(buf[i + j]) ? buf[i + j] : '.');
                log_len += ulog_strcpy(log_len, log_buf + log_len, dump_string);
            }
        }

        /* overflow check and reserve some space for newline sign */
        if (log_len + strlen(ULOG_NEWLINE_SIGN) > ULOG_LINE_BUF_SIZE)
        {
            log_len = ULOG_LINE_BUF_SIZE - strlen(ULOG_NEWLINE_SIGN);
        }

        /* package newline sign */
        log_len += ulog_strcpy(log_len, log_buf + log_len, ULOG_NEWLINE_SIGN);
        /*add string end sign*/
        log_buf[log_len] = '\0';
        /* do log output */
        do_output(LOG_LVL_DBG, NULL, TRUE, log_buf, log_len);
    }

    /* unlock output */
    output_unlock();
}

#ifdef ULOG_USING_FILTER
/**
 * Set the filter's level by different tag.
 * The log on this tag which level is less than it will stop output.
 *
 * example:
 *     // the example tag log enter silent mode
 *     ulog_set_filter_lvl("example", LOG_FILTER_LVL_SILENT);
 *     // the example tag log which level is less than INFO level will stop output
 *     ulog_set_filter_lvl("example", LOG_LVL_INFO);
 *     // remove example tag's level filter, all level log will resume output
 *     ulog_set_filter_lvl("example", LOG_FILTER_LVL_ALL);
 *
 * @param tag log tag
 * @param level The filter level. When the level is LOG_FILTER_LVL_SILENT, the log enter silent mode.
 *        When the level is LOG_FILTER_LVL_ALL, it will remove this tag's level filer.
 *        Then all level log will resume output.
 *
 * @return  0 : success
 *         -5 : no memory
 *         -10: level is out of range
 */
int ulog_tag_lvl_filter_set(const char* tag, uint32_t level)
{
    slist_t* node;
    ulog_tag_lvl_filter_t tag_lvl = NULL;
    int result = E_OK;

    if (level > LOG_FILTER_LVL_ALL)
        return E_INVAL;

    if (!ulog.init_ok)
        return result;

    /* lock output */
    output_lock();

    /* find the tag in list */
    for (node = slist_first(ulog_tag_lvl_list_get()); node; node = slist_next(node)) {
        tag_lvl = slist_entry(node, struct ulog_tag_lvl_filter, list);

        if (!strncmp(tag_lvl->tag, tag, ULOG_FILTER_TAG_MAX_LEN)) {
            break;
        } else {
            tag_lvl = NULL;
        }
    }

    /* find OK */
    if (tag_lvl) {
        if (level == LOG_FILTER_LVL_ALL) {
            /* remove current tag's level filter when input level is the lowest level */
            slist_remove(ulog_tag_lvl_list_get(), &tag_lvl->list);
            free(tag_lvl);
        } else {
            /* update level */
            tag_lvl->level = level;
        }
    } else {
        /* only add the new tag's level filer when level is not LOG_FILTER_LVL_ALL */
        if (level != LOG_FILTER_LVL_ALL) {
            /* new a tag's level filter */
            tag_lvl = (ulog_tag_lvl_filter_t)malloc(sizeof(struct ulog_tag_lvl_filter));

            if (tag_lvl) {
                memset(tag_lvl->tag, 0, sizeof(tag_lvl->tag));
                strncpy(tag_lvl->tag, tag, ULOG_FILTER_TAG_MAX_LEN);
                tag_lvl->level = level;
                slist_append(ulog_tag_lvl_list_get(), &tag_lvl->list);
            } else {
                result = E_NOMEM;
            }
        }
    }

    /* unlock output */
    output_unlock();

    return result;
}

/**
 * get the level on tag's level filer
 *
 * @param tag log tag
 *
 * @return It will return the lowest level when tag was not found.
 *         Other level will return when tag was found.
 */
uint32_t ulog_tag_lvl_filter_get(const char* tag)
{
    slist_t* node;
    ulog_tag_lvl_filter_t tag_lvl = NULL;
    uint32_t level = LOG_FILTER_LVL_ALL;

    if (!ulog.init_ok)
        return level;

    /* lock output */
    output_lock();

    /* find the tag in list */
    for (node = slist_first(ulog_tag_lvl_list_get()); node; node = slist_next(node)) {
        tag_lvl = slist_entry(node, struct ulog_tag_lvl_filter, list);

        if (!strncmp(tag_lvl->tag, tag, ULOG_FILTER_TAG_MAX_LEN)) {
            level = tag_lvl->level;
            break;
        }
    }

    /* unlock output */
    output_unlock();

    return level;
}

/**
 * get the tag's level list on filter
 *
 * @return tag's level list
 */
slist_t* ulog_tag_lvl_list_get(void)
{
    return &ulog.filter.tag_lvl_list;
}

/**
 * set log global filter level
 *
 * @param level log level: LOG_LVL_ASSERT, LOG_LVL_ERROR, LOG_LVL_WARNING, LOG_LVL_INFO, LOG_LVL_DBG
 *              LOG_FILTER_LVL_SILENT: disable all log output, except assert level
 *              LOG_FILTER_LVL_ALL: enable all log output
 */
void ulog_global_filter_lvl_set(uint32_t level)
{
    ASSERT(level <= LOG_FILTER_LVL_ALL);

    ulog.filter.level = level;
}

/**
 * get log global filter level
 *
 * @return log level: LOG_LVL_ASSERT, LOG_LVL_ERROR, LOG_LVL_WARNING, LOG_LVL_INFO, LOG_LVL_DBG
 *              LOG_FILTER_LVL_SILENT: disable all log output, except assert level
 *              LOG_FILTER_LVL_ALL: enable all log output
 */
uint32_t ulog_global_filter_lvl_get(void)
{
    return ulog.filter.level;
}

/**
 * set log global filter tag
 *
 * @param tag tag
 */
void ulog_global_filter_tag_set(const char* tag)
{
    ASSERT(tag);

    strncpy(ulog.filter.tag, tag, ULOG_FILTER_TAG_MAX_LEN);
}

/**
 * get log global filter tag
 *
 * @return tag
 */
const char* ulog_global_filter_tag_get(void)
{
    return ulog.filter.tag;
}

/**
 * set log global filter keyword
 *
 * @param keyword keyword
 */
void ulog_global_filter_kw_set(const char* keyword)
{
    ASSERT(keyword);

    strncpy(ulog.filter.keyword, keyword, ULOG_FILTER_KW_MAX_LEN);
}

/**
 * get log global filter keyword
 *
 * @return keyword
 */
const char* ulog_global_filter_kw_get(void)
{
    return ulog.filter.keyword;
}

#if defined(RT_USING_FINSH) && defined(FINSH_USING_MSH)
#include <finsh.h>

static void ulog_tag_lvl(uint8_t argc, char** argv)
{
    if (argc > 2) {
        if ((atoi(argv[2]) <= LOG_FILTER_LVL_ALL) && (atoi(argv[2]) >= 0)) {
            ulog_tag_lvl_filter_set(argv[1], atoi(argv[2]));
        } else {
            printf("Please input correct level (0-%d).\n", LOG_FILTER_LVL_ALL);
        }
    } else {
        printf("Please input: ulog_tag_lvl <tag> <level>.\n");
#ifndef ULOG_USING_SYSLOG
        printf("Assert  : 0\n");
        printf("Error   : 3\n");
        printf("Warning : 4\n");
        printf("Info    : 6\n");
        printf("Debug   : 7\n");
#else
        printf("EMERG   :   1 (1 << 0)\n");
        printf("ALERT   :   2 (1 << 1)\n");
        printf("CRIT    :   4 (1 << 2)\n");
        printf("ERR     :   8 (1 << 3)\n");
        printf("WARNING :  16 (1 << 4)\n");
        printf("NOTICE  :  32 (1 << 5)\n");
        printf("INFO    :  64 (1 << 6)\n");
        printf("DEBUG   : 128 (1 << 7)\n");
#endif /* ULOG_USING_SYSLOG */
    }
}
MSH_CMD_EXPORT(ulog_tag_lvl, Set ulog filter level by different tag.);

static void ulog_lvl(uint8_t argc, char** argv)
{
    if (argc > 1) {
        if ((atoi(argv[1]) <= LOG_FILTER_LVL_ALL) && (atoi(argv[1]) >= 0)) {
            ulog_global_filter_lvl_set(atoi(argv[1]));
        } else {
            printf("Please input correct level (0-%d).\n", LOG_FILTER_LVL_ALL);
        }
    } else {
        printf("Please input: ulog_lvl <level>.\n");
#ifndef ULOG_USING_SYSLOG
        printf("Assert  : 0\n");
        printf("Error   : 3\n");
        printf("Warning : 4\n");
        printf("Info    : 6\n");
        printf("Debug   : 7\n");
#else
        printf("EMERG   :   1 (1 << 0)\n");
        printf("ALERT   :   2 (1 << 1)\n");
        printf("CRIT    :   4 (1 << 2)\n");
        printf("ERR     :   8 (1 << 3)\n");
        printf("WARNING :  16 (1 << 4)\n");
        printf("NOTICE  :  32 (1 << 5)\n");
        printf("INFO    :  64 (1 << 6)\n");
        printf("DEBUG   : 128 (1 << 7)\n");
#endif /* ULOG_USING_SYSLOG */
    }
}
MSH_CMD_EXPORT(ulog_lvl, Set ulog global filter level.);

static void ulog_tag(uint8_t argc, char** argv)
{
    if (argc > 1) {
        if (strlen(argv[1]) <= ULOG_FILTER_TAG_MAX_LEN) {
            ulog_global_filter_tag_set(argv[1]);
        } else {
            printf("The tag length is too long. Max is %d.\n", ULOG_FILTER_TAG_MAX_LEN);
        }
    } else {
        ulog_global_filter_tag_set("");
    }
}
MSH_CMD_EXPORT(ulog_tag, Set ulog global filter tag);

static void ulog_kw(uint8_t argc, char** argv)
{
    if (argc > 1) {
        if (strlen(argv[1]) <= ULOG_FILTER_KW_MAX_LEN) {
            ulog_global_filter_kw_set(argv[1]);
        } else {
            printf("The keyword length is too long. Max is %d.\n", ULOG_FILTER_KW_MAX_LEN);
        }
    } else {
        ulog_global_filter_kw_set("");
    }
}
MSH_CMD_EXPORT(ulog_kw, Set ulog global filter keyword);

static void ulog_filter(uint8_t argc, char** argv)
{
#ifndef ULOG_USING_SYSLOG
    const char* lvl_name[] = { "Assert ", "Error  ", "Error  ", "Error  ", "Warning", "Info   ", "Info   ", "Debug  " };
#endif
    const char *tag = ulog_global_filter_tag_get(), *kw = ulog_global_filter_kw_get();
    slist_t* node;
    ulog_tag_lvl_filter_t tag_lvl = NULL;

    printf("--------------------------------------\n");
    printf("ulog global filter:\n");

#ifndef ULOG_USING_SYSLOG
    printf("level   : %s\n", lvl_name[ulog_global_filter_lvl_get()]);
#else
    printf("level   : %d\n", ulog_global_filter_lvl_get());
#endif

    printf("tag     : %s\n", strlen(tag) == 0 ? "NULL" : tag);
    printf("keyword : %s\n", strlen(kw) == 0 ? "NULL" : kw);

    printf("--------------------------------------\n");
    printf("ulog tag's level filter:\n");

    if (slist_isempty(ulog_tag_lvl_list_get())) {
        printf("settings not found\n");
    } else {
        /* lock output */
        output_lock();

        /* show the tag level list */
        for (node = slist_first(ulog_tag_lvl_list_get()); node; node = slist_next(node)) {
            tag_lvl = slist_entry(node, struct ulog_tag_lvl_filter, list);
            printf("%-*.s: ", ULOG_FILTER_TAG_MAX_LEN, tag_lvl->tag);

#ifndef ULOG_USING_SYSLOG
            printf("%s\n", lvl_name[tag_lvl->level]);
#else
            printf("%d\n", tag_lvl->level);
#endif
        }

        /* unlock output */
        output_unlock();
    }
}
MSH_CMD_EXPORT(ulog_filter, Show ulog filter settings);
#endif /* defined(USING_FINSH) && defined(FINSH_USING_MSH) */
#endif     /* ULOG_USING_FILTER */

/**
 * Register a call if something updated
 */
void ulog_register_callback(void (*cb)(void))
{
    ulog_cb = cb;
}

err_t ulog_backend_register(ulog_backend_t backend, const char *name, bool_t support_color)
{
    base_t level;

    ASSERT(backend);
    ASSERT(name);
    ASSERT(ulog.init_ok);
    ASSERT(backend->output);

    if (backend->init)
    {
        backend->init(backend);
    }

    backend->support_color = support_color;
    memcpy(backend->name, name, NAME_MAX_LEN);

    level = os_hw_interrupt_disable();
    slist_append(&ulog.backend_list, &backend->list);
    os_hw_interrupt_enable(level);

    return E_OK;
}

err_t ulog_backend_unregister(ulog_backend_t backend)
{
    base_t level;

    ASSERT(backend);
    ASSERT(ulog.init_ok);

    if (backend->deinit)
    {
        backend->deinit(backend);
    }

    level = os_hw_interrupt_disable();
    slist_remove(&ulog.backend_list, &backend->list);
    os_hw_interrupt_enable(level);

    return E_OK;
}

#ifdef ULOG_USING_ASYNC_OUTPUT

/**
 * asynchronous output logs to all backends
 *
 * @note you must call this function when ULOG_ASYNC_OUTPUT_BY_THREAD is disable
 */
void ulog_async_output(void)
{
    rbb_blk_t log_blk;
    ulog_frame_t log_frame;

    while ((log_blk = rbb_blk_get(ulog.async_rbb)) != NULL)
    {
        log_frame = (ulog_frame_t) log_blk->buf;

        if (log_frame->magic == ULOG_FRAME_MAGIC)
        {
            /* output to all backends */
            ulog_output_to_all_backend(log_frame->level, log_frame->tag, log_frame->is_raw, log_frame->log,
                                       log_frame->log_len);
        }

        rbb_blk_free(ulog.async_rbb, log_blk);
    }
}

#endif /* ULOG_USING_ASYNC_OUTPUT */

/**
 * flush all backends's log
 */
void ulog_flush(void)
{
    slist_t *node;
    ulog_backend_t backend;

    if (!ulog.init_ok)
        return;

#ifdef ULOG_USING_ASYNC_OUTPUT
    ulog_async_output();
#endif

    /* flush all backends */
    for (node = slist_first(&ulog.backend_list); node; node = slist_next(node))
    {
        backend = slist_entry(node, struct ulog_backend, list);

        if (backend->flush)
        {
            backend->flush(backend);
        }
    }
}

int ulog_init(void)
{
    if (ulog.init_ok)
        return 0;

    mutex_init(&ulog.output_locker);
    slist_init(&ulog.backend_list);

#ifdef ULOG_USING_FILTER
    slist_init(ulog_tag_lvl_list_get());
#endif

#ifdef ULOG_USING_ASYNC_OUTPUT
    ASSERT(ULOG_ASYNC_OUTPUT_STORE_LINES >= 2);
    /* async output ring block buffer */
    ulog.async_rbb = rbb_create(ALIGN(ULOG_ASYNC_OUTPUT_BUF_SIZE, ALIGN_SIZE), ULOG_ASYNC_OUTPUT_STORE_LINES);

    if (ulog.async_rbb == NULL)
    {
        printf("Error: ulog init failed! No memory for async rbb.\n");
        mutex_detach(ulog.output_locker);
        return E_NOMEM;
    }

#endif /* ULOG_USING_ASYNC_OUTPUT */

#ifdef ULOG_USING_FILTER
    ulog_global_filter_lvl_set(LOG_FILTER_LVL_ALL);
#endif

    ulog.init_ok = TRUE;

    return 0;
}


void ulog_deinit(void)
{
    slist_t *node;
    ulog_backend_t backend;

    if (!ulog.init_ok)
        return;

    /* deinit all backends */
    for (node = slist_first(&ulog.backend_list); node; node = slist_next(node))
    {
        backend = slist_entry(node, struct ulog_backend, list);

        if (backend->deinit)
        {
            backend->deinit(backend);
        }
    }

#ifdef ULOG_USING_FILTER
    /* deinit tag's level filter */
    {
        ulog_tag_lvl_filter_t tag_lvl;

        for (node = slist_first(ulog_tag_lvl_list_get()); node; node = slist_next(node)) {
            tag_lvl = slist_entry(node, struct ulog_tag_lvl_filter, list);
            free(tag_lvl);
        }
    }
#endif /* ULOG_USING_FILTER */

    mutex_detach(ulog.output_locker);

#ifdef ULOG_USING_ASYNC_OUTPUT
    rbb_destroy(ulog.async_rbb);
    // os_thread_delete(ulog.async_th);
#endif

    ulog.init_ok = FALSE;
}

#endif /* USING_ULOG */
