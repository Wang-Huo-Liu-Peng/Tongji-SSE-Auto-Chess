#include "goldenshovel_hero_design.h"
#include "Bullet.h"
#include "cocos2d.h"
#include <string>

USING_NS_CC;

Bullet::Bullet(MyHero* targetHero,Vec2 loc,int h,string name)
{
	//攻击英雄的子弹
	//参数依次为：目标英雄，子弹生成的位置，伤害，图片名字

	target_hero = targetHero;//传入的目标英雄
	target = target_hero->sprite->getPosition();//目标位置
	hurt = h;//子弹伤害与英雄伤害一样
	sprite = Sprite::create(name+".png");
	sprite->setPosition(loc);//loc为发射子弹的英雄的位置
}
Bullet::Bullet(MySprite* targetSprite, Vec2 loc, int h, string name)
{
	//攻击小小英雄的子弹
	//参数依次为：目标英雄，子弹生成的位置，伤害，图片名字

	target_sprite = targetSprite;//传入的目标英雄
	target = target_sprite->sprite->getPosition();//目标位置
	hurt = h;//子弹伤害为1
	sprite = Sprite::create(name + ".png");
	sprite->setPosition(loc);//loc为发射子弹的英雄的位置
}

Bullet::Bullet(MySprite* targetSprite,MyHero* targetHero, Vec2 loc, int h, string name,int AOE)
{
	//英雄释放大招所射出的范围伤害子弹
	//参数依次为：目标英雄，子弹生成的位置，伤害，图片名字

	target_sprite = targetSprite;//传入的目标英雄
	target_hero = targetHero;//传入的目标英雄
	target = targetHero->sprite->getPosition();//目标位置
	hurt = h;//子弹伤害
	sprite = Sprite::create(name + ".png");
	Size newSize(127, 150);  
	sprite->setContentSize(newSize);
	sprite->setPosition(loc);//loc为发射子弹的英雄的位置
	isAOE = AOE;//标记为范围伤害
}

bool Bullet::Hitted()
{
	//判断是否击中
	return sprite->getPositionX() == target.x && sprite->getPositionY() == target.y;
}

bool Bullet::HitHero()
{
	//击中英雄判定
	float distance_x = target_hero->sprite->getPositionX() - target.x;
	float distance_y = target_hero->sprite->getPositionY() - target.y;
	float distance = distance_x * distance_x + distance_y * distance_y;
	return distance <= plaid * plaid / 4;
}

void Bullet::Boom(vector<MyHero>& enemy)
{
	//范围伤害判定
	auto it = enemy.begin();
	while (it != enemy.end()) {
		float distance_x = it->sprite->getPositionX() - target.x;
		float distance_y = it->sprite->getPositionY() - target.y;
		float distance = distance_x * distance_x + distance_y * distance_y;
		if (distance <= plaid * plaid * 4) {
			it->current_hp -= hurt;
		}
		++it;
	}
}