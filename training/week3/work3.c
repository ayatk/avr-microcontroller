#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>

volatile unsigned char count;

ISR(TIMER2_COMPA_vect) {
    PORTD ^= _BV(PORTD3);
}

ISR(TIMER1_COMPA_vect) {
    PORTB++;
    if (count <= 1) {
        TIMSK2 ^= _BV(OCIE2A);
    }
    count = (count == 10) ? 0: count + 1;
}

int main() {
    DDRB = 0xFF;
    DDRC = 0x0F;
    DDRD = 0xFE;

    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;

    TCCR2B = 0x04;
    TCCR2A = 0x02;
    OCR2A = 283;

    TCCR1B = 0x0D;
    TCCR1A = 0x00;
    OCR1A = 781;

    TIMSK1 = _BV(PCIE1);
    sei();

    for (;;) {
        wdt_reset();
    }
    return 0;
}
