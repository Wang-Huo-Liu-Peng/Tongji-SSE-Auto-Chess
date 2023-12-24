#ifndef __CSOCKET_H__
#define __CSOCKET_H__
#include <windows.h>
#include "SocketEnum.h"
#include <iostream>
using namespace std; 

class CSocket
{
	public:
		CSocket(SocketEnum::SocketType _socketType=SocketEnum::Tcp);
	    ~CSocket();
		bool Connect(const char* ip,int port);		//链接 
		int Send(char* pBuf,int len);	//发送
		int Receive(int strLen);	//接收
		bool SetBlocking(bool isBlocking);//设置阻塞模式
		bool ShutDown(SocketEnum::ShutdownMode mode);
		const char* GetData() const;//获取接收数据
		SocketEnum::SocketError GetSocketError();
		void SetSocketHandle(SOCKET socket);
		void Close(); 
		bool IsExit();
	private: 

		void SetSocketError(SocketEnum::SocketError error);	//设置错误信息
		void SetSocketError(void);
		bool IsSocketValid(void);
		SOCKET csocket;
		bool isConnected;	//链接状态
		struct sockaddr_in serverAddress; 
		char* buffer;	//存接收数据
		int sendCount;	//发送数据长度
		int recvCount;	//接收数据长度
		bool isBlocking;	//是否是阻塞模式
		SocketEnum::SocketError socketError;
		SocketEnum::SocketType socketType; 
		WSADATA wsa; 
};

#endif