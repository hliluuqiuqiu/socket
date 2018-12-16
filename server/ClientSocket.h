#ifndef CLIENT_SOCKET_H_SQH
#define CLIENT_SOCKET_H_SQH
#ifdef _WIN32
#include <windows.h>
#include <winsock2.h>
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif
#ifdef __linux__
#define	SOCKET int 
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#endif
#include "ITcpRevHandler.h"
#define FIRST_BUF_LEN 8196
namespace sqh{
class ClientSocket{
private:
   // static const int FIRST_BUF_LEN;
    ITcpRecvHandler* m_handler;
    SOCKET m_socket;
    char m_firstLBuf[FIRST_BUF_LEN];
    int  m_used;
   // int m_firstLBufLen;
public:
    sockaddr_in m_addr;
    ClientSocket();
    ClientSocket(SOCKET socket);
    ~ClientSocket();
    void setRecvHandler(ITcpRecvHandler* handler);
    ITcpRecvHandler* getRecvHandler();
    SOCKET getSocket();
    char*  getFirstLBuf();
    const int  getFirstLBufLen();
    int recvData();
    std::list<TcpPacket*>* fecthPackets();

}; 
 //const int FIRST_BUF_LEN = 8196;  
}
#endif