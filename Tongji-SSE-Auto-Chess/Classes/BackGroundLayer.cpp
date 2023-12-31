#include "HelloWorldScene.h"
#include "BackGroundLayer.h"
#include "goldenshovel_hero_design.h"

#include "ui/CocosGUI.h"

using namespace ui;

USING_NS_CC;

bool BackGroundLayer::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    ///////////////////////////////
    //加入背景图片
    auto mySprite = Sprite::create("fight_map_1.png");//创建地图
    
    // 设置地图的锚点为左下角
    mySprite->setAnchorPoint(Vec2(0, 0));

    // 设置地图的大小为窗口大小
    mySprite->setContentSize(visibleSize);

    // 设置地图的位置为窗口左下角
    mySprite->setPosition(origin);

    //加入背景图片
    auto platform1 = Sprite::create("platform.png");//创建平台
    auto platform2 = Sprite::create("platform.png");//创建平台

    // 设置地图的大小为窗口大小

	platform1->setContentSize(Size(250,250));
	platform2->setContentSize(Size(250, 250));

    // 设置地图的位置为窗口左下角
    platform1->setPosition(platform1_px);
    platform2->setPosition(platform2_px);

    auto jiban = Sprite::create("jiban4.png");//创建地图
    jiban->setContentSize(Size(200,300));
    jiban->setPosition(Vec2(230, 900));

    // 加入场景
    this->addChild(mySprite, 0);
    this->addChild(platform1, 0);
    this->addChild(platform2, 0);
    this->addChild(jiban, 0);
    ///////////////////////////////

    return true;
}