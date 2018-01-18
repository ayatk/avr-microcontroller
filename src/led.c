#include <avr/io.h>
#include <avr/interrupt.h>
#include "led.h"

/* マトリクスLEDのダイナミック点灯(2ms毎) */
ISR(TIMER0_COMPA_vect) {
    static unsigned char sc = 0xFE;
    static unsigned char scan = 0;        //  LED 走査カウンタ

    // LEDの更新
    PORTB = 0;    // 残像対策
    sc = (sc << 1) | (sc >> 7);
    PORTD = (PORTD & 0x0F) | (sc & 0xF0);    // 上位4ビット書き換え
    PORTC = (PORTC & 0xF0) | (sc & 0x0F);    // 下位4ビット書き換え
    scan = (scan + 1) & 7;
    PORTB = led[scan];
}

/**
 * LEDの初期化処理
 */
void init_led(void) {
    // タイマ0(CTC): ダイナミック点灯用
    OCR0A = 249;    //  2mS
    TCCR0A = 2;
    TCCR0B = 3;    //  1/64
    TIMSK0 |= (1 << OCIE0A); // コンペアマッチA割り込み有効
}
