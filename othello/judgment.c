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
#include "othello.h"
#include "board.h"
#include "player.h"
#include "libs/sound.h"
#include "judgment.h"

void put_stone(int x, int y, int turn) {
    int count, vertical, horizontal, i;

    if (!can_put_stone(x, y, turn)) {
        return;
    }

    for (vertical = -1; vertical <= 1; vertical++) {      // 上下方向
        for (horizontal = -1; horizontal <= 1; horizontal++) {  // 左右方向
            if (vertical == 0 && horizontal == 0) {
                continue;
            }

            count = count_turn_over(turn, y, x, vertical, horizontal);

            for (i = 1; i <= count; i++) {
                matrix[y + i * vertical][x + i * horizontal] = turn; // 裏返す
            }
        }
    }

    matrix[y][x] = turn; // 石を置く
    beep(BEEP_C5, 3);
    next_turn();
}

bool can_put_stone(int x, int y, int turn) {
    int vertical, horizontal;

    if (matrix[y][x] != NONE) {
        return false;
    }

    for (vertical = -1; vertical <= 1; vertical++) {      // 上下方向
        for (horizontal = -1; horizontal <= 1; horizontal++) {  // 左右方向
            if (count_turn_over(turn, y, x, vertical, horizontal)) {
                return true;
            }
        }
    }

    return false;
}


int count_turn_over(int turn, int y, int x, int vertical, int horizontal) {
    int i;
    int opponent = (turn == WHITE) ? BLACK : WHITE;

    for (i = 1; matrix[y + i * vertical][x + i * horizontal] == opponent; i++) {
        if (y + i * vertical < 0
                || y + i * vertical > LED_SIZE - 1
                || x + i * horizontal < 0
                || x + i * horizontal > LED_SIZE - 1) {
            break;
        }
    };

    if (y + i * vertical < 0
            || y + i * vertical > LED_SIZE - 1
            || x + i * horizontal < 0
            || x + i * horizontal > LED_SIZE - 1) {
        return 0;
    }

    if (matrix[y + i * vertical][x + i * horizontal] == turn) {
        return i - 1;
    } else {
        return 0;
    }
}


int is_finish_game(int turn) {
    int x, y;
    int on = 0;

    for (y = 0; y < LED_SIZE; y++) {
        for (x = 0; x < LED_SIZE; x++) {
            // 置く場所があるなら続けられる
            if (can_put_stone(x, y, turn) == 1) {
                return 0;
            }
        }
    }

    // ONの個数を調べる
    for (y = 0; y < LED_SIZE; y++) {
        for (x = 0; x < LED_SIZE; x++) {
            if (matrix[y][x] == WHITE) {
                on++;
            }
        }
    }

    return on;
}

void replace(int x, int y, int ix, int iy) {
    int temp = matrix[iy][ix];
    matrix[iy][ix] = matrix[y][x];
    matrix[y][x] = temp;
}

void sort_led() {
    int temp = 0;
    int ix = 0, iy = 0;
    int x, y;

    for (y = 0; y < LED_SIZE; y++) {
        for (x = 0; x < LED_SIZE; x++) {
            if (matrix[y][x] == WHITE) {
                replace(x, y, ix, iy);
                ix++;

                if (ix == LED_SIZE) {
                    ix = 0;
                    iy++;
                }
            }
        }
    }

    temp = LED_SIZE * iy + ix;

    for (y = 0; y < LED_SIZE; y++) {
        for (x = 0; x < LED_SIZE; x++) {
            if (matrix[y][x] == BLACK) {
                replace(x, y, ix, iy);
                ix++;

                if (ix == LED_SIZE) {
                    ix = 0;
                    iy++;
                }
            }
        }
    }

    win_player = (temp > iy * LED_SIZE + ix - temp) ? WHITE : BLACK;
}

