// =====================================================================================
// 
//       Filename:  InfoProtoBuf.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2014年11月01日 10时29分18秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>

#include "InfoProtoBuf.h"
#include "ServerInfo.pb.h"
#include "Info.h"
#include "log.h"


bool InfoProtoBuf::packing(string info, int type, struct mypacket *infoPacket){
	infoPacket->infoTypes = type;
	infoPacket->infoLen = info.size();
	infoPacket->infoDate = info.c_str();
	
	return true;
}

bool InfoProtoBuf::msgSerialize(struct mypacket *infoPacket, ServerInfo::InfoPackage *senddata, char *buf){
	
	senddata->set_infotypes(infoPacket->infoTypes);
	senddata->set_infodata(infoPacket->infoDate);
	senddata->set_infolen(infoPacket->infoLen);
	bool flag = senddata->SerializeToArray(buf, senddata->ByteSize());

	if (flag == false){
		mylog("errlog.txt", "SerializeToArray error");

		return false;
	}

	return true;
}

