// =====================================================================================
// 
//       Filename:  1.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2014年11月03日 20时13分29秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unistd.h>

using namespace std;

string getNetworkStatus(){
	fstream reader1("/proc/net/dev", ios::in);
	char str[256];
	char tempName[10];
	unsigned long tempNum[14] = {0};
	unsigned long bytesRecv;
	unsigned long bytesTrans;
	int flag = 0;
	vector <long int> usefulData1;
	vector <long int> usefulData2;
	vector <string> devName;

	reader1.seekg(200, ios::beg);

	while (reader1.getline(str, 128)){
		cout << str << endl;
		bytesRecv = 0;
		bytesTrans = 0;

		sscanf(str, "%s%lu%lu%lu%lu%lu%lu%lu%lu%lu%lu%lu%lu%lu%lu%lu%lu", tempName, \
					&bytesRecv, &tempNum[0], &tempNum[1], &tempNum[2], &tempNum[3], \
					&tempNum[4], &tempNum[5], &tempNum[6], &bytesTrans, &tempNum[7],\
					&tempNum[8],  &tempNum[9],  &tempNum[10],  &tempNum[11],  &tempNum[12],  \
					&tempNum[13]);
		devName.push_back(tempName);
		usefulData1.push_back(bytesRecv);
		usefulData1.push_back(bytesTrans);
		cout << "Name " << tempName << " RECV " << bytesRecv << "   TRANS " << bytesTrans << endl;
	}

	reader1.close();
	sleep(10);
	fstream reader2("/proc/net/dev", ios::in);
	reader2.seekg(200, ios::beg);

	while (reader2.getline(str, 128)){
		cout << str << endl;
		bytesRecv = 0;
		bytesTrans = 0;

		sscanf(str, "%s%lu%lu%lu%lu%lu%lu%lu%lu%lu%lu%lu%lu%lu%lu%lu%lu", tempName, &bytesRecv, \
					&tempNum[0], &tempNum[1], &tempNum[2], &tempNum[3], &tempNum[4], &tempNum[5], \
					&tempNum[6], &bytesTrans, &tempNum[7],  &tempNum[8],  &tempNum[9],  &tempNum[10], 
					&tempNum[11],  &tempNum[12],  &tempNum[13]);
		usefulData2.push_back(bytesRecv);
		usefulData2.push_back(bytesTrans);
		cout << "Name " << tempName << " RECV " << bytesRecv << "   TRANS " << bytesTrans << endl;
	}
	int i = 0;
	while (i < devName.size()){
		unsigned long rate = (usefulData2[2 * i] + usefulData2[2 * i + 1] - usefulData1[2 * i] - usefulData1[2 * i + 1])/(1024);
		cout << devName[i] << " " << rate << endl;
		i++;
	}
	reader2.close();

	return " ";
}


int main(){
	getNetworkStatus();

	return 0;
}

