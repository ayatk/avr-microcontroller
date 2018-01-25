/*
 * Othello
 *
 * Copyright (c) 2017-2018 ayatk.
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#include "std/types.h"
#include "std/booliean.h"
#include "player.h"
#include "board.h"

/** プレイヤーの操作に関する構造体 */
typedef struct TARGET {
    int x, y;
    int state;
    int turn;
} TARGET;

/** プレイヤーの操作に関する変数 */
static TARGET target;
static volatile int player1;
static volatile int player2;

/** ターゲットの初期化 */
void target_init(int x, int y, int p1, int p2) {
    target.x = x;
    target.y = y;
    player1 = p1;
    player2 = p2;
    target.state = target.turn = p1;
}

/** ターゲットの現在地 */
int get_cursor_x() {
    return target.x;
}

int get_cursor_y() {
    return target.y;
}

/** ターゲットの点滅状態 */
int is_cursor_flash() {
    return target.state;
}

/* ターゲットを左に移動させる処理 */
void cursor_move_left() {
    target.x = (u_char) ((target.x + 1) & 7);
}

/** ターゲットを下に移動させる処理 */
void cursor_move_down() {
    target.y = (target.y < 7) ? target.y + 1 : 0;
}

/** 現在誰の番なのかを取得 */
int get_player_turn() {
    return target.turn;
}

/** 次の人へ */
void next_turn() {
    target.turn = (target.turn == player1) ? player2 : player1;
}

/** ターゲットの点滅状態を反転 */
void target_reverse_state() {
    target.state = (target.state == target.turn) ? NONE : target.turn;
}

