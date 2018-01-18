

typedef unsigned char uchar;

/*	ブザー用	*/
enum {
    BEEP_HIGH = 46,
    BEEP_LOW = 168,

    BEEP_C4 = 238,
    BEEP_D4 = 212,
    BEEP_E4 = 189,
    BEEP_F4 = 178,
    BEEP_G4 = 158,
    BEEP_A4 = 141,
    BEEP_B4 = 126,
    BEEP_C5 = 118
};

/*	システム定義		*/
extern void _wait(uchar wait);    //  時間待ち
extern uchar _rand(void);        //  擬似乱数生成
extern void _sound(uchar tone, uchar length);    //  ブザー

/*	ユーザー定義	*/
extern void init(void);

extern void loop(void);
