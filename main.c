#include "tcpoperate.h"
#include "sth.h"
#include "display.h"
#include "ncursesw/curses.h"

struct server_info {
	int port;
	char ip[];
};

int main() {
	
	//初始化屏幕
	display_win *win;
	display_init(&win);
	
	//初始化TCP客户端连接
	
	return 0;

}
