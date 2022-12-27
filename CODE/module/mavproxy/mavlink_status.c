

#include <common.h>
#include <mavlink.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "module/mavproxy/mavproxy.h"

static const mav_status_t mav_status[MAV_NOTICE_NUM] = {
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] calibration started: 2 gyro" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] calibration started: 2 accel" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] calibration started: 2 mag" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] calibration started: 2 level" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] calibration done:" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] calibration failed:" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] progress <0>" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] progress <10>" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] progress <20>" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] progress <30>" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] progress <40>" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] progress <50>" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] progress <60>" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] progress <70>" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] progress <80>" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] progress <90>" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] progress <100>" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] up orientation detected" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] down orientation detected" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] left orientation detected" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] right orientation detected" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] front orientation detected" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] back orientation detected" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] up side done, rotate to a different side" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] down side done, rotate to a different side" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] left side done, rotate to a different side" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] right side done, rotate to a different side" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] front side done, rotate to a different side" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "[cal] back side done, rotate to a different side" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "Welcome to use the StarryPilot!" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "Initialization Start:" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "Initialization finish! The Drone is ready to fly!" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "Sensor heating Start:" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "Sensor heating Finish!" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "Sensor heating is Disable!" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "Sensor check start:" },
    { .severity = MAV_SEVERITY_ERROR,
      .string = "Sensor check error!" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "Sensor check finish!" },
    { .severity = MAV_SEVERITY_ERROR,
      .string = "Gyro sensor undetected!" },
    { .severity = MAV_SEVERITY_ERROR,
      .string = "Gyro sensor uncalibrated!" },
    { .severity = MAV_SEVERITY_WARNING,
      .string = "Gyro sensor is need to calibrate!" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "Gyro sensor is OK!" },
    { .severity = MAV_SEVERITY_ERROR,
      .string = "Accel sensor uncalibrated!" },
    { .severity = MAV_SEVERITY_WARNING,
      .string = "Accel sensor is need to calibrate!" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "Accel sensor is OK!" },
    { .severity = MAV_SEVERITY_ERROR,
      .string = "Mag sensor undetected!" },
    { .severity = MAV_SEVERITY_ERROR,
      .string = "Mag sensor uncalibrated!" },
    { .severity = MAV_SEVERITY_WARNING,
      .string = "Mag sensor is need to calibrate!" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "Mag sensor is OK!" },
    { .severity = MAV_SEVERITY_ERROR,
      .string = "Baro sensor undetected!" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "Baro sensor is OK!" },
    { .severity = MAV_SEVERITY_ERROR,
      .string = "GPS undetected!" },
    { .severity = MAV_SEVERITY_INFO,
      .string = "GPS is OK!" },
};

mav_status_t mavlink_get_status_content(uint8_t status)
{
    return mav_status[status];
}

err_t mavlink_send_statustext(int severity, const char* fmt, ...)
{
    mavlink_statustext_t statustext;
    mavlink_message_t msg;
    mavlink_system_t mavlink_system = mavproxy_get_system();

    if (!fmt) {
        return E_EMPTY;
    }

    statustext.severity = severity;

    va_list ap;
    va_start(ap, fmt);
    vsnprintf((char*)statustext.text, sizeof(statustext.text), fmt, ap);
    va_end(ap);

    mavlink_msg_statustext_encode(mavlink_system.sysid, mavlink_system.compid, &msg, &statustext);

    return mavproxy_send_immediate_msg(&msg, true);
}
