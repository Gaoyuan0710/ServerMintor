// =====================================================================================
//
//       Filename:  errno.cpp
//
//    Description:
//
//        Version:  1.0
//        Created:  2014年10月15日 19时53分31秒
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
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>

using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::fstream;


bool mylog(string filename, string err){
	string absPath(filename);
	absPath.append(filename);

	int fd = open(absPath.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0664);
	
	flock(fd, LOCK_EX);

	int i = write(fd, err.c_str(), err.length());

	flock(fd, LOCK_UN);
	close(fd);

	if (i < 0){
		return false;
	}
	return true;
}

