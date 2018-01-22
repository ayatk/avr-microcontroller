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
#include "libs/switch.h"
#include "player.h"
#include "board.h"
#include "othello.h"


void init() {
    Board::reset();
    Player::init(Player::Cursor {0, 0}, true);
}

void loop() {
    Othello::play();
}

namespace Othello {

void play() {
    switch (Switch::getState()) {
    case Switch::LEFT:
        Player::cursorMoveLeft();
        break;

    case Switch::RIGHT:
        Player::cursorMoveDown();
        break;

    case Switch::BOTH:
        break;
    }
}

}
