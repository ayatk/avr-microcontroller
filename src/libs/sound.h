/*
 * Othello
 *
 * Copyright (c) 2017-2018 ayatk.
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#ifndef OTHELLO_LIBS_SOUND_H
#define OTHELLO_LIBS_SOUND_H

namespace Sound {

/**
 * ブザーの音階
 */
enum {
    C4 = 238,
    CS4 = 225,
    D4 = 212,
    DS4 = 200,
    E4 = 189,
    F4 = 178,
    FS4 = 168,
    G4 = 159,
    GS4 = 150,
    A4 = 142,
    AS4 = 134,
    B4 = 126,
    C5 = 119,
    CS5 = 113,
    D5 = 106,
    DS5 = 100,
    E5 = 95,
    F5 = 89,
    FS5 = 84,
    G5 = 80,
    GS5 = 75,
    A5 = 71,
    AS5 = 67,
    B5 = 63,
};

/**
 * ブザーの初期化処理
 */
void init();

/**
 * 音を鳴らす
 * @param tone ブザの音程
 * @param length 鳴らす長さ
 */
void beep(u_char tone, u_char length);

/**
 * ブザーの状態を更新する処理
 */
void update();

}

#endif 
