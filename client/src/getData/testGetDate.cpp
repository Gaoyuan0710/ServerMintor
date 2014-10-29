// =====================================================================================
// 
//       Filename:  testGetDate.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2014年10月29日 12时38分48秒
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

using std::endl;
using std::cout;

int main(int argc, char *argv[])
{
	GetData test(1);
	cout << " " << test.getInfo(4) << endl;

	return 0;
}

