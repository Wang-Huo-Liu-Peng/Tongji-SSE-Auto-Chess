#pragma once
#ifndef __PASSINFO__H__
#define __PASSINFO__H__

#include<string>



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


struct passinfo {
	char event[max_command_length] = { '0' };


	char account_number[max_ac_num] = { '0' };
	char password[max_ac_pw] = { '0' };

	int _result;
};



#endif 