#include "PrepareScene.h"
#include "BackGroundLayer.h"

bool PrepareScene::init(int player)
{

    return true;
}

PrepareScene* PrepareScene::create(int player)
{
    PrepareScene* ret = new (std::nothrow) PrepareScene();
    if (ret && ret->init(player))
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