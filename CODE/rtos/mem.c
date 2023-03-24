// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/12/30.
//

#include "mem.h"
#include "common.h"
#include "lib_mem.h"

/* Turn on some of these (set to non-zero) to debug kernel */
#define DEBUG_MEM                   0


static void (*os_malloc_hook)(void *ptr, size_t size);
static void (*os_free_hook)(void *ptr);

/**
 * @addtogroup Hook
 */

/**@{*/

/**
 * This function will set a hook function, which will be invoked when a memory
 * block is allocated from heap memory.
 *
 * @param hook the hook function
 */
void os_malloc_sethook(void (*hook)(void *ptr, size_t size))
{
    os_malloc_hook = hook;
}

/**
 * This function will set a hook function, which will be invoked when a memory
 * block is released to heap memory.
 *
 * @param hook the hook function
 */
void os_free_sethook(void (*hook)(void *ptr))
{
    os_free_hook = hook;
}

#define HEAP_MAGIC 0x1ea0
struct heap_mem
{
    /* magic and used flag */
    uint16_t magic;
    uint16_t used;

    size_t next, prev;
};

/** pointer to the heap: for alignment, heap_ptr is now a pointer instead of an array */
static uint8_t *heap_ptr;

/** the last entry, always unused! */
static struct heap_mem *heap_end;

#define MIN_SIZE 12

#define MIN_SIZE_ALIGNED     ALIGN(MIN_SIZE, ALIGN_SIZE)
#define SIZEOF_STRUCT_MEM    ALIGN(sizeof(struct heap_mem), ALIGN_SIZE)

static struct heap_mem *lfree;   /* pointer to the lowest free block */

static struct sem heap_sem;
static size_t mem_size_aligned;
static size_t used_mem, max_mem;

static void plug_holes(struct heap_mem *mem)
{
    struct heap_mem *nmem;
    struct heap_mem *pmem;

    ASSERT((uint8_t *)mem >= heap_ptr);
    ASSERT((uint8_t *)mem < (uint8_t *)heap_end);
    ASSERT(mem->used == 0);

    /* plug hole forward */
    nmem = (struct heap_mem *)&heap_ptr[mem->next];
    if (mem != nmem &&
        nmem->used == 0 &&
        (uint8_t *)nmem != (uint8_t *)heap_end)
    {
        /* if mem->next is unused and not end of heap_ptr,
         * combine mem and mem->next
         */
        if (lfree == nmem)
        {
            lfree = mem;
        }
        mem->next = nmem->next;
        ((struct heap_mem *)&heap_ptr[nmem->next])->prev = (uint8_t *)mem - heap_ptr;
    }

    /* plug hole backward */
    pmem = (struct heap_mem *)&heap_ptr[mem->prev];
    if (pmem != mem && pmem->used == 0)
    {
        /* if mem->prev is unused, combine mem and mem->prev */
        if (lfree == mem)
        {
            lfree = pmem;
        }
        pmem->next = mem->next;
        ((struct heap_mem *)&heap_ptr[mem->next])->prev = (uint8_t *)pmem - heap_ptr;
    }
}

/**
 * @ingroup SystemInit
 *
 * This function will initialize system heap memory.
 *
 * @param begin_addr the beginning address of system heap memory.
 * @param end_addr the end address of system heap memory.
 */
