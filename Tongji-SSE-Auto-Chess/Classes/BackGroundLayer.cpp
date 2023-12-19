#include "HelloWorldScene.h"
#include "BackGroundLayer.h"

USING_NS_CC;

bool BackGroundLayer::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    ///////////////////////////////
    //加入背景图片
    auto mySprite = Sprite::create("fight_map.png");//创建地图
    
    // 设置精灵图片的锚点为左下角
    mySprite->setAnchorPoint(Vec2(0, 0));

    // 设置精灵图片的大小为窗口大小
    mySprite->setContentSize(visibleSize);

    // 设置精灵图片的位置为窗口左下角
    mySprite->setPosition(origin);

    // 将精灵图片加入场景
    this->addChild(mySprite, 0);
    ///////////////////////////////

    return true;
}