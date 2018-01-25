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
#define NONE 6
#define WHITE 1
#define BLACK 5

void board_init();

void board_reset();

volatile int matrix[LED_SIZE][LED_SIZE];

void cursor_visible(bool enable);

#endif
