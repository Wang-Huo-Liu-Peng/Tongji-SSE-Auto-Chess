#pragma once
#include "goldenshovel_hero_design.h"
#include <string>

//商店类
class Store
{
public:
	MyHero HeroInShop[5];
	int button_x;         //按钮的x坐标
	int button_y;         //按钮的y坐标
	//MySprite smallhero; //属于哪个小小英雄
	int gold_x;           //持有金币的显示位置x
	int gold_y;           //持有金币的显示位置y
	void flushShop();     //刷新商店
	void setButton();     //放置刷新按钮
};

//英雄卡片类
class Card
{
public:
	MyHero Hero;
	string CardName;

};