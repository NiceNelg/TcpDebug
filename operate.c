#include "operate.h"
#include "tcpoperate.h"
#include "display.h"
#include <signal.h>

void operate_start(operate_set *operate_set) {
	operate_blocksignal(operate_set);
}


//注册信号的回调方法
void operate_registersignal(operate_set *operate_set) {
	//注册终止信号的回调方法（ctrl+v）
	
}
