//goldenshovel_hero_design.h
#pragma once
#include<iostream>
#include"HelloWorldScene.h"
using namespace std;
#define plaid_width 256
#define plaid_height 200

#define attack_ace 1    //攻击性大招
#define treat_ace 2     //治疗型大招

#define map_width 9
#define map_height 6


class MyHero;

extern MyHero* GameMap[map_width][map_height];

/*====================基类====================*/
//注意：该基类为抽象基类，不可直接生成对象
class MyObject{
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
    inline void hero_attack(vector <MyHero>& Hero_fighting);                           //攻击函数
    inline void hero_ultimate(int ace_mode);                       // 大招函数
    int gethp() { return this->current_hp; };
    void decreasehp() { this->current_hp -= 100; };
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
    inline BOOL IsInMap(int x, int y);
    inline void Find_Way_To_attack(int X, int Y, int& HX, int& HY, int distance);
    // 攻击距离
};
inline BOOL IsInMap(int x, int y) {
    if (x < map_width && x >= 0 && y < map_height && y >= 0) {
        return 1;
    }
    return 0;
}
inline void Find_Way_To_attack(int X, int Y, int& HX, int& HY, int distance) {
    int deltaX = X - HX;
    int deltaY = Y - HY;

    // 计算对角线距离
    int distanceToTarget = std::max(std::abs(deltaX), std::abs(deltaY));

    if (distanceToTarget <= distance) {
        // 如果当前距离已经小于等于攻击距离，无需移动
        return;
    }

    // 计算插值比例
    float t = static_cast<float>(distance) / distanceToTarget;

    // 使用插值计算新的位置
    HX = static_cast<int>(HX + t * deltaX);
    HY = static_cast<int>(HY + t * deltaY);
}


//英雄索敌 MAP不知道在哪里定义，歇逼了先
inline void MyHero::seek_enemy(MyHero hero) {
    BOOL find = 0;
    int distance = 1;
    int i;
    int j;
    while (!find) {
        for (i = -1; i < 1; i++) {
            for (j = -1; j < 1; j++) {
                if (i == 0 && j == 0) continue;
                if (GameMap[hero.location_x + distance * i][hero.location_y + j * distance] != nullptr)//这段应该是判断这个像素上有英雄，没写完整
                {
                    hero.current_enemy = GameMap[hero.location_x + distance * i][hero.location_y + j * distance];
                    find = 1;
                    break;
                }
                if (find == 1)
                    break;
            }
        }
        distance++;
    }
    while (hero.current_enemy->current_hp != 0) {
        if (hero.current_enemy->location_x - hero.location_x > hero.attack_distance) {
            GameMap[location_x][location_y] = nullptr;
            Find_Way_To_attack(hero.current_enemy->location_x, hero.current_enemy->location_y, hero.location_x, hero.location_y, hero.attack_distance);
            GameMap[location_x][location_y] = &hero;
            //hero.sprite 设计moveby和moveto，还没写
        }
    }
}





inline void MyHero::hero_attack(vector <MyHero>& Hero_fighting) {
    //当目前英雄没死，并且敌人没死绝，当前current_enemy死了的时候，找下一个敌人
    if (current_enemy == NULL || this->current_hp != 0 || Hero_fighting.empty() != 1) {
        seek_enemy(*this);
        return;
    }
    int last_attack_time;
    while (current_enemy != NULL && this->current_hp!= 0) {
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
extern string one_fee[4];
extern string two_fee[4];
extern string three_fee[4];
extern string four_fee[4];
extern string five_fee[4];

extern vector <MyHero> Hero_on_court_1;
extern vector <MyHero> Hero_on_court_2;
extern vector <MyHero> Hero_select_1;
extern vector <MyHero> Hero_select_2;
extern vector <MyHero> Hero_fighting_1;
extern vector <MyHero> Hero_fighting_2;

//数组大小代表随机刷新的商店个数
extern string Hero_1[5];
extern string Hero_2[5];


void make_a_random_hero(int fee[], string Hero_in_shop[]);
MyHero set_a_hero(string hero_name, string Hero_in_shop[], vector<MyHero>& Hero);