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
#include <sys/sysinfo.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <iostream>

#include "GetData.h"
#include "Info.h"

using std::vector;
using std::ios;
using std::fstream;

string GetData::getInfo(int type){
	switch(type) {
		case Notype:
			 return getError();
		case ClientBaseInfo:
			 return getClientInfo();
		case CpuInfo:
			 return getCpuInfo();
		case CpuRate:
			 return getCpuRate();
		case MemInfo:
			 return getMemInfo();
		case NetWorkInfo:
			 return getNetWorkStatus();
		case DiskIO:
			 return getDiskIO();
	}
	return getError();
}
string GetData::getError(){
	string errInfo = "{\"Error\":\"No Such Client\"}";

	return errInfo;
}
string GetData::getClientInfo(){
	FILE *pp;
	string Info = "";
	char buffer [128];
	int flag = 0;
	bool finishFlag = false;

	while (!finishFlag){
		switch (flag){
			case 0:
				pp = popen("uname -n", "r");
				if (fgets(buffer, sizeof(buffer), pp) != NULL){
					Info.append("{\"serverName\":\"");
					Info.append(buffer);
					Info = Info.substr(0, Info.length() - 1);
					Info.append("\",");
				}
				pclose(pp);
				flag = 1;
			case 1:
				pp = popen("uname -o", "r");
				if (fgets(buffer, sizeof(buffer), pp) != NULL){
					Info.append("\"serverOS\":\"");
					Info.append(buffer);
		 			Info = Info.substr(0, Info.length() - 1);
					Info.append("\",");
				}
				pclose(pp);
				flag = 2;
			case 2:
				pp = popen("uname -r", "r");
				if (fgets(buffer, sizeof(buffer), pp) != NULL){
					Info.append("\"serverKernel\":\"");
					Info.append(buffer);
					Info = Info.substr(0, Info.length() - 1);
					Info.append("\",");
				}
				pclose(pp);
				
				flag = 3;
			case 3:
				pp = popen("date", "r");
				
				if (fgets(buffer, sizeof(buffer), pp) != NULL){
					Info.append("\"serverTime\":\"");
					Info.append(buffer);
					Info = Info.substr(0, Info.length() - 1);
					Info.append("\"}");	
				}
				pclose(pp);

				flag = 4;
			default:
				finishFlag = true;
				break;
		}
	}

	if (flag == 4){
		return Info;
	}
	return ("{\"Error\":\"No Such Client\"}");
}

