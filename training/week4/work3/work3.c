#include <string.h>
#include "user.h"

/*	ローカル関数	*/
static void floor_up_or_down(void);
static void floor_up(void);
static void floor_down(void);
static void show_floor_num(void);
static void update_led(void);
void reverse(unsigned char *array, int size);

static int floor;

static int count = 0; // 秒数
static int state = 0; // ステートマシンの状態

unsigned char floor_led[5][8] = {
    {
        0b00011000,
        0b00111000,
        0b01111000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b00011000,
        0b01111110
    },
    {
        0b01111110,
        0b00000010,
        0b00000010,
        0b01111110,
        0b01111110,
        0b01000000,
        0b01000000,
        0b01111100,
    },
    {
        0b01111100,
        0b00000010,
        0b00000010,
        0b01111110,
        0b01111110,
        0b00000010,
        0b00000010,
        0b01111100,
    },
    {
        0b01000010,
        0b01000010,
        0b01000010,
        0b01111110,
        0b01111110,
        0b00000010,
        0b00000010,
        0b00000010,
    },
    {
        0b01111100,
        0b01000000,
        0b01000000,
        0b01111110,
        0b01111110,
        0b00000010,
        0b00000010,
        0b01111110,
    }
};
unsigned char up[8] = {
    0b00000000,
    0b00011000,
    0b00111100,
    0b01011010,
    0b10011001,
    0b00011000,
    0b00011000,
    0b00011000,
};

unsigned char down[8] = {
    0b00000000,
    0b00011000,
    0b00011000,
    0b10011001,
    0b01011010,
    0b00111100,
    0b00011000,
};

unsigned char tmp[8];

void reverse(unsigned char *array, int size) {
    int j;
    for (j = 0; j < size / 2; j++) {
        int t = array[j];
        array[j] = array[size - j - 1];
        array[size - j - 1] = t;
    }
}

/* ユーザー処理の初期化 */
void user_init(void) {
    state = 1;
    floor = 0;
}

/*	ユーザー処理（100mS 毎に呼ばれる）*/
void user_main(void) {
    floor_up_or_down();
    switch (state) {
    case 0:
        state = 1;
        break;
    case 1:
        show_floor_num();
        break;
    case 2:
        floor_down();
        break;
    case 3:
        floor_up();
        break;
    }
    update_led();
}

static void floor_up(void) {
    if (count == 0) {
        int i;
        for (i = 0; i < 8; i++) tmp[i] = up[i];
        count++;
        return;
    }

    if (count < 30) {
        reverse(tmp, 8);
        reverse(tmp, 7);
        reverse(tmp, 8);
        reverse(tmp, 8);
        count++;
    } else {
        state = 0;
        count = 0;
    }
}

static void floor_down(void) {
    if (count == 0) {
        int i;
        for (i = 0; i < 8; i++) tmp[i] = down[i];
        count++;
        return;
    }
    if (count < 20) {
        reverse(tmp, 7);
        reverse(tmp, 8);
        count++;
    } else {
        state = 0;
        count = 0;
    }
}

static void show_floor_num(void) {
    int i;
    for (i = 0; i < 8; i++) tmp[i] = floor_led[floor][i];
}

static void floor_up_or_down(void) {
    if (state != 1)
        return;
    switch (sw) {
    case 1: // 下の階
        if (floor > 0) {
            floor--;
            state = 2;
        }
        break;
    case 2: // 上の階
        if (floor < 5) {
            floor++;
            state = 3;
        }
        break;
    }
    sw_flag = 0;
}

/*	LED表示の更新*/
static void update_led(void) {
    int i;
    for (i = 0; i < 8; i++) led[i] = tmp[i];
}
