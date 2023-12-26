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

    int player1;//玩家1
    int player2;//玩家2

    int situation=Fighting;

    cocos2d::Label* expLabel;
    cocos2d::Label* moneyLabel;
    cocos2d::Label* levelLabel;


    void addHero(int,int,int);//英雄加入场上

    vector<Bullet> bullet;        //管理子弹

    void myupdate(float dt);      //游戏中需要时刻更新的东西
    void update_attack(float dt); //平A更新

    void check_death(vector<MyHero>& Hero_fighting);//移出死亡英雄
    void checkBullet();           //子弹回收，英雄扣血
    void checkUltimate(vector<MyHero>& Hero_fighting);//蓝条满放大招
    void seekAndMove(vector<MyHero>&,vector<MyHero>&);//英雄索敌并移动
    bool gameOver(int,int);              //本次对战结束

    void store_display();//商店显示
    void card_remove(int index);//选中的卡片移除
    void attribute_display();// 血条与蓝条的显示

    /*cocos2d::RefPtr<cocos2d::Sprite> backgroundRef;
    cocos2d::RefPtr<cocos2d::Label> labelRef;*/

    void error_display(const std::string& displayText);
    void error_window_close();

    /*==============监听器回调函数=================*/
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

private:
    int select_index; // 用于存储当前选中的备战席上的英雄的索引
    Vec2 initial_position;// 用于存储英雄的起始坐标

    //virtual void onEnter();
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    //CREATE_FUNC(BattleLayer);
};

#endif // __BATTLE_LAYER_H__  