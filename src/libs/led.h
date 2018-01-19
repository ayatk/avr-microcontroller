#ifndef _OTHELLO_LIBS_LED_H_
#define _OTHELLO_LIBS_LED_H_

/**
 * LEDマトリックスのサイズ
 */
#define LED_SIZE 8

/**
 * LEDのstate 
 */
enum {
    LED_ON,
    LED_HALF,   // 半分だけ点灯させる
    LED_OFF
};

/**
 * マトリックスLED
 */
volatile u_char led[LED_SIZE][LED_SIZE];

/**
 * LEDの初期化処理
 */
void init_led(void);

/**
 * LEDを全てOFFにする
 */
void reset_led(void);

#endif 

