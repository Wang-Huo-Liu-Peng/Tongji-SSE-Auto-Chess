#include "Game.h"
#include <goldenshovel_hero_design.h>

USING_NS_CC;

void PlayWith_AI()
{
    //场景名字暂用myScene，后续再考虑改名
    auto myScene = Scene::create();//创建新场景
    Director::getInstance()->pushScene(myScene);//将当前运行中的场景暂停并压入到场景栈中，并将传入的场景设置为当前运行场景

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //下面是游戏代码（场景为myScene）
    ////////////////
    //...
    ////////////////

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

void PlayWith_Player()
{
    auto myScene = Scene::create();//创建新场景
    Director::getInstance()->pushScene(myScene);//将当前运行中的场景暂停并压入到场景栈中，并将传入的场景设置为当前运行场景

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //下面是游戏代码
    ////////////////
    //...
    ////////////////

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

void slectMode()
{
    auto selcetMode_Scene = Scene::create();//创建新场景
    Director::getInstance()->pushScene(selcetMode_Scene);//将当前运行中的场景暂停并压入到场景栈中，并将传入的场景设置为当前运行场景

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //创建菜单(用标签创建)
    //创建一个TTFConfig对象来设置标签的共同属性
    TTFConfig labelConfig;
    labelConfig.fontFilePath = "fonts/Marker Felt.ttf";
    labelConfig.fontSize = 60;
    labelConfig.glyphs = GlyphCollection::DYNAMIC;
    labelConfig.outlineSize = 0;
    labelConfig.customGlyphs = nullptr;
    labelConfig.distanceFieldEnabled = false;

    //菜单所需要的标签
    auto ModeLabel_1 = Label::createWithTTF(labelConfig, "PlayWith_AI");
    auto ModeLabel_2 = Label::createWithTTF(labelConfig, "PlayWith_Player");

    // creating a Menu from a Vector of items
    Vector<MenuItem*> MenuItems;
    auto ModeItem_1 = MenuItemLabel::create(ModeLabel_1,
        [&](Ref* sender) {
            PlayWith_AI();
        });
    auto ModeItem_2 = MenuItemLabel::create(ModeLabel_2,
        [&](Ref* sender) {
            PlayWith_Player();
        });


    //设置各个标签的间距
    const int height = ModeItem_1->getContentSize().height;
    ModeItem_1->setPosition(Vec2(origin.x, origin.y));
    ModeItem_2->setPosition(Vec2(origin.x, origin.y - height));

    MenuItems.pushBack(ModeItem_1);
    MenuItems.pushBack(ModeItem_2);

    auto ModeMenu = Menu::createWithArray(MenuItems);
    ModeMenu->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2 - height * 2));
    selcetMode_Scene->addChild(ModeMenu, 1);//将整个菜单加入场景中

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
    selcetMode_Scene->addChild(exitMenu, 1);
}