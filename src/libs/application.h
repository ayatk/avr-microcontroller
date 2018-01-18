#ifndef _OTHELLO_LIBS_APPLICATION_H_
#define _OTHELLO_LIBS_APPLICATION_H_

typedef unsigned char uchar;

/**
 * アプリケーションの初期化処理 
 */
void init(void);

/**
 * メインループ 
 */
void loop(void);

/**
 * 時間待ち
 * 待ち時間は timeで指定した数に100msをかけたもの
 * 
 * @param time 待ち時間
 */
void wait(uchar time);

#endif
