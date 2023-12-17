#pragma once
#include<iostream>
#include"HelloWorldScene.h"
using namespace std;
#define plaid_width 256
#define plaid_height 200
/*====================基类====================*/
//注意：该基类为抽象基类，不可直接生成对象
class MyObject {
public:
	MyObject() {};
	MyObject(int hp, int xp, int av, int x = -1, int y = -1) :                             // 构造函数
		current_hp(hp), current_xp(xp), armor_value(av), location_x(x), location_y(y) {};

	//virtual void my_move(int new_x, int new_y) = 0;                                        // 移动函数（纯虚函数）

	cocos2d::Sprite* sprite;                                                               // 指针

protected:
	int full_hp;                                  // 满血
	int current_hp;                               // 当前血量
	int current_xp;                               // 当前蓝条
	int armor_value;                              // 护甲值

    int location_x;			                      // 横坐标
    int location_y;                               // 纵坐标
};

/*====================精灵类====================*/
class MySprite:public MyObject  {
public:
	MySprite() {};
	MySprite(int level, int hp, int xp, int av, int x = -1, int y = -1) :        // 构造函数
		MyObject(hp, xp, av, x, y), star_level(level) {};
	//virtual void my_move(int new_x, int new_y);                                  // 移动函数

private:
	int star_level;     // 星级
};

/*====================英雄类====================*/
class MyHero : public MyObject {
public:
	MyHero() {};
	MyHero(int index, int cost, int level, int power, int a_power, int n_c_r, int c_c_r, int ad, int hp, int xp, int av, int x = -1, int y = -1) : // 构造函数
		MyObject(hp, xp, av, x, y),
		battle_index(index), gold_cost(cost), star_level(level), attack_power(power), ace_attack_power(a_power),
		needed_cooldown_round(n_c_r), current_cooldown_round(c_c_r), attack_distance(ad) {};
	//virtual void my_move(int new_x, int new_y);  // 移动函数
	void seek_enemy(MyHero hero, vector<MyHero>& Hero_on_court);                           // 索敌函数
	void hero_ultimate();                        // 大招函数

	MyHero* current_enemy;
private:
	bool battle_index;                 // 判断是否在场
	int gold_cost;                     // 英雄花费 
	int star_level;                    // 星级
	int attack_power;                  // 攻击力
	int ace_attack_power;              // 大招攻击力
	int needed_cooldown_round;         // 大招所需冷却轮数
	int current_cooldown_round;        // 当前冷却轮数
	int attack_distance;               // 攻击距离
};

//英雄索敌
void MyHero::seek_enemy(MyHero hero, vector <MyHero>& Hero_on_court) {
    BOOL find = 0;
    int distance = 1;
    int i;
    int j;
    MyHero enemy;
    while (!find) {
        for (i = -1; i < 1; i++) {
            for (j = -1; j < 1; j++) {
                if (i == 0 && j == 0) continue;
                if (hero.location_x + distance * i * plaid_width, hero.location_y + j * distance * plaid_height)//这段应该是判断这个像素上有英雄，没写完整
                {
                    hero.current_enemy = &enemy;//此处第二个hero应该改成上面找到的这个英雄
                    find = 1;
                    break;
                }
                if (find == 1)
                    break;
            }
        }
        distance++;
    }
    while (enemy.current_hp) {
        if (enemy.location_x - hero.location_x > hero.attack_distance * plaid_width) {
            hero.location_x = enemy.location_x + hero.attack_distance * plaid_width * (hero.location_x - enemy.location_x) / abs(hero.location_x - enemy.location_x);
            hero.location_y = enemy.location_y + hero.attack_distance * plaid_height * (hero.location_y - enemy.location_y) / abs(hero.location_y - enemy.location_y);
            //hero.sprite 设计moveby和moveto，还没写
        }
    }
}