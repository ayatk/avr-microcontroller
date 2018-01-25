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


/** 勝利した時にならすBGM */
static volatile struct CODE win[] = {
    BEEP_END, 3,
    BEEP_E4, 2,
    BEEP_END, 0,
    BEEP_E4, 2,
    BEEP_END, 0,
    BEEP_E4, 2,
    BEEP_END, 0,
    BEEP_E4, 2,
    BEEP_END, 1,
    BEEP_D4, 2,
    BEEP_END, 1,
    BEEP_G4, 2,
    BEEP_END, 1,
    BEEP_E4, 8,
    BEEP_FINISH, 2
};

/** 敗北した時にならすBGM */
static volatile struct CODE lose[] = {
    BEEP_END, 3,
    BEEP_E4, 10,
    BEEP_D4, 10,
    BEEP_C4, 10,
    BEEP_FINISH, 0
};
/** 現在慣らしている音の、次の音を指定するための添字 */
static volatile u_char bgm_index = 0;

/** ゲームの状態 */
enum {
    PLAYING,
    FINISH,
    FINISHED,
};
static volatile int game_state = PLAYING;

static volatile int ai_clk;


/** 各種機能やタイマカウンタで用いる変数 */
static volatile u_char clk;
static volatile int cursor_clk;


/** 2ms毎に呼ばれる関数（タイマカウンタ）*/
ISR(TIMER0_COMPA_vect) {
    // 100msごとにgame_mainを起動する
    if (++clk >= 50) {
        clk = 0;
        // 指定した時間になると停止させる
        sound_update();
    }

    // 相手がプレイヤーじゃなければ疑似思考時間
    if (get_player_turn() == BLACK) {
        if (++ai_clk >= 500) {
            ai_clk = 0;

            int check = ai(get_player_turn());

            if (check == 1) {
                if (is_finish_game(get_player_turn()) > 0) {
                    game_state = FINISH;
                }
            }
        }
    }

    // 0.5sごとにカーソルを点滅させる処理
    if (++cursor_clk >= 250) {
        cursor_clk = 0;
        target_reverse_state();
    }
}

int main(void) {
    // LED表示するための変数
    DDRB = 0xff;
    DDRC = 0x0f;
    DDRD = 0xfa;
    PORTC = 0x30;
    PORTD = 0x00;
    PORTB = 0x00;

    OCR0A = 249; // 2ms
    TCCR0A = 2; // CTC MODE
    TCCR0B = 3; // 64PS
    TIMSK0 |= (1 << OCIE0A);

    // 初期化
    board_init();
    switch_init();
    sound_init();

    win_player = NONE;
    board_reset();
    // 最初の石とターゲットを配置
    matrix[3][3] = WHITE;
    matrix[4][4] = WHITE;
    matrix[3][4] = BLACK;
    matrix[4][3] = BLACK;
    target_init(2, 4, WHITE, BLACK);
    game_state = PLAYING;
    cursor_visible(true);

    // 割り込み処理を実行
    sei();

    // ゲームを回すforループ
    while (1) {
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
            game_state = FINISHED;
            break;

        case FINISHED:
            if (is_sound_playing() == 0) {
                u_char f = BEEP_FINISH;

                if (win_player == WHITE) {
                    if (win[bgm_index].tone != f) {
                        beep(win[bgm_index].tone, win[bgm_index].length);
                        bgm_index++;
                    }
                } else {
                    if (lose[bgm_index].tone != f) {
                        beep(lose[bgm_index].tone, lose[bgm_index].length);
                        bgm_index++;
                    }
                }
            }

            break;

        default:
            break;
        }
    }

    return 0;
}


/** ゲームの本体 */
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

            // プレイヤー2がAIで、自分の番でなければ通らない
            if (get_player_turn() != WHITE) {
                break;
            }

            put_stone(get_cursor_x(), get_cursor_y(), get_player_turn());

            if (is_finish_game(get_player_turn()) > 0) {
                game_state = FINISH;
            }

            ai_clk = 0;
            break;
        }
    }
}
