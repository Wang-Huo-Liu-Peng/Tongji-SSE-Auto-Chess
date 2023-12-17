#include "HelloWorldScene.h"
#include "Test_Scene_1.h"
//#include <goldenshovel_hero_design.h>

USING_NS_CC;

enum
{
    kTagSprite = 1,
};

Scene* Test_Scene_1::createScene()
{
    return Test_Scene_1::create();
}

bool Test_Scene_1::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    ///////////////////////////////

    auto listener = EventListenerTouchOneByOne::create();//创建鼠标事件监听器
    listener->onTouchBegan = CC_CALLBACK_2(Test_Scene_1::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(Test_Scene_1::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//事件分发器

    auto mySprite = Sprite::create("kunkun.png");//创建精灵
    mySprite->setPosition(Vec2(origin.x+ visibleSize.width/2,
        origin.y+ visibleSize.height/2));
    mySprite->setScale(0.5f);
    //this->addChild(mySprite, 1);//加入场景
    this->addChild(mySprite, 0, kTagSprite);

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

void Test_Scene_1::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

bool Test_Scene_1::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

void Test_Scene_1::onTouchEnded(Touch* touch, Event* event)
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

