#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "pthread.h"
#include <ctime>
#include <exception>
#define WIN32
#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <WinSock2.h>
	#include <Ws2tcpip.h>
	#include <cstdint>
	#define SHUT_RDWR SD_BOTH
	typedef int	socklen_t;
	//void sleep(uint32_t s);
	#pragma comment(lib, "ws2_32.lib")
	#pragma comment(lib, "pthreadVC2.lib")
#else
	#include <arpa/inet.h>
	#include <sys/socket.h>
	#include <unistd.h>
#endif
class exception
{
    public: std::string x;
    exception(std::string x):x(x){}
};
class Common
{
public:
	Common();
	~Common();
	static void sleep(uint32_t s);
	static std::string EOLN;
};

extern Common common;


using namespace std;


