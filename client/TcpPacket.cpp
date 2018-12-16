#include <iostream>
#include "TcpPacket.h"
namespace sqh{
TcpPacket::TcpPacket(int hLen, int tLen,int bLen,int bodylen)
:m_header_len(hLen), m_type_len(tLen),m_body_len(bLen),m_header(nullptr),m_bodyLen_len(bodylen),
    m_body(nullptr),m_type(nullptr)

{

}

bool TcpPacket::construct(){
    bool ret = true;
    m_header = new char[m_header_len];
    if( m_header == nullptr){
        ret = false;
    }

    m_body = new char[m_body_len];

    if( m_body == nullptr){
        delete[] m_header;
        ret = false;
    }

    m_type = new char[m_type_len];

    if( m_type == nullptr){
        delete[] m_body;
        delete[] m_header;

        ret = false;
    }

    return ret;
}

TcpPacket* TcpPacket::NewInstance(int hLen, int tLen,int bLen,int bodylen){
    TcpPacket* ret = new TcpPacket(hLen,tLen,bLen,bodylen);

    if(!ret || !ret->construct()){
        delete ret;
        ret = nullptr;
    }

    return ret;
}

const int TcpPacket::getHeaderLen(){
    return m_header_len;
}
const int TcpPacket::getTypeLen(){
    return this->m_type_len;
}
const int TcpPacket::getBodyLen(){
    return this->m_body_len;
}

 const int TcpPacket::getBodyLenSize(){
     return this->m_bodyLen_len;
 }

char* TcpPacket::getHeader(){
    return this->m_header;
}
char* TcpPacket::getType(){
    return this->m_type;
}
char* TcpPacket::getBody(){
    return this->m_body;
}


TcpPacket::~TcpPacket(){
    std::cout<< "~TcpPacket" <<std::endl;
    if(this->m_header){
        delete this->m_header;
        this->m_header = nullptr;
    }

    if(this->m_body){
        delete this->m_body;
        this->m_body = nullptr;
    }

    if(this->m_type){
        delete this->m_type;
        this->m_type = nullptr;
    }

    
}

}
