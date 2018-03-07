#ifndef __OPERATE__
#define __OPERATE__

#include <pthread.h>
#include "sth.h"
#include "display.h"
#include "tcpoperate.h"

typedef struct operate_set{
	//被屏蔽的原始信号集
	sigset_t oldset;
	//添加屏蔽的信号集
	sigset_t set;

}operate_set;

void operate_start(operate_set *operate_set);
//void operator_start(server_info server_info, display_win *win);

void operate_blocksignal(operate_set *operate_set);

#endif
