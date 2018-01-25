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

enum {
    PLAYER,
    AI,
};

void target_init(int x, int y, int p1, int p2);

int get_cursor_x();

int get_cursor_y();

int is_cursor_flash();

void cursor_move_left();

void cursor_move_down();

int get_player_turn();

void next_turn();

void target_reverse_state();

#endif
