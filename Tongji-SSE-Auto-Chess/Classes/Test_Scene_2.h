    #pragma once
#ifndef __TEST_SCENE_2_H__
#define __TEST_SCENE_2_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class Test_Scene_2 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    Label* bgmLabel;
    Label* sfxLabel;
    void bgmSliderCallback(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType eventType);
    void sfxSliderCallback(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType eventType);


    // implement the "static create()" method manually
    CREATE_FUNC(Test_Scene_2);
};

#endif // __TEST_SCENE_2_H__   