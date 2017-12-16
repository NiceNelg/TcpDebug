#ifndef __DISPLAY__
#define __DISPLAY__

#include <curses.h>
#include <stdlib.h>

//定义窗口结构体
typedef struct win {
	WINDOW *win_send;
	WINDOW *win_revice;
	WINDOW *win_command;
}display_win;

//初始化屏幕
void display_init(display_win **win);



#endif
