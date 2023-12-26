#pragma once
#ifndef __LOAD__SERVER__H__
#define __LOAD__SERVER__H__
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>

#define ACCOUNT_FILE "account_info.txt"

class account;

class load_server {
public:

	static load_server& getInstance(){
		static load_server server;
		return server;
	}

	int set_account(account ac);
	int delete_account(account ac);
	int load_in(account ac);

private:

	load_server() { init(ACCOUNT_FILE); }
	~load_server() { end(); }

	int init(std::string filename);
	int end();
	std::vector<account> account_info;
	std::string filename;

};

class account {
	friend class load_server;
public:
	//account() {}
	account(std::string account, std::string password) :account_number(account),password(password) {}
	std::string account_number;
private:
	std::string password;
};


int load_server::init(std::string filename) {
	this->filename = filename;

	std::fstream fs;

	//加错误处理
	fs.open(filename, 'r');

	account ac("","");
	while (!fs.eof()) {
		fs >> ac.account_number;
		fs >> ac.password;
		account_info.push_back(ac);
	}

	fs.close();

	return 1;
}

int load_server::set_account(account ac) {
	for (auto person : account_info) {
		if (person.account_number == ac.account_number)
			return 0;
	}

	account_info.push_back(ac);

	return 1;
}

int load_server::delete_account(account ac) {
	int pos = -1;

	for (auto person : account_info) {
		pos++;
		if (person.account_number == ac.account_number)
		{
			std::vector<account>::iterator iter = account_info.begin() + pos;
			iter = account_info.erase(iter);
			return 1;
		}
	}

	return 0;
}


//登录，如果账号密码正确返回1，可以登陆，如果账号存在密码不正确返回0，账号都不存在返回-1
int load_server::load_in(account ac) {
	
	for (auto person : account_info) {
		if (person.account_number == ac.account_number)
		{
			if (person.password == ac.password)
				return 1;
			else
				return 0;
		}
	}
	
	return -1;
}


int load_server::end() {
	std::fstream fs;

	fs.open(filename, 'w');

	std::vector<account>::iterator iter = account_info.begin();

	while (iter != account_info.end()) {
		fs << iter->account_number << "  " << iter->password << std::endl;

		iter++;
	}

	fs.close();
	return 1;
}
#endif //__LOAD__SERVER__H__