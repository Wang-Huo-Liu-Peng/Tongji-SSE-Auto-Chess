#pragma once
#include"hero_simple.h"
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
#define max_hero_num 10
#define max_name_length 15

struct passinfo {


	char event[max_command_length] = { '0' };

	char account_number[max_ac_num] = { '0' };
	char password[max_ac_pw] = { '0' };


	hero_simple  hero_court[max_hero_num] = {};
	hero_simple  hero_bench[max_hero_num] = {};

	int court;
	int bench;

	int _result=0;
	int _already_get_hero;
};



#endif 