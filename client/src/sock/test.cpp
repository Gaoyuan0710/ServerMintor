// =====================================================================================
// 
//       Filename:  test.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2014年10月15日 21时47分27秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include <unistd.h>

#include "socketOperator.h"
#include "ServerInfo.pb.h"

using namespace mySystemMintor;
using namespace std;


int main(int argc, char *argv[])
{
	sockOperator testSocket;
	testSocket.setAddrPort("127.0.0.1", "8089");
	testSocket.connectServer();


	struct mypacket Info;
	Info.types = 1;
	Info.len = 2;
	Info.value = "nihaommmm";

	char tmp[100];
	testSocket.msgSerialize(Info, tmp, sizeof(struct mypacket));

	while (1){
		testSocket.sendInfo(tmp, testSocket.getPacketLen());

		sleep(1);
	}


	return 0;
}

