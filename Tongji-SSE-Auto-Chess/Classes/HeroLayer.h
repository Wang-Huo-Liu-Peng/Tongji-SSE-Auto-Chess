#pragma once
#ifndef __HERO_LAYER_H__
#define __HERO_LAYER_H__

#include "cocos2d.h"

//此图层拿来测试用的，后期删除
class HeroLayer : public cocos2d::Layer
{
public:
    virtual bool init();

    //void addSprite(Sprite* sprite) { addChild(sprite, 1); };
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HeroLayer);

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif // __HERO_LAYER_H__  