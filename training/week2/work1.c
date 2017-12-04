#include <avr/io.h>
#include <avr/wdt.h>

#define CTOP 200000

int main() {

    unsigned long cnt = 0;
    unsigned int n = 0;
    unsigned int add = 1;
    unsigned int is_back = 1;

    // PORT settings
    DDRB = 0xFF;
    DDRC = 0x0F;
    DDRD = 0xFE;

    PORTB = 0x0007;
    PORTC = 0x00;
    PORTD = 0x00;

    while (1) {
        wdt_reset();
        cnt++;

        if (cnt > CTOP) {
            cnt = 0;

            PORTB = 0x0007 << n;

            if (n == 9) {
                add = -1;
            }
            if (n == 0) {
                add = 1;
            }
            n += add;
        }
    }
}
