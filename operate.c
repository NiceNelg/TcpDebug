#include "operate.h"
#include "tcpoperate.h"
#include "display.h"
#include <signal.h>

void operate_start(display_win **win) {
	operate_registersignal();
}


//注册信号的回调方法
void operate_registersignal() {
	//注册终止信号的回调方法（ctrl+v）
	signal(SIGINT, operate_sigint);
}

//当接收到终止信号时执行的方法
void operate_sigint(int sign) {
	display_end(&win);
	exit(0);
}
