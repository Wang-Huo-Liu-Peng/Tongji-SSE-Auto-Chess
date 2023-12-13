#pragma once
#ifndef __PLAYWITH_PLAYER_H__
#define __PLAYWITH_PLAYER_H__

#include "cocos2d.h"

class PlayWithPlayer : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(PlayWithPlayer);
};

#endif // __PLAYWITH_PLAYER_H__ 