/*
 * Othello
 *
 * Copyright (c) 2017-2018 ayatk.
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef OTHELLO_PLAYER_H
#define OTHELLO_PLAYER_H

enum {
    PLAYER,
    AI,
};

void target_init(u_char x, u_char y, int p1, int p2);

/**
 * カーソルのX座標
 * @return
 */
int get_cursor_x();

/**
 * カーソルの座標
 * @return
 */
int get_cursor_y();

/**
 * カーソルが光っているかどうか
 * @return
 */
int is_cursor_flash();

/**
 * カーソルを左に動かす
 */
void cursor_move_left();

/**
 * カーソルを下に動かす
 */
void cursor_move_down();

/**
 * 現在のターンのプレーヤーを取得
 * @return AIかPLAYERか
 */
int get_player_turn();

/**
 * 次のプレーヤーに移行
 */
void next_turn();

/**
 * カーソルの状態を反転させる
 */
void target_reverse_state();

#endif
