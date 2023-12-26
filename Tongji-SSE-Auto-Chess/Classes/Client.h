#include <windows.h>
#include <process.h>
#include <iostream>
using namespace std;
#pragma comment(lib,"ws2_32.lib") 
#include "CSocket.h"
#include"ThreadPool.h"

#define  BUF_LEN 1024
#define serverIp  "192.168.14.164"
//192.168.14.164
#define serverPort 1986


class Client {
public:
	static Client* getInstance() {
		static Client _client;
		return &_client;
	}

	char msg[BUF_LEN];
	char* EXIT = "EXIT";
	char* CONNECTED = "CONNECTED";
	inline int connect_to_server();
	inline void recv_msg();
	inline int send_msg(char* msg);
	inline void begin_send_and_listen();
	ThreadPool pool;
	CSocket csocket;
private:
	Client() {
		pool.init();
	}

	~Client() {
		send_msg(EXIT);
	}
};

void Client::recv_msg()
{
	if (&(this->csocket) != NULL)
	{
		csocket.Receive(BUF_LEN);
		//_endthread();
	}
}

int Client::connect_to_server() {
	bool connect = csocket.Connect(serverIp, serverPort);
	csocket.SetBlocking(false);
	return connect;
}

int Client::send_msg(char* msg) {
	//char buf[BUF_LEN];
	/*if ((csocket.buffer_send) != NULL)
		delete[](csocket.buffer_send);
	csocket.buffer_send = new char[BUF_LEN];
	strcpy(csocket.buffer_send, msg);*/
	//cin >> csocket.buffer_send;
	//csocket.Send(csocket.buffer_send, strlen(csocket.buffer_send));
	int result = csocket.Send(msg, strlen(msg));
	return result;
}

void Client::begin_send_and_listen() {
	auto lambda = [=]() {
		if (&(this->csocket) != NULL)
		{
			this->csocket.Receive(BUF_LEN);
			//_endthread();
		}
	};
	pool.submit(lambda);
	/*while (1)
	{
		char buf[BUF_LEN];
		cin >> buf;

		csocket.Send(buf, strlen(buf));
		if (csocket.IsExit())
		{
			csocket.Close();
			cout << "exit success" << endl;
			break;
		}
	}
	getchar();*/
}

