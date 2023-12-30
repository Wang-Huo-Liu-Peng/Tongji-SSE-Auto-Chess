#pragma once
#ifndef __MATCH_OVER_SCENE_H__
#define __MATCH_OVER_SCENE_H__

#include "cocos2d.h"
#include "BackGroundLayer.h"

class MatchOverScene : public cocos2d::Scene
{
public:
    static MatchOverScene* create(int index);

    virtual bool init(int);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
};

#endif // __MATCH_OVER_SCENE_H__    
