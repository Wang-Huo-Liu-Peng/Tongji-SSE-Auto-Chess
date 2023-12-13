#pragma once
#include<iostream>
using namespace std;

/*====================基类====================*/
//注意：该基类为抽象基类，不可直接生成对象
class MyObject{
public:
	MyObject(int hp, int xp, int av, int x = -1, int y = -1) :                             // 构造函数
		current_hp(hp), current_xp(xp), armor_value(av), location_x(x), location_y(y) {};

	virtual void my_move(int new_x, int new_y) = 0;                                        // 移动函数（纯虚函数）


protected:
	int full_hp;                                  // 满血
	int current_hp;                               // 当前血量
	int current_xp;                               // 当前蓝条
	int armor_value;                              // 护甲值

	int location_x;			                      // 横坐标
	int location_y;                               // 纵坐标

	Sprite* sprite;
};

/*====================精灵类====================*/
class MySprite:public MyObject  {
public:
	MySprite(int level, int hp, int xp, int av, int x = -1, int y = -1) :        // 构造函数
		MyObject(hp, xp, av, x, y), star_level(level) {};
	virtual void my_move(int new_x, int new_y);                                  // 移动函数

private:
	int star_level;     // 星级
};

/*====================英雄类====================*/
class MyHero : public MyObject {
public:
	MyHero(int index, int cost, int level, int power, int a_power, int n_c_r, int c_c_r, int hp, int xp, int av, int x = -1, int y = -1) : // 构造函数
		MyObject(hp, xp, av, x, y),
		battle_index(index), gold_cost(cost), star_level(level), attack_power(power), ace_attack_power(a_power),
		needed_cooldown_round(n_c_r), current_cooldown_round(c_c_r) {};
	virtual void my_move(int new_x, int new_y);  // 移动函数
    void seek_enemy();                           // 索敌函数
	void hero_ultimate();                        // 大招函数

private:
	bool battle_index;                 // 判断是否在场
	int gold_cost;                     // 英雄花费 
    int star_level;                    // 星级
	int attack_power;                  // 攻击力
	int ace_attack_power;              // 大招攻击力
	int needed_cooldown_round;         // 大招所需冷却轮数
    int current_cooldown_round;        // 当前冷却轮数
};