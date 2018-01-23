/*
 * Othello
 *
 * Copyright (c) 2017-2018 ayatk.
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#include <avr/interrupt.h>
#include "std/types.h"
#include "std/rand.h"
#include "board.h"
#include "player.h"


// 表示用
static u_char _led[LED_SIZE];

u_char matrix[LED_SIZE][LED_SIZE];

/* マトリクスLEDのダイナミック点灯(2ms毎) */
ISR (TIMER0_COMPA_vect) {
    static u_char sc = 0xFE;
    static u_char scan = 0; //  LED 走査カウンタ
    u_char i;

    // LEDの更新
    PORTB = 0;    // 残像対策
    sc = (sc << 1) | (sc >> 7);
    PORTD = (PORTD & 0x0F) | (sc & 0xF0);   // 上位4ビット書き換え
    PORTC = (PORTC & 0xF0) | (sc & 0x0F);   // 下位4ビット書き換え
    scan = (u_char) ((scan + 1) & 7);
    _led[scan] = 0; // LEDを綺麗にする

    for (i = 0; i < LED_SIZE; i++) {
        if (scan == player_get_y() && player_get_x() == i) {
            _led[scan] |= 1 << i;
        }

        switch (matrix[scan][i]) {
        case BLACK:

            // 擬似乱数がグレイコードなので0x18ぐらいが
            // ちょうどいい点滅間隔
            if (!(rand() & 0x18)) {
                _led[scan] |= 1 << i;
            }

            break;

        case WHITE:
            _led[scan] |= 1 << i;
            break;
        }

    }

    PORTB = _led[scan];
}

/**
 * LEDの初期化処理
 */
void board_init() {
    // タイマ0(CTC): ダイナミック点灯用
    OCR0A = 25; // 100マイクロ秒
    TCCR0A = 2;
    TCCR0B = 2; // PS=32
    TIMSK0 |= (1 << OCIE0A); // コンペアマッチA割り込み有効

    board_reset();
}

/**
 * LEDを全てOFFにする
 */
void board_reset() {
    u_char i, j;

    for (i = 0; i < LED_SIZE; i++) {
        for (j = 0; j < LED_SIZE; j++) {
            matrix[i][j] = NONE;
        }

        _led[i] = 0;
    }
}

