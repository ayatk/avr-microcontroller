#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

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

unsigned char show_led[8];

volatile unsigned char mv_flag;

volatile unsigned char count;
volatile unsigned char matrix_count;

void update_led();

ISR(TIMER0_COMPA_vect) {
    static int cnt;
    cnt++;
    if (cnt == 125) {
        cnt = 0;
        count = (count == 9) ? 0 : count + 1;
        mv_flag = 1;    // 200msごとにセット
    }
    update_led();    // ダイナミックスキャン点灯
}

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

int main() {
    unsigned char n;

    DDRB = 0xFF;
    DDRC = 0x0F;
    DDRD = 0xFE;

    PORTB = 0x00;
    PORTC = 0x30;
    PORTD = 0x00;

    // タイマ設定
    TCNT0 = 0;
    OCR0A = 249;
    TCCR0A = 2;
    TCCR0B = 3;
    TIMSK0 |= _BV(OCIE0A);    // コンペアマッチA割り込み(2ms)


    sei();
    for (;;) {
        wdt_reset();
        if (mv_flag == 1) {
            mv_flag = 0;
            int i;
            for (n = 0; n <= 7; n++) show_led[n] = led[count][n];
        }

    }
    return 0;
}
