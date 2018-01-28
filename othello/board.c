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
#include "std/types.h"
#include "std/booliean.h"
#include "board.h"
#include "player.h"

int count;
u_char led[LED_SIZE];
static u_char scan;

static bool display_target = false;

ISR(TIMER1_COMPA_vect) {
    u_char sc;
    int x;
    PORTB = 0; // led表示初期化
    scan = (scan + 1) & 7;
    sc = ~(1 << scan);
    led[scan] = 0; // led表示初期化
    PORTC = 0x30 | (sc & 0x0f);// スイッチ用のプルアップを兼ねる
    PORTD = sc & 0xf0;

    count = (count >= NONE - 1) ? 1 : count + 1;

    for (x = 0; x < LED_SIZE; x++) {
        int timing = 1;

        if (display_target == 1
                && scan == LED_SIZE - get_cursor_y() - 1
                && get_cursor_x() == x) {
            timing = get_cursor_color();
        } else {
            timing = matrix[LED_SIZE - scan - 1][x];
        }

        if (count % timing == 0) {
            u_char temp = 1 << (LED_SIZE - x - 1);
            led[scan] |= temp;
        }
    }

    PORTB = led[scan];
}

void board_init() {
    count = 0;
    board_reset();

    // タイマ1(CTC): ダイナミック点灯用
    TCCR1A = 0;
    TCCR1B = 0b00001010; // CTCモード(OCR1A), PS=8
    OCR1A = 500;
    TIMSK1 |= (1 << OCIE1A); // コンペアマッチA割り込み有効
}

void board_reset() {
    int x, y;

    for (y = 0; y < LED_SIZE; y++) {
        for (x = 0; x < LED_SIZE; x++) {
            matrix[y][x] = NONE;
        }

        led[y] = 0;
    }
}

void cursor_visible(bool enable) {
    display_target = enable;
}


void sort_led() {
    int ix = 0, iy = 0;
    int x, y;

    for (y = 0; y < LED_SIZE; y++) {
        for (x = 0; x < LED_SIZE; x++) {
            if (matrix[y][x] == WHITE) {
                // スワップ
                matrix[iy][ix] ^= matrix[y][x] ^= matrix[iy][ix] ^= matrix[y][x];
                ix++;

                if (ix == LED_SIZE) {
                    ix = 0;
                    iy++;
                }
            }
        }
    }
}

