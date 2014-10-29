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
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "GetData.h"
#include "Info.h"


string GetData::getInfo(int type){
	switch(type) {
		case Notype:
			 return getError();
		case ClientListInfo:
			 return getClientInfo();
		case CpuInfo:
			 return getCpuInfo();
		case CpuRate:
			 return getCpuRate();
	}
}
string GetData::getError(){
	string errInfo = "No Such Client";

	return errInfo;
}
string GetData::getClientInfo(){
	FILE *pp;
	string Info = "";
	char buffer [128];

	pp = popen("uname -a", "r");

	if (fgets(buffer, sizeof(buffer), pp) != NULL){
		Info.append(buffer);

		return Info;
	}

	Info.append("Info Get Error");
	return Info;
}

string GetData::getCpuInfo(){
	FILE *pp;
	string Info = "";
	char buffer [128];

	pp = popen("cat /proc/cpuinfo |grep name |cut -f2 -d: |uniq -c", "r");

	if (fgets(buffer, sizeof(buffer), pp) != NULL){
		Info.append(buffer);

		return Info;
	}

	Info.append("Info Get Error");
	return Info;
}

string GetData::getMemInfo(){
	FILE *pp;
	string Info = "";
	char buffer [128];

	pp = popen("vmstat", "r");

	if (fgets(buffer, sizeof(buffer), pp) != NULL){
		Info.append(buffer);

		return Info;
	}

	Info.append("Info Get Error");
	return Info;
}

string GetData::getCpuRate(){
	FILE *fp;
	char buf[128];
	char cpu[5];
	char tmp[256];
	string Info = "";
	long int user, nice, sys, idle, iowait, irq, softirq;
	long int all1, all2, idle1, idle2;
	float usage;

	int i = 5;
	while (i--){
		fp = fopen("/proc/stat", "r");
	
		if (fp == NULL){
			Info.append("Info Get Error");

			return Info;
		}

		fgets(buf, sizeof(buf), fp);
		sscanf(buf, "%s%d%d%d%d%d%d%d", cpu, &user, &nice, &sys,
					&idle, &iowait, &irq, &softirq);

		all1 = user + nice + sys + idle + iowait + irq + softirq;
		idle1 = idle;

		rewind(fp);
		sleep(WAIT_TIME);
		memset(buf, 0, sizeof(buf));
	
		user = nice = sys = idle = iowait = irq = softirq = 0;

		fgets(buf, sizeof(buf), fp);
		sscanf(buf, "%s%d%d%d%d%d%d%d", cpu, &user, &nice, &sys,
					&idle, &iowait, &irq, &softirq);
		all2 = user + nice + sys + idle + iowait + irq + softirq;
		idle2 = idle;

		usage = (float) (all2 - all1 - (idle2 - idle1)) / (all2 - \
					all1) * 100;

		cout << "Cpu Use " << usage << endl;

		Info.append("Cpu Use ");

		sprintf(tmp, "%.2f", usage);

		Info.append(tmp);
	}
	close(fp);
	return Info;

}

