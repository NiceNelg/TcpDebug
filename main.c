#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {

	//连接套接字编号
	int socketfd;
	
	//定义服务器地址结构体变量
	struct sockaddr_in sockaddr;

	//获取服务器地址和端口
	char *serverIp = "127.0.0.1";
	unsigned int serverPort = 9908;
	
	socketfd = socket( AF_INET, SOCK_STREAM, 0 );

	//初始化变量
	memset( &sockaddr, 0, sizeof(sockaddr) );
	sockaddr.sin_family = AF_INET;
	//将整数数值转换程网络字节序
	sockaddr.sin_port = htons( serverPort );
	inet_pton( AF_INET, serverIp, &sockaddr.sin_addr );

	//连接服务器
	if( (connect( socketfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr) )) < 0 ) {
		printf( "connect error %s\nerrorno: %d\n", strerror(errno), errno );
		exit(0);
	}
	return 0;
}
