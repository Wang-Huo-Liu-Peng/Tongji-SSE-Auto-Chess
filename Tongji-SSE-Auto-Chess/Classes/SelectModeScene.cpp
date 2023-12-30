#include "SimpleAudioEngine.h"
#include "SelectModeScene.h"
#include "PlayWithAI.h"
#include "PlayWithPlayer.h"
#include "PrepareScene.h"
#include "BattleScene.h"
#include "goldenshovel_hero_design.h"

USING_NS_CC;

Scene* SelectModeScene::createScene()
{
    return SelectModeScene::create();
}

bool SelectModeScene::init()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
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
            Player[1].Operator = HUMAN;
            Player[2].Operator = AI;
            Player[1].refresh_shop_free();
            Player[2].refresh_shop_free();
            PrepareScene* prepare1 = PrepareScene::create(1);
            Director::getInstance()->replaceScene(prepare1);
        });
    auto ModeItem_2 = MenuItemLabel::create(ModeLabel_2,
        [&](Ref* sender) {
            Player[1].Operator = HUMAN;
            Player[2].Operator = HUMAN;
            Player[1].refresh_shop_free();
            PrepareScene* prepare1 = PrepareScene::create(1);
            Director::getInstance()->replaceScene(prepare1);
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
    this->addChild(ModeMenu, 1);//将整个菜单加入场景中

    //退出当前场景的按钮
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        [&](Ref* sender) {
            menuCloseCallback(this);
            //Director::getInstance()->popScene();//释放当前场景，再从场景栈中弹出栈顶的场景，并将其设置为当前运行场景。
            //CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        });
    float x = origin.x + visibleSize.width - closeItem->getContentSize().width;
    float y = origin.y + closeItem->getContentSize().height;
    closeItem->setPosition(Vec2(x, y));

    auto exitMenu = Menu::create(closeItem, NULL);
    exitMenu->setPosition(Vec2::ZERO);
    this->addChild(exitMenu, 1);

    return true;
}

void SelectModeScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}