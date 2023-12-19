#pragma once
#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

#include "cocos2d.h"

//此图层用于存放背景图片
class BackGroundLayer : public cocos2d::Layer
{
public:
    virtual bool init();

    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(BackGroundLayer);
};

#endif // __BACKGROUND_LAYER_H__  