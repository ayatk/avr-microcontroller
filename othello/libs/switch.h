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

/** チャタリング待ち時間 */
#define SW_INTERVAL 4000UL

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

void switch_update();

bool is_switch_changed();

u_char get_switch_state();

#endif
