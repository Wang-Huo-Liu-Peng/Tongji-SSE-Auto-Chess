#pragma once
#include<iostream>
#include"HelloWorldScene.h"
using namespace std;
#define plaid_width 256
#define plaid_height 200

#define attack_ace 1    //攻击性大招
#define treat_ace 2     //治疗型大招
/*====================基类====================*/
//注意：该基类为抽象基类，不可直接生成对象
class MyObject {
public:
	MyObject() {};
	MyObject(int hp, int xp, int av, int x = -1, int y = -1) :                             // 构造函数
		current_hp(hp), /*current_xp(xp), armor_value(av),*/ location_x(x), location_y(y) {};

	//virtual void my_move(int new_x, int new_y) = 0;                                        // 移动函数（纯虚函数）

	cocos2d::Sprite* sprite;                                                               // 指针

protected:
	int full_hp;                                  // 满血
	int current_hp;                               // 当前血量

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
	MyHero(int on_court, int gold_cost, int star_level, int attack_power, int ace_attack_power,
        int needed_cooldown_round, int current_cooldown_round, int attack_distance,double attack_cd, 
        int hp, /*int xp, int av,*/ int x = -1, int y = -1) : // 构造函数
		MyObject(hp,/* xp, av,*/ x, y),
        on_court(on_court), gold_cost(gold_cost), star_level(star_level), attack_power(attack_power), ace_attack_power(ace_attack_power),
		needed_cooldown_round(needed_cooldown_round), current_cooldown_round(current_cooldown_round), attack_distance(attack_distance),
        attack_cd(attack_cd){};
	//virtual void my_move(int new_x, int new_y);  // 移动函数
    inline void seek_enemy(MyHero hero);                           // 索敌函数
    inline void hero_attack();                           //攻击函数
    inline void hero_ultimate(int ace_mode);                       // 大招函数

	MyHero* current_enemy;
private:
	bool on_court;                 // 判断是否在场
	int gold_cost;                     // 英雄花费 
	int star_level;                    // 星级
	int attack_power;                  // 攻击力
	int ace_attack_power;              // 大招攻击力
	int needed_cooldown_round;         // 大招所需冷却轮数
    int current_cooldown_round;        // 当前冷却轮数
    double attack_cd;                     //攻击cd
    int attack_distance;
    // 攻击距离
};

//英雄索敌
inline void MyHero::seek_enemy(MyHero hero) {
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

inline void MyHero::hero_attack() {
    if (current_enemy == NULL) {   //没有攻击目标或者攻击目标死亡后未重新寻找目标
        seek_enemy(*this);
    }
    int last_attack_time;
    while (current_enemy != NULL) {
        last_attack_time = time(NULL);              //记录攻击的时间点
        //攻击动画
        if (this->attack_power < current_enemy->current_hp) {  //不能直接击杀
            current_enemy->current_hp -= this->attack_power;
            //current_enemy->sprite->minus_hp(); //掉血动画
        }
        else {                                                 //直接击杀
            current_enemy->current_hp = 0;
            //current_enemy->sprite->minus_hp(); //掉血动画
            current_enemy = NULL;
        }
        if (current_enemy == NULL)            //击杀后将敌人置为NULL退出循环
            break;
        while (1) {                             //攻击cd
            int now_time = time(NULL);
            if (now_time - last_attack_time >= attack_cd)
                break;
        }
    }
}

inline void MyHero::hero_ultimate(int ace_mode)                        // 大招函数
{
    if (current_enemy == NULL) {
        seek_enemy(*this);  //调用索敌函数
    }
    //this->Sprite->perform_ace();//释放大招的动画，如果有
    if (ace_mode == attack_ace)
    {
        if (!(ace_attack_power < current_enemy->current_hp)) {  //直接击杀
            current_enemy->current_hp = 0;
            //attacking_hero->sprite->minus_hp_animation();//掉血条动画
        }
        else {      //未直接击杀
            current_enemy->current_hp -= ace_attack_power;
            //attacking_hero->sprite->minus_hp_animation();//掉血条动画
        }
    }
    else if (ace_mode == treat_ace) {
        if (ace_attack_power < (current_enemy->full_hp - current_hp)) {     //回满血
            current_enemy->current_hp += ace_attack_power;
            //attacking_hero->sprite->add_hp_animation();//回血条动画
        }
        else {      //不够回满血
            current_enemy->current_hp = full_hp;
            //attacking_hero->sprite->add_hp_animation();//回血条动画
        }
    }
}

extern std::map<std::string, MyHero> Hero_list;