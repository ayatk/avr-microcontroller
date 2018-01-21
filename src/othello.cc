/*
 * Othello
 *
 * Copyright (c) 2017-2018 ayatk.
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */

#include "std/types.h"
#include "libs/application.h"
#include "libs/led.h"

volatile u_char Led::matrix[LED_SIZE][LED_SIZE];

void init() {
    Led::matrix[3][3] = Led::ON;
    Led::matrix[4][4] = Led::ON;
    Led::matrix[3][4] = Led::HALF;
    Led::matrix[4][3] = Led::HALF;
}

void loop() {
}
