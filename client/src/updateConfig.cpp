// =====================================================================================
// 
//       Filename:  updateConfig.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年02月16日 13时29分46秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <iostream>
#include <string>

#include "updateConfig.h"
#include "log.h"

using std::string;
using std::cout;
using std::endl;

int getSleepTime(int oldTime){
	char buf[512];

	int fd = open( "config.txt", O_RDONLY);
	
	if( -1 == flock(fd, LOCK_NB | LOCK_EX)){
		return oldTime;
	}
	read(fd, buf, sizeof(int));

	string num = "";
	num.append(buf);
	int newTime = atoi(num.c_str());

	flock(fd, LOCK_UN);
	close(fd);
	
	return newTime;


}
int updateSleepTime(int newTime){
	char buf[512];
	
	int fd = open( "config.txt", O_WRONLY);
	
	flock(fd, LOCK_EX);

	sprintf(buf, "%d", newTime);
	
	int i = write(fd, buf, strlen(buf));

	if (i < 0){
		mylog("errlog.txt", "updateTime error");
	}

	flock(fd, LOCK_UN);
	close(fd);
	
	return newTime;
}

