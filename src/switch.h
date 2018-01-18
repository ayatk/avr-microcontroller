#ifndef _OTHELLO_SWITCH_H_
#define _OTHELLO_SWITCH_H_

 /**
  * スイッチの状態を定義した列挙型
  */
enum {
    SW_NONE = 0,
    SW_LEFT = 1,
    SW_RIGHT = 2,
    SW_BOTH = 3
};

/**
 * スイッチの状態を取得する関数
 *
 * @return スイッチのstate
 */
int get_switch_state(void);

#endif 
