// =====================================================================================
// 
//       Filename:  getData.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2014年10月28日 20时28分43秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include <string>

//#include "Info.h"

using std::endl;
using std::cout;
using std::cin;
using std::string;

const int WAIT_TIME = 1;

class GetData{
	public:
		GetData(){}
		string getInfo(int types);
		string getError();
		string getClientInfo();
		string getCpuInfo();
		string getMemInfo();
		string getCpuRate();
		string getNetWorkStatus();
		string getDiskIO();
		string getIp();

		string getProSortByCpu();
		string getProSortByMem();
		string getNetWorkNums();
};
