#ifndef _OTHELLO_LIBS_APPLICATION_H_
#define _OTHELLO_LIBS_APPLICATION_H_

/**
 * アプリケーションの初期化処理 
 */
void init();

/**
 * メインループ 
 */
void loop();

/**
 * 時間待ち
 * 待ち時間は timeで指定した数に100msをかけたもの
 * 
 * @param time 待ち時間
 */
void wait(u_char time = 0);

#endif
