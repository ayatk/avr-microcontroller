#ifndef OTHELLO_LIBS_SWITCH_H
#define OTHELLO_LIBS_SWITCH_H

namespace Switch {

 /**
  * スイッチの状態を定義した列挙型
  */
enum {
    NONE,
    LEFT,
    RIGHT,
    BOTH
};

/**
 * スイッチの初期化処理
 */
void init();

/**
 * スイッチの状態を取得する関数
 *
 * @return スイッチのstate
 */
u_char getState();

}

#endif 
