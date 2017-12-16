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

	//建立新窗口
	(*win)->win_send = newwin(15,50,1,1);//新窗口(行，列,begin_y,begin_x) 

  box( (*win)->win_send,ACS_VLINE,ACS_HLINE); 

  mvwprintw( (*win)->win_send,3,1, "send windows"); 

  mvwprintw( (*win)->win_send,2,1,"www.deepfuturesoft.info");

}
