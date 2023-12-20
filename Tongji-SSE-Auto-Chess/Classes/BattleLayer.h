#pragma once
#ifndef __BATTLE_LAYER_H__
#define __BATTLE_LAYER_H__

#include "cocos2d.h"
#include "goldenshovel_hero_design.h"

class BattleLayer : public cocos2d::Layer
{
public:
    Vector<MyHero> hero_of_red;   //ºì·½Ó¢ÐÛ
    Vector<MyHero> hero_of_blue;  //À¶·½Ó¢ÐÛ
    void update(float dt);
    MyHero hero1;
    MyHero hero2;
    virtual bool init();
    void attack();
    void Delete_death(vector<MyHero>& Hero_fighting) {
        auto it = Hero_fighting.begin();
        while (it != Hero_fighting.end()) {
            if (it->gethp() == 0) {
                this->removeChild(it->sprite, true);
                it = Hero_fighting.erase(it);
            }
            else {
                ++it;
            }
        }
    }
    //virtual void onEnter();
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(BattleLayer);

    //void battle();
};

#endif // __BATTLE_LAYER_H__  