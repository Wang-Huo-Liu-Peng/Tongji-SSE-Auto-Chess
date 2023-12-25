#pragma once
#ifndef __BATTLE_LAYER_H__
#define __BATTLE_LAYER_H__

#include "cocos2d.h"
#include "goldenshovel_hero_design.h"
#include "Bullet.h"

class BattleLayer : public cocos2d::Layer
{
public:
    virtual bool init(int Player1,int Player2);
    static BattleLayer* create(int Player1, int Player2);
    void BattleLayer::test();
    int player1;
    int player2;

    int select_index; // 用于存储当前选中的备战席上的英雄的索引

    vector<MyHero> blueHero;     //蓝方英雄（场上）
    vector<MyHero> redHero;      //红方英雄（场上）

    void getHero(vector<MyHero>& Hero, int);
    void addHero(vector<MyHero>& Hero_fighting);

    vector<Bullet> bullet;        //管理子弹

    void myupdate(float dt);      //游戏中需要时刻更新的东西
    void update_attack(float dt); //平A更新

    void BattleLayer::check_death(vector<MyHero>& Hero_fighting);//移出死亡英雄
    void checkBullet();           //子弹回收，英雄扣血
    void checkUltimate(vector<MyHero>& Hero_fighting);//蓝条满放大招
    void seekAndMove(vector<MyHero>&,vector<MyHero>&);//英雄索敌并移动

    void store_display();//商店显示
    void card_remove(int index);//选中的卡片移除

    /*cocos2d::RefPtr<cocos2d::Sprite> backgroundRef;
    cocos2d::RefPtr<cocos2d::Label> labelRef;*/

    void error_display(const std::string& displayText);
    void error_window_close();

    void attribute_display();// 血条与蓝条的显示

    /*==============监听器回调函数=================*/
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    //virtual void onEnter();
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    //CREATE_FUNC(BattleLayer);
};

#endif // __BATTLE_LAYER_H__  