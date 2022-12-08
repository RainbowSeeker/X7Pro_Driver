#include <common.h>
#include "player.h"

int player_play(player_t player)
{
    uint32_t level;

    if ((player->status != PLAYER_RUNNING) || (player->playing != 1)) {
        /* 关闭全局中断 */
        level = os_hw_interrupt_disable();

        /* 设定播放状态为播放状态 */
        player->status = PLAYER_RUNNING;

        /* 打开全局中断 */
        os_hw_interrupt_enable(level);

        /*释放信号量通知播放线程开始播放*/
        os_sem_release(player->sem_play);
    }

    return 0;
}

int player_stop(player_t player)
{
    uint32_t level;

    if (player->status == PLAYER_RUNNING) {
        /* 关闭全局中断 */
        level = os_hw_interrupt_disable();

        /* 设定播放状态为播放状态 */
        player->status = PLAYER_STOP;
        player->song_current = 0;   //正在播放的歌曲
        player->song_num = 0;       //歌曲总数
        player->song_time_pass = 0; //已经播放的时间

        /* 打开全局中断 */
        os_hw_interrupt_enable(level);
    }

    return 0;
}

int player_last(player_t player)
{
    uint16_t len;
    uint32_t level;

    /* 关闭全局中断 */
    level = os_hw_interrupt_disable();

    /* 将当前播放歌曲的序号 减一 */
    if (player->song_current > 1) {
        player->song_current--;
    } else {
        player->song_current = player->song_num;
    }

    /* 更新播放器的当前歌曲的播放时间以及总时间 */
    player->song_time_pass = 0;

    /* 打开全局中断 */
    os_hw_interrupt_enable(level);

    player->decode->control(player->song_sheet[player->song_current - 1], DECODE_OPS_CMD_GET_LEN, &len);

    /* 关闭全局中断 */
    level = os_hw_interrupt_disable();

    player->song_time_all = len;

    /* 打开全局中断 */
    os_hw_interrupt_enable(level);

    if (player->status != PLAYER_RUNNING) {
        player_play(player);
    }

    return 0;
}

int player_next(player_t player)
{
    uint16_t len;
    uint32_t level;

    /* 关闭全局中断 */
    // level = os_hw_interrupt_disable();

    /* 将当前播放歌曲的序号 加一 */
    if (player->song_current < player->song_num) {
        player->song_current++;
    } else {
        player->song_current = 1;
        player_stop(player);
        return 0;
    }

    /* 更新播放器的当前歌曲的播放时间以及总时间 */
    player->song_time_pass = 0;

    /* 打开全局中断 */
    // os_hw_interrupt_enable(level);

    player->decode->control(player->song_sheet[player->song_current - 1], DECODE_OPS_CMD_GET_LEN, &len);

    /* 关闭全局中断 */
    level = os_hw_interrupt_disable();

    player->song_time_all = len;

    /* 打开全局中断 */
    os_hw_interrupt_enable(level);

    if (player->status != PLAYER_RUNNING) {
        player_play(player);
    }

    return 0;
}
int player_control(player_t player, int cmd, void* arg)
{
    uint32_t level;

    switch (cmd) {
    case PLAYER_CMD_PLAY:
        player_play(player);
        break;

    case PLAYER_CMD_STOP:
        player_stop(player);
        break;

    case PLAYER_CMD_LAST:
        player_last(player);
        break;

    case PLAYER_CMD_NEXT:
        player_next(player);
        break;

    case PLAYER_CMD_SET_VOL:
        /* 关闭全局中断 */
        level = os_hw_interrupt_disable();
        player->volume = *(uint8_t*)arg;
        /* 打开全局中断 */
        os_hw_interrupt_enable(level);
        player->audio->control(AUDIO_OPS_CMD_SET_VOL, &player->volume);
        break;

    case PLAYER_CMD_GET_VOL:
        *(uint8_t*)arg = player->volume;
        break;

    case PLAYER_CMD_GET_STATUS:
        *(uint8_t*)arg = player->status;
        break;
    }

    return 0;
}
int player_add_song(player_t player, void* song)
{
    uint32_t level;

    if (player->song_num == PLAYER_SONG_NUM_MAX) {
        return -1;
    }

    /* 关闭全局中断 */
    level = os_hw_interrupt_disable();

    player->song_sheet[player->song_num] = song;
    player->song_num++;

    /* 打开全局中断 */
    os_hw_interrupt_enable(level);

    return 0;
}

