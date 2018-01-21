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

namespace Board {

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
extern Color matrix[LED_SIZE][LED_SIZE];


/**
 * LEDの初期化処理
 */
void init();

/**
 * LEDを全てOFFにする
 */
void reset();

}

#endif 

