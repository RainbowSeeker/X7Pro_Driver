#ifndef LIST_H__
#define LIST_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "common_def.h"
/*
 * Copied from include/linux/...
 */

#undef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) & ((TYPE*)0)->MEMBER)

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:        the pointer to the member.
 * @type:       the type of the container struct this is embedded in.
 * @member:     the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({          \
    void *__mptr = (void *)(ptr);                    \
    ((type *)(__mptr - offsetof(type, member))); })


/**
 * Double List structure
 */
struct list_node
{
    struct list_node *next;
    struct list_node *prev;
};
typedef struct list_node list_t;


#define LIST_HEAD_INIT(name) \
    {                        \
        &(name), &(name)     \
    }

#define LIST_HEAD(name) \
    struct list_node name = LIST_HEAD_INIT(name)

#define LIST_DEF(name) \
    struct list_node name = LIST_HEAD_INIT(name)

/**
 * @brief initialize a list
 *
 * @param l list to be initialized
 */
static inline void list_init(list_t *l)
{
    l->next = l->prev = l;
}

/**
 * @brief insert a node after a list
 *
 * @param l list to insert it
 * @param n new node to be inserted
 */
static inline void list_insert_after(list_t *l, struct list_node *n)
{
    l->next->prev = n;
    n->next = l->next;

    l->next = n;
    n->prev = l;
}

/**
 * @brief insert a node before a list
 *
 * @param n new node to be inserted
 * @param l list to insert it
 */
static inline void list_insert_before(list_t *l, struct list_node *n)
{
    l->prev->next = n;
    n->prev = l->prev;

    l->prev = n;
    n->next = l;
}

/**
 * @brief remove node from list.
 * @param n the node to remove from the list.
 */
static inline void list_remove(struct list_node *n)
{
    n->next->prev = n->prev;
    n->prev->next = n->next;

    n->next = n->prev = n;
}

/**
 * @brief tests whether a list is empty
 * @param l the list to test.
 */
static inline int list_isempty(const list_t *l)
{
    return l->next == l;
}

/**
 * @brief get the list length
 * @param l the list to get.
 */
