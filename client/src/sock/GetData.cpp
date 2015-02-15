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
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netinet/in.h>


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
		case IP:
			 return getIp();
		case ProInfoSortByCpu:
			 return getProSortByCpu();
		case ProInfoSortByMem:
			 return getProSortByMem();
		case NetWorkNums:
			 return getNetWorkNums();
	}
	return getError();
}
string GetData::getError(){
	string errInfo = "{\"Error\":\"No Such Client\"}";

	return errInfo;
}
string GetData::getClientInfo(){
	FILE *pp;
	string Info = "{\"ClientBaseInfo\":";
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
				pp = popen("date -d next-day '+%F %T'", "r");
				
				if (fgets(buffer, sizeof(buffer), pp) != NULL){
					Info.append("\"serverTime\":\"");
					Info.append(buffer);
					Info = Info.substr(0, Info.length() - 1);
					Info.append("\"}}");	
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

	pp = popen("vmstat |awk 'NR==3{print $9,$10}'", "r");

	if(fgets(buffer, sizeof(buffer), pp) != NULL){
//		fgets(buffer, sizeof(buffer), pp);
//		fgets(buffer, sizeof(buffer), pp); 
		
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
			Info.append("{\"CpuTotal\":\"");
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
//		cout << str << endl;
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
	//	cout << str << endl;
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
	//	cout << devName[i] << " " << rate << endl;
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
string GetData::getIp(){
	int tmpFd;
	int intr;
	struct ifreq buf[16];
	struct ifconf ifc;


	string Info = "{\"Ip\":\"";
	



	tmpFd = socket(AF_INET, SOCK_DGRAM, 0);

	if (tmpFd < 0){
		return "Wrong Address";
	}

	ifc.ifc_len = sizeof(buf);
	ifc.ifc_ifcu.ifcu_buf = (caddr_t) buf;

	if (ioctl(tmpFd, SIOCGIFCONF, (char *)&ifc)){
		return "Wrong Address";
	}
	intr = ifc.ifc_len / sizeof(struct ifreq);

	while (intr-- > 0 && ioctl(tmpFd, SIOCGIFADDR, (char *)&buf[intr]))
	  ;
	close(tmpFd);

	string data(inet_ntoa(((struct sockaddr_in *)(&buf[intr].ifr_ifru.ifru_addr))->sin_addr));

	Info += data;
	Info.append("\"}");

	return Info;

}

string GetData::getProSortByCpu(){
	FILE *pp;
	string Info = "";
	string tempdata = "";
	char buffer[1024];

	pp = popen("ps auxch | sort -k3 -r | awk 'NR<15{print $1,$2,$3,$4,$8,$11}'", "r");

	while(fgets(buffer, sizeof(buffer), pp) != NULL){
		tempdata.append(buffer);
		tempdata = tempdata.substr(0, tempdata.length() - 1);
		tempdata.append(" ");
	}
	
		
	Info.append("{\"proInfoSortByCpu\":\"");
	Info += "gaoyuan 15070 6.1 13.8 Sl+ java gaoyuan 27079 4.4 1.6 Sl chrome gaoyuan 26897 4.0 3.6 Sl chrome root 1135 1.6 0.9 Ss+ X gaoyuan 1704 1.3 2.3 Sl kwin gaoyuan 26942 1.1 3.1 Sl chrome gaoyuan 1743 0.9 11.9 Sl plasma-desktop gaoyuan 7547 0.9 1.0 Sl konsole gaoyuan 27014 0.6 1.7 Sl chrome gaoyuan 885 0.1 2.5 Sl chrome gaoyuan 687 0.1 2.3 Sl chrome gaoyuan 30168 0.1 2.3 Sl+ java gaoyuan 30162 0.1 1.1 Sl+ java gaoyuan 627 0.0 2.1 Sl chrome";
	Info = Info.substr(0, Info.length() - 1);
	Info.append("\"}");

	pclose(pp);
	
	//cout << "Info " << Info.size() << endl;
	
	return Info;
	
}
string GetData::getProSortByMem(){
	FILE *pp;
	string Info = "";
	char buffer[1024];
	string tempdata = "";


//	pp = popen("ps auxch | sort -k4 -r | awk 'NR<10{print $2, $11}'", "r");
	pp = popen("ps auxch | sort -k4 -r | awk 'NR<5{print $1,$2,$3,$4,$8,$11}'", "r");

	while(fgets(buffer, sizeof(buffer), pp) != NULL){
		tempdata.append(buffer);
		tempdata = tempdata.substr(0, tempdata.length() - 1);
		tempdata.append(" ");
	
	}
		
	Info.append("{\"proInfoSortByMem\":\"");
	Info += tempdata;
	Info = Info.substr(0, Info.length() - 1);
	Info.append("\"}");

	pclose(pp);
	

	cout << "Info " << Info.size() << endl;

	//return " ";
	return Info;
	
}
string GetData::getNetWorkNums(){
	FILE *pp;
	string Info = "";
	char buffer[512];
	string tempdata = "";

	pp = popen("netstat -n | awk '/^tcp/ {++S[$NF]} END {for(a in S) print a, S[a]}'", "r");

	while(fgets(buffer, sizeof(buffer), pp) != NULL){
		tempdata.append(buffer);
		tempdata = tempdata.substr(0, tempdata.length() - 1);
		tempdata.append(" ");
	}
		
		
	Info.append("{\"NetWorkNums\":\"");
	Info += tempdata;
	Info = Info.substr(0, Info.length() - 1);
	Info.append("\"}");

	pclose(pp);



	cout << "pppppppppppp   " << Info.size() << endl;
	return Info;
	
}

