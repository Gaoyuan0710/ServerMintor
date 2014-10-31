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
		case MemInfo:
			 return getMemInfo();
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
	int j = 2;
	
	fp = fopen("/proc/stat", "r");
	if (fp == NULL){
		Info.append("Info Get Error");
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
	while (i < 5){
		if (i == 0 ){
			Info.append("Cpu Total :");
			sprintf(tmp, "%.2f", usage[i]);
			Info.append(tmp);
			Info.append("%\n");
			i++;
			continue;
		}
		Info.append("Cpu");
		Info.append(":");
		Info += i;
		sprintf(tmp, "%.2f", usage[i]);
		Info.append(tmp);
		Info.append("%\n");
		i++;
	}
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
		Info.append("MemTotal:");
		sprintf(tmp, "%d", sys.totalram / (1024 * 1024));
		Info.append(tmp);
		
		Info.append("\nMemFree:");
		sprintf(tmp, "%d", sys.freeram / (1024 * 1024));
		Info.append(tmp);
		
		Info.append("\nSwapTotal:");
		sprintf(tmp, "%d", sys.totalswap / (1024 * 1024));
		Info.append(tmp);
		
		Info.append("\nSwapFree:");
		sprintf(tmp, "%d", sys.freeswap / (1024 * 1024));
		Info.append(tmp);
	}
	else{
		Info.append("Get Info Error");
	}
	return Info;
}
