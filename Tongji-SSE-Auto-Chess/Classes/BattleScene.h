#pragma once
#ifndef __BATTLE_SCENE_H__
#define __BATTLE_SCENE_H__

#include "cocos2d.h"
#include "goldenshovel_hero_design.h"

class BattleScene : public cocos2d::Scene
{
public:
    static BattleScene* create(int Player1,int Player2);
    virtual bool init(int Player1,int Player2);

    BattleLayer* HeroBattle;//战斗层

    int player1;       //玩家下标
    int player2;       //玩家下标

    Label* roundLabel;//轮数显示标签

    void ifGameOver(float);//判断这轮战斗是否结束
    void CountDown(float dt);
};

#endif // __BATTLE_SCENE_H__
