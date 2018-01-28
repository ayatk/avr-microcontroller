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

// スイッチの状態
enum Switch state;
u_char sw_now;
int sw_cnt;

bool pc = false;


ISR(PCINT1_vect) {
    pc = !pc;

    // PORTCのピン変化割り込み有効
    PCIFR |= _BV(PCIF1);
}

void switch_init() {
    // PORTCのピン変化割り込み有効
    PCICR |= _BV(PCIE1);

    // 割り込みを認めるビット位置を指定
    PCMSK1 = _BV(PCINT12) | _BV(PCINT13);
}

void switch_update() {
    if (pc) {
        sw_cnt = (sw_cnt < SW_INTERVAL) ? sw_cnt + 1 : 0;

        if (sw_cnt == 0) {
            sw_now = ((~PINC >> 4) & 3);
            pc = false;
        }
    }
}

bool is_switch_changed() {
    if (sw_now != state) {
        state = (enum Switch) sw_now;
        return true;
    }

    return false;
}

enum Switch get_switch_state() {
    return state;
}
