// =====================================================================================
// 
//       Filename:  main.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2014年11月01日 13时21分38秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include <string>
#include <unistd.h>

#include "InfoProtoBuf.h"
#include "Info.h"
#include "ServerInfo.pb.h"
#include "GetData.h"
#include "socketOperator.h"


using std::cout;
using std::endl;


int main(int argc, char *argv[])
{
	string info = "";
	sockOperator sockop;
	sockop.setAddrPort("127.0.0.1", "8089");
	sockop.connectLoop();
	int countNum = 0;
	
	while (1){
		bool flag;
		struct mypacket packet;
		ServerInfo::InfoPackage senddata;
		GetData getData;
		char temp[256];

	
		info.append(getData.getInfo(countNum % 6 + 1));
		cout << info << endl; 
		flag = InfoProtoBuf::packing(info, ClientBaseInfo, &packet);

		cout << "Types: " << packet.infoTypes << endl;
		cout << "Len: " << packet.infoLen<< endl;
		cout << "Data: " << packet.infoDate << endl;

		if (flag != true){
			cout << " Packing error" << endl;

			return -1;
		}
		flag = InfoProtoBuf::msgSerialize(&packet, &senddata, temp);

		if (flag != true ){
			cout << "msSerialize error" << endl;

			return -1;
		}
		sockop.sendInfo(temp, senddata.ByteSize());
		info = "";
		countNum++;
		sleep(5);
	}

	return 0;
}

