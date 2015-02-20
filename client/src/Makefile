collectClient:main.o ServerInfo.pb.o socketOperator.o InfoProtoBuf.o GetData.o collect.o updateConfig.o log.o
	g++ -g -o collectClient main.o ServerInfo.pb.o socketOperator.o InfoProtoBuf.o GetData.o collect.o updateConfig.o  log.o -lprotobuf
main.o:main.cpp InfoProtoBuf.h Info.h ServerInfo.pb.h GetData.h socketOperator.h updateConfig.h log.h
	g++ -c main.cpp 
ServerInfo.pb.o:ServerInfo.pb.cc ServerInfo.pb.h 
	g++ -c ServerInfo.pb.cc
socketOperator.o:socketOperator.cpp socketOperator.h log.h updateConfig.h
	g++ -c socketOperator.cpp
InfoProtoBuf.o:InfoProtoBuf.cpp InfoProtoBuf.h Info.h ServerInfo.pb.h log.h
	g++ -c InfoProtoBuf.cpp
GetData.o:GetData.cpp GetData.h Info.h log.h
	g++ -c GetData.cpp
collect.o:collect.cpp collect.h updateConfig.h log.h
	g++ -c collect.cpp updateConfig.cpp
updateConfig.o:updateConfig.cpp updateConfig.h log.h
	g++ -c updateConfig.cpp
log.o:log.cpp log.h
	g++ -c log.cpp
clean:
	rm *.o
