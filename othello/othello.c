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
#include "libs/application.h"
#include "libs/switch.h"
#include "player.h"
#include "board.h"
#include "othello.h"


void init() {
    board_reset();
    othello_reset();
    player_init(0, 0, true);
}

void loop() {
    othello_play();
}

void othello_play() {
    switch (get_switch_state()) {
    case SWITCH_LEFT:
        cursor_move_left();
        break;

    case SWITCH_RIGHT:
        cursor_move_down();
        break;

    case SWITCH_BOTH:
        break;
    }
}

void othello_reset() {
    matrix[3][3] = WHITE;
    matrix[4][4] = WHITE;
    matrix[3][4] = BLACK;
    matrix[4][3] = BLACK;
}
