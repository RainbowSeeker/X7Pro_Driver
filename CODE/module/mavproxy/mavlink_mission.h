

#ifndef MAVLINK_MISSION_H__
#define MAVLINK_MISSION_H__

#ifdef __cplusplus
extern "C" {
#endif

void handle_mission_message(mavlink_message_t* msg);

#ifdef __cplusplus
}
#endif

#endif
