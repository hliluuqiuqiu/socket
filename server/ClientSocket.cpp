
#include <iostream>
#include "ClientSocket.h"

namespace sqh{

    ClientSocket::ClientSocket()
    : m_socket(-1),m_handler(nullptr)
    {

    }

    ClientSocket::ClientSocket(SOCKET socket)
    : m_socket(socket),m_handler(nullptr)
    {

    }

    ClientSocket::~ClientSocket(){
        if(m_socket != -1){                     
            close(m_socket);
        }
        if(m_handler){
            delete  m_handler;
        }
    }
    void ClientSocket::setRecvHandler(ITcpRecvHandler* handler){
        m_handler = handler;
    }
    ITcpRecvHandler* ClientSocket::getRecvHandler(){
        return m_handler;
    }
    SOCKET ClientSocket::getSocket(){
        return m_socket;
    }

    char*  ClientSocket::getFirstLBuf(){
        return m_firstLBuf;
    }

    const int  ClientSocket::getFirstLBufLen(){
        return FIRST_BUF_LEN;
    }

    int ClientSocket::recvData(){
        int revCount = recv(m_socket,m_firstLBuf,FIRST_BUF_LEN, 0);
        if(revCount <= 0){
            return -1;
        }

        bool ret = m_handler->setRawData(m_firstLBuf,revCount);

        if(ret == false){
            std::cout<<"circle mem full"<<std::endl;
        }
        return revCount;
    }

    std::list<TcpPacket*>* ClientSocket::fecthPackets(){
       std::list<TcpPacket*>* ret = nullptr;

       if(m_handler){
           ret = m_handler->fetch();
       } 

       return ret;
    }
}