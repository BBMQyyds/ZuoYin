#pragma once
#include <WinSock2.h>
//��������
class Server {
private:
	//�����׽���
	SOCKET serviceSocket{};
	SOCKET recvClientSocket{};
	char recvBuf[1024] = {};
public:
public:
	Server(const char ip[10], int port);
	~Server();
	void startListen();
private:
	void receive();
	void feedback();
	void initWSADATA();
	void initListen();
	void initSocket(const char ip[10], int port);
};