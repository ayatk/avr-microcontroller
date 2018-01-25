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

typedef struct TARGET {
    int x, y;
    int state;
    int turn;
} TARGET;

static TARGET target;
static volatile int player1;
static volatile int player2;

void target_init(int x, int y, int p1, int p2) {
    target.x = x;
    target.y = y;
    player1 = p1;
    player2 = p2;
    target.state = target.turn = p1;
}

int get_cursor_x() {
    return target.x;
}

int get_cursor_y() {
    return target.y;
}

int is_cursor_flash() {
    return target.state;
}

void cursor_move_left() {
    target.x = (u_char) ((target.x + 1) & 7);
}

void cursor_move_down() {
    target.y = (u_char) ((target.y + 1) & 7);
}

int get_player_turn() {
    return target.turn;
}

void next_turn() {
    target.turn = (target.turn == player1) ? player2 : player1;
}

void target_reverse_state() {
    target.state = (target.state == target.turn) ? NONE : target.turn;
}

