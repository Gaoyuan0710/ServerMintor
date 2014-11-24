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

bool sendConfigureInfo(sockOperator sockop){
	bool flag;
	struct mypacket packet;
	string info = "";
	ServerInfo::InfoPackage senddata;
	GetData getData;
	char temp[1024];
	int countNum = 1;

	info.append("{\"BaseInfo\":[");
	while (1){
		info.append(getData.getInfo(countNum));
		cout << info << endl; 

		if (countNum == 2){
			break;
		}
		info.append(",");
		countNum++;
	}
	info.append("]}");
	flag = InfoProtoBuf::packing(info, ClientBaseInfo, &packet);
	if (flag != true){
		cout << " Packing error" << endl;
		
		return false;
	}
	cout << "Types: " << packet.infoTypes << endl;
	cout << "Len: " << packet.infoLen<< endl;
	cout << "Data: " << packet.infoDate << endl;

	flag = InfoProtoBuf::msgSerialize(&packet, &senddata, temp);
	
	if (flag != true ){
		cout << "msSerialize error" << endl;
		
		return false;
	}


	sockop.sendInfo(temp, senddata.ByteSize());
	
	return true;
}

bool sendMonitor(sockOperator sockop){
	bool flag;
	struct mypacket packet;
	string info = "";
	ServerInfo::InfoPackage senddata;
	GetData getData;
	char temp[1024];
	int countNum = 3;

	info.append("{\"MonitorInfo\":[");
	while (1){
		info.append(getData.getInfo(countNum));
		cout << info << endl; 

		if (countNum == 6){
			break;
		}
		info.append(",");
		countNum++;
	}
	info.append("]}");
	flag = InfoProtoBuf::packing(info, ClientBaseInfo, &packet);
	if (flag != true){
		cout << " Packing error" << endl;
		
		return false;
	}
	cout << "Types: " << packet.infoTypes << endl;
	cout << "Len: " << packet.infoLen<< endl;
	cout << "Data: " << packet.infoDate << endl;

	flag = InfoProtoBuf::msgSerialize(&packet, &senddata, temp);
	
	if (flag != true ){
		cout << "msSerialize error" << endl;
		
		return false;
	}


	sockop.sendInfo(temp, senddata.ByteSize());


	cout << info << endl;

	cout << "Good" << endl;
	
	return true;
}

int main(int argc, char *argv[])
{
	sockOperator sockop;
	sockop.setAddrPort("127.0.0.1", "8089");
	sockop.connectLoop();
	int countNum = 0;
	
	sendConfigureInfo(sockop);
	while (1){
		sendMonitor(sockop);

		sleep(10);
	}

	return 1;
}

