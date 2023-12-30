#include "PrepareScene.h"
#include "BattleScene.h"
#include "BackGroundLayer.h"
#include "PrepareLayer.h"

USING_NS_CC;

bool PrepareScene::init(int Player)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    player = Player;    //当前玩家下标

    BackGroundLayer* Map = BackGroundLayer::create();
    this->addChild(Map);//背景图片

    PrepareLayer* Prepare = PrepareLayer::create(player);
    this->addChild(Prepare);//备战层

    this->scheduleOnce(schedule_selector(PrepareScene::goToBattle), 3.0f);

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

void PrepareScene::goToBattle(float dt)
{
    BattleScene* battle = BattleScene::create(1, 2);
    Director::getInstance()->replaceScene(battle);
}

PrepareScene* PrepareScene::create(int Player)
{
    PrepareScene* ret = new (std::nothrow) PrepareScene();
    if (ret && ret->init(Player))
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

