#include "HelloWorldScene.h"
#include "Test_Scene_3.h"

USING_NS_CC;


Scene* Test_Scene_3::createScene()
{
    return Test_Scene_3::create();
}

bool Test_Scene_3::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    ///////////////////////////////
    /*
    创建事件监听器
    指定监听器的回调接口实现方法
    将设定好的监听器 注册到分发器内
    */
    auto mySprite = Sprite::create("kunkun.png");//创建精灵
    mySprite->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    mySprite->setScale(0.5f);
    this->addChild(mySprite, 0);

    auto player1 = LayerColor::create(Color4B::RED, 100, 100);
    player1->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 + 100));
    addChild(player1);
    
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->onTouchBegan = [](Touch* t, Event* e)->bool {
        log("成功检测到点击了");
       
        
        return true;
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, player1);



    ///////////////////////////////


    //退出当前场景的按钮
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        [&](Ref* sender) {
            Director::getInstance()->popScene();//释放当前场景，再从场景栈中弹出栈顶的场景，并将其设置为当前运行场景。
        });
    float x = origin.x + visibleSize.width - closeItem->getContentSize().width;
    float y = origin.y + closeItem->getContentSize().height;
    closeItem->setPosition(Vec2(x, y));

    auto exitMenu = Menu::create(closeItem, NULL);
    exitMenu->setPosition(Vec2::ZERO);
    this->addChild(exitMenu, 1);

    return true;
}

void Test_Scene_3::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

/**************下面是拖动的代码****************************/
/*
#ifndef __HERO_LAYER_H__
#define __HERO_LAYER_H__

#include "cocos2d.h"

class TestLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(TestLayer);

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif // __TEST_LAYER_H__

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "HelloWorldScene.h"
#include "TestLayer.h"

USING_NS_CC;

enum
{
    kTagSprite = 1,
};

bool TestLayer::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    ///////////////////////////////
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(TestLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(TestLayer::onTouchMoved, this);  // Added onTouchMoved
    listener->onTouchEnded = CC_CALLBACK_2(TestLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto mySprite = Sprite::create("grossini.png");
    mySprite->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    mySprite->setScale(0.5f);

    this->addChild(mySprite, 0, kTagSprite);
    ///////////////////////////////

    return true;
}

bool TestLayer::onTouchBegan(Touch* touch, Event* event)
{
    auto location = touch->getLocation();

    auto s = getChildByTag(kTagSprite);
    s->stopAllActions();

    // Optional: Set sprite's position immediately to the touch location when touched
    s->setPosition(location);

    return true;
}

void TestLayer::onTouchMoved(Touch* touch, Event* event)
{
    auto location = touch->getLocation();

    auto s = getChildByTag(kTagSprite);
    s->setPosition(location);
}

void TestLayer::onTouchEnded(Touch* touch, Event* event)
{
    auto location = touch->getLocation();

    auto s = getChildByTag(kTagSprite);
    s->stopAllActions();
    s->runAction(MoveTo::create(1, Vec2(location.x, location.y)));

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

    s->runAction(RotateTo::create(1, at));
}
*/