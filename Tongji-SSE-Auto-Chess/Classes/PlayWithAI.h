#pragma once
#ifndef __PLAYWITH_AI_H__
#define __PLAYWITH_AI_H__

#include "cocos2d.h"

class PlayWithAI : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void PlayWithAI::AIPlayerBrain();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(PlayWithAI);
};

#endif // __PLAYWITH_AI_H__ 