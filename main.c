#include "tcpoperate.h"
#include "sth.h"
#include "display.h"
#include <ncursesw/curses.h>
#include "operate.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
	//屏蔽信号
	

	//初始化TCP客户端连接参数
	server_info server_info;
	server_info.ip = (char *)malloc(15 * sizeof(char));
	server_info.ip = argv[1];
	server_info.port = (int)atoi(argv[2]);
	//连接TCP服务器
	server_info.fd = tcp_connect(server_info.ip, server_info.port);
	if( server_info.fd < 0 ) {
		return 0;
	}
	//初始化屏幕
	display_win *win;
	display_init(&win);
	//开始操作流程
	operate_set operate_set;
	operate_start(&operate_set);
	getch();
	display_end(&win);
	return 0;

}
