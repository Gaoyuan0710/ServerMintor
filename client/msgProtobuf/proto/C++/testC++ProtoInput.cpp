// =====================================================================================
// 
//       Filename:  testC++Proto.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2014年10月16日 20时20分04秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include <fstream>
#include <string>

#include "ServerInfo.pb.h"

using namespace std;

void getpacket(ServerInfo::Packet *packet){
	packet->set_len(1);
	packet->set_types(2);
	packet->set_value("nihao");
}
int main(int argc, char *argv[])
{

GOOGLE_PROTOBUF_VERIFY_VERSION;

	ServerInfo::Packet myPacket;
	
	getpacket(&myPacket);
	fstream output("kankan", ios::out | ios::trunc | ios::binary);
	if (!myPacket.SerializeToOstream(&output)){
		cout << "asdasd" << endl;
	}

	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}

