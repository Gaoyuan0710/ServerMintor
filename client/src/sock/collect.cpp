// =====================================================================================
// 
//       Filename:  collect.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年01月14日 14时24分53秒
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

bool collectConfigureInfo(int fd){
	bool flag;
	struct mypacket packet;
	string info = "";
	ServerInfo::InfoPackage sendData;
	GetData getData;
	char temp[1024];
	int countNum = 1;

	info.append("{\"BaseInfo\":[");
	while (1){
		info.append(getData.getInfo(countNum));

		if (countNum == 2){
			break;
		}
		info.append(",");
		countNum++;
	}
	info.append("]}");

	flag = InfoProtoBuf::packing(info, CpuInfo, &packet);

	if (flag != true){
		cout << "Packing error" << endl;

		return false;
	}
/*
	cout << "Types: " << packet.infoTypes << endl;
	cout << "Len: " << packet.infoLen << endl;
	cout << "Data:" << packet.infoDate << endl;
*/	
	flag = InfoProtoBuf::msgSerialize(&packet, &sendData, temp);

	if (flag != true){
		cout << "msgSerialize error" << endl;

		return false;
	}

	write (fd, temp, sendData.ByteSize());

	return true;
	
}

bool collectMonitor(int fd){
	bool flag;
	struct mypacket packet;
	string info = "";
	ServerInfo::InfoPackage sendData;
	GetData getData;
	char temp[2014];
	int countNum = 3;

	info.append("{\"MonitorInfo\":[");
	while (1){
		info.append(getData.getInfo(countNum));

		if (countNum == 6){
			break;
		}
		info.append(",");
		countNum++;
	}
	info.append("]}");
	flag = InfoProtoBuf::packing(info, CpuInfo, &packet);

	if (flag != true){
		cout << " Packing error" << endl;

		return false;
	}
	
/*	cout << "Types: " << packet.infoTypes << endl;
	cout << "Len: " << packet.infoLen << endl;
	cout << "Data:" << packet.infoDate << endl;

*/
	flag = InfoProtoBuf::msgSerialize(&packet, &sendData, temp);

	if (flag != true){
		cout << "msgSerialize error" << endl;

		return false;
	}

	write (fd, temp, sendData.ByteSize());

	return true;
	

}

void collectMain(int fd){
	collectConfigureInfo(fd);

	while (1){
		collectMonitor(fd);
		sleep(50);
	}
}

