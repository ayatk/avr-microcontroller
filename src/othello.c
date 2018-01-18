#include <math.h>
#include <string.h>
#include "user.h"

static uchar flash_count;

static uchar cursor_matrix[LED_SZ] = { 0 };
static uchar cursor_x = 0;
static uchar cursor_y = 0;

void reverse(uchar *array, uchar size) {
    uchar j;

    for (j = 0; j < size / 2; j++) {
        uchar t = array[j];
        array[j] = array[size - j - 1];
        array[size - j - 1] = t;
    }
}

void flash(void) {
    switch (sw) {
    case 0:
        if (flash_count == 5) {

            if (led[cursor_y] == 0) {
                memcpy(led, cursor_matrix, sizeof(led));
            } else {
                led[cursor_y] = 0;
            }

            flash_count = 0;
        } else {
            flash_count++;
        }

        break;

    case 1:
    case 2:
        flash_count = 0;
        memcpy(led, cursor_matrix, sizeof(led));
        break;
    }
}

void user_init(void) {
    cursor_matrix[0] = 1;
}

void user_main(void) {
    switch (sw) {
    case 1:
        cursor_matrix[cursor_y] = (cursor_matrix[cursor_y] << 1) | (cursor_matrix[cursor_y] >> 7);
        cursor_x = log10(cursor_matrix[cursor_y]) / log10(2);
        break;

    case 2:
        cursor_y = (cursor_y == 7) ? 0 : cursor_y + 1;
        reverse(cursor_matrix, 7);
        reverse(cursor_matrix, 8);
        break;
    }

    flash();
}
