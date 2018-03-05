#include "tcpoperate.h"
#include "sth.h"
#include "display.h"
#include <ncursesw/curses.h>
#include "link.h"
#include <stdlib.h>

struct server {
	int port;
	char *ip;
	int fd;
};

int main(int argc, char *argv[]) {
	
	//初始化TCP客户端连接参数
	struct server server_info;
	server_info.ip = (char *)malloc(15 * sizeof(char));
	server_info.ip = argv[1];
	server_info.port = (int)atoi(argv[2]);
	//连接TCP服务器
	server_info.fd = tcp_connect(server_info.ip, server_info.port);
	//初始化屏幕
	display_win *win;
	display_init(&win);
	
	
	return 0;

}
