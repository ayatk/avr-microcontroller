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

typedef struct Cursor {
    u_char x: 4;
    u_char y: 4;
} Cursor;


Cursor cursor;
bool player_turn;

/// 初期化
void player_init(u_char x, u_char y, bool _player_turn) {
    cursor.x = x;
    cursor.y = y;
    player_turn = _player_turn;
}

u_char player_get_x() {
    return cursor.x;
}

u_char player_get_y() {
    return cursor.y;
}

void cursor_move_left() {
    cursor.x = (u_char) ((cursor.x + 1) & 7);
}

void cursor_move_down() {
    cursor.y = (u_char) ((cursor.y + 1) & 7);
}


