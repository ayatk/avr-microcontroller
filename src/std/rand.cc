#include "types.h"
#include "rand.h"

static volatile u_int rnd;

u_int rand(void) {
    rnd++;  // 乱数更新
    return rnd ^ (rnd >> 1);    // グレイコードカウンタ
}
