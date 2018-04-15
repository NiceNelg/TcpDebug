#ifndef __CONTROLLER__
#define __CONTROLLER__

#include <pthread.h>
#include "sth.h"
#include "tcpoperate.h"
#include "display.h"
#include <signal.h>
#include "keyboard.h"

//控制器的线程变量
typedef struct{
	pthread_t keyboard;
	pthread_t display;
	pthread_t tcpoperate;
}controller_pthread;

//各命令对应编码
typedef struct{
	//发送数据
	int send;
	//切换成16进制数据
	int hex;
	//切换成普通字符串数据
	int string;
	//退出程序
	int exit;
}controller_command;

void controller_start();

//void operate_blocksignal(operate_set *operate_set);

void controller_registersignal();

void controller_sigint(int sign);

//键盘监听线程执行的方法
void *controller_keyboard();
#endif
