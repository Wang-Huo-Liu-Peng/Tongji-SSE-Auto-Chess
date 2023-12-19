#include "HelloWorldScene.h"
#include "Test_Scene_1.h"
#include "HeroLayer.h"
#include "BackGroundLayer.h"
//#include <goldenshovel_hero_design.h>

USING_NS_CC;

Scene* Test_Scene_1::createScene()
{
    return Test_Scene_1::create();
}

bool Test_Scene_1::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    ///////////////////////////////
    Kun = HeroLayer::create();
    bg = BackGroundLayer::create();
    store = StoreLayer::create();

    store->herolayer = Kun;
    this->addChild(Kun,1);
    this->addChild(bg);
    this->addChild(store,1);

    store->addShop();
    //addShop();

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

/*
void Test_Scene_1::addShop()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //制作英雄卡片
    auto HeroCard = MenuItemImage::create(
        "Annie_Card.png",
        "Annie_Card.png",
        [&](Ref* sender) {
            auto Annie = Sprite::create("Annie.png");
            Annie->setPosition(500,500);
            this->addChild(Annie, 1);
        });
    float x = origin.x + visibleSize.width / 2 - HeroCard->getContentSize().width;
    float y = origin.y + HeroCard->getContentSize().height;
    HeroCard->setPosition(Vec2(x, y));

    auto addHero = Menu::create(HeroCard, NULL);
    addHero->setPosition(Vec2::ZERO);
    Kun->addChild(addHero, 1);
}*/
