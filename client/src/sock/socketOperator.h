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
#ifndef _SOCKETOPERATOR_H_
#define _SOCKETOPERATOR_H_

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
#include <arpa/inet.h>
#include <sys/epoll.h>

#include "ServerInfo.pb.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::string;

#define BUFLINE 1024


class sockOperator{
	public:
		sockOperator(string dest, string port, int pipeFd){
			this->dest = dest;
			this->port = port;
			this->pipeFd = pipeFd;
		}
		void socketMain();
		bool sendInfo(char *info, int len);
		bool setAddrPort();
		bool connectServer();
		bool connectLoop();
		bool addEvent(int epollFd, int fd, int state);
		bool deleteEvent(int epollFd, int fd, int state);
		bool modifyEvent(int epollFd, int fd, int state);
		bool dealPipeRead(char *buf);
		bool dealSockFd();
		
		bool dealWrite(char *buf);
		void dealWithEpoll();

	private:
		struct sockaddr_in destAddress;
		int sockfd;
		static const int kMaxFdSize = 100;
		static const int kEpollEvent = 100;
		int pipeFd;
		int epollFd;
		string dest;
		string port;


};



#endif