string GetData::getCpuInfo(){
	FILE *pp;
	string Info = "";
	char buffer [128];

	pp = popen("cat /proc/cpuinfo |grep name |cut -f2 -d: |uniq -c", "r");

	if (fgets(buffer, sizeof(buffer), pp) != NULL){
		Info.append("{\"CpuInfo\":\"");
		Info.append(buffer);
		Info = Info.substr(0, Info.length() - 1);
		Info.append("\"}");

		return Info;
	}

	Info.append("{\"Error\":\"No Such Client\"}");
	return Info;
}
string GetData::getDiskIO(){
	FILE *pp;
	string Info = "";
	char buffer[128];

	pp = popen("vmstat |awk '{print $9,$10}'", "r");

	if(fgets(buffer, sizeof(buffer), pp) != NULL){
		fgets(buffer, sizeof(buffer), pp);
		fgets(buffer, sizeof(buffer), pp); 
		
		Info.append("{\"IOInfo\":\"");
		Info.append(buffer);
		Info = Info.substr(0, Info.length() - 1);
		Info.append("\"}");

		pclose(pp);
		return Info;
	}
	
}
string GetData::getCpuRate(){
	FILE *fp;
	char buf[128];
	char cpu[5];
	char tmp[256];
	string Info = "";
	long  user[5], nice[5], sys[5], idle[5], iowait[5], irq[5], softirq[5];
	long  all1[5], all2[5];
	float usage[5];
	long int tt1[5], tt2[5];

	fp = fopen("/proc/stat", "r");
	if (fp == NULL){
		Info.append("{\"Error\":\"No Such Client\"}");
		return Info;
	}
	int i = 0;
	while (i < 5){
		fgets(buf, sizeof(buf), fp);
		sscanf(buf, "%s %ld %ld %ld %ld %ld %ld %ld", cpu, &user[i], &nice[i],
					&sys[i], &idle[i], &iowait[i], &irq[i], &softirq[i]);
		all1[i] = user[i] + nice[i] + sys[i] + idle[i] + iowait[i] + irq[i] + softirq[i];
		tt1[i] = user[i] + sys[i];
		i++;
	}
	sleep(2);
	fclose(fp);

	fp = fopen("/proc/stat", "r");
	rewind(fp);
	i = 0;
	while (i < 5){
		fgets(buf, sizeof(buf), fp);
		sscanf(buf, "%s %ld %ld %ld %ld %ld %ld %ld", cpu, &user[i], &nice[i], &sys[i],
					&idle[i], &iowait[i], &irq[i], &softirq[i]);
		all2[i] = user[i] + nice[i] + sys[i] + idle[i] + iowait[i] + irq[i] + softirq[i];
		tt2[i] = user[i] + sys[i];
		usage[i] = (((float) (tt2[i] - tt1[i]) )/ (all2[i] - all1[i])) * 100;
		i++;
	}
	i = 0;
	Info.append("{\"CpuRate\":[");
	while (i < 5){
		if (i == 0 ){
			Info.append("{\"Cpu Total \":\"");
			sprintf(tmp, "%.2f", usage[i]);
			Info.append(tmp);
			Info.append("%\"},");
			i++;
			continue;
		}
		Info.append("{\"Cpu");
		sprintf(tmp, "%d", i);
		Info.append(tmp);
		Info.append("\":\"");
		sprintf(tmp, "%.2f", usage[i]);
		Info.append(tmp);
		Info.append("%\"},");
		i++;
	}
	Info = Info.substr(0, Info.length() - 1);
	Info.append("]}");
	fclose(fp);
	return Info;
}
string GetData::getMemInfo(){
	string Info = "";
	struct sysinfo sys;
	int flag;
	char tmp[128];

	flag = sysinfo(&sys);
	if (flag == 0){
		Info.append("{\"MemInfo\":[");	
		Info.append("{\"MemTotal\":\"");
		sprintf(tmp, "%ld", (long int)sys.totalram / (1024 * 1024));
		Info.append(tmp);
//		Info = Info.substr(0, Info.length() - 1);
		Info.append("\"},");

		Info.append("{\"MemFree\":\"");
		sprintf(tmp, "%ld", (long int)sys.freeram / (1024 * 1024));
	
		Info.append(tmp);
//		Info = Info.substr(0, Info.length() - 1);
		Info.append("\"},");


		Info.append("{\"SwapTotal\":\"");
		sprintf(tmp, "%ld", (long int)sys.totalswap / (1024 * 1024));
		Info.append(tmp);
//		Info = Info.substr(0, Info.length() - 1);
		Info.append("\"},");


		Info.append("{\"SwapFree\":\"");
		sprintf(tmp, "%ld", (long int)sys.freeswap / (1024 * 1024));
		Info.append(tmp);
//		Info = Info.substr(0, Info.length() - 1);
		Info.append("\"}");
		Info.append("]}");

	}
	else{
		Info.append("{\"Error\":\"Get Info Error\"}");
		return Info;
	}
	return Info;
}

string GetData::getNetWorkStatus(){
	char str[256];
	char tempName[10];
	unsigned long tempNum[14] = {0};
	unsigned long bytesRecv;
	unsigned long bytesTrans;
	int flag = 0;
	string Info = "{\"NetWorkInfo\":[";
	vector <long int> usefulData1;
	vector <long int> usefulData2;
	vector <string> devName;

	fstream reader1("/proc/net/dev", ios::in);
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
	}

	reader1.close();
	sleep(1);
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
	}
	int i = 0;
	char tmp[100];
	while (i < devName.size()){
		unsigned long rate = (usefulData2[2 * i] + usefulData2[2 * i + 1] - usefulData1[2 * i] - usefulData1[2 * i + 1])/(1024);
		cout << devName[i] << " " << rate << endl;
		Info.append("{\"");
		Info.append(devName[i]);
		Info.append("\":\"");
		sprintf(tmp, "%d", (int)rate);
		Info.append(tmp);
		Info.append("kb/s\"},");
		i++;
	}
	Info = Info.substr(0, Info.find_last_of(","));
//	Info = Info.substr(0, Info.length() - 1);
	Info.append("]}");
	reader2.close();

	return Info;
}

