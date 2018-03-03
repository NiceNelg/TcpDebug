#include "tcpoperate.h"
#include "sth.h"
#include "display.h"
#include <ncursesw/curses.h>
#include "link.h"
#include <stdlib.h>

struct server_info {
	int port;
	char *ip;
};

int main(int argc, char *argv[]) {
	
	//初始化TCP客户端连接
	struct server_info server_info;
	server_info.ip = (char *)malloc(15 * sizeof(char));
	server_info.ip = argv[1];
	server_info.port = (int)atoi(argv[2]);

	printf("server_ip:%s,server_port:%d\n", server_info.ip, server_info.port);
	return 0;
	//初始化屏幕
	display_win *win;
	display_init(&win);
	
	
	return 0;

}
