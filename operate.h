#ifndef __OPERATE__
#define __OPERATE__

#include <pthread.h>
#include "sth.h"
#include "tcpoperate.h"
#include "display.h"
#include <signal.h>

void operate_start();

//void operate_blocksignal(operate_set *operate_set);

void operate_registersignal();

void operate_sigint(int sign);
#endif
