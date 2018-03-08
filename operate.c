#include "operate.h"

void operate_start() {
	//为特定信号注册回调方法
	operate_registersignal();
	//开启键盘检测线程，检测键盘输入执行指定命令
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
