#include <iostream>
#include "TcpServer.h"
int main(int argc, char const *argv[])
{
    /* code */
    sqh::TcpSever server;
    server.init();
    server.bind1(nullptr,6950);
    server.listen1(5);
    while(true)
        server.select1();
    return 0;
}
