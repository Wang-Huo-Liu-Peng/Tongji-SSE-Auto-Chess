#pragma once
#ifndef __BATTLE_LAYER_H__
#define __BATTLE_LAYER_H__

#include "cocos2d.h"
#include "goldenshovel_hero_design.h"

class BattleLayer : public cocos2d::Layer
{
public:
    void update(float dt);
    virtual bool init();
    MyHero hero1;
    MyHero hero2;
    /*
    vector<MyHero> hero_of_red;   //�췽Ӣ��
    vector<MyHero> hero_of_blue;  //����Ӣ��
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
    }*/
    //virtual void onEnter();
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(BattleLayer);

    //void battle();
};

#endif // __BATTLE_LAYER_H__  