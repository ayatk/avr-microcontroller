/*
 * Othello
 *
 * Copyright (c) 2017-2018 ayatk.
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../std/types.h"
#include "../std/booliean.h"
#include "switch.h"

/** スイッチとチャタリング対策に使う変数 */
u_char state;
u_char sw_now;
int sw_cnt;

/** ピン変化割り込みとスイッチの処理に使用 */
u_char pc = 0;


/** スイッチのピン変化割り込み */
ISR(PCINT1_vect) {
    if (pc == 0) {
        pc = 1;
    }

    // ブロックしているピン変化割り込みをキャンセル
    PCIFR |= _BV(PCIF1);
}

void switch_init() {
    // PORTCのピン変化割り込み有効
    PCICR |= _BV(PCIE1);
    // 割り込みを認めるビット位置を指定
    PCMSK1 = _BV(PCINT12) | _BV(PCINT13);
    sw_now = 0x30;
    state = 0;
}

void switch_update() {
    if (pc) {
        sw_cnt = (sw_cnt < SW_INTERVAL) ? sw_cnt + 1 : 0;

        if (sw_cnt == 0) {
            sw_now = ((~PINC >> 4) & 3);
            pc = 0;
        }
    }
}

bool is_switch_changed() {
    if (sw_now != state) {
        state = sw_now;
        return true;
    }

    return false;
}

u_char get_switch_state() {
    return state;
}
