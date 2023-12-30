#pragma once
//using namespace std;

#ifndef __PASSINFO__H__
#define __PASSINFO__H__
#include<vector>


#define Register "REGISTER"
#define SendHero "SENDHERO"

#define Login "LOGIN"
#define Exit  "Exit"

#define max_command_length 32
#define max_ac_num  12
#define max_ac_pw 12



struct passinfo {


	char event[max_command_length] = { '0' };

	char account_number[max_ac_num] = { '0' };
	char password[max_ac_pw] = { '0' };

	void* hero_on_court;
	void* hero_on_bench;

	int _result;
	int _already_get_hero;
};



#endif 