void system_heap_init(void *begin_addr, void *end_addr)
{
    struct heap_mem *mem;
    ubase_t begin_align = ALIGN((ubase_t)begin_addr, ALIGN_SIZE);
    ubase_t end_align   = ALIGN_DOWN((ubase_t)end_addr, ALIGN_SIZE);

    DEBUG_NOT_IN_INTERRUPT;

    /* alignment addr */
    if ((end_align > (2 * SIZEOF_STRUCT_MEM)) &&
        ((end_align - 2 * SIZEOF_STRUCT_MEM) >= begin_align))
    {
        /* calculate the aligned memory size */
        mem_size_aligned = end_align - begin_align - 2 * SIZEOF_STRUCT_MEM;
    }
    else
    {
        printf("mem init, error begin address 0x%x, and end address 0x%x\n",
                   (ubase_t)begin_addr, (ubase_t)end_addr);

        return;
    }

    /* point to begin address of heap */
    heap_ptr = (uint8_t *)begin_align;

    DEBUG_LOG(DEBUG_MEM, ("mem init, heap begin address 0x%x, size %d\n",
            (ubase_t)heap_ptr, mem_size_aligned));

    /* initialize the start of the heap */
    mem        = (struct heap_mem *)heap_ptr;
    mem->magic = HEAP_MAGIC;
    mem->next  = mem_size_aligned + SIZEOF_STRUCT_MEM;
    mem->prev  = 0;
    mem->used  = 0;

    /* initialize the end of the heap */
    heap_end        = (struct heap_mem *)&heap_ptr[mem->next];
    heap_end->magic = HEAP_MAGIC;
    heap_end->used  = 1;
    heap_end->next  = mem_size_aligned + SIZEOF_STRUCT_MEM;
    heap_end->prev  = mem_size_aligned + SIZEOF_STRUCT_MEM;

    os_sem_init(&heap_sem, "heap", 1);

    /* initialize the lowest-free pointer to the start of the heap */
    lfree = (struct heap_mem *)heap_ptr;
}

/**
 * @addtogroup MM
 */

/**@{*/

/**
 * Allocate a block of memory with a minimum of 'size' bytes.
 *
 * @param size is the minimum size of the requested block in bytes.
 *
 * @return pointer to allocated memory or NULL if no free memory was found.
 */
void *malloc(size_t size)
{
    size_t ptr, ptr2;
    struct heap_mem *mem, *mem2;

    if (size == 0)
        return NULL;

    DEBUG_NOT_IN_INTERRUPT;

    if (size != ALIGN(size, ALIGN_SIZE))
        DEBUG_LOG(DEBUG_MEM, ("malloc size %d, but align to %d\n",
                size, ALIGN(size, ALIGN_SIZE)));
    else
        DEBUG_LOG(DEBUG_MEM, ("malloc size %d\n", size));

    /* alignment size */
    size = ALIGN(size, ALIGN_SIZE);

    if (size > mem_size_aligned)
    {
        DEBUG_LOG(DEBUG_MEM, ("no memory\n"));

        return NULL;
    }

    /* every data block must be at least MIN_SIZE_ALIGNED long */
    if (size < MIN_SIZE_ALIGNED)
        size = MIN_SIZE_ALIGNED;

    /* take memory semaphore */
    os_sem_take(&heap_sem, OS_WAITING_FOREVER);

    for (ptr = (uint8_t *)lfree - heap_ptr;
         ptr < mem_size_aligned - size;
         ptr = ((struct heap_mem *)&heap_ptr[ptr])->next)
    {
        mem = (struct heap_mem *)&heap_ptr[ptr];

        if ((!mem->used) && (mem->next - (ptr + SIZEOF_STRUCT_MEM)) >= size)
        {
            /* mem is not used and at least perfect fit is possible:
             * mem->next - (ptr + SIZEOF_STRUCT_MEM) gives us the 'user data size' of mem */

            if (mem->next - (ptr + SIZEOF_STRUCT_MEM) >=
                (size + SIZEOF_STRUCT_MEM + MIN_SIZE_ALIGNED))
            {
                /* (in addition to the above, we test if another struct heap_mem (SIZEOF_STRUCT_MEM) containing
                 * at least MIN_SIZE_ALIGNED of data also fits in the 'user data space' of 'mem')
                 * -> split large block, create empty remainder,
                 * remainder must be large enough to contain MIN_SIZE_ALIGNED data: if
                 * mem->next - (ptr + (2*SIZEOF_STRUCT_MEM)) == size,
                 * struct heap_mem would fit in but no data between mem2 and mem2->next
                 * @todo we could leave out MIN_SIZE_ALIGNED. We would create an empty
                 *       region that couldn't hold data, but when mem->next gets freed,
                 *       the 2 regions would be combined, resulting in more free memory
                 */
                ptr2 = ptr + SIZEOF_STRUCT_MEM + size;

                /* create mem2 struct */
                mem2       = (struct heap_mem *)&heap_ptr[ptr2];
                mem2->magic = HEAP_MAGIC;
                mem2->used = 0;
                mem2->next = mem->next;
                mem2->prev = ptr;

                /* and insert it between mem and mem->next */
                mem->next = ptr2;
                mem->used = 1;

                if (mem2->next != mem_size_aligned + SIZEOF_STRUCT_MEM)
                {
                    ((struct heap_mem *)&heap_ptr[mem2->next])->prev = ptr2;
                }
                used_mem += (size + SIZEOF_STRUCT_MEM);
                if (max_mem < used_mem)
                    max_mem = used_mem;
            }
            else
            {
                /* (a mem2 struct does no fit into the user data space of mem and mem->next will always
                 * be used at this point: if not we have 2 unused structs in a row, plug_holes should have
                 * take care of this).
                 * -> near fit or excact fit: do not split, no mem2 creation
                 * also can't move mem->next directly behind mem, since mem->next
                 * will always be used at this point!
                 */
                mem->used = 1;
                used_mem += mem->next - ((uint8_t *)mem - heap_ptr);
                if (max_mem < used_mem)
                    max_mem = used_mem;
            }
            /* set memory block magic */
            mem->magic = HEAP_MAGIC;

            if (mem == lfree)
            {
                /* Find next free block after mem and update lowest free pointer */
                while (lfree->used && lfree != heap_end)
                    lfree = (struct heap_mem *)&heap_ptr[lfree->next];

                ASSERT(((lfree == heap_end) || (!lfree->used)));
            }

            os_sem_release(&heap_sem);
            ASSERT((ubase_t)mem + SIZEOF_STRUCT_MEM + size <= (ubase_t)heap_end);
            ASSERT((ubase_t)((uint8_t *)mem + SIZEOF_STRUCT_MEM) % ALIGN_SIZE == 0);
            ASSERT((((ubase_t)mem) & (ALIGN_SIZE - 1)) == 0);

            DEBUG_LOG(DEBUG_MEM,
                         ("allocate memory at 0x%x, size: %d\n",
                                 (ubase_t)((uint8_t *)mem + SIZEOF_STRUCT_MEM),
                                 (ubase_t)(mem->next - ((uint8_t *)mem - heap_ptr))));

            OBJECT_HOOK_CALL(os_malloc_hook,
                                (((void *)((uint8_t *)mem + SIZEOF_STRUCT_MEM)), size));

            /* return the memory data except mem struct */
            return (uint8_t *)mem + SIZEOF_STRUCT_MEM;
        }
    }

    os_sem_release(&heap_sem);

    return NULL;
}

