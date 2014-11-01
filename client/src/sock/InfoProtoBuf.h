// =====================================================================================
// 
//       Filename:  InfoProtoBuf.h
//
//    Description:  
//
//        Version:  1.0
//        Created:  2014年11月01日 10时38分43秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#ifndef _INFOPROTOBUF_H
#define _INFOPROTOBUF_H

#include <iostream>
#include <string>

#include "ServerInfo.pb.h"

using std::string;

class InfoProtoBuf{
	public:
		InfoProtoBuf(){}
		static bool packing(string info, int type, struct mypacket *
					infoPacket);
		static bool msgSerialize(struct mypacket *infoPacket, 
					ServerInfo::InfoPackage senddata, char *buf);


};

#endif
