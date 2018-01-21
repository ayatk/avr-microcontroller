/*
 * Othello
 *
 * Copyright (c) 2017-2018 ayatk.
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#include "types.h"
#include "rand.h"

static volatile u_int rnd;

u_int rand() {
    rnd++;  // 乱数更新
    return rnd ^ (rnd >> 1);    // グレイコードカウンタ
}
