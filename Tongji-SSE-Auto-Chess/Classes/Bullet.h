#pragma once
#include "HelloWorldScene.h"
#include "goldenshovel_hero_design.h"
#include <string>

USING_NS_CC;

class Bullet
{
	friend class BattleLayer;
private:
	int hurt;           //子弹伤害
	MyHero* target_hero;//目标英雄
	Sprite* sprite;     //内置精灵

	Vec2 position;      //当前坐标
	Vec2 target;        //目标坐标

	string picture_name;//图片名字
public:
	Bullet(MyHero*,Vec2,int,string);    //构造函数
	bool ifHit();       //判断是否击中
};