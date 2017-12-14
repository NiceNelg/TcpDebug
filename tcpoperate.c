#include "tcpoperate.h"

//设置连接超时时间
static const int TIMEOUT_TIME = 6;

int tcp_connect(char *temp_server_ip, int server_port) {
	//服务器地址
	char *server_ip;
	//连接数据结构体
	struct sockaddr_in sockaddr;
	//套接字编号
	int fd;
	//状态码
	int flags;
	//连接状态
	int connect_status;
	//时间结构体
	struct timeval timeval;
	//文件集合
	fd_set wset;
	//连接状态码
	int status = -1;
	//连接状态码长度
	int len;

	//保证传入的服务器地址数据正确性
	server_ip = (char *)malloc(sizeof(char) * strlen(temp_server_ip));
	memcpy(server_ip, temp_server_ip, strlen(temp_server_ip) - 1);

	//创建套接字
	if( ( fd = socket(AF_INET, SOCK_STREAM, 0) ) < 0 ){
		printf("create connect fail\n");
		return -1;
	}
	//初始化连接数据结构体
	memset(&sockaddr, 0, sizeof( struct sockaddr ));
	//设置连接类型
	sockaddr.sin_family = AF_INET;
	//将服务器端口转换成大端类型数据并设置(将设置端口数转换成符合tcp协议的数值)
	sockaddr.sin_port = htons(server_port);
	//将服务器地址设置成大端类型数据并设置(将服务器地址转换成符合tcp协议的数值)
	sockaddr.sin_addr.s_addr = inet_addr(server_ip);
	
	//读取套接字状态标志（因在Linux中套接字等多种数据流可当做文件看待，因此可以使用fcntl函数读取其状态标志）
	if( (flags = fcntl(fd, F_GETFL, 0)) < 0 ) {
		//套接字文件描述符不存在，套接字创建失败
		printf("errno:%d,err_message:%s\n", errno, strerror(errno));
		//结束程序
		return -1;
	}

	//将连接设置成非阻塞状态(因套接字在Linux平台下可当做文件看待，因此可以用fcntl函数设置其属性)
	if( (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0) ) {
		printf("change fd fail");
	}

	//连接服务器
	if( (connect_status = connect(fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) != 0) ) {
		
		//若errno等于EINPROGRESS表示正在连接，但未连接成功
		if( errno != EINPROGRESS ) {
			printf("connect fail\n");
			return -1;
		}
		//初始化时间结构体
		timeval.tv_sec = TIMEOUT_TIME;
		//此结构体成员代表设置的毫秒数
		timeval.tv_usec = 0;
		//清空文件集合变量
		FD_ZERO(&wset);
		//将连接套接字作为文件加入到集合中
		FD_SET(fd, &wset);
		//使用Select是可以完成非阻塞方式工作的函数，它能够监视我们需要监视的文件描述符的变化情况——读写或是异常
		//具体解释select的参数：
		//
		//参数一：是一个整数值，是指集合中所有文件描述符的范围，即所有文件描述符的最大值加1
		//
		//参数二：是指向fd_set结构的指针，这个集合中包括我们要监视的文件描述符如果这个集合中有一个文件可读，
		//select就会返回一个大于0的值，表示有文件可读，如果没有可读的文件，则根据timeout参数再判断是否超时，
		//若超出timeout的时间，select返回0，若发生错误返回负值。可以传入NULL值，表示不关心任何文件的读变化。
		//
		//参数三：是指向fd_set结构的指针，这个集合中包括我们要监视的文件描述符如果这个集合中有一个文件可写，
		//select就会返回一个大于0的值，表示有文件可写，如果没有可写的文件，则根据timeout参数再判断是否超时，
		//若超出timeout的时间，select返回0，若发生错误返回负值。可以传入NULL值，表示不关心任何文件的写变化。
		//
		//参数四：如上，监视文件的错误异常
		//
		//参数五：是select的超时时间，它可以使select处于三种状态，
		//第一，若将NULL以形参传入，即不传入时间结构，就是将select置于阻塞状态，一定等到监视文件描述符集合中
		//某个文件描述符发生变化为止；
		//第二，若将时间值设为0秒0毫秒，就变成一个纯粹的非阻塞函数，不管文件描述符是否有变化，都立刻返回继续
		//执行，文件无变化返回0，有变化返回一个正值；
		//第三，timeout的值大于0，这就是等待的超时时间，即select在timeout时间内阻塞，超时时间之内有事件到来就
		//返回了，否则在超时后不管怎样一定返回，返回值同上述。			
		
		//连接6秒，超时则代表连接失败
		connect_status = select(fd+1, NULL, &wset, NULL, &timeval);
		switch( connect_status ) {
			case -1:{
				printf("connect error\n");
				return -1;
			}break;

			case 0:{
				printf("connect timeout\n");
				return -1;
			}break;

			default:{
				//判断套接字编号是否在文件描述符集合中
				if(FD_ISSET(fd, &wset)) {
					//判断连接套接字状态
					if(getsockopt(fd, SOL_SOCKET, SO_ERROR, &status, (socklen_t *)&len) < 0) {
						return -1;
					}
					if( status == 0 ) {
						connect_status = 1;
					} else {
						connect_status = 0;
					}
					
				}
				printf("connect success\n");
			}break;
		}
	}

	//将套接字设置回阻塞状态
	fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) & O_NONBLOCK);

	//判断是否连接成功
	if(!connect_status) {
		close(fd);
		printf("connect fail\n");
		return -1;
	}

	return fd;
}
