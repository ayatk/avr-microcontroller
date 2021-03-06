#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>

#define BAUD 38400
#define N 16 // バッファサイズ

unsigned int is_beep = 0;
unsigned int hz;
unsigned int msec;
unsigned int count;

ISR(USART_RX_vect) {
    static char buf[N];			// 文字バッファ
    static int n = 0;			// 文字バッファ中のデータ数

    buf[n] = UDR0;
    n++;

    if (N <= n) {
        n = 0;
        return;
    }

    if (buf[n - 1] == '\r') {
        // 読み込み
        fscanf(buf, "%d,%d", &hz, &msec);

        // hzのバリデーション
        if (hz > 2000) {
            hz = 2000;
        } else if (hz < 262) {
            hz = 262;
        }

        PORTB = OCR2A = (8000000 / (2 * 64 * hz)) - 1;
        is_beep = 1;
        n = 0;
    }
}

ISR(TIMER1_COMPA_vect) {
    if (is_beep && count < msec) {
        count++;
    } else {
        PORTB = OCR2A = 0;
        count = 0;
        is_beep = 0;
    }
}

int main(void) {
    DDRD = 0xFE;
    DDRC = 0x0F;
    DDRB = 0xFF;

    PORTD = 0x00;
    PORTC = 0x30;
    PORTB = 0x00;

    /* 通信速度設定 */
    UBRR0 = (F_CPU >> 4) / BAUD - 1;
    UCSR0C = 0x06;

    // 受信（割り込み）
    UCSR0B = _BV(RXCIE0) | _BV(RXEN0);

    TCCR1B = 0x0B;
    TCCR1A = 0x00;
    OCR1A = 124;

    // タイマ2(CTC,COM)
    TCCR2B = 0x44; // プリスケーラ64
    TCCR2A = 0x12;
    OCR2A = 0;

    TIMSK1 = _BV(PCIE1);
    sei();

    for (;;) {
        wdt_reset();
    }

    return 0;
}
