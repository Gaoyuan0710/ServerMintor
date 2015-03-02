// =====================================================================================
// 
//       Filename:  updateConfig.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年02月16日 13时26分02秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#ifndef UPDATECONFIG_H
#define UPDATECONFIG_H

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>


int getSleepTime(int sleepTime);
int updateSleepTime(int sleepTime);

#endif
