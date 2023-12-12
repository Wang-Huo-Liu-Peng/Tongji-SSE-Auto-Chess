#include "Test.h"

void Test_Scene_1()
{
    auto myScene = Scene::create();//创建新场景
    Director::getInstance()->pushScene(myScene);//将当前运行中的场景暂停并压入到场景栈中，并将传入的场景设置为当前运行场景

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //以下为你的测试代码（场景为myScene）
    ///////////////////////////////

    auto mySprite = Sprite::create("kunkun.png");//创建精灵
    mySprite->setPosition(Vec2(origin.x+ visibleSize.width/2,
        origin.y+ visibleSize.height/2));
    mySprite->setScale(0.5f);
    myScene->addChild(mySprite, 1);//加入场景
    

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
    myScene->addChild(exitMenu, 1);
}