/*
 * Othello
 *
 * Copyright (c) 2017-2018 ayatk.
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#include <avr/interrupt.h>
#include "../std/types.h"
#include "sound.h"

static u_char period;

void sound_init() {
    // タイマ2(CTC): ブザー用
    TCCR2A = 0;
    //  1/64  , コンペアマッチ出力B有効（トグル）
    TCCR2B = 0x44;
}

void beep(u_char tone, u_char length) {
    OCR2A = tone;
    period = length;
    TCCR2A = 0x12;
}

void sound_update() {
    if (period) {
        if (--period == 0) {
            TCCR2A = 0;
        }
    }
}
