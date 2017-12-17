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

//定义窗口信息结构体
typedef struct display_win_info {
	//curses库WINDOW序号
	WINDOW *index;
	//窗口所占行数
	unsigned short int row;
	//窗口所占列数
	unsigned int col;
}display_win_info;

//定义窗口结构体
typedef struct win {
	//发送提示窗口
	display_win_info win_tip_send;
	//发送窗口
	display_win_info win_send;
	//接收提示窗口
	display_win_info win_tip_revice;
	//接收窗口
	display_win_info win_revice;
	//命令提示窗口
	display_win_info win_tip_command;
	//命令窗口
	display_win_info win_command;
	//终端窗口信息
	struct winsize terminal_info;
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
