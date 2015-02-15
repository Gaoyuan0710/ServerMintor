// =====================================================================================
// 
//       Filename:  Info.h
//
//    Description:  
//
//        Version:  1.0
//        Created:  2014年10月28日 20时38分47秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include <string>

using std::string;

enum InfoType{
	Notype = 0,
	ClientBaseInfo = 1,
	CpuInfo = 2,
	IP = 3,
	MemInfo = 4,
	CpuRate = 5,
	NetWorkInfo = 6,
	DiskIO = 7,
	ProInfoSortByCpu = 8,
	ProInfoSortByMem = 9,
	NetWorkNums = 10
};
struct mypacket{
	int infoTypes;
	int infoLen;
	string infoDate;
};

