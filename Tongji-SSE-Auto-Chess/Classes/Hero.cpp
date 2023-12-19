#include "goldenshovel_hero_design.h"
#include <map>
#include <string>

std::map<std::string, MyHero> Hero_list = {
	//参考网站 https://tftactics.gg/champions  https://lol.qq.com/tft/#/champion


	//一费
	//安妮 https://lol.qq.com/tft/#/championDetail/1
	{"Annie", MyHero(0, 1, 1, 40, 70, 7, 0, 4, 0.7, 500, -1, -1)},
	//库奇 https://lol.qq.com/tft/#/championDetail/42
	{"Corki", MyHero(0, 1, 1, 48, 80, 8, 0, 4, 0.7, 450, -1, -1)},
	//塔里克 https://lol.qq.com/tft/#/championDetail/44
	{"Taric", MyHero(0, 1, 1, 55, 60, 12, 0, 1, 0.55, 650, -1, -1)},
	//伊芙琳 https://lol.qq.com/tft/#/championDetail/12
	{"Evelynn", MyHero(0, 1, 1, 45, 60, 12, 0, 1, 0.7, 550, -1, -1)},


	//二费
	//凯尔
	{"Kayle", MyHero(0, 2, 1, 35, 100, 12, 0, 3, 0.75, 550, -1, -1)},
	//盖伦
	{"Garen", MyHero(0, 2, 1, 55, 90, 12, 0, 1, 0.7, 750, -1, -1)},
	//老鼠
	{"Twitch", MyHero(0, 2, 1, 50, 100, 12, 0, 5, 0.7, 550, -1, -1)},
	//塞纳
	{"Senna", MyHero(0, 2, 1, 40, 80, 12, 0, 6, 0.7, 600, -1, -1)},


	//三费
	//阿木木 https://tftactics.gg/champions/amumu
	{"Amumu", MyHero(0, 3, 1, 45, 100, 12, 0, 1, 0.65, 550, -1, -1)},
	//卢卡斯 https://tftactics.gg/champions/lux
	{"Lux", MyHero(0, 3, 1, 40, 100, 12, 0, 4, 0.7, 700, -1, -1)},
	//塞米尔 https://tftactics.gg/champions/samira
	{"Samira", MyHero(0, 3, 1, 60, 100, 12, 0, 4, 0.7, 600, -1, -1)},
	//尼克 https://tftactics.gg/champions/neeko
	{"Neeko", MyHero(0, 3, 1, 50, 100, 12, 0, 4, 0.6, 850, -1, -1)},


	//四费
	//卡尔萨斯 https://lol.qq.com/tft/#/championDetail/28
	{"Karthus",MyHero(0,4,1,50,125,7,0,4,0.65,700,-1,-1)},
	//佛耶戈 https://lol.qq.com/tft/#/championDetail/234
	{"Viego",MyHero(0,4,1,80,115,8,0,1,0.85,900,-1,-1)},
	//伊泽瑞尔 https://lol.qq.com/tft/#/championDetail/81
	{"Ezreal",MyHero(0,4,1,50,120,6,0,4,0.85,700,-1,-1)},
	//波比 https://lol.qq.com/tft/#/championDetail/50
	{"Poppy",MyHero(0,4,1,60,130,7,0,1,0.8,1000,-1,-1)},

	//五费
	//卢锡安 https://lol.qq.com/tft/#/championDetail/236
	{"Lucian",MyHero(0,5,1,75,200,6,0,4,0.7,750,-1,-1)},
	//凯隐 https://lol.qq.com/tft/#/championDetail/141
	{"Kayn",MyHero(0,5,1,75,180,5,0,1,0.95,1000,-1,-1)},
	//奇亚娜 https://lol.qq.com/tft/#/championDetail/246
	{"Qiyana",MyHero(0,5,1,70,190,5,0,1,0.9,950,-1,-1)},
	//吉格斯 https://lol.qq.com/tft/#/championDetail/115
	{"Ziggs",MyHero(0,5,1,65,220,5,0,4,0.8,800,-1,-1)}
	
	// ... 其他英雄
};
string one_fee[4] = { "Annie", "Corki", "Taric", "Evelynn" };
string two_fee[4] = { "Kayle", "Garen", "Twitch", "Senna" };
string three_fee[4] = { "Amumu", "Lux", "Samira", "Neeko" };
string four_fee[4] = { "Karthus", "Viego", "Ezreal", "Poppy" };
string four_five[4] = { "Lucian", "Kayn", "Qiyana", "Ziggs" };
