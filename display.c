#include "display.h"

//获取屏幕信息
void static display_getwindosinfo( display_win *win ) {
	ioctl(STDIN_FILENO, TIOCGWINSZ, &(*win).win_info);
}

//初始化屏幕
void display_init(display_win **win) {
	//初始化窗口结构体
	*win = (display_win *)malloc( sizeof(display_win *) * 3 + sizeof(struct winsize) );
	(*win)->win_send = (WINDOW *)malloc(sizeof(WINDOW));
	(*win)->win_revice = (WINDOW *)malloc(sizeof(WINDOW));
	(*win)->win_command = (WINDOW *)malloc(sizeof(WINDOW));

	//获取当前终端信息
	display_getwindosinfo(*win);
	
	//开启curses库
	initscr();
	//开启键盘特殊字元输入
	keypad(stdscr, true);

	//新窗口(行，列,begin_y,begin_x) 
	//建立子窗口
	(*win)->win_send = derwin(
			stdscr,
			(int)( (*win)->win_info.ws_row * 0.7 ), 
			(int)( (*win)->win_info.ws_col / 2 ), 
			0,
			0
	);
	
	box( (*win)->win_send,ACS_VLINE,ACS_HLINE); 

  mvwprintw( (*win)->win_send, 1, 1, "send windows"); 

  mvwprintw( (*win)->win_send,2,1,"www.deepfuturesoft.info");

	refresh();
	wrefresh((*win)->win_send);
	//touchwin((*win)->win_send);

}

//删除屏幕
void display_del(display_win *win, const char *member) {
	//筛选成员
	if( strcmp(member,"win_send") == 0 ) {
		delwin(win->win_send);
	}else if( strcmp(member, "win_revice") == 0 ) {
		delwin(win->win_revice);
	}else if( strcmp(member, "win_command") == 0 ) {
		delwin(win->win_command);
	}
}

//结束屏幕显示
void display_end(display_win **win) {
	//删除所有屏幕
	delwin( (*win)->win_send );
	delwin( (*win)->win_revice );
	delwin( (*win)->win_command );

	//结束屏幕
	endwin();

	//释放指针
	free(*win);
}
	
	
