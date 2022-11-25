// Copyright (c) 2022 By RainbowSeeker.

//
// Created by 19114 on 2022/11/22.
//

#include "mcn.h"
#include "string.h"
#include "sys.h"


static mcn_list_t __mcn_list = {.hub = NULL, .next = NULL};
static osTimerId timer_mcn_freq_est;

/**
 * @brief Topic publish frequency estimator entry
 *
 * @param parameter Unused
 */
static void mcn_freq_est_entry(const void *parameter)
{
    for (mcn_list_t *cp = &__mcn_list; cp != NULL; cp = cp->next)
    {
        mcn_hub_t *hub = cp->hub;
        if (hub == NULL)
        {
            break;
        }

        /* calculate publish frequency */
        uint32_t cnt = 0;
        for (int i = 0; i < MCN_FREQ_EST_WINDOW_LEN; i++)
        {
            cnt += hub->freq_est_window[i];
            hub->freq = (float) cnt / MCN_FREQ_EST_WINDOW_LEN;
        }
        /* move window */
        hub->window_index = (hub->window_index + 1) % MCN_FREQ_EST_WINDOW_LEN;
        hub->freq_est_window[hub->window_index] = 0;
    }
}

/**
 * @brief Clear uMCN node renewal flag
 *
 * @param node_t uMCN node
 */
void mcn_node_clear(mcn_node_t *node_t)
{
    assert(node_t != NULL);

    if (node_t == NULL)
    {
        return;
    }

    OS_ENTER_CRITICAL;
    node_t->renewal = 0;
    OS_EXIT_CRITICAL;
}

/**
 * @brief Suspend a uMCN topic
 *
 * @param hub uMCN hub
 */
void mcn_suspend(mcn_hub_t *hub)
{
    hub->suspend = 1;
}

/**
 * @brief Resume a uMCN topic
 *
 * @param hub uMCN hub
 */
void mcn_resume(mcn_hub_t *hub)
{
    hub->suspend = 0;
}

/**
 * @brief Get uMCN list
 *
 * @return mcn_list_t *uMCN list pointer
 */
mcn_list_t *mcn_get_list(void)
{
    return &__mcn_list;
}

/**
 * @brief Iterate all uMCN hubs in list
 *
 * @param ite uMCN list pointer
 * @return mcn_hub_t *uMCN hub
 */
mcn_hub_t *mcn_iterate(mcn_list_t **ite)
{
    mcn_hub_t *hub;
    mcn_list_t *node = *ite;

    if (node == NULL)
    {
        return NULL;
    }
    hub = node->hub;
    *ite = node->next;

    return hub;
}

/**
 * @brief Poll for topic status
 * @note This function would return immediately
 *
 * @param node_t uMCN node
 * @return true Topic updated
 * @return false Topic not updated
 */
bool mcn_poll(mcn_node_t *node_t)
{
    bool renewal;

    assert(node_t != NULL);

    OS_ENTER_CRITICAL;
    renewal = node_t->renewal;
    OS_EXIT_CRITICAL;

    return renewal;
}

/**
 * @brief Wait for topic update
 * @note event must has been provided when subscribe the topic
 *
 * @param node_t uMCN node
 * @param timeout Wait timeout
 * @return true Topic updated
 * @return false Topic not updated
 */
bool mcn_wait(mcn_node_t *node_t, int32_t timeout)
{
    assert(node_t != NULL);
    assert(node_t->event != NULL);

    return osSemaphoreWait(node_t->event, timeout) == 0 ? true : false;
}

/**
 * @brief Copy uMCN topic data from hub
 * @note This function will clear the renewal flag
 *
 * @param hub uMCN hub
 * @param node_t uMCN node
 * @param buffer buffer to received the data
 * @return err_status_e E_OK indicates success
 */
err_status_e mcn_copy(mcn_hub_t *hub, mcn_node_t *node_t, void *buffer)
{
    assert(hub != NULL);
    assert(node_t != NULL);
    assert(buffer != NULL);

    if (hub->pdata == NULL)
    {
        /* copy from non-advertised hub */
        return E_RROR;
    }

    if (!hub->published)
    {
        /* copy before published */
        return E_NOTHANDLE;
    }

    OS_ENTER_CRITICAL;
    memcpy(buffer, hub->pdata, hub->obj_size);
    node_t->renewal = 0;
    OS_EXIT_CRITICAL;

    return E_OK;
}

/**
 * @brief Copy uMCN topic data from hub
 * @note This function will directly copy topic data from hub no matter it has been
 * updated or not and won't clear the renewal flag
 *
 * @param hub
 * @param buffer
 * @return err_status_e
 */
err_status_e mcn_copy_from_hub(mcn_hub_t *hub, void *buffer)
{
    assert(hub != NULL);
    assert(buffer != NULL);

    if (hub->pdata == NULL)
    {
        /* copy from non-advertised hub */
        return E_RROR;
    }

    if (!hub->published)
    {
        /* copy before published */
        return E_NOTHANDLE;
    }

    OS_ENTER_CRITICAL;
    memcpy(buffer, hub->pdata, hub->obj_size);
    OS_EXIT_CRITICAL;

    return E_OK;
}

/**
 * @brief Advertise a uMCN topic
 *
 * @param hub uMCN hub
 * @param echo Echo function to print topic contents
 * @return err_status_e E_OK indicates success
 */
