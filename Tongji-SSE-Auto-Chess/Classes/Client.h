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


	int connect_to_server();
	void recv();
	void begin_listen();
	ThreadPool pool;
	CSocket csocket;
private:
	Client() {
		pool.init();
	}
};

void Client::recv()
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


void Client::begin_listen() {
	auto lambda = [=]() {
		if (&(this->csocket) != NULL)
		{
			this->csocket.Receive(BUF_LEN);
			_endthread();
		}
	};
	pool.submit(lambda);
	while (1)
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
	getchar();
}

