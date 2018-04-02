#include "controller.h"

static controller controller_entity;

void controller_start() {
	//为特定信号注册回调方法
	controller_registersignal();
	//开启键盘检测线程，检测键盘输入执行指定命令
	pthread_create(&(controller_entity.keyboard), NULL, controller_keyboard, NULL);
}


//注册信号的回调方法
void controller_registersignal() {
	//注册终止信号的回调方法（ctrl+v）
	signal(SIGINT, controller_sigint);
}

//当接收到终止信号时执行的方法
void controller_sigint(int sign) {
	display_end(&win);
	exit(0);
}

//监听键盘线程执行的方法
void *controller_keyboard() {
	keyboard_init();
	while(1) {
		keyboard_hit();
		printf("\n%d\n", keyboard_readch());
	}
	keyboard_close();
}