err_status_e mcn_advertise(mcn_hub_t *hub, int (*echo)(void *parameter))
{
    void *pdata;
    void *next;

    assert(hub != NULL);

    if (hub->pdata != NULL)
    {
        /* already advertised */
        return E_NOTHANDLE;
    }

    pdata = MCN_MALLOC(hub->obj_size);
    if (pdata == NULL)
    {
        return E_NOMEM;
    }
    memset(pdata, 0, hub->obj_size);

    next = MCN_MALLOC(sizeof(mcn_list_t));
    if (next == NULL)
    {
        MCN_FREE(pdata);
        return E_NOMEM;
    }

    OS_ENTER_CRITICAL;
    hub->pdata = pdata;
    hub->echo = echo;

    /* update Mcn List */
    mcn_list_t *cp = &__mcn_list;

    while (cp->next != NULL)
    {
        /* find last node */
        cp = cp->next;
    }

    if (cp->hub != NULL)
    {
        cp->next = (mcn_list_t *) next;
        cp = cp->next;
    }

    cp->hub = hub;
    cp->next = NULL;

    /* init publish freq estimator window */
    memset(hub->freq_est_window, 0, 2 * MCN_FREQ_EST_WINDOW_LEN);
    hub->window_index = 0;

    OS_EXIT_CRITICAL;

    return E_OK;
}

/**
 * @brief Subscribe a uMCN topic
 *
 * @param hub uMCN hub
 * @param event Event handler to provide synchronize poll
 * @param pub_cb Topic published callback function
 * @return mcn_node_t *Subscribe node, return NULL if fail
 */
mcn_node_t *mcn_subscribe(mcn_hub_t *hub, osSemaphoreId event, void (*pub_cb)(void *parameter))
{
    assert(hub != NULL);

    if (hub->link_num >= MCN_MAX_LINK_NUM)
    {
        printf("mcn link num is already full!\n");
        return NULL;
    }

    mcn_node_t *node = (mcn_node_t *) MCN_MALLOC(sizeof(mcn_node_t));

    if (node == NULL)
    {
        printf("mcn create node fail!\n");
        return NULL;
    }

    node->renewal = 0;
    node->event = event;
    node->pub_cb = pub_cb;
    node->next = NULL;

    OS_ENTER_CRITICAL;

    /* no node link yet */
    if (hub->link_tail == NULL)
    {
        hub->link_head = hub->link_tail = node;
    }
    else
    {
        hub->link_tail->next = node;
        hub->link_tail = node;
    }

    hub->link_num++;
    OS_EXIT_CRITICAL;

    if (hub->published)
    {
        /* update renewal flag as it's already published */
        node->renewal = 1;

        if (node->pub_cb)
        {
            /* if data published before subscribe, then call callback immediately */
            node->pub_cb(hub->pdata);
        }
    }

    return node;
}

/**
 * @brief Unsubscribe a uMCN topic
 *
 * @param hub uMCN hub
 * @param node Subscribe node
 * @return err_status_e E_OK indicates success
 */
err_status_e mcn_unsubscribe(mcn_hub_t *hub, mcn_node_t *node)
{
    assert(hub != NULL);
    assert(node != NULL);

    /* traverse each node */
    mcn_node_t *cur_node = hub->link_head;
    mcn_node_t *pre_node = NULL;

    while (cur_node != NULL)
    {
        if (cur_node == node)
        {
            /* find node */
            break;
        }

        pre_node = cur_node;
        cur_node = cur_node->next;
    }

    if (cur_node == NULL)
    {
        /* can not find */
        return E_EMPTY;
    }

    /* update list */
    OS_ENTER_CRITICAL;

    if (hub->link_num == 1)
    {
        hub->link_head = hub->link_tail = NULL;
    }
    else
    {
        if (cur_node == hub->link_head)
        {
            hub->link_head = cur_node->next;
        }
        else if (cur_node == hub->link_tail)
        {
            if (pre_node)
            {
                pre_node->next = NULL;
            }
            hub->link_tail = pre_node;
        }
        else
        {
            pre_node->next = cur_node->next;
        }
    }

    hub->link_num--;
    OS_EXIT_CRITICAL;

    /* free current node */
    MCN_FREE(cur_node);
    // cur_node = NULL;

    return E_OK;
}

/**
 * @brief Publish uMCN topic
 *
 * @param hub uMCN hub, which can be obtained by MCN_HUB() macro
 * @param data Data of topic to publish
 * @return err_status_e E_OK indicates success
 */
err_status_e mcn_publish(mcn_hub_t *hub, const void *data)
{
    assert(hub != NULL);
    assert(data != NULL);

    if (hub->pdata == NULL)
    {
        /* hub is not advertised yet */
        return E_RROR;
    }

    if (hub->suspend)
    {
        return E_NOTHANDLE;
    }

    /* update freq estimator window */
    hub->freq_est_window[hub->window_index]++;

    OS_ENTER_CRITICAL;
    /* copy data to hub */
    memcpy(hub->pdata, data, hub->obj_size);
    /* traverse each node */
    mcn_node_t *node = hub->link_head;

    while (node != NULL)
    {
        /* update each node's renewal flag */
        node->renewal = 1;
        /* send out event to wakeup waiting task */
        if (node->event)
        {
            osSemaphoreRelease(node->event);
        }

        node = node->next;
    }

    hub->published = 1;
    OS_EXIT_CRITICAL;

    /* invoke callback func */
    node = hub->link_head;

    while (node != NULL)
    {
        if (node->pub_cb != NULL)
        {
            node->pub_cb(hub->pdata);
        }

        node = node->next;
    }

    return E_OK;
}

/**
 * @brief Initialize uMCN module
 *
 * @return err_status_e E_OK indicates success
 */
err_status_e mcn_init(void)
{
    osTimerDef(mcn, mcn_freq_est_entry);
    timer_mcn_freq_est = osTimerCreate(osTimer(mcn), osTimerPeriodic, NULL);

    if (osTimerStart(timer_mcn_freq_est, 1000) != osOK)
    {
        return E_RROR;
    }

    return E_OK;
}

