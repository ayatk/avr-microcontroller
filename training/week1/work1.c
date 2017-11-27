#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>

ISR (TIMER1_COMPA_vect) {
    TCCR2A ^= 0x10;
    OCR2A;
}

int main() {

    // Port settings
    DDRD = 0x08;
    PORTD = 0x00;

    // Timer
    TCNT2 = 0;
    OCR2A = 150;
    TCCR2A = 0x12;
    TCCR2B = 0x04;

    TCNT1 = 0;
    OCR1A = 4000;
    TCCR1A = 0x00;
    TCCR1B = 0x0D;
    TIMSK1 = _BV(OCIE1A);

    // Allow timer interruption.
    sei();

    // Main event loop
    while (1) {
        // Cleared Watch dog timer
        wdt_reset();
    }
    return 0;
}

