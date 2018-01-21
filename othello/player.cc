/*
 * Othello
 *
 * Copyright (c) 2017-2018 ayatk.
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#include "std/types.h"
#include "player.h"

namespace Player {

Cursor cursor;
bool player_turn;

/// 初期化
void init(u_char x, u_char y, bool _player_turn) {
    cursor.x = x;
    cursor.y = y;
    player_turn = _player_turn;
}

u_char getX() {
    return cursor.x;
}

u_char getY() {
    return cursor.y;
}

void cursorMoveLeft() {
    cursor.x = static_cast<u_char>((cursor.x + 1) & 7);
}

void cursorMoveDown() {
    cursor.y = static_cast<u_char>((cursor.y + 1) & 7);
}

}

