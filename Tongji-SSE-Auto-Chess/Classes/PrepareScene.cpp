#include "PrepareScene.h"
#include "BackGroundLayer.h"

bool PrepareScene::init(int Player)
{
    BackGroundLayer* Map = BackGroundLayer::create();
    this->addChild(Map);//背景图片

    player = Player;    //当前玩家下标

    return true;
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

void PrepareScene::addHero(vector<MyHero>& Hero)
{
    for (int i = 0; i < Hero.size(); i++) {
        this->addChild(Hero[i].sprite, 0);
    }
}