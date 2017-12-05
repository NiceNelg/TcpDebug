#include "tcpoperate.h"

int tcp_connect(char *temp_server_ip, int server_port) {
	//服务器地址
	char *server_ip;
	//连接数据结构体
	struct sockaddr_in sockaddr_in;
	//套接字编号
	int fd;
	//状态码
	int flags;
	//连接状态
	int connect_status;

	//保证传入的服务器地址数据正确性
	server_ip = (char *)malloc(sizeof(temp_server_ip));
	memcpy(server_ip, temp_server_ip, strlen(temp_server_ip));

	//创建套接字
	fd = socket(AF_INET, SOCK_STREAM, 0);
	//初始化连接数据结构体
	memset(&sockaddr_in, 0, sizeof(sockaddr));
	//设置连接类型
	sockaddr_in.sin_family = AF_INET;
	//将服务器端口转换成大端类型数据并设置(将设置端口数转换成符合tcp协议的数值)
	sockaddr_in.sin_port = htons(server_port);
	//将服务器地址设置成大端类型数据并设置(将服务器地址转换成符合tcp协议的数值)
	inet_pton(AF_INET, server_ip, &sockaddr_in);
	
	//读取套接字状态标志（因在Linux中套接字等多种数据流可当做文件看待，因此可以使用fcntl函数读取其状态标志）
	if( (flags = fcntl(fd, F_GETFL, 0)) < 0 ) {
		//套接字文件描述符不存在，套接字创建失败
		printf("errno:%d,err_message:%s\n", errno, strerror(errno));
		//结束程序
		exit(0);
	}

	//将连接设置成非阻塞状态(因套接字在Linux平台下可当做文件看待，因此可以用fcntl函数设置其属性)
	if( (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0) ) {
		printf("change fd fail");
	}

	//连接服务器
	if( (connect_status = connect(fd, (struct sockaddr *)&sockaddr_in, sizeof(sockaddr_in)) < 0) ) {
		
	}

	return fd;
}
