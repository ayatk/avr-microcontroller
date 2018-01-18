

typedef unsigned char uchar;

/*	システム定義		*/
extern void _wait(uchar wait);    //  時間待ち
extern uchar _rand(void);        //  擬似乱数生成
extern void _sound(uchar tone, uchar length);    //  ブザー

/*	ユーザー定義	*/
extern void init(void);

extern void loop(void);
