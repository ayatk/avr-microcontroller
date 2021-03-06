/*
 * Othello
 *
 * Copyright (c) 2017-2018 ayatk.
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef OTHELLO_H
#define OTHELLO_H

/**
 * ゲームの状態
 */
enum GameState {
    PLAYING,
    FINISH,
};

/**
 * ゲーム本体
 */
void othello_play();

#endif
