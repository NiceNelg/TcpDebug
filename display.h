#ifndef __DISPLAY__
#define __DISPLAY__

#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

//定义窗口结构体
typedef struct win {
	//发送窗口
	WINDOW *win_send;
	//接收窗口
	WINDOW *win_revice;
	//命令窗口
	WINDOW *win_command;
	//终端窗口信息
	struct winsize win_info;
}display_win;

//获取屏幕信息
void static display_getwindosinfo( display_win *win );

//初始化屏幕
void display_init(display_win **win);

//删除窗口
void display_del(display_win *win, const char *member);

//结束屏幕
void display_end(display_win **win);

#endif
