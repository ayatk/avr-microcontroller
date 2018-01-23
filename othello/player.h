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

void player_init(u_char x, u_char y, _Bool _player_turn);

u_char player_get_x();

u_char player_get_y();

void cursor_move_left();

void cursor_move_down();

#endif
