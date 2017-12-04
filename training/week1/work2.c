#include <avr/io.h>
#include <avr/wdt.h>

#define CTOP 20000

int main() {
    static unsigned long cnt = 0;
    unsigned int loop_count = 8;
    unsigned int show_led = 0x80;
    // LED1 lighting pattern
    unsigned int led1 = 0xA8;
    // LED2 lighting pattern
    unsigned int led2 = 0x02;

    // Port settings
    DDRC = 0x30;
    PORTC = 0x00;

    // Main event loop
    while (1) {
        // LED
        PORTC = ((show_led & led1) != 0 ? 0x10 : 0x00)
                + ((show_led & led2) != 0 ? 0x20 : 0x00);

        cnt++;
        wdt_reset();

        if (cnt > CTOP) {
            if (loop_count == 0) {
                show_led = 0x80;
                loop_count = 8;
            } else {
                show_led >>= 1;
                loop_count -= 1;
            }
            cnt = 0;
        }
    }
    return 0;
}
