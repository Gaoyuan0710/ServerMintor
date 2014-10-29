// =====================================================================================
// 
//       Filename:  GetData.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2014年10月28日 20时52分08秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include <sys/utsname.h>

#include "GetData.h"
#include "Info.h"

string GetData::getInfo(int type){
	switch(type) {
		case Notype:
			 return getError();
		case ClientListInfo:
			 return getClientInfo();
	}
}
string GetData::getError(){
	string errInfo = "No Such Client";

	return errInfo;
}
string GetData::getClientInfo(){
	struct utsname ClientInfo;
	string Info = "";
	if (uname(&ClientInfo) == 0){
		Info.append(ClientInfo.sysname);
		Info.append(" ");
		Info.append(ClientInfo.nodename);
		Info.append(" ");
		Info.append(ClientInfo.version);
		Info.append(" ");
		Info.append(ClientInfo.release);
		Info.append(" ");
		Info.append(ClientInfo.machine);
		Info.append(" ");
		Info.append(ClientInfo.domainname);
		Info.append(" ");


		return Info;
	}

	Info.append("Info Get Error");
	return Info;
}
