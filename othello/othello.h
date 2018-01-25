/*
 * Othello
 *
 * Copyright (c) 2017-2018 ayatk.
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef OTHELLO_H
#define OTHELLO_H

typedef struct CODE {
    volatile int tone;
    volatile u_char length;
} CODE;

volatile u_char win_player;

void othello_play();

void othello_reset();

#endif
