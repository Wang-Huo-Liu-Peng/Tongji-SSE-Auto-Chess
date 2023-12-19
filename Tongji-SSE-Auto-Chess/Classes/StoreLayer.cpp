#include "HelloWorldScene.h"
#include "goldenshovel_hero_design.h" 
#include "StoreLayer.h"
using namespace std;

USING_NS_CC;

bool StoreLayer::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    ///////////////////////////////

    ///////////////////////////////

    return true;
}

void StoreLayer::addShop()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //ÖÆ×÷Ó¢ÐÛ¿¨Æ¬
    auto HeroCard = MenuItemImage::create(
        "Annie_Card.png",
        "Annie_Card.png",
        [&](Ref* sender) {
            auto Annie = Sprite::create("Annie.png");
            Annie->setPosition(500, 500);
            this->addChild(Annie, 1);
        });
    float x = origin.x + visibleSize.width / 2 - HeroCard->getContentSize().width;
    float y = origin.y + HeroCard->getContentSize().height;
    HeroCard->setPosition(Vec2(x, y));

    auto addHero = Menu::create(HeroCard, NULL);
    addHero->setPosition(Vec2::ZERO);
    herolayer->addChild(addHero, 1);
}