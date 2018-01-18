#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include "std/boolean.h"
#include "led.h"
#include "sound.h"
#include "switch.h"
#include "lib.h"


static volatile bool user_flag;    //  ユーザー処理の開始フラグ
static volatile uchar delay;    //  待ち時間カウンタ
static volatile uchar rnd;        //  擬似乱数のカウンタ

/* ユーザ処理のための割り込み */
ISR(TIMER1_COMPB_vect) {
    OCR1B = TCNT1 + 780;
    TIFR1 = _BV(OCF1B);    // フラグクリア

    if (delay) {    // 待ち
        delay--;
    }

    sound_update();

    user_flag = true;    // ユーザコードを呼び出す
}

int main(void) {
    // LED,スイッチ,ブザーのポート設定
    DDRB = 0xFF;
    DDRC = 0x0F;
    DDRD = 0xFA;
    PORTC = 0x30;    // 入力ピンをプルアップ
    PORTD = 0x00;

    // タイマ1(ノーマル)：100msの定期割り込み
    TCCR1A = 0x00;
    TCCR1B = 0x05;
    TIMSK1 |= _BV(OCIE1B);    // コンペアマッチB割り込み有効化(100ms)
    TCNT1 = 0xFFFF;

    // 各種初期化処理
    init_switch();
    init_sound();
    init_led();

    init();    // ユーザ処理初期化
    sei();          // システムとしての割り込みの有効化

    for (user_flag = false;;) {
        wdt_reset();

        if (user_flag) {    //  ユーザー処理の起動
            loop();
            user_flag = 0;
        }
    }

    return 0;
}

/* 時間待ち( n * 100ms) */
void _wait(uchar n) {
    for (delay = n; delay;) {
        wdt_reset();
    }
}

/* 擬似乱数生成 */
uchar _rand(void) {
    rnd++;    // 乱数更新
    return (uchar) (rnd ^ (rnd << 1));    // グレイコードカウンタ
}
