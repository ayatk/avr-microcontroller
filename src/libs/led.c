#include <avr/io.h>
#include <avr/interrupt.h>
#include "../std/types.h"
#include "led.h"

/* マトリクスLEDのダイナミック点灯(2ms毎) */
ISR(TIMER0_COMPA_vect) {
    static u_char sc = 0xFE;
    static u_char scan = 0;        //  LED 走査カウンタ

    // LEDの更新
    PORTB = 0;    // 残像対策
    sc = (sc << 1) | (sc >> 7);
    PORTD = (PORTD & 0x0F) | (sc & 0xF0);    // 上位4ビット書き換え
    PORTC = (PORTC & 0xF0) | (sc & 0x0F);    // 下位4ビット書き換え
    scan = (u_char) ((scan + 1) & 7);
    PORTB = led[scan];
}

/**
 * LEDの初期化処理
 */
void init_led(void) {
    // タイマ0(CTC): ダイナミック点灯用
    OCR0A = 25; // 100マイクロ秒
    TCCR0A = 2;
    TCCR0B = 2; // PS=32
    TIMSK0 |= (1 << OCIE0A); // コンペアマッチA割り込み有効
}
