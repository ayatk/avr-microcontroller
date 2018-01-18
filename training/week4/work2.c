#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

volatile unsigned char tone = 10;	// 音程
volatile unsigned char level = 100;	// 音量

#define CTOP 10000UL

unsigned char sw;
unsigned char sw_flag;

ISR(TIMER2_OVF_vect) {
    static unsigned char cnt = 0;
    cnt++;

    if (cnt >= tone) {
        cnt = 0;
        OCR2B = OCR2B ? 0 : level;
    }
}

void update_sw() {
    static char stat = 0;
    static unsigned long cnt = 0;
    unsigned char tmp;            // 現在のポート入力

    tmp = (~PINC >> 4) & 3;

    switch (stat) {
    case 0:
        if (sw != tmp) {
            cnt = CTOP;
            stat = 1;
        }

        break;

    case 1:
        cnt--;

        if (cnt == 0) {
            if (sw != tmp) {
                sw_flag = 1;    // フラグを立てる
                sw = tmp;    // 変数swを更新
            }

            stat = 0;
        }

        break;
    }

    return;
}

int main(void) {
    DDRC = 0x0F;
    DDRD = 0xF8;

    PORTC = 0x30;	// 入力ピンをプルアップ
    PORTD = 0x00;

    TCCR2A = 0x23;
    TCCR2B = 0x01;
    OCR2B = 0;

    TIMSK2 = 1 << TOIE2;

    sei();

    for (;;) {
        update_sw();

        if (sw_flag) {    // スイッチ変化を検出したら
            sw_flag = 0;    // フラグをクリア

            switch (sw) {
            case 1:
                tone--;
                OCR2A = 114;
                break;

            case 2:
                tone++;
                break;
            }
        }

        wdt_reset();
    }
}
