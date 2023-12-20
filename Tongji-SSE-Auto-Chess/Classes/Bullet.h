#pragma once
#include "HelloWorldScene.h"
#include "goldenshovel_hero_design.h"
#include <string>

USING_NS_CC;

class Bullet :public Sprite
{
private:
	int hurt;           //子弹伤害
	MyHero* target_hero;//目标英雄

	int location_x;     //当前坐标
	int location_y;

	int target_x;       //目标坐标
	int target_y;      

	string picture_name;//图片名字
public:
	Bullet();           //构造函数
	bool ifHit();       //判断是否击中
	void update();
};