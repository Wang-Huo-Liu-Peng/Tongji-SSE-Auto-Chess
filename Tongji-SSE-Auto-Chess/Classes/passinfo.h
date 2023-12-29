#pragma once
//using namespace std;

#ifndef __PASSINFO__H__
#define __PASSINFO__H__
#include<vector>


#define Register "REGISTER"
#define Login "LOGIN"
#define Exit  "Exit"

#define max_command_length 32
#define max_ac_num  12
#define max_ac_pw 12



struct passinfo {

	passinfo() :hero_on_court(), hero_fighting() {};

	char event[max_command_length] = { '0' };

	char account_number[max_ac_num] = { '0' };
	char password[max_ac_pw] = { '0' };

	std::vector<int> a;
	void* hero_on_court;
	void* hero_fighting;

	int _result;
};



#endif 