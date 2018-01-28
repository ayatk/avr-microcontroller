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

// プレーヤーカーソルの座標系
typedef struct Cursor {
    u_char x;
    u_char y;
} Cursor;

// プレーヤーカーソル
static Cursor cursor;
// プレーヤーのターンかどうか
static bool player_turn;
// プレーヤーのカーソルを点滅させる時に使う
static enum Color state;

void player_init(u_char x, u_char y, enum Player player) {
    cursor.x = x;
    cursor.y = y;
    player_turn = (player == PLAYER);
    state = (player == PLAYER) ? WHITE : BLACK;
}

int get_cursor_x() {
    return cursor.x;
}

int get_cursor_y() {
    return cursor.y;
}

int is_cursor_flash() {
    return state;
}

void cursor_move_right() {
    cursor.x = (u_char) ((cursor.x + 1) & 7);
}

void cursor_move_down() {
    cursor.y = (u_char) ((cursor.y + 1) & 7);
}

enum Player get_player_turn() {
    return (player_turn) ? PLAYER : AI;
}

enum Color get_player_color() {
    return (get_player_turn() == PLAYER) ? WHITE : BLACK;
}

void next_turn() {
    player_turn = !player_turn;
    cursor_visible(player_turn);
}

void target_reverse_state() {
    state = (state != NONE) ? NONE : get_player_color();
}

