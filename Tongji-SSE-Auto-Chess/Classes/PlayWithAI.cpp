#include "PlayWithAI.h"
#include "BackGroundLayer.h"
#include "BattleLayer.h"

USING_NS_CC;

Scene* PlayWithAI::createScene()
{
    return PlayWithAI::create();
}

bool PlayWithAI::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    ///////////////////////////////
    BackGroundLayer* Map = BackGroundLayer::create();
    this->addChild(Map);

    Player[1].Hero_in_shop[0] = "Annie";
    Player[1].Hero_in_shop[1] = "Corki";
    Player[1].Hero_in_shop[2] = "Taric";
    Player[1].Hero_in_shop[3] = "Twitch";
    Player[1].Hero_in_shop[4] = "Senna";

    Player[2].Hero_in_shop[0] = "Evelynn";
    Player[2].Hero_in_shop[1] = "Kayle";
    Player[2].Hero_in_shop[2] = "Corki";
    Player[2].Hero_in_shop[3] = "Annie";
    Player[2].Hero_in_shop[4] = "Garen";

    Player[1].set_a_hero("Annie");
    Player[1].set_a_hero("Taric");
    Player[1].set_a_hero("Senna");
    Player[2].set_a_hero("Evelynn");
    Player[2].set_a_hero("Garen");
    Player[2].set_a_hero("Kayle");

    //MyHero hero1 = set_a_hero("Annie", Hero_1, Hero_on_court_1);
    //hero1.sprite->setPosition(Vec2(2000, 1000));
    //Player[1].Hero_on_bench.push_back(hero1);
    //this->addChild(Player[1].Hero_on_bench[0].sprite, 2);

    BattleLayer* HeroBattle = BattleLayer::create();
    //HeroBattle->allocate(Player[1], Player[2]);
    this->addChild(HeroBattle);
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

void PlayWithAI::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}