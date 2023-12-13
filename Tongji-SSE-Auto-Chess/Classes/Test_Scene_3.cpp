#include "HelloWorldScene.h"
#include "Test_Scene_3.h"

USING_NS_CC;

Scene* Test_Scene_3::createScene()
{
    return Test_Scene_3::create();
}

bool Test_Scene_3::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    ///////////////////////////////
    auto label1 = Label::createWithTTF("My Game", "fonts/Marker Felt.ttf", 36);
    label1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    this->addChild(label1);

    auto sprite1 = Sprite::create("mingrixiang.png");
    sprite1->setPosition(Vec2(100, 100));

    this->addChild(sprite1);
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

void Test_Scene_3::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

/***********************************************************************************************************************************************/
#include <iostream>
using namespace std;

//class Object {
//public:
//    Object();
//    virtual void move(int new_x, int new_y);
//protected:
//    int health;
//    int experience;
//    int armor;
//    int x;
//    int y;
//};
//
//class HeroBranch : public Object {
//public:
//    HeroBranch();
//    void attack();
//    void displayInfo();
//
//private:
//    int attack_damage;
//    int star_level;
//};
//
//class SpriteBranch : public Object {
//public:
//    SpriteBranch();
//    void displayInfo();
//private:
//    int star_level;
//};