/*
 * Recursion Co., Ltd. EMB-88 DTR Reset program for macOS
 * ver 0.02
 *
 * Author: Takago Lab
 * Date: 2017/8/31
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <termios.h>

int main(int argc, char *argv[]) {
    int fd;
    int dtr = TIOCM_DTR;
    char *devname = "/dev/ttyACM0";

    if (argc == 2) {
        devname = argv[1];
    }

    if ((fd = open(devname, O_RDWR | O_NOCTTY)) < 0) {
        perror(devname);
        exit(1);
    }
    // printf("EMB88 Reset DTR [%s]\n", devname);

    /* 他のプロセスでシリアル通信が継続的に行われていると，1回のDTRリセットでは
       PROGモードに以降できないことがある．以下を繰り返すと大抵PROGにモードに移行できる．
    */
    int cnt = 50;
    while (--cnt) {
        ioctl(fd, TIOCMBIC, &dtr);   // DTRクリア
        usleep(1000);
        ioctl(fd, TCIFLUSH); // シリアル受信バッファクリア（重要）
        ioctl(fd, TCOFLUSH); // シリアル送信バッファクリア（重要）
        ioctl(fd, TIOCMBIS, &dtr);   // DTRセット
    }

    ERR:
    close(fd);
    sleep(2); // （重要）
    return 0;
}
