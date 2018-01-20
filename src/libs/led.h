#ifndef OTHELLO_LIBS_LED_H
#define OTHELLO_LIBS_LED_H

/**
 * LEDマトリックスのサイズ
 */
#define LED_SIZE 8

namespace Led {

/**
 * LEDのstate 
 */
enum {
    ON,
    HALF,   // 半分だけ点灯させる
    OFF
};

/**
 * マトリックスLED
 */
extern volatile u_char matrix[LED_SIZE][LED_SIZE];



/**
 * LEDの初期化処理
 */
void init();

/**
 * LEDを全てOFFにする
 */
void reset();

}

#endif 

