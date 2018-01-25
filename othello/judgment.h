/*
 * Othello
 *
 * Copyright (c) 2017-2018 ayatk.
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef OTHELLO_JUDGMENT_H
#define OTHELLO_JUDGMENT_H


bool can_put_stone(int x, int y, int turn);

void put_stone(int x, int y, int turn);

int count_turn_over(int turn, int x, int y, int vertical, int horizontal);

int is_finish_game(int turn);

void sort_led();

#endif