int player_show(player_t player)
{
    char name[PLAYER_SONG_NAME_LEN_MAX + 1];
    uint8_t i;
    uint16_t percent;

    printf("*********** Beep Player ***********\n");

    /* 打印歌单 */
    for (i = 0; i < player->song_num; i++) {
        player->decode->control(player->song_sheet[i], DECODE_OPS_CMD_GET_NAME, name);
        printf("%02d. %s\n", i + 1, name);
    }

    /* 打印当前播放状态 */
    if (PLAYER_RUNNING == player->status) {
        printf("<---  正在播放：");
    } else {
        printf("<---  暂停播放：");
    }

    /* 打印当前歌曲 */
    player->decode->control(player->song_sheet[player->song_current - 1], DECODE_OPS_CMD_GET_NAME, name);
    printf("%s", name);
    printf("--->\n");

    /* 打印播放进度 */
    percent = player->song_time_pass * 100 / player->song_time_all;
    printf("播放进度：%02d%%  音量大小：%02d%%\n", percent, player->volume);

    printf("***********************************\n");

    return 0;
}

static void player_entry(void* parameter)
{
    player_t player = (player_t)parameter;
    uint8_t buffer[PLAYER_BUFFER_SIZE], size;

    while (1) {
        if (player->status == PLAYER_RUNNING) {
            player->playing = 1;
            size = player->song_time_all - player->song_time_pass;

            if (size > PLAYER_BUFFER_SIZE)
                size = PLAYER_BUFFER_SIZE;

            size = player->decode->read(player->song_sheet[player->song_current - 1], player->song_time_pass, buffer, size);

            if (size > 0) {
                player->audio->write(buffer, size);
                player->song_time_pass += size;
            }

            /* 如果播放时间到了，切换到下一首 */
            if (player->song_time_pass >= player->song_time_all) {
                player_next(player);
                // player_show(player);
            }
        } else {
            player->playing = 0;
            /* 暂停播放时关闭音频设备*/
            player->audio->close();

            /* 等待播放的信号量 */
            os_sem_take(player->sem_play, osWaitForever);

            /* 开始播放时打开音频设备*/
            player->audio->open();
        }
    }
}

int player_start(player_t player)
{
    uint16_t len;
    static uint8_t inited = 0;

    /* 检测播放器是否已经在运行 */
    if (inited == 1) {
        return -E_RROR;
    }

    if (player->song_num == 0) {
        return -1;
    }

    /* 调用接口初始化解码器 */
    player->decode->init();

    player->status = PLAYER_STOP;
    player->volume = PLAYER_SOUND_SIZE_DEFAULT;
    player->song_current = 1;
    player->song_time_pass = 0;
    player->decode->control(player->song_sheet[player->song_current - 1], DECODE_OPS_CMD_GET_LEN, &len);
    player->song_time_all = len;

    /* 调用接口初始化音频设备 */
    player->audio->init();
    player->audio->control(AUDIO_OPS_CMD_SET_VOL, &player->volume);

    /* 初始化动态信号量 */
    os_sem_create(&player->sem_play);

    if (player->sem_play == NULL) {
        return -E_RROR;
    }

    /* 创建动态线程 */
    player->play_thread = os_thread_create("player",
                                           player_entry,
                                           player,
                                           20,
                                           512);

    if (player->play_thread != NULL) {
//        rt_thread_startup(player->play_thread);
    } else {
        os_sem_delete(player->sem_play);
        return -E_RROR;
    }

    inited = 1;

    return 0;
}
