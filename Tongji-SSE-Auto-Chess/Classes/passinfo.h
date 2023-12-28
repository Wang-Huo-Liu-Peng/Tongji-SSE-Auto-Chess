#pragma once
#ifndef __PASSINFO__H__
#define __PASSINFO__H__

//#include "goldenshovel_hero_design.h"

#define max_command_length 32
#define max_ac_num  12
#define max_ac_pw 12


//char Register[max_command_length] = { "REGISTER" };
//char Login[max_command_length] = { "LOGIN" };
//
//
//char Exit[max_command_length] = { "Exit" };

#define Register "REGISTER"
#define Login "LOGIN"
#define Exit  "Exit"

using namespace std;

struct passinfo {
	char event[max_command_length] = { '0' };

	char account_number[max_ac_num] = { '0' };
	char password[max_ac_pw] = { '0' };

	//vector<MyHero> hero_on_court;
	//vector<MyHero> hero_fighting;

	int _result;
};



#endif 