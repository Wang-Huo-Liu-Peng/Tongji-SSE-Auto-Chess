#include <windows.h>
#include <process.h>
#include <iostream>
#include "CSocket.h"
#include"ThreadPool.h"
#include <string>
#include<passinfo.h>
using namespace std;


#pragma comment(lib,"ws2_32.lib") 

#define  BUF_LEN 1024
#define serverIp  "100.66.149.169"
//192.168.14.164
#define serverPort 1986


class Client {
public:
	static Client* getInstance() {
		static Client _client;
		return &_client;
	}

	//passinfo* passInfo;
	inline void write_account(char* str);
	inline void write_password(char* ac_pw);
	inline void write_event(char* _event);
	inline void write_hero_on_court(void* hero_on_court);
	inline void write_hero_fighting(void* hero_fighting);
	inline void* get_hero_fighting();
	inline void* get_hero_on_court();
	inline void set_get_state(int _get_state);
	inline int get_get_state();
	inline int connect_to_server();
	inline void recv_msg();
	inline void send_msg(passinfo* passInfo);
	inline void send_msg();
	inline void begin_send_and_listen();
	ThreadPool pool;
	CSocket csocket;
private:
	Client() {
		pool.init();
	}
};

void Client::write_account(char* ac_num) {
	
	strcpy(this->csocket._passInfo->account_number,ac_num);
}

void Client::write_password(char* ac_pw) {

	strcpy(this->csocket._passInfo->password, ac_pw);
}

void Client::write_hero_on_court(void* hero_on_court) {
	this->csocket._passInfo->hero_on_court = hero_on_court;
}

void* Client::get_hero_on_court() {
	return this->csocket._passInfo->hero_on_court;
}

void Client::write_hero_fighting(void* hero_fighting) {
	this->csocket._passInfo->hero_fighting = hero_fighting;
}

void* Client::get_hero_fighting() {
	return this->csocket._passInfo->hero_fighting ;
}

void Client::write_event(char* _event) {
	strcpy(this->csocket._passInfo->event, _event);
}

void Client::set_get_state(int _get_state) {
	this->csocket._passInfo->_already_get_hero = _get_state;
}

int Client::get_get_state() {
	return this->csocket._passInfo->_already_get_hero;
}

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

void Client::send_msg() {
	csocket.Send();
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