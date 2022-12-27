
#ifndef MAVPROXY_H__
#define MAVPROXY_H__

#include <common.h>
#include <mavlink.h>

#include "module/mavproxy/mavlink_console.h"
#include "module/mavproxy/mavlink_mission.h"
#include "module/mavproxy/mavlink_param.h"
#include "module/mavproxy/mavlink_status.h"
#include "module/mavproxy/mavproxy_cmd.h"
#include "module/mavproxy/mavproxy_dev.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EVENT_MAVPROXY_UPDATE    (1 << 0)
#define EVENT_MAVCONSOLE_TIMEOUT (1 << 1)
#define EVENT_SEND_ALL_PARAM     (1 << 2)

typedef bool (*msg_pack_cb_t)(mavlink_message_t* msg_t);

err_t mavproxy_init(void);
void mavproxy_loop(void);
mavlink_system_t mavproxy_get_system(void);
err_t mavproxy_set_channel(uint8_t chan);
err_t mavproxy_send_event(uint32_t event_set);
err_t mavproxy_send_immediate_msg(const mavlink_message_t* msg, bool sync);
err_t mavproxy_register_period_msg(uint8_t msgid, uint16_t period_ms, msg_pack_cb_t msg_pack_cb, bool auto_start);

#ifdef __cplusplus
}
#endif

#endif
