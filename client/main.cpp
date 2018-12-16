#include "TcpClient.h"
#include "TcpRecvHandler.h"
using namespace sqh;
int main(int argc, char const *argv[])
{
    for(int i = 0 ; i < 1 ; i++)
    {
        sqh::TcpClient*  client = new sqh::TcpClient();
        TcpRecvHandler* handler = new TcpRecvHandler(10240);
        client->setHandler(handler);
        client->init();
        std::string addr("45.76.186.72");
        client->conn(&addr,7212);
        client->select1();

    }
     
    return 0;
}
