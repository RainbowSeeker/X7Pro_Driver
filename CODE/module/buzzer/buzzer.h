#ifndef BUZZER_H__
#define BUZZER_H__

#ifdef __cplusplus
extern "C" {
#endif

void tone_play_startup(void);
int buzzer_on(void);
int buzzer_off(void);
int buzzer_init(void);
void buzzer_start_note(unsigned frequency);

#ifdef __cplusplus
}
#endif

#endif /* BUZZER_H__ */
