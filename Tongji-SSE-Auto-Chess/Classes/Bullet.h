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
	MyHero* target_hero=nullptr;//目标英雄
	MySprite* target_sprite=nullptr;//目标小小英雄
	Sprite* sprite;     //内置精灵

	Vec2 target;        //目标坐标

	string picture_name;//图片名字
public:
	Bullet(MyHero*,Vec2,int,string);      //构造函数
	Bullet(MySprite*, Vec2, int, string); //构造函数2
	bool Hitted();      //判断是否到达目标位置
	bool HitHero();     //是否打中英雄（目标位置与英雄位置是否一致）
};