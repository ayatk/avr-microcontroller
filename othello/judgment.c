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

void put_stone(int x, int y, enum Color turn) {
    int count, vertical, horizontal, i;

    if (!can_put_stone(x, y, turn)) {
        return;
    }

    // 8方向の石の判定と裏返し
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
    beep(BEEP_A4, 3);
    next_turn();
}

bool can_put_stone(int x, int y, enum Color turn) {
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


int count_turn_over(enum Color turn, int y, int x, int vertical, int horizontal) {
    int i;

    // 相手の石の色
    enum Color opponent = (turn == WHITE) ? BLACK : WHITE;

    // 相手の石の色が出るまでforで回す
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


int is_finish_game(enum Color turn) {
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
