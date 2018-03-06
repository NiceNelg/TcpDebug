#include "operate.h"
#include "tcpoperate.h"
#include "display.h"
#include <signal.h>

void operate_start(operate_set *operate_set) {
	//屏蔽信号
	//初始化信号集（将信号集设置为空）
  sigemptyset(&(operate_set->set));
  sigaddset(&(operate_set->set),SIGINT);
  sigprocmask(SIG_BLOCK,&(operate_set->set),NULL);
}
