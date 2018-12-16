#include "TcpClient.h"
namespace sqh{
    TcpClient::TcpClient():m_socket(INVALID_SOCKET),serverAddr(nullptr),serverPort(0),m_handler(nullptr)
    {


    }
    SOCKET TcpClient::init(){
        SOCKET ret  = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (ret == INVALID_SOCKET)
	    {
		    std::cout << "vSocket ERROR" << std::endl;
		   
	    }else{
            m_socket = ret;
        }

        return ret;
    }
    bool TcpClient::conn(std::string* _addr,int port){
        bool ret = false;
        if(_addr == nullptr){
            return ret;
        }
        serverAddr  =  new std::string(*_addr);
	    sockaddr_in  addr = {};
	    addr.sin_family = AF_INET;
#ifdef _WIN32	
	    addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
#else
	
	    addr.sin_addr.s_addr = inet_addr(serverAddr->c_str());//inet_addr("127.0.0.1");
#endif

	    addr.sin_port = htons(port);
	    ret = connect(m_socket,(sockaddr*)&addr,sizeof(addr));
	    if (ret == SOCKET_ERROR) {
		    std::cout << "connect ERROR" << std::endl;
		    return ret;
	    }
         std::cout << "connect success" << std::endl;
        ret = true;
        return ret;
    }

    bool TcpClient::select1(){
        fd_set readFds;
	    fd_set writeFds;
	    fd_set exceptionFds;
        char sendBuf[256] = {0};
	    int selectRet = -1;
        while (false) {
            FD_ZERO(&readFds);
            FD_ZERO(&writeFds);
            FD_ZERO(&exceptionFds);

            FD_SET(m_socket, &readFds);
            FD_SET(m_socket, &writeFds);
            FD_SET(m_socket, &exceptionFds);
            selectRet = select(m_socket + 1, &readFds, &writeFds, &exceptionFds, NULL);
        //	std::cout << "hello selectRet" << std::endl;
            if (selectRet < 0) {
                return 0;
            }
            
            if (FD_ISSET(m_socket, &readFds)) {
                    onRecv();
                }
            else if (FD_ISSET(m_socket, &writeFds)) {
                    char buf[1024] = {0};
                    std::cin>>buf;	
                    if (strcmp(sendBuf, "exit") == 0) {
                        break;
                    }
                    else {
                        //printf("send:%s\n",sendBuf);
                       // sendData(sendBuf, strlen(name) + 1 + 6);
                    }
                
                }
            
        }
	
            return true;
    }

    void TcpClient::onRecv(){       
        int revCount = recv(m_socket, recvBuf, sizeof(recvBuf), 0);
        if(revCount == SOCKET_ERROR || revCount == 0){
            close(m_socket);
            printf("vSocket close \n");
            return ;
        }
       // m_handler->setRawData(recvBuf,revCount);
      //  onNetMsg(m_handler->fetch());
        //printf("vount : %d,ser : %s\n", revCount, recvBuf);
    }
    void TcpClient::onNetMsg(std::list<TcpPacket*>* packets){
        if(packets == nullptr){
            return;
        }

        for(auto it = packets->begin(); it != packets->end();){
          // std::cout << "body[0]:"<<((int)(((*it)->getBody())[0]))<<std::endl;
           
           printf("body[0] %s\n",(*it)->getBody());
           TcpPacket* p = (*it);
           it = packets->erase(it);
           delete p;
           p = nullptr;

        }
       // printf("delete packets\n");
        std::cout <<"delete packets;"<<std::endl;
        delete packets;

    }
    int TcpClient::sendData(char* data ,int len){
        if(data == nullptr || len == 0){
            return 0;
        }

        send(m_socket, data, len, 0);  
    }

    void TcpClient::setHandler(ITcpRecvHandler* handler){
        m_handler = handler;
    }

    TcpClient::~TcpClient(){
        if(serverAddr){
            delete serverAddr;
            serverAddr = nullptr;            
        }

        if(m_handler){
           delete  m_handler;
        }
    }

}