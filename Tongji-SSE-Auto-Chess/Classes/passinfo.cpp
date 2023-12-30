#include"passinfo.h"
#include "goldenshovel_hero_design.h"

struct passinfo {
	/*char Register[max_command_length] = { "REGISTER" };
	char Login[max_command_length] = { "LOGIN" };


	char Exit[max_command_length] = { "Exit" };*/

	char event[max_command_length] = { '0' };

	char account_number[max_ac_num] = { '0' };
	char password[max_ac_pw] = { '0' };

	std::vector<int> a;
	std::vector<MyHero> hero_on_court;
	std::vector<MyHero> hero_fighting;

	int _result;
};