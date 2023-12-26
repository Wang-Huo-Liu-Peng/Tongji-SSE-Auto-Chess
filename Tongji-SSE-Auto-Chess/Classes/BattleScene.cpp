#include "BattleScene.h"
#include "BackGroundLayer.h"
#include "BattleLayer.h"

bool BattleScene::init(int Player1,int Player2)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    player1 = Player1;    //当前玩家下标
    player2 = Player2;    //当前玩家下标

    //Player[player1].copy();
    //Player[player2].copy();

    BackGroundLayer* Map = BackGroundLayer::create();
    this->addChild(Map);//背景图片层

    BattleLayer* HeroBattle = BattleLayer::create(1, 2);
    this->addChild(HeroBattle);//战斗层



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

BattleScene* BattleScene::create(int Player1,int Player2)
{
    BattleScene* ret = new (std::nothrow) BattleScene();
    if (ret && ret->init(Player1,Player2))
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