#ifndef __OPERATE__
#define __OPERATE__

#include <pthread.h>
#include "sth.h"
#include "display.h"
#include "tcpoperate.h"

void operate_start();

//void operate_blocksignal(operate_set *operate_set);

void operate_registersignal();

//当接收到终止信号时执行的方法
void operate_sigint(int sign);
#endif
