#pragma once
#ifndef __SELECTMODE_SCENE_H__
#define __SELECTMODE_SCENE_H__

#include "cocos2d.h"

class SelectModeScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(SelectModeScene);
};

#endif // __SELECTMODE_SCENE_H__