#pragma once
#ifndef __PREPARE_LAYER_H__
#define __PREPARE_LAYER_H__

#include "cocos2d.h"
#include "goldenshovel_hero_design.h"

class PrepareLayer : public cocos2d::Layer
{
public:
    virtual bool init(int index);
    static PrepareLayer* create(int index);
    void update(float dt);
    int player;//玩家1

    void addHero(int, int, int);//英雄加入场上
    void addSprite(int);        //小小英雄加入场上
    cocos2d::Label* expLabel;
    cocos2d::Label* moneyLabel;
    cocos2d::Label* levelLabel;
    void store_display();//商店显示
    void card_remove(int index);//选中的卡片移除

    /*==============监听器回调函数=================*/
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    void onMouseDown(EventMouse* event);
    void onMouseUp(EventMouse* event);

private:
    int select_index; // 用于存储当前选中的备战席上的英雄的索引
    int type_index;
    Vec2 initial_position;// 用于存储英雄的起始坐标
};

#endif // __PREPARE_LAYER_H__  
