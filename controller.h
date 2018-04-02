#ifndef __CONTROLLER__
#define __CONTROLLER__

#include <pthread.h>
#include "sth.h"
#include "tcpoperate.h"
#include "display.h"
#include <signal.h>
#include "keyboard.h"

typedef struct{
	pthread_t keyboard;
	pthread_t display;
	pthread_t tcpoperate;
}controller;

void controller_start();

//void operate_blocksignal(operate_set *operate_set);

void controller_registersignal();

void controller_sigint(int sign);

//键盘监听线程执行的方法
void *controller_keyboard();
#endif
