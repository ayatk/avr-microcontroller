/*
 * Othello
 *
 * Copyright (c) 2017-2018 ayatk.
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef OTHELLO_LIBS_APPLICATION_H
#define OTHELLO_LIBS_APPLICATION_H

/**
 * アプリケーションの初期化処理 
 */
void init();

/**
 * メインループ 
 */
void loop();

/**
 * 時間待ち
 * 待ち時間は timeで指定した数に100msをかけたもの
 * 
 * @param time 待ち時間
 */
void wait(u_char time = 0);

#endif
