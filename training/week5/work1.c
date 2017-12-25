#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>

#define BAUD 38400
#define N 2 // バッファサイズ

unsigned char show_led[8];
unsigned char led[10][8] = {
    {
        0b00111100,
        0b01000010,
        0b01000010,
        0b01000010,
        0b01000010,
        0b01000010,
        0b01000010,
        0b00111100,
    },
    {
        0b00011000,
        0b00111000,
        0b01111000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b01111110
    },
    {
        0b01111110,
        0b00000010,
        0b00000010,
        0b01111110,
        0b01111110,
        0b01000000,
        0b01000000,
        0b01111100,
    },
    {
        0b01111100,
        0b00000010,
        0b00000010,
        0b01111110,
        0b01111110,
        0b00000010,
        0b00000010,
        0b01111100,
    },
    {
        0b01000010,
        0b01000010,
        0b01000010,
        0b01111110,
        0b01111110,
        0b00000010,
        0b00000010,
        0b00000010,
    },
    {
        0b01111100,
        0b01000000,
        0b01000000,
        0b01111110,
        0b01111110,
        0b00000010,
        0b00000010,
        0b01111110,
    },
    {
        0b01111100,
        0b01000000,
        0b01000000,
        0b01111110,
        0b01111110,
        0b01000010,
        0b01000010,
        0b01111110,
    },
    {
        0b01111110,
        0b01000010,
        0b01000010,
        0b00000010,
        0b00000010,
        0b00000010,
        0b00000010,
        0b00000010,
    },
    {
        0b01111110,
        0b01000010,
        0b01000010,
        0b01111110,
        0b01111110,
        0b01000010,
        0b01000010,
        0b01111110,
    },
    {
        0b01111110,
        0b01000010,
        0b01000010,
        0b01111110,
        0b01111110,
        0b00000010,
        0b00000010,
        0b00000010,
    }
};
unsigned char no_led[8] = {
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
};


volatile unsigned char count;

/*  文字受信割り込み    */
ISR(USART_RX_vect) {
    static char buf[0]; // 文字バッファ

    buf[0] = UDR0;
    memcpy(show_led, led[atoi(buf)], sizeof(led[atoi(buf)]));
    count = 0;
    TIMSK1 = _BV(PCIE1);
    return;
}

ISR(TIMER1_COMPA_vect) {
    i

    void update_led() {
        static unsigned char sc = 0xFE;
        static unsigned char scan = 0;

        PORTB = 0;    // 残像対策
        sc = (sc << 1) | (sc >> 7);
        PORTD = (PORTD & 0x0F) | (sc & 0xF0);    // 上位4ビット書き換え
        PORTC = (PORTC & 0xF0) | (sc & 0x0F);    // 下位4ビット書き換え
        scan = (scan + 1) & 7;
        PORTB = show_led[scan];
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
        f (count >= 5) {
            memcpy(show_led, no_led, sizeof(no_led));
        }
        count = (count == 10) ? 0: count + 1;
    }
    TCCR1B = 0x0D;
    TCCR1A = 0x00;
    OCR1A = 781;

    // タイマ2(CTC,COM)
    TCCR2B = 0x44;
    TCCR2A = 0x12;
    OCR2A = 0;

    sei();
    for (;;) {
        update_led();
        wdt_reset();
    }
    return 0;
}
