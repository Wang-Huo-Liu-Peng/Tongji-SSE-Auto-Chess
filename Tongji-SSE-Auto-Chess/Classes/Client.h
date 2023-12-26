#include <windows.h>
#include <process.h>
#include <iostream>
using namespace std;
#include <string>
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


	inline int connect_to_server();
	inline void recv_msg();
	inline void send_msg(passinfo* passInfo);
	inline void begin_send_and_listen();
	ThreadPool pool;
	CSocket csocket;
private:
	Client() {
		pool.init();
	}
};

void Client::recv_msg()
{
	if (&(this->csocket) != NULL)
	{
		csocket.Receive(BUF_LEN);
		_endthread();
	}
}

int Client::connect_to_server() {
	bool connect = csocket.Connect(serverIp, serverPort);
	csocket.SetBlocking(false);
	return connect;
}

void Client::send_msg(passinfo* passInfo) {
	csocket.Send(passInfo, sizeof(passinfo));
	return;
}

void Client::begin_send_and_listen() {
	auto lambda = [&]() {
		if (&(this->csocket) != NULL)
		{
			this->csocket.Receive(sizeof(passinfo));
			//_endthread();
		}
	};
	pool.submit(lambda);

	if (csocket.IsExit())
	{
		csocket.Close();
		cout << "exit success" << endl;
	}
}