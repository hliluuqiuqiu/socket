#ifndef TCPSERVER_H_SQH
#define TCPSERVER_H_SQH
#ifdef _WIN32
#include <windows.h>
#include <winsock2.h>
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif
#ifdef __linux__
#define	SOCKET int 
#define INVALID_SOCKET  ((SOCKET)(~0))
#define SOCKET_ERROR            (-1)
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
//#define IPPROTO_TCP 0
#endif
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "ClientSocket.h"
#include "TcpPacket.h"
#include <list>

namespace sqh{

class  TcpSever{
private:
   // enum SERVER_STATUS {INIT,BIND,LISTEN};
    SOCKET  m_vsocket;
    unsigned int m_port;

    std::vector<ClientSocket*>* clients;

   // SERVER_STATUS status; 
public:
    TcpSever();
    bool init();
    bool bind1(std::string* _addr , unsigned int _port);
    bool listen1(int maxNum);
    void accept1();
    virtual int select1();
    virtual int onRecive(ClientSocket* client);
    virtual void onNetMsg(SOCKET _socket,std::list<TcpPacket*>* packets);
    virtual ~TcpSever();
};

}


#endif