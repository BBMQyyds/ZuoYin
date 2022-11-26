#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<string>
#include<cstring>
#include<WS2tcpip.h>
#include <WinSock2.h>
#include<Windows.h>
#pragma comment(lib, "ws2_32.lib")
#include "Server.h"
#include "StringUtils.h"
#include "JsonUtils.h"
#include "Singleton.h"

Server::Server(const char ip[10], int port) {
	std::cout << "\n-----------������-----------" << std::endl;
	initWSADATA();
	initSocket(ip, port);
	initListen();
}

//��ֹ������
Server::~Server() {
	closesocket(serviceSocket);
	WSACleanup();
	std::cout << "������ֹͣ" << std::endl;
	std::cin.get();
}

//��ʼ����
void Server::startListen() {
	while (true) {
		receive();
		feedback();
		closesocket(recvClientSocket);
	}
}

//��������
void Server::receive() {
	sockaddr_in revClientAddr{};

	//��ʼ���ͻ���socket
	recvClientSocket = INVALID_SOCKET;
	int _revSize = sizeof(sockaddr_in);
	recvClientSocket = accept(serviceSocket, (SOCKADDR*)&revClientAddr, &_revSize);

	//�жϽ����Ƿ�ɹ�
	if (INVALID_SOCKET == recvClientSocket) {
		std::cout << "����˽�������ʧ��!" << std::endl;
	}
	else {
		std::cout << "����˽�������ɹ�!" << std::endl;
	}
}

//��������
void Server::feedback() {
	//��������
	int reLen = recv(recvClientSocket, recvBuf, 1024, 0);

	//��������
	std::string receiveText = recvBuf;
	receiveText = StringUtils::getInstance().midstr(receiveText, "/?", "HTTP");
	StringUtils::getInstance().replace_all(receiveText, "%22", "\"");

	//��ӡ����
	std::cout << "��������������:\n" << receiveText << std::endl;

	//��������
	Json::Value root = JsonUtils::getInstance().readJsonFromString(receiveText);

	//��������
	BackData* backdata = nullptr;
	std::string content;

	if (!root.isMember("command")) {
		ReceiveDataFromSetter data = JsonUtils::getInstance().ReceiveDataFromSetterFromJsonValue(root);
		bool success = Singleton::getInstance().disposeSetterData(data);
		content = std::to_string(success);
		content = (content == "1" ? "true" : "false");
	}
	else {
		ReceiveDataFromPlayer data = JsonUtils::getInstance().ReceiveDataFromPlayerFromJsonValue(root);
		backdata = Singleton::getInstance().disposePlayerData(data);
		content = JsonUtils::getInstance().BackDataToString(backdata);
	}

	//���ɷ�������
	std::string sendText = "";
	sendText += "http/1.1 200 ok\r\n";
	sendText += "Access-Control-Allow-Origin:*\r\n";
	sendText += "Access-Control-Allow-Headers:*\r\n";
	sendText += "Content-Type: text/html;charset=ANSI\r\n";
	sendText += "Content-Length:";
	sendText += std::to_string(content.size());
	sendText += "\r\n\r\n";
	sendText += content;

	//��������
	int sLen = send(recvClientSocket, sendText.c_str(), sendText.size(), 0);

	//�жϷ����Ƿ�ɹ�
	if (SOCKET_ERROR == reLen) {
		std::cout << "����˷�������ʧ��" << std::endl;
	}
	else {
		std::cout << "��������������:\n" << content << std::endl;
	}
	std::cout << std::endl;
}

void Server::initWSADATA() {
	//��ʼ��
	WSADATA wsadata;
	//make word
	int err = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if (err != 0) {
		printf("WSAStartup failed with error: %d\n", err);
		return;
	}
}

void Server::initSocket(const char ip[10], int port) {
	//socket(Э����,socket���ݴ��䷽ʽ,ĳ��Э��)
	serviceSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == serviceSocket) {
		std::cout << "�׽��ִ�����ʧ��!" << std::endl;
	}
	else {
		std::cout << "�׽��ִ����ɹ�!" << std::endl;
	}

	//���׽��� ָ���󶨵�IP��ַ�Ͷ˿ں�
	//
	//һ���󶨵�ַ:��IP��ַ,�ж˿ں�,��Э����
	sockaddr_in socketAddr{};
	socketAddr.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &socketAddr.sin_addr.S_un.S_addr);
	socketAddr.sin_port = htons(port);

	//ǿ������ת��
	int bRes = bind(serviceSocket, (SOCKADDR*)&socketAddr, sizeof(SOCKADDR));

	if (SOCKET_ERROR == bRes) {
		std::cout << "��ʧ��!" << std::endl;
	}
	else {
		std::cout << "�󶨳ɹ�!" << std::endl;
	}
}

void Server::initListen() {
	//����������
	//
	//SOMAXCONN ������̴�ſͻ������������
	int lLen = listen(serviceSocket, SOMAXCONN);
	if (SOCKET_ERROR == lLen) {
		std::cout << "����ʧ��!" << std::endl;
	}
	else {
		std::cout << "�����ɹ�!" << std::endl << std::endl;
	}
}