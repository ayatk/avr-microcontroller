#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>

#define CTOP 10000UL

volatile unsigned char stat;
unsigned char sw;
unsigned char sw_flag;

ISR(PCINT1_vect) {
    stat = 1;
}

void update_sw() {
    static unsigned long cnt;
    switch (stat) {
    case 0:
        return;
    case 1:
        cnt = CTOP;
        stat = 2;
        return;
    case 2:
        cnt--;
        if (cnt == 0) {
            sw = ~(PINC >> 4) & 3;    // 変数swを更新
            sw_flag = 1;    // フラグを立てる
            stat = 0;
        }
        return;
    }
}

int main() {
    DDRB = 0xFF;
    DDRC = 0x2F;
    DDRD = 0xFE;

    PORTB = 0x00;
    PORTC = 0x10;
    PORTD = 0x00;

    PCICR = _BV(PCIE1);
    PCMSK1 = 0x30;
    sei();

    int i = 0;

    for (;;) {    // イベントループ
        wdt_reset();
        update_sw();
        if (sw_flag) {
            sw_flag = 0;
            switch (sw) {
            case 0:
                break;
            case 1:
                PORTC ^= 0x20;
                break;
            case 3:
                PORTC ^= 0x20;
                break;
            }
        }
        PORTB = sw + (stat << 2);
    }
    return 0;
}