/**
 * This function will change the previously allocated memory block.
 *
 * @param rmem pointer to memory allocated by malloc
 * @param newsize the required new size
 *
 * @return the changed memory block address
 */
void *realloc(void *rmem, size_t newsize)
{
    size_t size;
    size_t ptr, ptr2;
    struct heap_mem *mem, *mem2;
    void *nmem;

    DEBUG_NOT_IN_INTERRUPT;

    /* alignment size */
    newsize = ALIGN(newsize, ALIGN_SIZE);
    if (newsize > mem_size_aligned)
    {
        DEBUG_LOG(DEBUG_MEM, ("realloc: out of memory\n"));

        return NULL;
    }
    else if (newsize == 0)
    {
        free(rmem);
        return NULL;
    }

    /* allocate a new memory block */
    if (rmem == NULL)
        return malloc(newsize);

    os_sem_take(&heap_sem, OS_WAITING_FOREVER);

    if ((uint8_t *)rmem < (uint8_t *)heap_ptr ||
        (uint8_t *)rmem >= (uint8_t *)heap_end)
    {
        /* illegal memory */
        os_sem_release(&heap_sem);

        return rmem;
    }

    mem = (struct heap_mem *)((uint8_t *)rmem - SIZEOF_STRUCT_MEM);

    ptr = (uint8_t *)mem - heap_ptr;
    size = mem->next - ptr - SIZEOF_STRUCT_MEM;
    if (size == newsize)
    {
        /* the size is the same as */
        os_sem_release(&heap_sem);

        return rmem;
    }

    if (newsize + SIZEOF_STRUCT_MEM + MIN_SIZE < size)
    {
        /* split memory block */

        ptr2 = ptr + SIZEOF_STRUCT_MEM + newsize;
        mem2 = (struct heap_mem *)&heap_ptr[ptr2];
        mem2->magic = HEAP_MAGIC;
        mem2->used = 0;
        mem2->next = mem->next;
        mem2->prev = ptr;
        mem->next = ptr2;
        if (mem2->next != mem_size_aligned + SIZEOF_STRUCT_MEM)
        {
            ((struct heap_mem *)&heap_ptr[mem2->next])->prev = ptr2;
        }

        if (mem2 < lfree)
        {
            /* the splited struct is now the lowest */
            lfree = mem2;
        }

        plug_holes(mem2);

        os_sem_release(&heap_sem);

        return rmem;
    }
    os_sem_release(&heap_sem);

    /* expand memory */
    nmem = malloc(newsize);
    if (nmem != NULL) /* check memory */
    {
        memcpy(nmem, rmem, size < newsize ? size : newsize);
        free(rmem);
    }

    return nmem;
}

