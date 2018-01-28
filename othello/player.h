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

/**
 * プレーヤーの状態
 */
enum Player {
    PLAYER,
    AI,
};

/**
 * プレーヤーの初期化処理
 * @param x 起動時にプレーヤーのカーソルを置くX座標 (0 <= X <= 7)
 * @param y 起動時にプレーヤーのカーソルを置くY座標 (0 <= Y <= 7)
 * @param player 先行のプレーヤー
 */
void player_init(u_char x, u_char y, enum Player player);

/**
 * カーソルのX座標
 * @return X座標
 */
int get_cursor_x();

/**
 * カーソルのY座標
 * @return Y座標
 */
int get_cursor_y();

/**
 * カーソルの色を取得
 * @return
 */
enum Color get_cursor_color();

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
