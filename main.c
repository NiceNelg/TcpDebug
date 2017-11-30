#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXLINE 2048

int main() {

	//定义接收发送buff
	char sendline[MAXLINE];
	char revline[MAXLINE];
	char command[50];

	//连接套接字编号
	int socketfd;
	
	//定义服务器地址结构体变量
	struct sockaddr_in sockaddr;

	//定义服务器地址和端口
	char serverIp[15];
	unsigned int serverPort;

	//设置服务器地址
	printf("Set Server IP\n");
	fgets(serverIp, 15, stdin);

	//设置端口
	printf("Set Server port\n");
	scanf("%d", &serverPort);
	
	//创建套接字
	socketfd = socket(AF_INET, SOCK_STREAM, 0);

	//初始化变量
	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	//将整数数值转换程网络字节序(将设置端口数转换成符合tcp协议的数值)
	sockaddr.sin_port = htons(serverPort);
	//将设置的服务器地址转换成符合tpc协议的数值
	inet_pton(AF_INET, serverIp, &sockaddr.sin_addr);

	//连接服务器
	if( (connect(socketfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr))) < 0 ) {
		printf("connect error %s\nerrorno: %d\n", strerror(errno), errno);
		exit(0);
	}

	while(1) {
		//获取命令
		fgets(command, 50, stdin);
		//筛选命令
		switch() {
		
		}
		//输入数据
		fgets(sendline, MAXLINE, stdin);

		//发送数据
		if(send(socketfd, sendline, strlen(sendline), 0) < 0) {
			printf("send data error:%s\nerrno:%d\n", strerror(errno), errno);
			exit(0);
		}

		//打印数据
		if(recv(socketfd, revline, strlen(revline), 0) < 0) {
			printf("revice data error:%s\nerrno:%d\n", strerror(errno), errno);
			exit(0);
		} else {
			printf("revice data: %x", revline);
		}
	}

	//关闭连接
	close(socketfd);
	printf("exit\n");
	return 0;
}

int selectCommand(const char *command) {

}
