#include "goldenshovel_hero_design.h"
#include "Bullet.h"
#include "cocos2d.h"
#include <string>

USING_NS_CC;

Bullet::Bullet(MyHero* targetHero,Vec2 loc,int h,string name)
{
	//参数依次为：目标英雄，子弹生成的位置，伤害，图片名字
	//position = loc;//loc为发射子弹的英雄的位置
	target_hero = targetHero;//传入的目标英雄
	hurt = h;//子弹伤害与英雄伤害一样
	sprite = Sprite::create(name+".png");
	sprite->setPosition(loc);
}

bool Bullet::Hitted()
{
	//判断是否击中
	return sprite->getPositionX() == target.x&&sprite->getPositionY()==target.y;
}