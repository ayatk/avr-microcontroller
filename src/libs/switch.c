#include <avr/io.h>
#include <avr/interrupt.h>
#include "switch.h"

// 押しボタン状態
static unsigned char sw;
// スイッチ変化を示すフラグ(クリアはユーザ側で実施)
static unsigned char sw_flag;

ISR(PCINT1_vect) {
    OCR1A = TCNT1 + 500;    // タイマ1に比較値設定(今から64ms後に割り込む)
    TIFR1 = _BV(OCF1A);        // フラグクリア
    TIMSK1 |= _BV(OCIE1A);    // タイマ1・コンペアマッチA割り込み有効化
}

// チャタリング終了後，64ms後に呼び出される
ISR(TIMER1_COMPA_vect) {
    sw = (~PINC >> 4) & 3;    // スイッチ変数の更新
    sw_flag = 1;
    TIMSK1 &= ~_BV(OCIE1A);    // タイマ1・コンペアマッチA割り込み無効化
}

/**
 * スイッチの初期化処理
 */
void init_switch(void) {
    //  ピン変化割り込み有効
    PCICR = _BV(PCIE1);
    PCMSK1 = 0x30;
}

int get_switch_state(void) {
    return sw;
}
