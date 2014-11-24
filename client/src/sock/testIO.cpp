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
	int countNum = 6;
	
	while (1){
		bool flag;
		struct mypacket packet;
		GetData getData;
		char temp[256];

	
		info.append(getData.getInfo(countNum));
		cout << info << endl; 

		cout << "Types: " << packet.infoTypes << endl;
		cout << "Len: " << packet.infoLen<< endl;
		cout << "Data: " << packet.infoDate << endl;

		info = "";
		sleep(5);
	}

	return 0;
}

