#include <avr/io.h>
#include <avr/wdt.h>

#define CTOP 200000

unsigned char led[8] = {
    0b00011000,
    0b00111000,
    0b01111000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b01111110,
};

void update_led() {
    static unsigned char sc = 0xFE;
    static unsigned char scan = 0;

    PORTB = 0;
    sc = (sc << 1) | (sc >> 7);
    PORTD = (PORTD & 0x0F) | (sc & 0xF0);
    PORTC = (PORTC & 0xF0) | (sc & 0x0F);
    scan = (scan + 1) & 7;
    PORTB = led[scan];
}

int main() {

    unsigned long cnt = 0;

    // PORT settings
    DDRB = 0xFF;
    DDRC = 0x0F;
    DDRD = 0xFE;

    PORTB = 0xFF;
    PORTC = 0x00;
    PORTD = 0x00;

    while (1) {
        wdt_reset();
        cnt++;

        update_led();
        if (cnt >= CTOP) {
            cnt = 0;
            int i = 0;
            for (i = 0; i < 8; ++i) {
                led[i] = (led[i] >> 1) | (led[i] << 7);
            }
        }
    }
    return 0;
}
