#pragma once
#ifndef __BATTLE_LAYER_H__
#define __BATTLE_LAYER_H__

#include "cocos2d.h"
#include "goldenshovel_hero_design.h"
#include "Bullet.h"

class BattleLayer : public cocos2d::Layer
{
public:
    virtual bool init();

    vector<MyHero> blueHero;     //蓝方英雄（场上）
    vector<MyHero> redHero;      //红方英雄（场上）

    void allocate(int,int);
    void getHero(vector<MyHero>& Hero, int);
    void addHero(vector<MyHero>& Hero_fighting);

    vector<Bullet> bullet;        //管理子弹

    void myupdate(float dt);      //游戏中需要时刻更新的东西
    void update_attack(float dt); //平A更新

    void BattleLayer::check_death(vector<MyHero>& Hero_fighting);//移出死亡英雄
    void checkBullet();           //子弹回收，英雄扣血
    void checkUltimate(vector<MyHero>& Hero_fighting);//蓝条满放大招
    void seekAndMove(vector<MyHero>&,vector<MyHero>&);//英雄索敌并移动

    //virtual void onEnter();
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(BattleLayer);
};

#endif // __BATTLE_LAYER_H__  