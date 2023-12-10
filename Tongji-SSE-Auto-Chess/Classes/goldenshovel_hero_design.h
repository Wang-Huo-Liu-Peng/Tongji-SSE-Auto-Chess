#pragma once
#include<iostream>
using namespace std;

#define max_hero_grade 3            //英雄最高星级 

class goldenshovel_hero {
public:
	goldenshovel_hero();

	string hero_name;                //英雄名
	string ace_name;                 //大招名称
	int belongs_to;					 //当前卡牌属于的小小英雄的编号
	
	//int star_rating;                 //英雄星级
	int gold_cost;                   //英雄花费 

	int needed_charge_round;         //大招所需蓄力轮数
	int current_charge_round;        //当前蓄力轮数

	int attack_speed;                //攻击速度 
	int attack_distance;             //攻击距离
	int attack_power;                //攻击力
	int ace_attck_power;             //大招攻击力

	int full_hp;                     //满血血量
	int current_hp;                  //当前血量
	//int magic_resistance;            //魔抗 
	//int physical_resistance;         //物抗 
	//int armor_value;                 //护甲值 

	//int search_enemy_num=1;          //索敌数量 
	
	//记录当前英雄在棋盘上的位置
	int location_x = -1;			 //横坐标
	int location_y = -1;             //纵坐标
private:
};
