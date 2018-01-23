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

/**
 * LEDマトリックスのサイズ
 */
#define LED_SIZE 8

/**
 * LEDのstate 
 */
enum Color {
    WHITE,
    BLACK, // 半分だけ点灯させる
    NONE,
};

/**
 * マトリックスLED
 */
extern u_char matrix[LED_SIZE][LED_SIZE];


/**
 * LEDの初期化処理
 */
void board_init();

/**
 * LEDを全てOFFにする
 */
void board_reset();

#endif 

