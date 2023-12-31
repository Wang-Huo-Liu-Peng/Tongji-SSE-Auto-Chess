#include "HelloWorldScene.h"
#include "MatchOverScene.h"
#include "BackGroundLayer.h"
//#include <goldenshovel_hero_design.h>
#include "goldenshovel_hero_design.h"

USING_NS_CC;

bool MatchOverScene::init(int index)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    ///////////////////////////////
    //胜利场景布置
    char num = index + '0';
    string picture = "Player-";
    picture += num;
    picture += ".png";

    Player[index].sprite = Sprite::create(picture);
    float x1 = visibleSize.width / 2;
    float y1 = visibleSize.height / 2;
    Player[index].sprite->setContentSize(Size(400,550));
    Player[index].sprite->setPosition(Vec2(origin.x + x1, origin.y + y1-200));

    auto Ruobao = Sprite::create("ruobao.png");
    Ruobao->setPosition(Vec2(170, Player[index].sprite->getContentSize().height + 200));

    auto overLabel = Label::createWithSystemFont("WINNER!", "Arial", 120);
    overLabel->setPosition(Vec2(x1 , 2*y1-overLabel->getContentSize().height));
    this->addChild(overLabel, 1);

    Player[index].sprite->addChild(Ruobao);
    this->addChild(Player[index].sprite);

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

void MatchOverScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

MatchOverScene* MatchOverScene::create(int index)
{
    MatchOverScene* ret = new (std::nothrow) MatchOverScene();
    if (ret && ret->init(index))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}
