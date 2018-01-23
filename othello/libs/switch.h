/*
 * Othello
 *
 * Copyright (c) 2017-2018 ayatk.
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef OTHELLO_LIBS_SWITCH_H
#define OTHELLO_LIBS_SWITCH_H


/**
 * スイッチの状態を定義した列挙型
 */
enum {
    SWITCH_NONE,
    SWITCH_LEFT,
    SWITCH_RIGHT,
    SWITCH_BOTH
};

/**
 * スイッチの初期化処理
 */
void switch_init();

/**
 * スイッチの状態を取得する関数
 *
 * @return スイッチのstate
 */
u_char get_switch_state();

#endif 
