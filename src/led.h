#ifndef _OTHELLO_LED_H_
#define _OTHELLO_LED_H_

/**
 * LEDマトリックスのサイズ
 */
#define LED_SIZE 8

/**
 * マトリックスLED
 */
volatile unsigned char led[LED_SIZE];

/**
 * LEDの初期化処理
 */
void init_led(void);

#endif 

