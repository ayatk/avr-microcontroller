/*
 * Othello
 *
 * Copyright (c) 2017-2018 ayatk.
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef OTHELLO_BOARD_H
#define OTHELLO_BOARD_H

#define LED_SIZE 8

// 石の色
#define NONE 6
#define WHITE 1
#define BLACK 5

// 石の情報が入る配列
volatile int matrix[LED_SIZE][LED_SIZE];

/**
 * 盤の初期化
 */
void board_init();

/**
 * 盤のリセット
 */
void board_reset();

/**
 * カーソルを表示させるかどうか
 * @param enable trueで表示
 */
void cursor_visible(bool enable);

#endif
