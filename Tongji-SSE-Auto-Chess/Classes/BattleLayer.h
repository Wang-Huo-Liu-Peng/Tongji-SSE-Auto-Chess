#pragma once
#ifndef __BATTLE_LAYER_H__
#define __BATTLE_LAYER_H__

#include "cocos2d.h"
#include "goldenshovel_hero_design.h"
#include "Bullet.h"

class BattleLayer : public cocos2d::Layer
{
public:
    MySprite* player_red;         //红方玩家
    MySprite* player_blue;        //蓝方玩家
    vector<Bullet> bullet;        //管理子弹

    void schedule(SEL_SCHEDULE selector); //定时器,逐帧刷新
    void schedule(SEL_SCHEDULE selector,float interval); //定时器，隔interval秒刷新
    virtual void update(float dt);        //游戏中需要时刻更新的东西
    void update_attack(float dt); //平A更新

    bool IsZeroHp(MyHero& hero);  //英雄是否死亡
    void check_death(vector<MyHero>& my_vec, vector<MyHero>& enemy_vec);//移出死亡英雄
    void BulletMove();            //子弹移动
    void BulletDelete();          //子弹回收，英雄扣血
    void HeroMove(vector<MyHero>&);//英雄移动

    virtual bool init();
    MyHero hero1;
    MyHero hero2;
    /*
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