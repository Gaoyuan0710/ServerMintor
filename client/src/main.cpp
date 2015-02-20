// =====================================================================================
// 
//       Filename:  main.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年01月14日 15时01分27秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Gaoyuan, sishuiliunian0710@gmail.com
//        Company:  Class 1204 of Computer Science and Technology
// 
// =====================================================================================

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string>

#include "collect.h"
#include "socketOperator.h"

using std::string;

int main(int argc, char *argv[])
{
	int fd[2];
	pid_t pid;

	if (argc != 2){
		std::cout << "Please use like ./collectClient + clientNum" << std::endl;
		return -1;
	}
	
	int clientId;

	sscanf(argv[1], "%d", &clientId);


	if (pipe(fd) < 0){
		perror("pipe error");

		return -1;
	}

	if ((pid = fork()) < 0){
		perror("fork error");


		return -1;
	}
	else if (pid > 0){
		close(fd[1]);
		sockOperator mysocket("127.0.0.1", "8089", fd[0], clientId);
		mysocket.socketMain();
	}
	else {
		close(fd[0]);
		collectMain(fd[1], clientId);
	}

	return 0;
}

