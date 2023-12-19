#pragma once
#ifndef __BATTLE_LAYER_H__
#define __BATTLE_LAYER_H__

#include "cocos2d.h"
#include "goldenshovel_hero_design.h"

//此图层用于存放战斗场景
class BattleLayer : public cocos2d::Layer
{
public:
    MyHero hero1;
    MyHero hero2;
    virtual bool init();

    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(BattleLayer);
};

#endif // __BATTLE_LAYER_H__  