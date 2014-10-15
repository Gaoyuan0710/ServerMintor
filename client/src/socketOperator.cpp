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

#include "../include/socketOperator.h"
#include "log.cpp"

namespace mySystemMintor{
bool sockOperator::setAddrPort(string dest, string port){	
	bzero(&destAddress, sizeof(destAddress));
	destAddress.sin_family = AF_INET;
	destAddress.sin_port = htons(atoi(port.c_str()));
	inet_pton(AF_INET, dest.c_str(), &destAddress.sin_port);

	return true;
}
bool sockOperator::connectServer(){
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	if (sockfd < 0){
		mylog("errlog.txt", "Socket create err\n");

		exit (-1);
	}
	int ret = connect(sockfd, (struct sockaddr *) & destAddress, 
				sizeof(destAddress));
	if (ret != 0){
		mylog("errlog.txt", "Connect err\n");

		exit (-1);
	}

	return true;
}
bool sockOperator::sendInfo(string info){
//	int ret =  send(destAddress, info.c_str(), sizeof(info.length()), 0);


	int ret =  send(sockfd, "nihao", sizeof("nihao"), 0);
	if (ret != sizeof(struct packet)){
		mylog("errlog.txt", "Send Msg err\n");

		return false;
	}

	return true;
}

}

