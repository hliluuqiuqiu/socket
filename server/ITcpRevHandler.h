#ifndef ITCPRECV_HANDLER_H_SQH
#define ITCPRECV_HANDLER_H_SQH
#include "TcpPacket.h"
#include<list>
namespace sqh{
class ITcpRecvHandler{
public:
virtual bool setRawData(char* data,int len) = 0;
virtual std::list<TcpPacket*>* fetch() = 0;
};

}
#endif