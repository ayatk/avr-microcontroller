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
#include <avr/wdt.h>
#include "std/types.h"
#include "std/booliean.h"
#include "libs/sound.h"
#include "libs/switch.h"
#include "player.h"
#include "board.h"
#include "othello.h"
#include "judgment.h"
#include "ai.h"

enum GameState {
    PLAYING,
    FINISH,
};

static enum GameState game_state = PLAYING;

static int ai_clk;

static u_char clk;
static int cursor_clk;


/** 2ms毎に呼ばれる関数（タイマカウンタ）*/
ISR(TIMER0_COMPA_vect) {
    // 100msごとにgame_mainを起動する
    if (++clk >= 50) {
        clk = 0;
        // 指定した時間になると停止させる
        sound_update();
    }

    // AIのターン
    if (get_player_turn() == AI) {
        if (++ai_clk >= 500) {
            ai_clk = 0;

            // AIが石をおく。
            // どこにも置けなければゲーム終了
            if (ai(get_player_color())) {
                if (is_finish_game(get_player_color()) > 0) {
                    game_state = FINISH;
                }
            }
        }
    }

    if (++cursor_clk >= 250) {
        cursor_clk = 0;
        target_reverse_state();
    }
}

int main(void) {
    // LED,スイッチ,ブザーのポート設定
    DDRB = 0xFF;
    DDRC = 0x0F;
    DDRD = 0xFA;
    PORTC = 0x30;   // 入力ピンをプルアップ
    PORTD = 0x00;

    OCR0A = 249; // 2ms
    TCCR0A = 2; // CTC MODE
    TCCR0B = 3; // 64PS
    TIMSK0 |= (1 << OCIE0A);

    // 初期化
    board_init();
    switch_init();
    sound_init();
    board_reset();

    matrix[3][3] = WHITE;
    matrix[4][4] = WHITE;
    matrix[3][4] = BLACK;
    matrix[4][3] = BLACK;
    target_init(2, 4, PLAYER);
    game_state = PLAYING;
    cursor_visible(true);

    // 割り込み処理を実行
    sei();

    while (true) {
        wdt_reset();
        switch_update();

        // ゲームの状態によって処理を変える
        switch (game_state) {
        case PLAYING:
            othello_play();
            break;

        case FINISH:
            cursor_visible(false);
            sort_led();
            break;
        }
    }

    return 0;
}


void othello_play() {
    // スイッチの結果を更新
    if (is_switch_changed()) {
        switch (get_switch_state()) {
        case SWITCH_LEFT:
            cursor_move_left();
            break;

        case SWITCH_RIGHT:
            cursor_move_down();
            break;

        case SWITCH_BOTH:

            // AIのターンなら操作無効
            if (get_player_turn() == AI) {
                break;
            }

            put_stone(get_cursor_x(), get_cursor_y(), get_player_color());

            if (is_finish_game(get_player_color()) > 0) {
                game_state = FINISH;
            }

            ai_clk = 0;
            break;

        default:
            break;
        }
    }
}
