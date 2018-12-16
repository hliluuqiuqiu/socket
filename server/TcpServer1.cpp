#include "TcpRecvHandler.h"
#include "TcpServer.h"
namespace sqh{
TcpSever::TcpSever():m_vsocket(0),clients(nullptr),m_port(0)
{
    clients = new std::vector<ClientSocket*>();
}
bool TcpSever::init(){
    m_vsocket  = socket(AF_INET,SOCK_STREAM,0);
    if (m_vsocket == INVALID_SOCKET)
	{
		std::cout << "vSocket ERROR" << std::endl;
		return false;
	}

}
bool TcpSever::bind1(std::string* _addr , unsigned int _port){
    sockaddr_in  addr;
	memset(&addr,0,sizeof(sockaddr_in));
	addr.sin_family = AF_INET;
#ifdef _WIN32	
	addr.sin_addr.S_un.S_addr = _addr == NULL? htonl(INADDR_ANY) : inet_addr(_addr->c_str());
#else
	addr.sin_addr.s_addr = (_addr == NULL)? htonl(INADDR_ANY) : inet_addr(_addr->c_str());
#endif
    addr.sin_port = htons(_port);
    int ret;
	ret = bind(m_vsocket, (sockaddr*)&addr,sizeof(addr));
	if (ret == SOCKET_ERROR) {
		std::cout << "bind ERROR" << std::endl;
		
	}
    return (ret == 0);

}
bool TcpSever::listen1(int maxNum){
    int ret = listen(m_vsocket,maxNum);
	if (ret == SOCKET_ERROR) {
		std::cout << "listen ERROR" << std::endl;
		//return 0;
	}
    return (ret == 0);

}
void TcpSever::accept1(){
	int static clientCount = 0;
    sockaddr_in addrClient = {0};
	unsigned int addrLen = sizeof(addrClient);

    SOCKET clientSocket = accept(m_vsocket, (sockaddr*)&addrClient, &addrLen);

	if (clientSocket == INVALID_SOCKET) {
		std::cout << "accept ERROR" << std::endl;

	}
	else {
		std::cout << "accept clent: " << ++clientCount << std::endl;
		printf("client addr: %s\n ", inet_ntoa(addrClient.sin_addr));
		ClientSocket* client = new ClientSocket(clientSocket);

		if(client == nullptr){
			std::cout << "non mem on accept" << std::endl;
			return;
		}
		TcpRecvHandler* handler = new TcpRecvHandler(10240);

		if(client == nullptr){
			std::cout << "non mem on accept" << std::endl;
			delete client;
			client = nullptr;
			return;
		}

		client->setRecvHandler(handler);
		client->m_addr = addrClient;
		clients->push_back(client);
	}
  
}
int TcpSever::select1(){
    int selectMax = m_vsocket;
    fd_set readFds;
	fd_set writeFds;
	fd_set exceptionFds;
    sockaddr_in addrClient = {0};
	unsigned int addrLen = sizeof(addrClient);
	int selectRet = 0;
	FD_ZERO(&readFds);
	FD_ZERO(&writeFds);
	FD_ZERO(&exceptionFds);
	FD_SET(m_vsocket, &readFds);
	FD_SET(m_vsocket, &writeFds);
	FD_SET(m_vsocket, &exceptionFds);
	for (int i = 0; i < clients->size(); i++) {
		FD_SET((*clients)[i]->getSocket(), &readFds);
		if((*clients)[i]->getSocket() > selectMax){
				selectMax = (*clients)[i]->getSocket();
		}
	}
	selectRet = select(selectMax+1, &readFds, &writeFds, &exceptionFds, NULL);
	if (selectRet < 0) {
		std::cout << "select  ERROR" << std::endl;
		return 0;
	}

	if (FD_ISSET(m_vsocket, &readFds)) {
		FD_CLR(m_vsocket, &readFds);
        accept1();
	}
	else {
#ifdef _WIN32			
		if (readFds.fd_count > 0) {
			for (int i = 0; i < readFds.fd_count; i++) {
				int processRet = processRecv(readFds.fd_array[i]);
				if (processRet == -1) {
					std::vector<SOCKET>::iterator iter = std::find(clients.begin(), clients.end(), readFds.fd_array[i]);
					if (iter != clients.end()) {
						 clients.erase(iter);
					}
				}
			}

		}
#else
		if(selectRet > 0){
			//	std::cout<<"arriv here"<<std::endl;
			for (auto iter = clients->begin(); iter != clients->end(); ) {
        		if(FD_ISSET((*iter)->getSocket(), &readFds)){
						int processRet = onRecive(*iter);
						if(processRet == -1){
							ClientSocket* gclient = *iter;
							close((*iter)->getSocket());
							iter = clients->erase(iter);
							delete gclient;
							gclient = nullptr;
							continue;
						}
				}
				iter++;
    		}

		}

#endif			
			
	}
	
}
int TcpSever::onRecive(ClientSocket*  s){
    char clientBuff[256] = { 0 };
	char sendbuff[256] = {(char)0xfe,(char)0xef,0x01,0x00};
	int revCount = 0;
	const char* name = "Im server";
	const char* version = "ver 0.0.1";
	const char* age = "two days";
	//revCount = recv(s->getSocket, s->getFirstLBuf, s->getFirstLBufLen, 0);
	revCount = s->recvData();
	if (revCount <= 0) {
		std::cout << "recv ERROR" << std::endl;
		return -1;
	}
	
	std::list<TcpPacket*>* packets = s->fecthPackets();
	onNetMsg(s->getSocket(),packets);
	/*
	if (strcmp(clientBuff, "name") == 0) {
		int sendLen = strlen(name) + 1;
		sendbuff[4] = (sendLen >> 8) & 0xff;
		sendbuff[5] = (sendLen) & 0xff;
		memcpy(sendbuff + 6,name,sendLen);
		sendbuff[5 + sendLen] = 0;
		send(s, sendbuff, strlen(name) + 1 + 6, 0);
	}
	else if (strcmp(clientBuff, "version") == 0) {
		send(s, version, strlen(version), 0);
	}
	else if (strcmp(clientBuff, "age") == 0) {
		send(s, age, strlen(age) + 1, 0);
	}*/
	return 0;

}
void TcpSever::onNetMsg(SOCKET _socket,std::list<TcpPacket*>* packets){
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
 //   std::cout <<"delete packets;"<<std::endl;
    delete packets;

}
TcpSever::~TcpSever(){
    delete clients;
}
}