/*
 * Othello
 *
 * Copyright (c) 2017-2018 ayatk.
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#include "std/booliean.h"
#include "board.h"
#include "judgment.h"
#include "ai.h"

// 重み付けまっぷ
int map[LED_SIZE][LED_SIZE] = {
    {30,  -12, 0,  -1, -1, 0,  -12, 30},
    {-12, -15, -3, -3, -3, -3, -15, -12},
    {0,   -3,  0,  -1, -1, 0,  -3,  0},
    {-1,  -3,  -1, -1, -1, -1, -3,  -1},
    {-1,  -3,  -1, -1, -1, -1, -3,  -1},
    {0,   -3,  0,  -1, -1, 0,  -3,  0},
    {-12, -15, -3, -3, -3, -3, -15, -12},
    {30,  -12, 0,  -1, -1, 0,  -12, 30}
};

typedef struct AiTarget {
    int index; // 座標
    int score; // 重み
} AiTarget;

bool ai(enum Color turn) {
    int x, y;
    int i;
    AiTarget ai_target[64];
    int index = 0;
    int decide = 0;

    for (i = 0; i < 64; i++) {
        ai_target[i].index = 0;
        ai_target[i].score = 0;
    }

    for (y = 0; y < LED_SIZE; y++) {
        for (x = 0; x < LED_SIZE; x++) {
            if (can_put_stone(x, y, turn)) {
                ai_target[index].index = y * LED_SIZE + x;
                ai_target[index].score = map[y][x];
                index++;
            }
        }
    }

    // 最も高いスコアを出す
    for (i = 0; i < index; i++) {
        if (ai_target[decide].score < ai_target[i].score) {
            decide = i;
        }
    }

    if (index != 0) {
        index = ai_target[decide].index;
        x = index % LED_SIZE;
        y = index / LED_SIZE;
        put_stone(x, y, turn);
        return true;
    }

    return false;
}
