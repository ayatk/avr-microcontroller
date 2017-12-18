#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>

volatile unsigned char count;
/* * * * * * * * * * * * *
 *	情報工 専門実験A 2017
 *	./avr/w4/list4_4.c
 * * * * * * * * * * * * */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>


ISR(TIMER1_COMPA_vect) {
        PORTB++;
        if (count < 1) {
            TIMSK2 = 1 << TOIE2;
        } else {
            TIMSK2 = 0;
        }
        count = (count == 10) ? 0: count + 1;
}

int main(void)
{
	DDRD = 0xFE;

	TCCR2A = 0x23;
	TCCR2B = 0x06;
	OCR2A = 141;

	TCCR1B = 0x0D;
    TCCR1A = 0x00;
    OCR1A = 781;

    TIMSK1 = _BV(PCIE1);
	sei();
	for (;;) {
		wdt_reset();
	}
}
