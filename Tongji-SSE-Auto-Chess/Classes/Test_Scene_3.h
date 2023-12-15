#pragma once
#ifndef __TEST_SCENE_3_H__
#define __TEST_SCENE_3_H__

#include "cocos2d.h"

class Test_Scene_3 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Test_Scene_3);
};

#endif // __TEST_SCENE_3_H__   