/**
 * This function will contiguously allocate enough space for count objects
 * that are size bytes of memory each and returns a pointer to the allocated
 * memory.
 *
 * The allocated memory is filled with bytes of value zero.
 *
 * @param count number of objects to allocate
 * @param size size of the objects to allocate
 *
 * @return pointer to allocated memory / NULL pointer if there is an error
 */
void *calloc(size_t count, size_t size)
{
    void *p;

    /* allocate 'count' objects of size 'size' */
    p = malloc(count * size);

    /* zero the memory */
    if (p)
        memset(p, 0, count * size);

    return p;
}

/**
 * This function will release the previously allocated memory block by
 * malloc. The released memory block is taken back to system heap.
 *
 * @param rmem the address of memory which will be released
 */
void free(void *rmem)
{
    struct heap_mem *mem;

    if (rmem == NULL)
        return;

    DEBUG_NOT_IN_INTERRUPT;

    ASSERT((((ubase_t)rmem) & (ALIGN_SIZE - 1)) == 0);
    ASSERT((uint8_t *)rmem >= (uint8_t *)heap_ptr &&
              (uint8_t *)rmem < (uint8_t *)heap_end);

    OBJECT_HOOK_CALL(os_free_hook, (rmem));

    if ((uint8_t *)rmem < (uint8_t *)heap_ptr ||
        (uint8_t *)rmem >= (uint8_t *)heap_end)
    {
        DEBUG_LOG(DEBUG_MEM, ("illegal memory\n"));

        return;
    }

    /* Get the corresponding struct heap_mem ... */
    mem = (struct heap_mem *)((uint8_t *)rmem - SIZEOF_STRUCT_MEM);

    DEBUG_LOG(DEBUG_MEM,
                 ("release memory 0x%x, size: %d\n",
                         (ubase_t)rmem,
                         (ubase_t)(mem->next - ((uint8_t *)mem - heap_ptr))));


    /* protect the heap from concurrent access */
    os_sem_take(&heap_sem, OS_WAITING_FOREVER);

    /* ... which has to be in a used state ... */
    if (!mem->used || mem->magic != HEAP_MAGIC)
    {
        printf("to free a bad data block:\n");
        printf("mem: 0x%08x, used flag: %d, magic code: 0x%04x\n", mem, mem->used, mem->magic);
    }
    ASSERT(mem->used);
    ASSERT(mem->magic == HEAP_MAGIC);
    /* ... and is now unused. */
    mem->used  = 0;
    mem->magic = HEAP_MAGIC;

    if (mem < lfree)
    {
        /* the newly freed struct is now the lowest */
        lfree = mem;
    }

    used_mem -= (mem->next - ((uint8_t *)mem - heap_ptr));

    /* finally, see if prev or next are free also */
    plug_holes(mem);
    os_sem_release(&heap_sem);
}


void memory_info(uint32_t *total,
                    uint32_t *used,
                    uint32_t *max_used)
{
    if (total != NULL)
        *total = mem_size_aligned;
    if (used  != NULL)
        *used = used_mem;
    if (max_used != NULL)
        *max_used = max_mem;
}


#ifdef RT_USING_FINSH
#include <finsh.h>

void list_mem(void)
{
    printf("total memory: %d\n", mem_size_aligned);
    printf("used memory : %d\n", used_mem);
    printf("maximum allocated memory: %d\n", max_mem);
}
FINSH_FUNCTION_EXPORT(list_mem, list memory usage information)

#endif