static inline unsigned int list_len(const list_t *l)
{
    unsigned int len = 0;
    const list_t *p = l;
    while (p->next != l)
    {
        p = p->next;
        len ++;
    }

    return len;
}

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_add(struct list_node *new,
                              struct list_node *prev,
                              struct list_node *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

/**
 * list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
static inline void list_add(struct list_node *new, struct list_node *head)
{
    __list_add(new, head, head->next);
}

/**
 * list_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
static inline void list_add_tail(struct list_node *new, struct list_node *head)
{
    __list_add(new, head->prev, head);
}

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_del(struct list_node *prev, struct list_node *next)
{
    next->prev = prev;
    prev->next = next;
}

/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty() on entry does not return true after this, the entry is
 * in an undefined state.
 */
static inline void __list_del_entry(struct list_node *entry)
{
    __list_del(entry->prev, entry->next);
}

static inline void list_del(struct list_node *entry)
{
    __list_del_entry(entry);
    entry->next = NULL;
    entry->prev = NULL;
}

/**
 * list_is_first -- tests whether @list is the first entry in list @head
 * @list: the entry to test
 * @head: the head of the list
 */
static inline int list_is_first(const struct list_node *list,
                                const struct list_node *head)
{
    return list->prev == head;
}

/**
 * list_is_last - tests whether @list is the last entry in list @head
 * @list: the entry to test
 * @head: the head of the list
 */
static inline int list_is_last(const struct list_node *list,
                               const struct list_node *head)
{
    return list->next == head;
}

/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
static inline int list_empty(const struct list_node *head)
{
    return head->next == head;
}

/**
 * list_entry - get the struct for this entry
 * @ptr:	the &struct list_node pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_node within the struct.
 */
#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

/**
 * list_first_entry - get the first element from a list
 * @ptr:	the list head to take the element from.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_node within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define list_first_entry(ptr, type, member) \
    list_entry((ptr)->next, type, member)

/**
 * list_last_entry - get the last element from a list
 * @ptr:	the list head to take the element from.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_node within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define list_last_entry(ptr, type, member) \
    list_entry((ptr)->prev, type, member)

/**
 * list_next_entry - get the next element in list
 * @pos:	the type * to cursor
 * @member:	the name of the list_node within the struct.
 */
#define list_next_entry(pos, type, member) \
    list_entry((pos)->member.next, type, member)

/**
 * list_prev_entry - get the prev element in list
 * @pos:	the type * to cursor
 * @member:	the name of the list_node within the struct.
 */
#define list_prev_entry(pos, type, member) \
    list_entry((pos)->member.prev, type, member)

/**
 * list_for_each	-	iterate over a list
 * @pos:	the &struct list_node to use as a loop cursor.
 * @head:	the head for your list.
 */
#define list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

/**
 * list_for_each_prev	-	iterate over a list backwards
 * @pos:	the &struct list_node to use as a loop cursor.
 * @head:	the head for your list.
 */
#define list_for_each_prev(pos, head) \
    for (pos = (head)->prev; pos != (head); pos = pos->prev)

/**
 * list_for_each_safe - iterate over a list safe against removal of list entry
 * @pos:	the &struct list_node to use as a loop cursor.
 * @n:		another &struct list_node to use as temporary storage
 * @head:	the head for your list.
 */
#define list_for_each_safe(pos, n, head)                   \
    for (pos = (head)->next, n = pos->next; pos != (head); \
         pos = n, n = pos->next)

/**
 * list_for_each_prev_safe - iterate over a list backwards safe against removal of list entry
 * @pos:	the &struct list_node to use as a loop cursor.
 * @n:		another &struct list_node to use as temporary storage
 * @head:	the head for your list.
 */
#define list_for_each_prev_safe(pos, n, head) \
    for (pos = (head)->prev, n = pos->prev;   \
         pos != (head);                       \
         pos = n, n = pos->prev)

/**
 * list_for_each_entry	-	iterate over list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head for your list.
 * @member:	the name of the list_node within the struct.
 */
#define list_for_each_entry(pos, type, head, member) \
    for (pos = list_first_entry(head, type, member); \
         &pos->member != (head);                     \
         pos = list_next_entry(pos, type, member))

/**
 * list_for_each_entry_reverse - iterate backwards over list of given type.
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head for your list.
 * @member:	the name of the list_node within the struct.
 */
#define list_for_each_entry_reverse(pos, type, head, member) \
    for (pos = list_last_entry(head, type, member);          \
         &pos->member != (head);                             \
         pos = list_prev_entry(pos, type, member))


/**
 * Single List structure
 */
struct slist_node
{
    struct slist_node *next;                         /**< point to next node. */
};
typedef struct slist_node slist_t;                /**< Type for single list. */


#define SLIST_OBJECT_INIT(object) { NULL }

/**
 * @brief initialize a single list
 *
 * @param l the single list to be initialized
 */
static inline void slist_init(slist_t *l)
{
    l->next = NULL;
}

static inline void slist_append(slist_t *l, slist_t *n)
{
    struct slist_node *node;

    node = l;
    while (node->next) node = node->next;

    /* append the node to the tail */
    node->next = n;
    n->next = NULL;
}

static inline void slist_insert(slist_t *l, slist_t *n)
{
    n->next = l->next;
    l->next = n;
}

static inline unsigned int slist_len(const slist_t *l)
{
    unsigned int len = 0;
    const slist_t *list = l->next;
    while (list != NULL)
    {
        list = list->next;
        len++;
    }

    return len;
}

static inline slist_t *slist_remove(slist_t *l, slist_t *n)
{
    /* remove slist head */
    struct slist_node *node = l;
    while (node->next && node->next != n) node = node->next;

    /* remove node */
    if (node->next != (slist_t *) 0) node->next = node->next->next;

    return l;
}

static inline slist_t *slist_first(slist_t *l)
{
    return l->next;
}

static inline slist_t *slist_tail(slist_t *l)
{
    while (l->next) l = l->next;

    return l;
}

static inline slist_t *slist_next(slist_t *n)
{
    return n->next;
}

static inline int slist_isempty(slist_t *l)
{
    return l->next == NULL;
}

/**
 * @brief get the struct for this single list node
 * @param node the entry point
 * @param type the type of structure
 * @param member the name of list in structure
 */
#define slist_entry(node, type, member) \
    container_of(node, type, member)

/**
 * slist_for_each - iterate over a single list
 * @pos:    the slist_t * to use as a loop cursor.
 * @head:   the head for your single list.
 */
#define slist_for_each(pos, head) \
    for (pos = (head)->next; pos != NULL; pos = pos->next)

/**
 * slist_for_each_entry  -   iterate over single list of given type
 * @pos:    the type * to use as a loop cursor.
 * @head:   the head for your single list.
 * @member: the name of the list_struct within the struct.
 */
#define slist_for_each_entry(pos, head, member) \
    for (pos = slist_entry((head)->next, typeof(*pos), member); \
         &pos->member != (NULL); \
         pos = slist_entry(pos->member.next, typeof(*pos), member))

/**
 * slist_first_entry - get the first element from a slist
 * @ptr:    the slist head to take the element from.
 * @type:   the type of the struct this is embedded in.
 * @member: the name of the slist_struct within the struct.
 *
 * Note, that slist is expected to be not empty.
 */
#define slist_first_entry(ptr, type, member) \
    slist_entry((ptr)->next, type, member)

/**
 * slist_tail_entry - get the tail element from a slist
 * @ptr:    the slist head to take the element from.
 * @type:   the type of the struct this is embedded in.
 * @member: the name of the slist_struct within the struct.
 *
 * Note, that slist is expected to be not empty.
 */
#define slist_tail_entry(ptr, type, member) \
    slist_entry(slist_tail(ptr), type, member)


#ifdef __cplusplus
}
#endif

#endif
