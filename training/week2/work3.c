#include <avr/io.h>
#include <avr/wdt.h>
#include <string.h>

#define CTOP 20000
#define CHATTERING 200


unsigned char sw;
unsigned char sw_flag;

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

void update_sw() {
    static char stat = 0;
    static unsigned long cnt = 0;
    unsigned char tmp;

    tmp = (~PINC >> 4) & 3;

    switch (stat) {
        case 0:
            if (sw != tmp) {
                cnt = CHATTERING;
                stat = 1;
            }
            break;
        case 1:
            cnt--;
            if (cnt == 0) {
                if (sw != tmp) {
                    sw_flag = 1;
                    sw = tmp;
                }
                stat = 0;
            }
            break;
    }
    return;
}

void reverse(char *array, int size) {
    int j;
    for (j = 0; j < size / 2; j++) {
        int t = array[j];
        array[j] = array[size - j - 1];
        array[size - j - 1] = t;
    }
}

int main() {

    unsigned long cnt = 0;

    // PORT settings
    DDRB = 0xFF;
    DDRC = 0x0F;
    DDRD = 0xFE;

    PORTB = 0xFF;
    PORTC = 0x30;
    PORTD = 0x00;

    while (1) {
        wdt_reset();
        cnt++;

        update_sw();
        update_led();
        if (cnt > CTOP) {

            cnt = 0;

            int i, k;
            unsigned char tmp_led;
            switch (sw) {
                case 1:
                    for (i = 0; i < 8; ++i) led[i] = (led[i] >> 1) | (led[i] << 7);
                    break;
                case 2:
                    reverse(led, 7);
                    reverse(led, 8);
                    break;
                case 3:
                    reverse(led, 7);
                    reverse(led, 8);
                    for (k = 0; k < 8; ++k) led[k] = (led[k] >> 1) | (led[k] << 7);
                    break;
            }
        }
    }
    return 0;
}
