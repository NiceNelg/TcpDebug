#include "display.h"

//获取屏幕信息
void static display_getwindosinfo( display_win *win ) {
	ioctl(STDIN_FILENO, TIOCGWINSZ, &(*win).terminal_info);
}

//初始化屏幕
void display_init(display_win **win) {
	//初始化窗口结构体
	*win = (display_win *)malloc(sizeof(display_win));
	(*win)->win_tip_send.index = (WINDOW *)malloc(sizeof(WINDOW));
	(*win)->win_send.index = (WINDOW *)malloc(sizeof(WINDOW));
	(*win)->win_tip_revice.index = (WINDOW *)malloc(sizeof(WINDOW));
	(*win)->win_revice.index = (WINDOW *)malloc(sizeof(WINDOW));
	(*win)->win_tip_command.index = (WINDOW *)malloc(sizeof(WINDOW));
	(*win)->win_command.index = (WINDOW *)malloc(sizeof(WINDOW));
	
	//获取当前终端信息
	display_getwindosinfo(*win);
	
	//兼容中文字符
	setlocale(LC_ALL, "");
	//开启curses库
	initscr();
	noecho();
	//开启键盘特殊字元输入
	keypad(stdscr, true);
	//建立主体窗口
	display_init_send(*win);
	display_init_revice(*win);
	display_init_command(*win);
	refresh();
	//wrefresh((*win)->win_send.index);
	//touchwin((*win)->win_send);

}

//建立发送窗口
void static display_init_send(display_win *win) {

	//记录发送提示窗口的起始位置和所占的位置
	win->win_tip_send.row_start = 0;
	win->win_tip_send.row = 3;
	win->win_tip_send.col_start = 0;
	win->win_tip_send.col = (int)(win->terminal_info.ws_col / 2);
	//相对于终端窗口建立发送提示窗口,并记录窗口索引,从0行0列开始，占终端窗口的2行，宽度为半屏
	win->win_tip_send.index = derwin(
			stdscr,
			win->win_tip_send.row,
			win->win_tip_send.col,
			win->win_tip_send.row_start,
			win->win_tip_send.col_start
	);
	//给发送提示窗口划线
	box( win->win_tip_send.index,ACS_VLINE,ACS_HLINE); 
	//设置发送提示窗口内容
  mvwprintw(win->win_tip_send.index, 1, 1, "发送窗口"); 

	//记录发送窗口的起始位置和所占位置
	win->win_send.row_start = (win->win_tip_send.row_start + win->win_tip_send.row + 1);
	win->win_send.row = (int)( (win->terminal_info.ws_row - win->win_tip_send.row_start - win->win_tip_send.row - 1) * 0.8 );
	win->win_send.col_start = 0;
	win->win_send.col = (int)(win->terminal_info.ws_col / 2);
	//相对于终端窗口建立发送提示窗口，并记录窗口索引
	win->win_send.index = derwin(
			stdscr,
			win->win_send.row,
			win->win_send.col,
			win->win_send.row_start,
			win->win_send.col_start
	);

	//给发送窗口划线
	box( win->win_send.index,ACS_VLINE,ACS_HLINE); 
}

