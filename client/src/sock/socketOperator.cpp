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

#include "socketOperator.h"
#include "ServerInfo.pb.h"
#include "../log/log.cpp"

namespace mySystemMintor{
bool sockOperator::setAddrPort(string dest, string port){	
	bzero(&destAddress, sizeof(destAddress));
	this->destAddress.sin_family = AF_INET;
	this->destAddress.sin_port = htons(atoi(port.c_str()));
	if (inet_pton(AF_INET, dest.c_str(), &destAddress.sin_addr) <= 0){
		printf("inet_pton error");
	}

	return true;
}
bool sockOperator::connectServer(){


	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0){
		mylog("errlog.txt", "Socket create err\n");

		exit (-1);
	}
	
	int ret = connect(sockfd, (struct sockaddr *) &destAddress, 
				sizeof(destAddress));
	if (ret != 0){
		printf ("%d\n", ret);
		perror("connect error");
		mylog("errlog.txt", "Connect err\n");

		exit (-1);
	}

	return true;
}
bool sockOperator::sendInfo(char *info, int len){
	int ret =  send(sockfd, info, len, 0);

//	int ret =  send(sockfd, "nihaoma", sizeof("nihaoma"), 0);
	cout << "Send " << ret << endl;

	if (ret != len ){
		mylog("errlog.txt", "Send Msg err\n");

		return false;
	}

	return true;
}
void sockOperator::msgSerialize(struct mypacket Info, char *buf, int len){
	senddata.set_infotypes(Info.types);
	senddata.set_infolen(Info.len);
	senddata.set_infodata(Info.value);

//	senddata.SerializeToArray(buf, senddata.ByteSize())
	senddata.SerializeToArray(buf, len);
}

}
