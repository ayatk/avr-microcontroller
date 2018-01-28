/*
 * Othello
 *
 * Copyright (c) 2017-2018 ayatk.
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef OTHELLO_JUDGMENT_H
#define OTHELLO_JUDGMENT_H

/**
 * 指定した座標に石が置けるか判定する
 * @param x ボードのX座標
 * @param y ボードのX座標
 * @param turn 石の色
 * @return 置けるならtrue、置けないならfalse
 */
bool can_put_stone(int x, int y, enum Color turn);

/**
 * 指定した座標に石を置く
 *
 * @param x ボードのX座標
 * @param y ボードのX座標
 * @param turn 石の色
 */
void put_stone(int x, int y, enum Color turn);

/**
 * ある方向にある相手の石をどれだけひっくり返せるかを計算する
 * verticalは-1が上方向、0が現在の位置、1が下方向を表す。
 * horizontalは-1が左、0が現在の位置、1が右を表す。
 *
 * @param x ボードのX座標
 * @param y ボードのX座標
 * @param turn 石の色
 * @param vertical Y方向
 * @param horizontal X方向
 * @return ひっくり返せる石の数
 */
int count_turn_over(enum Color turn, int x, int y, int vertical, int horizontal);

/**
 * ゲームが終わりか判断する
 * @param turn 石の色
 * @return 終わりなら0、終わりでないなら残りの石の数
 */
int is_finish_game(enum Color turn);

/**
 * 終了時に石を綺麗に並べる
 */
void sort_led();

#endif
