#include "goldenshovel_hero_design.h"
#include "Bullet.h"
#include "cocos2d.h"
#include <string>

USING_NS_CC;

Bullet::Bullet(MyHero* targetHero,Vec2 loc,int h,string name)
{
	//参数依次为：目标英雄，子弹生成的位置，伤害，图片名字

	target_hero = targetHero;//传入的目标英雄
	target = target_hero->sprite->getPosition();//目标位置
	hurt = h;//子弹伤害与英雄伤害一样
	sprite = Sprite::create(name+".png");
	sprite->setPosition(loc);//loc为发射子弹的英雄的位置
}
Bullet::Bullet(MySprite* targetSprite, Vec2 loc, int h, string name)
{
	//参数依次为：目标英雄，子弹生成的位置，伤害，图片名字

	target_sprite = targetSprite;//传入的目标英雄
	target = target_sprite->sprite->getPosition();//目标位置
	hurt = h;//子弹伤害为1
	sprite = Sprite::create(name + ".png");
	sprite->setPosition(loc);//loc为发射子弹的英雄的位置
}

bool Bullet::Hitted()
{
	//判断是否击中
	return sprite->getPositionX() == target.x && sprite->getPositionY() == target.y;
}

bool Bullet::HitHero()
{
	//目标位置与英雄位置是否一致
	return target.x == target_hero->sprite->getPositionX() && target.y == target_hero->sprite->getPositionY();
}