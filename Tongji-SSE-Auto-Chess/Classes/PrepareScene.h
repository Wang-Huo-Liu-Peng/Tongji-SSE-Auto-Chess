#pragma once
#ifndef __PREPARE_SCENE_H__
#define __PREPARE_SCENE_H__

#include "cocos2d.h"

class PrepareScene : public cocos2d::Scene
{
public:
    static PrepareScene* create(int player);

    virtual bool init(int player);

    // implement the "static create()" method manually
};

#endif // __PREPARE_SCENE_H__
