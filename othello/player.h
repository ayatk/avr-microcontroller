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

enum Player {
    PLAYER,
    AI,
};

void target_init(u_char x, u_char y, enum Player player);

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
 * カーソルを右に動かす
 */
void cursor_move_right();

/**
 * カーソルを下に動かす
 */
void cursor_move_down();

/**
 * 現在のターンのプレーヤーを取得
 * @return AIかPLAYERか
 */
enum Player get_player_turn();

/**
 * 現在のターンのプレーヤーの石の色を取得
 * @return 石の色
 */
enum Color get_player_color();

/**
 * 次のプレーヤーに移行
 */
void next_turn();

/**
 * カーソルの状態を反転させる
 */
void target_reverse_state();

#endif
