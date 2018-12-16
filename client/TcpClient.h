#ifndef CLINET_TCP_SQH
#define CLINET_TCP_SQH
#ifdef _WIN32
#include <windows.h>
#include <winsock2.h>
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif
#ifdef __linux__
#define	 SOCKET int
#define INVALID_SOCKET  ((SOCKET)(~0))
#define SOCKET_ERROR            (-1)
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
//#define IPPROTO_TCP 0
#endif
 #include <stdio.h> 
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include "TcpPacket.h"
#include "ITcpRevHandler.h"
namespace sqh{
class TcpClient{
private:
    SOCKET m_socket;
    std::string* serverAddr ;
    int serverPort;
    ITcpRecvHandler* m_handler;
    char recvBuf[8019];
public:
    SOCKET init();
    TcpClient();
    bool conn(std::string*,int);
    void setHandler(ITcpRecvHandler* handler);
    virtual bool select1();
    virtual void onRecv();
    virtual void onNetMsg(std::list<TcpPacket*>* packets);
    virtual int sendData(char* data , int len);

    virtual ~TcpClient();
};

}
#endif