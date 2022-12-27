

#ifndef MAVLINK_CONSOLE_H__
#define MAVLINK_CONSOLE_H__

#include <common.h>
#include <mavlink.h>

#ifdef __cplusplus
extern "C" {
#endif

err_t mavlink_console_init(void);
void mavlink_console_process_rx_msg(const mavlink_serial_control_t* serial_control);
void mavlink_console_handle_timeout(void);

#ifdef __cplusplus
}
#endif

#endif
