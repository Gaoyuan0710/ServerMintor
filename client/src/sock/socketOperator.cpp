// =====================================================================================
// 
//       Filename:  socketOperator.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2014年10月14日 21时26分14秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>

#include "socketOperator.h"
#include "ServerInfo.pb.h"
#include "../log/log.cpp"

bool sockOperator::setAddrPort(){	
	bzero(&destAddress, sizeof(destAddress));
	this->destAddress.sin_family = AF_INET;
	this->destAddress.sin_port = htons(atoi(this->port.c_str()));
	if (inet_pton(AF_INET, this->dest.c_str(), &destAddress.sin_addr) <= 0){
		printf("inet_pton error");
	}

	return true;
}
bool sockOperator::connectServer(){


	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0){
		mylog("errlog.txt", "Socket create err\n");

		return false;
	}
	
	int ret = connect(sockfd, (struct sockaddr *) &destAddress, 
				sizeof(destAddress));
	if (ret != 0){
		printf ("%d\n", ret);
		perror("connect error");
		mylog("errlog.txt", "Connect err\n");

		return false;
	}

	return true;
}
bool sockOperator::sendInfo(char *info, int len){
	int ret =  send(sockfd, info, len, 0);
	
	cout << "Send " << ret << endl;

	if (ret != len ){
		mylog("errlog.txt", "Send Msg err\n");

		return false;
	}


	return true;
}
bool sockOperator::connectLoop(){
	bool flag = true;

	while (1){
		flag = connectServer();

		if (flag == true){
			break;
		}

		sleep(10);
	}
	return true;
}

void sockOperator::socketMain(){
	this->setAddrPort();
	this->connectLoop();
	this->dealWithEpoll();
}
void sockOperator::dealWithEpoll(){
	struct epoll_event event[this->kEpollEvent];
	int epollFd;
	char dataBuf[1024];

	epollFd = epoll_create(kMaxFdSize);
	
	addEvent(epollFd, sockfd, EPOLLIN);
	addEvent(epollFd, pipeFd, EPOLLIN);

	for (;;){
		int ret = epoll_wait(epollFd, event, kEpollEvent, -1);

		for (int i = 0; i < ret ; i++){
			int fd = event[i].data.fd;

			if ((event[i].events & EPOLLIN) && (fd == pipeFd)){
				dealPipeRead(dataBuf);
			}
			else if ((event[i].events & EPOLLIN) && (fd == sockfd)){
				dealSockFd();
			}
			else if (event[i].events & EPOLLOUT){
				dealWrite(dataBuf);
			}
		}
	}
}

bool sockOperator::dealSockFd(){
	int readLen;
	char buf[1024];
	
	readLen = read(sockfd, buf, 1024);
	if (readLen >= 0){
		cout << "Recv Message From Server\n" << buf;
	}
	else {
		perror("read from server error");

		exit(1);
	}

	return true;
}
bool sockOperator::dealPipeRead(char *buf){
	int readLen;

	readLen = read(pipeFd, buf, 1024);

	if (-1 == readLen){
		perror("read error");
		close(pipeFd);
		deleteEvent(epollFd, pipeFd, EPOLLIN);
		exit (1);
	}
	else if (readLen == 0){
		fprintf(stderr, "close collect function");
		close(pipeFd);
		deleteEvent(epollFd, pipeFd, EPOLLIN);
	}
	else{
		cout << "Recv Message From CollectFunction\n" << buf << endl;
		modifyEvent(epollFd, sockfd, EPOLLOUT);
//		dealWrite(buf);
	//	write(sockfd, buf, readLen);
	}

	return true;
}

bool sockOperator::dealWrite(char *buf){
	int writeLen;

	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "ssssssssssssssss" << endl;
	writeLen = write(sockfd, buf, strlen(buf));

	if (writeLen == -1){
		perror("write error");
		close(sockfd);
		deleteEvent(epollFd, sockfd, EPOLLOUT);
	}
	else{
		modifyEvent(epollFd, sockfd, EPOLLIN);
	}
	memset(buf, 0, sizeof(buf));	
} 

bool sockOperator::deleteEvent(int epollFd, int fd, int state){
	struct epoll_event tmp;

	tmp.events = state;
	tmp.data.fd = fd;

	epoll_ctl(epollFd, EPOLL_CTL_DEL, fd, &tmp);

	return true;
}
bool sockOperator::modifyEvent(int epollFd, int fd, int state){
	struct epoll_event tmp;

	tmp.events = state;
	tmp.data.fd = fd;

	epoll_ctl(epollFd, EPOLL_CTL_MOD, fd, &tmp);

	return true;
}

bool sockOperator::addEvent(int epollFd, int fd, int state){
	struct epoll_event tmp;

	tmp.events = state;
	tmp.data.fd = fd;

	epoll_ctl(epollFd, EPOLL_CTL_ADD,fd, &tmp);

	return true;
}
