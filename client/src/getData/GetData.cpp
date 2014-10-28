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

#include "GetData.h"
#include "Info.h"

string getData::getInfo(int type){
	switch(type) {
		case:Notype:
			 return getError();
		case:ClientListInfo:
			 return getClientInfo();
	}
}
string getData::getError(){
	string errInfo = "No Such Client";

	return errInfo;
}
string getData::getClientInfo(){
}
