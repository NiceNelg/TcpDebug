#include "display.h"

//初始化屏幕
void display_init(display_win **win) {
	//初始化窗口结构体
	*win = (display_win *)malloc( sizeof(display_win *) );
	(*win)->win_send = (WINDOW *)malloc(sizeof(WINDOW));
	(*win)->win_revice = (WINDOW *)malloc(sizeof(WINDOW));
	(*win)->win_command = (WINDOW *)malloc(sizeof(WINDOW));

	//开启curses库
	initscr();
	//开启键盘特殊字元输入
	keypad(stdscr, true);



}
