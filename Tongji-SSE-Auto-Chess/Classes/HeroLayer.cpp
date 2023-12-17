#include "HelloWorldScene.h"
#include "HeroLayer.h"

USING_NS_CC;

enum
{
    kTagSprite = 1,
};

bool HeroLayer::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    ///////////////////////////////
    auto listener = EventListenerTouchOneByOne::create();//创建鼠标事件监听器
    listener->onTouchBegan = CC_CALLBACK_2(HeroLayer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(HeroLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//事件分发器

    auto mySprite = Sprite::create("kunkun.png");//创建精灵
    mySprite->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    mySprite->setScale(0.5f);
    //this->addChild(mySprite, 1);//加入场景
    this->addChild(mySprite, 0, kTagSprite);
    ///////////////////////////////

    return true;
}

bool HeroLayer::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

void HeroLayer::onTouchEnded(Touch* touch, Event* event)
{
    auto location = touch->getLocation();//获取鼠标点击位置

    auto s = getChildByTag(kTagSprite);//获取节点（的一种方式）
    s->stopAllActions();
    s->runAction(MoveTo::create(1, Vec2(location.x, location.y)));//移动位置

    float o = location.x - s->getPosition().x;
    float a = location.y - s->getPosition().y;
    float at = (float)CC_RADIANS_TO_DEGREES(atanf(o / a));

    if (a < 0)
    {
        if (o < 0)
            at = 180 + fabs(at);
        else
            at = 180 - fabs(at);
    }

    s->runAction(RotateTo::create(1, at));//旋转动作
}