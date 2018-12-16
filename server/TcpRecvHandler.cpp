#include <iostream>
#include "TcpPacket.h"
#include "TcpRecvHandler.h"
namespace sqh{
TcpRecvHandler::TcpRecvHandler(size_t size)
: m_cirBuffer(nullptr)
{
    m_cirBuffer = CircleBuffer::NewInstance(size);
    if(m_cirBuffer == nullptr){
        std::cout<<"TcpRecvHandler alloc failed"<<std::endl;
    }   
}  
bool TcpRecvHandler::setRawData(char* data,int len){
    return (this->m_cirBuffer)->set(data,len);
}

std::list<TcpPacket*>* TcpRecvHandler::fetch(){
    std::list<TcpPacket*>* ret = new std::list<TcpPacket*>();
    char head[2 + 2 + 2] = {0};
    int packetLen = 0;
    bool while_condition = true;

    while(while_condition){
       if(m_cirBuffer->get(head,sizeof(head)) ){
           int bodyLen = ((head[4] & 0xff) << 8 | (head[5] & 0xff)) & 0xffff;
           packetLen = bodyLen + 2 + 2 + 2;
           if(packetLen > m_cirBuffer->size()){
                break;
           }else{
                TcpPacket*  packet = TcpPacket::NewInstance(2,2,bodyLen,2);
                if(packet == nullptr){
                   break;
                }

                m_cirBuffer->fetch(packet->getHeader(), packet->getHeaderLen()); 
                m_cirBuffer->fetch(packet->getType(), packet->getTypeLen());
                m_cirBuffer->fetch(packet->getBody(), packet->getBodyLenSize());

                m_cirBuffer->fetch(packet->getBody(), packet->getBodyLen());
                ret->push_back(packet);
           }
       } else{
           break;
       }

    }
     

    return ret;
}

TcpRecvHandler::~TcpRecvHandler(){
    if(this->m_cirBuffer){
        delete this->m_cirBuffer;
        this->m_cirBuffer = nullptr;
    }
}

}