//建立接收窗口
void static display_init_revice(display_win *win) {

	//记录接收提示窗口的起始位置和所占位置
	win->win_tip_revice.row_start = 0;
	win->win_tip_revice.row = 3;
	win->win_tip_revice.col_start = win->win_tip_send.col_start + win->win_tip_send.col + 1;
	win->win_tip_revice.col = (int)(win->terminal_info.ws_col - win->win_tip_send.col_start - win->win_tip_send.col - 1);
	//相对于终端窗口建立接收提示窗口,并记录窗口索引,从0行0列开始，占终端窗口的2行，宽度为半屏
	win->win_tip_revice.index = derwin(
			stdscr,
			win->win_tip_revice.row,
			win->win_tip_revice.col,
			win->win_tip_revice.row_start,
			win->win_tip_revice.col_start
	);
	//给接收提示窗口划线
	box( win->win_tip_revice.index,ACS_VLINE,ACS_HLINE); 
	//设置接收提示窗口内容
  mvwprintw(win->win_tip_revice.index, 1, 1, "接收窗口"); 

	//记录接收窗口的起始位置和所占位置
	win->win_revice.row_start = win->win_tip_revice.row_start + win->win_tip_revice.row + 1;
	win->win_revice.row = (int)( (win->terminal_info.ws_row - win->win_tip_revice.row_start - win->win_tip_revice.row - 1) * 0.8 );
	win->win_revice.col_start = win->win_send.col_start + win->win_send.col + 1;
	win->win_revice.col = (int)(win->terminal_info.ws_col - win->win_send.col_start - win->win_send.col - 1);
	//相对于终端窗口建立接收提示窗口，并记录窗口索引
	win->win_revice.index = derwin(
			stdscr,
			win->win_revice.row,
			win->win_revice.col, 
			win->win_revice.row_start,
			win->win_revice.col_start
	);

	//给接收窗口划线
	box( win->win_revice.index,ACS_VLINE,ACS_HLINE); 
}

//建立命令发送窗口
void static display_init_command(display_win *win) {

	//记录命令提示窗口的起始位置和所占的位置
	win->win_tip_command.row_start = win->win_send.row_start + win->win_send.row + 1;
	win->win_tip_command.row = 3;
	win->win_tip_command.col_start = 0;
	win->win_tip_command.col = win->terminal_info.ws_col;
	//相对于终端窗口建立命令提示窗口,并记录窗口索引,从0行0列开始，占终端窗口的2行，宽度为半屏
	win->win_tip_command.index = derwin(
			stdscr,
			win->win_tip_command.row,
			win->win_tip_command.col,
			win->win_tip_command.row_start,
			win->win_tip_command.col_start
	);
	//给命令提示窗口划线
	box( win->win_tip_command.index,ACS_VLINE,ACS_HLINE); 
	//设置命令提示窗口内容
  mvwprintw(win->win_tip_command.index, 1, 1, "数据发送窗口"); 

	//记录命令窗口所占位置
	win->win_command.row_start = win->win_tip_command.row_start + win->win_tip_command.row + 1;
	win->win_command.row = (int)(win->terminal_info.ws_row - win->win_command.row_start);
	win->win_command.col_start = 0;
	win->win_command.col = (int)(win->terminal_info.ws_col);
	//相对于终端窗口建立接收命令窗口，并记录窗口索引
	win->win_command.index = derwin(
			stdscr,
			win->win_command.row,
			win->win_command.col, 
			win->win_command.row_start,
			win->win_command.col_start
	);

	//给接收窗口划线
	box( win->win_command.index,ACS_VLINE,ACS_HLINE); 
}

//删除屏幕
void display_del(display_win *win, const char *member) {
	//筛选成员
	if( strcmp(member,"win_tip_send") == 0 ) {
		delwin(win->win_tip_send.index);
	}else if( strcmp(member, "win_send") == 0 ) {
		delwin(win->win_send.index);
	}else if( strcmp(member, "win_tip_revice") == 0 ) {
		delwin(win->win_tip_revice.index);
	}else if( strcmp(member, "win_revice") == 0 ) {
		delwin(win->win_revice.index);
	}else if( strcmp(member, "win_tip_command") == 0 ) {
		delwin(win->win_tip_command.index);
	}else if( strcmp(member, "win_command") == 0 ) {
		delwin(win->win_command.index);
	}
}

//结束屏幕显示
void display_end(display_win **win) {
	//删除所有屏幕
	delwin((*win)->win_tip_send.index);
	delwin((*win)->win_send.index);
	delwin((*win)->win_tip_revice.index);
	delwin((*win)->win_revice.index);
	delwin((*win)->win_tip_command.index);
	delwin((*win)->win_command.index);

	//结束屏幕
	endwin();

	//释放指针
	free(*win);
}


