#include "std/types.h"
#include "libs/application.h"
#include "libs/led.h"


void init(void) {
    led[3][3] = LED_ON;
    led[4][4] = LED_ON;
    led[3][4] = LED_HALF;
    led[4][3] = LED_HALF;
}

void loop(void) {
}
