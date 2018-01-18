#ifndef _OTHELLO_LIBS_SOUND_H_
#define _OTHELLO_LIBS_SOUND_H_

/**
 * ブザーの音階
 */
enum {
    BEEP_C4 = 238,
    BEEP_CS4 = 225,
    BEEP_D4 = 212,
    BEEP_DS4 = 200,
    BEEP_E4 = 189,
    BEEP_F4 = 178,
    BEEP_FS4 = 168,
    BEEP_G4 = 159,
    BEEP_GS4 = 150,
    BEEP_A4 = 142,
    BEEP_AS4 = 134,
    BEEP_B4 = 126,
    BEEP_C5 = 119,
    BEEP_CS5 = 113,
    BEEP_D5 = 106,
    BEEP_DS5 = 100,
    BEEP_E5 = 95,
    BEEP_F5 = 89,
    BEEP_FS5 = 84,
    BEEP_G5 = 80,
    BEEP_GS5 = 75,
    BEEP_A5 = 71,
    BEEP_AS5 = 67,
    BEEP_B5 = 63,
};

/**
 * ブザーの初期化処理
 */
void init_sound(void);

/**
 * 音を鳴らす
 * @param tone ブザの音程
 * @param length 鳴らす長さ
 */
void sound(unsigned char tone, unsigned char length);

/**
 * ブザーの状態を更新する処理
 */
void sound_update(void);

#endif 
