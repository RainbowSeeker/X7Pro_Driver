#ifndef BUZZER_TUNE_H__
#define BUZZER_TUNE_H__

#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TUNE_STARTUP  0
#define TUNE_ERROR    1
#define TUNE_SD_ERROR 2

int buzzer_tune_init(void);
int buzzer_tune_play(int tune);

#ifdef __cplusplus
}
#endif

#endif
