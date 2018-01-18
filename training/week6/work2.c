#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>

#define BAUD 38400

enum ADC_MUX {
    PHOTO_TR = 0x5,
    LED1 = 0x4,	// LED1(LED4)
    IV1 = 0xE	// 内部電圧1.1V
};

enum ADC_MUX adev = PHOTO_TR;	// 測定対象を選択
volatile unsigned int val;
volatile unsigned char adc_flag = 0;
volatile char buff[16];
volatile char low[16];
volatile char up[16];

ISR(ADC_vect) {
    TIFR1 = _BV(OCF1B);	// トリガー用のフラグのクリア
    val = ADC;
    adc_flag = 1;

    if (adev == LED1) {	// LEDは光入力に鈍感なので，その対策
        DDRC |= 0x10;	// 出力ピンに変更
        PORTC &= ~0x10;	// 出力電圧を0Vにする(放電される)
        DDRC &= ~0x10;	// 入力ピンに戻す
    }
}

ISR(USART_UDRE_vect) {
    static char n;
    UDR0 = buff[n++];

    if (buff[n] == '\0') {
        UCSR0B &= ~_BV(UDRIE0);	// 空き割り込み停止
        n = 0;
    }
}

int main(void) {
    // LED および SW1,2 のポート設定
    DDRD = 0xFE;
    DDRC = 0x0F;
    DDRB = 0xFF;

    PORTD = 0x00;
    PORTC = 0x00;
    PORTB = 0x00;

    OCR1A = 49999;
    OCR1B = 0;
    TCCR1A = 0;
    TCCR1B = 0xA;	// PS=8, CTC, 50msごとにCompBフラグが立つ

    ADMUX = _BV(REFS0);	// REF電圧(AVCC)
    ADMUX |= adev;	// ADC入力の設定
    ADCSRB = 5;	// 自動トリガー(TIMER1_COMPB)
    ADCSRA = _BV(ADEN) | 0x7 | _BV(ADATE) | _BV(ADIE);
    ADCSRA |= _BV(ADSC);	// ADIFクリアと変換開始

    /* 通信速度設定 */
    UBRR0 = (F_CPU >> 4) / BAUD - 1;
    UCSR0A = 0;

    /* データ8ビット，パリティなし，ストップビット1個 */
    UCSR0C = 0x06;
    UCSR0B = _BV(TXEN0);

    sei();

    for (;;) {
        wdt_reset();

        if (adc_flag) {
            itoa((((val * 100) * 4.5)) / 1024, buff, 10);
            // 下位2桁を切り取り
            int low_digit = (strlen(buff) > 2) ? 2 : 1;
            strncpy(low, buff + (strlen(buff) - low_digit), strlen(buff));
            // 下位2桁を削除
            strncpy(buff, buff, 1);
            buff[1] = '\0';

            // 全部くっつける
            strcat(buff, ".");
            strcat(buff, low);

            // CRLFを追加
            strcat(buff, "\r\n");

            /* 空き割り込み有効化 */
            UCSR0B |= _BV(UDRIE0);
            adc_flag = 0;
        }
    }

    return 0;
}
