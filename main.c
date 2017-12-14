#include "tcpoperate.h"
#include "sth.h"

#define MAXLINE 2048

//命令列表结构体
struct order_list {
	char quit[3];
	char send_string[3];
	char send_hex[4];
}order_list={"q\n", "s\n", "sh\n"};

//函数定义
void tcp_operate(int socketfd, const char *sendline);

int main() {

	//定义接收发送buff
	char sendline[MAXLINE];
	char sendline_temp[MAXLINE];
	//命令缓存区
	char command[50];
	char command_temp[50];

	//连接套接字编号
	int socketfd;
	//连接服务器地址和端口号
	char *server_ip;
	int server_port;

	//设置服务器地址
	printf("Set Server IP:");
	setbuf(stdin, NULL);
	server_ip = (char *)malloc(sizeof(char) * 20);
	fgets(server_ip, 20, stdin);
	//设置端口
	printf("Set Server port:");
	setbuf(stdin,NULL);
	scanf("%d", &server_port);
	
	socketfd = tcp_connect(server_ip, server_port);
	//连接服务器
	if( socketfd < 0 ) {
		exit(0);
	}

	while(1) {
		//清空命令缓冲区
		memset(command_temp, 0, sizeof(command_temp));
		memset(command, 0, sizeof(command));
		//提示
		printf("command >");
		//清空终端输入缓冲区，避免数据混淆
		setbuf(stdin, NULL);
		//获取命令
		fgets(command_temp, 50, stdin);
		memcpy(command, command_temp, strlen(command_temp));
		

		//筛选命令
		if(strcmp(command, order_list.quit) == 0) {
			printf("program exit\n");
			exit(0);
		} else if(strcmp(command, order_list.send_hex) == 0) {
			continue;
		} else if( (strcmp(command, order_list.send_string) == 0) || (strcmp(command, "\n") == 0) ) {
			//输入数据
			memset(sendline, 0, sizeof(sendline_temp));
			memset(sendline, 0, sizeof(sendline));
			//提示
			printf("data >");
			setbuf(stdin, NULL);
			fgets(sendline_temp, MAXLINE, stdin);
			memcpy(sendline, sendline_temp, strlen(sendline_temp) - 1);
			//发送数据
			tcp_operate(socketfd, sendline);
		}
	}

	//关闭连接
	close(socketfd);
	printf("exit\n");
	return 0;
}

void tcp_operate(int socketfd, const char *sendline) {
	//接受数据buf
	char revline[MAXLINE];

	int length;
	int i;

	//发送数据
	if(send(socketfd, sendline, strlen(sendline), 0) < 0) {
		printf("send data error:%s\nerrno:%d\n", strerror(errno), errno);
		exit(0);
	}else {
		printf("send data:%s\n", sendline);
	}

	//打印数据
	if(recv(socketfd, revline, MAXLINE, 0) < 0) {
		printf("revice data error:%s\nerrno:%d\n", strerror(errno), errno);
		exit(0);
	} else {
		printf("revice data:%s\n", revline);
		length = strlen(revline);
		printf("revice data_hex:\n");
		for(i=0;i<length;i++) {
			printf("%#X ", (unsigned int)revline[i]);
		}
		printf("\n");
	}
}
