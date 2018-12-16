#ifndef TCP_RECV_HANDLER_SQH
#define TCP_RECV_HANDLER_SQH
#include "ITcpRevHandler.h"
#include "CircleBuffer.h"
namespace sqh{
class TcpRecvHandler : public ITcpRecvHandler {
private:
CircleBuffer* m_cirBuffer;
public:
    TcpRecvHandler(size_t size);
    bool setRawData(char* data,int len);
    std::list<TcpPacket*>* fetch();
    ~TcpRecvHandler();
};
}
#endif