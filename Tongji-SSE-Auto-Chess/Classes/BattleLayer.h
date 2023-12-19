#pragma once
#ifndef __BATTLE_LAYER_H__
#define __BATTLE_LAYER_H__

#include "cocos2d.h"

class BattleLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(BattleLayer);
};

#endif // __BATTLE_LAYER_H__  