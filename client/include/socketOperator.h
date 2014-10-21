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

#include "ServerInfo.pb.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

#define BUFLINE 1024

namespace mySystemMintor{


struct packet{
	int types;
	int len;
	char value[BUFLINE];
};

class sockOperator{
	public:
		sockOperator(){}
		bool sendInfo(char *info, int len);
		void msgSerialize(struct packet info, char *buf, int len);
//		string msgDeserialize(ServerInfo::InfoPackage msg);
		bool setAddrPort(string dest, string port);
		bool connectServer();
	private:
		struct sockaddr_in destAddress;
		int sockfd;


};


}

#endif
