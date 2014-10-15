// =====================================================================================
// 
//       Filename:  test.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2014年10月15日 21时47分27秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>

#include "socketOperator.cpp"

using namespace mySystemMintor;
using namespace std;

int main(int argc, char *argv[])
{
	sockOperator testSocket;
	testSocket.setAddrPort("127.0.0.1", "6666");
	testSocket.connectServer();

	cout << "i" << endl;

	while (1){
		testSocket.sendInfo("niaho");
		cout << "o" ;
	}


	return 0;
}

