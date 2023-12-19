#pragma once
#ifndef __STORE_LAYER_H__
#define __STORE_LAYER_H__

#include "cocos2d.h"
#include "HeroLayer.h"

//此图层用来放商店
class StoreLayer : public cocos2d::Layer
{   
public:
    virtual bool init();

    HeroLayer* herolayer;   //目标层，即从商店加入到的那个图层
    void addShop();

    // implement the "static create()" method manually
    CREATE_FUNC(StoreLayer);
};

#endif // __STORE_LAYER_H__  