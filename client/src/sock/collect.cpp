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

		if (countNum == 3){
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


//	int i = write (fd, a.c_str(), a.size());
	return true;
	
}

bool collectMonitor(int fd){
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

//string tmp = "{\"ProInfoSortByCpu\":[{\"proInfoSortByCpu\":\"gaoyuan 15070 6.1 13.8 Sl+ java gaoyuan 27079 4.4 1.6 Sl chrome gaoyuan 26897 4.0 3.6 Sl chrome root 1135 1.6 0.9 Ss+ X gaoyuan 1704 1.3 2.3 Sl kwin gaoyuan 26942 1.1 3.1 Sl chrome gaoyuan 1743 0.9 11.9 Sl plasma-desktop gaoyuan 7547 0.9 1.0 Sl konsole gaoyuan 27014 0.6 1.7 Sl chrome gaoyuan 885 0.1 2.5 Sl chrome gaoyuan 687 0.1 2.3 Sl chrome gaoyuan 30168 0.1 2.3 Sl+ java gaoyuan 30162 0.1 1.1 Sl+ java gaoyuan 627 0.0 2.1 Sl chrom\"}]}";
//info.append(",");
//info.append(tmp);


	//cout << "Monitor size "  << info.size() << endl;

//	flag = InfoProtoBuf::packing(tmp, CpuInfo, &packet);
	flag = InfoProtoBuf::packing(info, CpuInfo, &packet);

	if (flag != true){
		cout << " Packing error" << endl;

		return false;
	}
	
//	cout << "Types: " << packet.infoTypes << endl;
//	cout << "Len: " << packet.infoLen << endl;
//	cout << "Data:" << packet.infoDate << endl;


	memset(temp, 0, sizeof(temp));

	flag = InfoProtoBuf::msgSerialize(&packet, &sendData, temp);


	if (flag != true){
		cout << "msgSerialize error" << endl;

		return false;
	}

	int i = write (fd, temp, sendData.ByteSize());


	cout << "Common pipe write = " << i << " " << sendData.ByteSize()  << " " << strlen(temp)<< endl;
//	int i = write (fd, a.c_str(), a.size());
	cout << "i = " << i << " " << sendData.ByteSize() << endl;
	return true;
	

}
bool collectProInfoSortByCpu(int fd){
	bool flag;
	struct mypacket packet;
	string info = "";
	ServerInfo::InfoPackage sendData;
	GetData getData;
	char temp[2014];
	int countNum = 8;

	info.append("{\"ProInfoSortByCpu\":[");
	while (1){
		info.append(getData.getInfo(countNum));

		if (countNum == 8){
			break;
		}
		info.append(",");
		countNum++;
	}
	info.append("]}");


string tmp = "{\"ProInfoSortByCpu\":[{\"proInfoSortByCpu\":\"gaoyuan 15070 6.1 13.8 Sl+ java gaoyuan 27079 4.4 1.6 Sl chrome gaoyuan 26897 4.0 3.6 Sl chrome root 1135 1.6 0.9 Ss+ X gaoyuan 1704 1.3 2.3 Sl kwin gaoyuan 26942 1.1 3.1 Sl chrome gaoyuan 1743 0.9 11.9 Sl plasma-desktop gaoyuan 7547 0.9 1.0 Sl konsole gaoyuan 27014 0.6 1.7 Sl chrome gaoyuan 885 0.1 2.5 Sl chrome gaoyuan 687 0.1 2.3 Sl chrome gaoyuan 30168 0.1 2.3 Sl+ java gaoyuan 30162 0.1 1.1 Sl+ java gaoyuan 627 0.0 2.1 Sl chrom\"}]}";
//	cout << "Info " << info.size() << endl;
	
//flag = InfoProtoBuf::packing(info, CpuInfo, &packet);

	flag = InfoProtoBuf::packing(tmp, CpuInfo, &packet);

	memset(temp, 0, sizeof(temp));

	flag = InfoProtoBuf::msgSerialize(&packet, &sendData, temp);

	if (flag != true){
		cout << "msgSerialize error" << endl;

		return false;
	}

	int i = write (fd, temp, sendData.ByteSize());


	cout << "CPU pipe write = " << i << " " << sendData.ByteSize()  << " " << strlen(temp)<< endl;
	return true;
	

}

bool collectProInfoSortByMem(int fd){
	bool flag;
	struct mypacket packet;
	string info = "";
	ServerInfo::InfoPackage sendData;
	GetData getData;
	char temp[2014];
	int countNum = 9;

	info.append("{\"ProInfoSortByMem\":[");
	while (1){
		info.append(getData.getInfo(countNum));

		if (countNum == 9){
			break;
		}
		info.append(",");
		countNum++;
	}
	info.append("]}");


	cout << "IIIIII" << info.size() << endl;
	flag = InfoProtoBuf::packing(info, CpuInfo, &packet);

	if (flag != true){
		cout << " Packing error" << endl;

		return false;
	}
	
//	cout << "Types: " << packet.infoTypes << endl;
//	cout << "Len: " << packet.infoLen << endl;

	
	
//	cout << "Data:" << packet.infoDate << endl;

//	cout << endl;

	flag = InfoProtoBuf::msgSerialize(&packet, &sendData, temp);


	if (flag != true){
		cout << "msgSerialize error" << endl;

		return false;
	}

	int i = write (fd, temp, sendData.ByteSize());


//	int i = write (fd, a.c_str(), a.size());
//	cout << "i = " << i << " " << sendData.ByteSize()  << "sizeof " << strlen(temp)<< endl;
	return true;
	

}










bool collectNetWorkMums(int fd){
	bool flag;
	struct mypacket packet;
	string info = "";
	ServerInfo::InfoPackage sendData;
	GetData getData;
	char temp[2014];
	int countNum = 10;

	info.append("{\"NetWorkNums\":[");
	while (1){
		info.append(getData.getInfo(countNum));

		if (countNum == 10){
			break;
		}
		info.append(",");
		countNum++;
	}
	info.append("]}");


	cout << "IIIIII" << info.size() << endl;
	flag = InfoProtoBuf::packing(info, CpuInfo, &packet);

	if (flag != true){
		cout << " Packing error" << endl;

		return false;
	}
	
//	cout << "Types: " << packet.infoTypes << endl;
//	cout << "Len: " << packet.infoLen << endl;

	
	
//	cout << "Data:" << packet.infoDate << endl;

//	cout << endl;

	flag = InfoProtoBuf::msgSerialize(&packet, &sendData, temp);
//	string a = "";

//	char a[2048];
//	flag = InfoProtoBuf::msgSerializee(&packet, &sendData, &a);


	if (flag != true){
		cout << "msgSerialize error" << endl;

		return false;
	}

	int i = write (fd, temp, sendData.ByteSize());

//	int i = write (fd, a.c_str(), a.size());

	//	cout << "i = " << i << " " << sendData.ByteSize()  << "sizeof " << strlen(temp)<< endl;
	return true;
	

}






void collectMain(int fd){
	collectConfigureInfo(fd);
	while (1){
		collectMonitor(fd);

	//	sleep(25);

//		collectProInfoSortByCpu(fd);
/*		sleep(1);
		collectProInfoSortByMem(fd);
		sleep(1);
		collectNetWorkMums(fd);
*/		sleep(6);
	//	sleep(25);
	}
}


