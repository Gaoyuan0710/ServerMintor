collectClient:main.o ServerInfo.pb.o socketOperator.o InfoProtoBuf.o GetData.o collect.o
	g++ -o collectClient main.o ServerInfo.pb.o socketOperator.o InfoProtoBuf.o GetData.o collect.o -lprotobuf
main.o:main.cpp InfoProtoBuf.h Info.h ServerInfo.pb.h GetData.h socketOperator.h
	g++ -c main.cpp 
ServerInfo.pb.o:ServerInfo.pb.cc ServerInfo.pb.h
	g++ -c ServerInfo.pb.cc
socketOperator.o:socketOperator.cpp socketOperator.h ../log/log.cpp
	g++ -c socketOperator.cpp
InfoProtoBuf.o:InfoProtoBuf.cpp InfoProtoBuf.h Info.h ServerInfo.pb.h
	g++ -c InfoProtoBuf.cpp
GetData.o:GetData.cpp GetData.h Info.h
	g++ -c GetData.cpp
collect.o:collect.cpp collect.h
	g++ -c collect.cpp
clean:
	rm *.o
