#pragma once
#ifndef __PREPARE_SCENE_H__
#define __PREPARE_SCENE_H__

#include "cocos2d.h"
#include "goldenshovel_hero_design.h"

class PrepareScene : public cocos2d::Scene
{
public:
    static PrepareScene* create(int Player);
    virtual bool init(int Player);

    int player;       //Íæ¼ÒÏÂ±ê

    void addHero(vector<MyHero>&);
};

#endif // __PREPARE_SCENE_H__
