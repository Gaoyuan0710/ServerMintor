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
	long int user[5], nice[5], sys[5], idle[5], iowait[5], irq[5], softirq[5];
	long int all1[5], all2[5], idle1[5], idle2[5];
	float usage[5];

	long int user_pass[5], sys_pass[5], idle_pass[5];

	int j = 5;
	while (j--){
		fp = fopen("/proc/stat", "r");
	
		if (fp == NULL){
			Info.append("Info Get Error");

			return Info;
		}
		int i = 0;
		while (i < 5){
			fgets(buf, sizeof(buf), fp);
			sscanf(buf, "%s%d%d%d%d%d%d%d", cpu, &user[i], &nice[i], &sys[i],
						&idle[i], &iowait[i], &irq[i], &softirq[i]);
			
			all1[i] = user[i] + nice[i] + sys[i] + idle[i] + iowait[i] + irq[i] + softirq[i];
			idle1[i] = idle[i];
			user_pass[i] = user[i] + sys[i];
			i++;
		}
		rewind(fp);
		sleep(WAIT_TIME);
		memset(buf, 0, sizeof(buf));
	
		memset(user, 0, sizeof(user));
		memset(nice, 0, sizeof(nice));
		memset(sys, 0, sizeof(sys));
		memset(idle, 0, sizeof(idle));
		memset(irq, 0, sizeof(irq));
		memset(softirq, 0, sizeof(softirq));
		memset(iowait, 0, sizeof(iowait));
	
	
	//	user = nice = sys = idle = iowait = irq = softirq = 0;

		i = 0;

		while (i < 5){
			fgets(buf, sizeof(buf), fp);
			sscanf(buf, "%s%d%d%d%d%d%d%d", cpu, &user[i], &nice[i], &sys[i],
						&idle[i], &iowait[i], &irq[i], &softirq[i]);
			
			all2[i] = user[i] + nice[i] + sys[i] + idle[i] + iowait[i] + irq[i] + softirq[i];
			idle2[i] = idle[i];
			sys_pass[i] = user[i] + sys[i];
			i++;
		}
		i = 0;
		while (i < 5){
			usage[i] = ((float) (user_pass[i] - sys_pass[i]) )/ (user_pass[i] - sys_pass[i] - idle2[i] + idle1[i]) * 100;

		//	usage[i] = ((float) (user2[i] + sys2[i] - user1[i] - sys ) )/ (user[i] + nice[i] + sys[i] + idle[i])  * 100;
			cout << i << " : " << usage[i] << endl;
			i++;
		}
		i = 0;

	/*	while (i < 5){
			if (i == 0){
				cout << "Cpu Use " << usage[i] << endl;
				i++;
				continue;
			}
	
			cout << "Cpu" << i << " Use " << usage[i] << endl;

		//		Info.append("Cpu Use ");
	//		sprintf(tmp, "%.2f", usage);
	//		Info.append(tmp);
			i++;
		}
		j--;*/
	//	close(fp);
	}
	return Info;

}

