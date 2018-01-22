/*
 * Othello
 *
 * Copyright (c) 2017-2018 ayatk.
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef OTHELLO_PLAYER_H
#define OTHELLO_PLAYER_H


namespace Player {

struct Cursor {
    u_char x:4;
    u_char y:4;
};

void init(Cursor cursor, bool player_turn = true);

u_char getX();

u_char getY();

void cursorMoveLeft();

void cursorMoveDown();

}

#endif
