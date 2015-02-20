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
#include "updateConfig.h"
#include "log.h"

using std::cout;
using std::endl;

bool collectConfigureInfo(int fd, int num){
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

		if (countNum == 3){
			break;
		}
		info.append(",");
		countNum++;
	}
	info.append("]}");

	flag = InfoProtoBuf::packing(info, num, &packet);

	if (flag != true){

		mylog ("errlog.txt", "packing error");

		return false;
	}
	
	flag = InfoProtoBuf::msgSerialize(&packet, &sendData, temp);

	if (flag != true){
		return false;
	}

	int i = write (fd, temp, sendData.ByteSize());

	if (i < 0){
		mylog("errlog.txt", "write to pipe error");

		return false;
	}

	return true;
	
}

bool collectMonitor(int fd, int num){
	bool flag;
	struct mypacket packet;
	string info = "";
	ServerInfo::InfoPackage sendData;
	GetData getData;
	char temp[2014];
	int countNum = 4;

	info.append("{\"MonitorInfo\":[");
	while (1){
		info.append(getData.getInfo(countNum));
		
		if (countNum == 10){
			break;
		}
		info.append(",");
		countNum++;
	}
	info.append("]}");

	flag = InfoProtoBuf::packing(info, num, &packet);

	if (flag != true){
		mylog("errlog.txt", "Packing error");

		return false;
	}

	memset(temp, 0, sizeof(temp));

	flag = InfoProtoBuf::msgSerialize(&packet, &sendData, temp);


	if (flag != true){
		mylog("errlog.txt", "msgSerialize error");

		return false;
	}

	int i = write (fd, temp, sendData.ByteSize());


	if (i < 0){
		mylog("errlog.txt", "write to pipe error");

		return false;
	}
	return true;
}


void collectMain(int fd, int num){

	int sleepTime = getSleepTime(30);

	if (sleepTime < 30){
		sleepTime = 30;
	}

	collectConfigureInfo(fd, num);
	while (1){
		collectMonitor(fd, num);

		sleep(10);
		sleep(sleepTime);

		sleepTime = getSleepTime(30);
	}
}


