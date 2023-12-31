//Hero.cpp
#pragma once
#include "goldenshovel_hero_design.h"
#include <map>
#include <string>

std::map<std::string, MyHero> Hero_list = {
	//参考网站 https://tftactics.gg/champions  https://lol.qq.com/tft/#/champion


	//一费
	//安妮 https://lol.qq.com/tft/#/championDetail/1
	{"Annie", MyHero(0, 1, 1, 50, 70, 7, 0, 4, 0.7, 500, -1, -1)},
	//库奇 https://lol.qq.com/tft/#/championDetail/42
	{"Corki", MyHero(0, 1, 1, 48, 80, 8, 0, 4, 0.7, 450, -1, -1)},
	//塔里克 https://lol.qq.com/tft/#/championDetail/44
	{"Taric", MyHero(0, 1, 1, 55, 60, 12, 0, 1, 0.55, 650, -1, -1)},
	//伊芙琳 https://lol.qq.com/tft/#/championDetail/12
	{"Evely", MyHero(0, 1, 1, 45, 60, 12, 0, 1, 2, 550, -1, -1)},


	//二费
	//凯尔
	{"Kayle", MyHero(0, 2, 1, 35, 100, 12, 0, 3, 0.75, 550, -1, -1)},
	//盖伦
	{"Garen", MyHero(0, 2, 1, 55, 90, 12, 0, 1, 0.7, 750, -1, -1)},
	//老鼠
	{"Twitc", MyHero(0, 2, 1, 50, 100, 12, 0, 5, 0.7, 550, -1, -1)},
	//塞纳
	{"Senna", MyHero(0, 2, 1, 40, 80, 12, 0, 6, 0.7, 600, -1, -1)},



	//三费
	//阿木木 https://tftactics.gg/champions/amumu
	{"Amumu", MyHero(0, 3, 1, 45, 100, 12, 0, 1, 0.65, 550, -1, -1)},
	//卢卡斯 https://tftactics.gg/champions/lux
	{"Luxss", MyHero(0, 3, 1, 40, 100, 12, 0, 4, 0.7, 700, -1, -1)},
	//塞米尔 https://tftactics.gg/champions/samira
	{"Samir", MyHero(0, 3, 1, 60, 100, 12, 0, 4, 0.7, 600, -1, -1)},
	//尼克 https://tftactics.gg/champions/neeko
	{"Neeko", MyHero(0, 3, 1, 50, 100, 12, 0, 4, 0.6, 850, -1, -1)},


	//四费
	//卡尔萨斯 https://lol.qq.com/tft/#/championDetail/28
	{"Karth",MyHero(0,4,1,50,125,7,0,4,0.65,700,-1,-1)},
	//佛耶戈 https://lol.qq.com/tft/#/championDetail/234
	{"Viego",MyHero(0,4,1,80,115,8,0,1,0.85,900,-1,-1)},
	//伊泽瑞尔 https://lol.qq.com/tft/#/championDetail/81
	{"Ezrea",MyHero(0,4,1,50,120,6,0,4,0.85,700,-1,-1)},
	//波比 https://lol.qq.com/tft/#/championDetail/50
	{"Poppy",MyHero(0,4,1,60,130,7,0,1,0.8,1000,-1,-1)},

	//五费
	//卢锡安 https://lol.qq.com/tft/#/championDetail/236
	{"Lucia",MyHero(0,5,1,75,200,6,0,4,0.7,750,-1,-1)},
	//凯隐 https://lol.qq.com/tft/#/championDetail/141
	{"Kaynn",MyHero(0,5,1,75,180,5,0,1,0.95,1000,-1,-1)},
	//奇亚娜 https://lol.qq.com/tft/#/championDetail/246
	{"Qiyan",MyHero(0,5,1,70,190,5,0,1,0.9,950,-1,-1)},
	//吉格斯 https://lol.qq.com/tft/#/championDetail/115
	{"Ziggs",MyHero(0,5,1,65,220,5,0,4,0.8,800,-1,-1)},

	//六费
	//蔡徐坤
    {"Kunku",MyHero(0,6,1,100,300,10,10,10,10,500,-1,-1)},

	//丁真
	{"Dingz",MyHero(0,6,1,100,300,10,10,10,10,500,-1,-1)}
	
	// ... 其他英雄
};
string one_fee[4] = { "Annie", "Corki", "Taric", "Evely" };
string two_fee[4] = { "Kayle", "Garen", "Twitc", "Senna" };
string three_fee[4] = { "Amumu", "Luxss", "Samir", "Neeko" };
string four_fee[4] = { "Karth", "Viego", "Ezrea", "Poppy" };
string five_fee[4] = { "Lucia", "Kaynn", "Qiyan", "Ziggs" };


//vector<MySprite> Player = {
//	MySprite(1,100,5),//小小英雄开局等级为1,血量为100，金币为5
//	MySprite(1,100,5),
//	MySprite(1,100,5),
//	MySprite(1,100,5),
//	MySprite(1,100,5),
//	MySprite(1,100,5),
//	MySprite(1,100,5),
//	MySprite(1,100,5),
//};

vector<MySprite> Player = {
	MySprite(1,20,5),//小小英雄开局等级为1,血量为100，金币为5
	MySprite(1,20,5),
	MySprite(1,20,5),
	MySprite(1,20,5),
	MySprite(1,20,5),
	MySprite(1,20,5),
	MySprite(1,20,5),
	MySprite(1,20,5),
};

int Posibility_Of_Hero[MAX_LEVEL][5] = {
	{75,25,0,0,0},
	{45,40,15,0,0},
	{45,33,20,2,0},
	{25,40,30,5,0},
	{19,30,35,15,1},
	{16,20,35,25,4},
	{9,15,30,30,16}
};//每个等级对应英雄刷新可能性

int level_up_exp[6] = { 10,20,30,40,50,60 };//每个等级升级对应需要的经验


std::map<std::string, Equipment> Equipment_list = {
	//暂时添加一个作为范例
	{"Sword",Equipment(0,10)}
};

bool MyHero::enemyInDistance()
{
	float distance_x = sprite->getPositionX() - current_enemy->sprite->getPositionX();
	float distance_y = sprite->getPositionY() - current_enemy->sprite->getPositionY();
	float distance = distance_x * distance_x + distance_y * distance_y;
	if (distance <= attack_distance*plaid*plaid*2)
		return true;
	else
		return false;
}



