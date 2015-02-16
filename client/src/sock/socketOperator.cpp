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

#include "updateConfig.h"
#include "socketOperator.h"
#include "ServerInfo.pb.h"
#include "../log/log.cpp"

using std::string;


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
	cout << "Connect Successfully" << endl;
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
	char dataBuf[2048];

	epollFd = epoll_create(kMaxFdSize);
	
	addEvent(epollFd, sockfd, EPOLLIN);
	addEvent(epollFd, pipeFd, EPOLLIN);

	for (;;){
		memset(dataBuf, 0, sizeof(dataBuf));

		int ret = epoll_wait(epollFd, event, kEpollEvent, -1);

		for (int i = 0; i < ret ; i++){
			int fd = event[i].data.fd;

			if ((event[i].events & EPOLLIN) && (fd == pipeFd)){
				cout << "pipeFd read" << endl;
				dealPipeRead(dataBuf);
			}
			if ((event[i].events & EPOLLIN) && (fd == sockfd)){
				cout << "sockFd read" << endl;
			//	dealPipeRead(dataBuf);
				dealSockFd();
			}
			if ((event[i].events & EPOLLOUT) && (fd == sockfd)){
				cout << "sockFd write" << endl;
			//	dealPipeRead(dataBuf);
		//		dealWrite(dataBuf);
			}
		}
	}
}

bool sockOperator::dealSockFd(){
	int readLen;
	char buf[2048];
	
	readLen = read(sockfd, buf, 2048);
	if (readLen >= 0){
		cout << "Recv Message From Server\n" << buf << endl;

		dealOrder(buf);

//		sleep(1);
	}
	else {
		perror("read from server error");

//		exit(1);
	}

	return true;
}
bool sockOperator::dealPipeRead(char *buf){
	int readLen;

	bzero(buf, sizeof(buf));
	readLen = read(pipeFd, buf, 2048);

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
		cout << "Recv Message From CollectFunction\n" << endl;

		cout << "pipeRead " << readLen << "while buf size " << strlen(buf) << endl;
	//	cout << buf << endl;
//		modifyEvent(epollFd, sockfd, EPOLLOUT);
//		dealWrite(buf);
//
//		cout << buf << endl;

int i = 		write(sockfd, buf, readLen);

		cout << "socket write " << i << endl;

	}

	return true;
}

bool sockOperator::dealWrite(char *buf){
	int writeLen;

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

	int flag = epoll_ctl(epollFd, EPOLL_CTL_MOD, fd, &tmp);
	cout << flag << endl;

	return true;
}

bool sockOperator::addEvent(int epollFd, int fd, int state){
	struct epoll_event tmp;

	tmp.events = state;
	tmp.data.fd = fd;

	epoll_ctl(epollFd, EPOLL_CTL_ADD,fd, &tmp);

	return true;
}

void sockOperator::dealOrder(string order){

	
	int index1 = order.find_first_of("&");
	int index2 = order.find_last_of("&");


	string myOrder = order.substr(0, index1);
	
	string serverId = order.substr(index1 + 1, index2 - index1 - 1);
	
	string parameter = order.substr(index2 + 1, order.length());

	cout << index1 << " " << index2 << endl;
	cout << myOrder << endl;
	cout << serverId << endl;
	cout << parameter << endl;
/*
	if (string(myorder) == string("")){
		 myOrder = "init 6";
		 
//		 system(myOrder.c_str());
	}
	else if (string(order) == string("upateTime")){
		updateSleepTime()
	}
	else {
		myOrder = "kill -s 9 ";
		myOrder += order;
		
//		system(myOrder.c_str());
	}
	
*/

} 
