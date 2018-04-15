#include "controller.h"

static controller_pthread pthread;
static controller_command command = {6,8,1,2};

void controller_start() {
	//为特定信号注册回调方法
	controller_registersignal();
	//开启键盘检测线程，检测键盘输入执行指定命令
	pthread_create(&(pthread.keyboard), NULL, controller_keyboard, NULL);
}


//注册信号的回调方法
void controller_registersignal() {
	//注册终止信号的回调方法（ctrl+v）
	signal(SIGINT, controller_sigint);
}

//当接收到终止信号时执行的方法
void controller_sigint(int sign) {
	display_end(&win);
	keyboard_close();
	exit(0);
}

//键盘输入后的操作
static void controller_keyboard_hit() {
	char controller_char;
	keyboard_hit();
	controller_char = keyboard_readch();
	//判断输入是否为命令，解析命令
	if(controller_char == command.send) {
		//发送命令的操作
		printf("send\n");
	} else if(controller_char == command.hex) {
		//切换成16进制数据
		printf("Hex\n");
	} else if(controller_char == command.string) {
		//切换成字符串进制数据
		printf("String\n");
	} else if(controller_char == command.exit) {
		//退出程序
		controller_sigint(0);
	} else {
		//输入数据
		printf("Input\n");
	}
}

//监听键盘线程执行的方法
void *controller_keyboard() {
	keyboard_init();
	while(1) {
		controller_keyboard_hit();
	}
	keyboard_close();
}
