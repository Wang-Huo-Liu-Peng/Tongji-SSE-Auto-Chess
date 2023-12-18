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
    /*
    创建事件监听器
    指定监听器的回调接口实现方法
    将设定好的监听器 注册到分发器内
    */
    auto mySprite = Sprite::create("kunkun.png");//创建精灵
    mySprite->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    mySprite->setScale(0.5f);
    this->addChild(mySprite, 0);

    auto player1 = LayerColor::create(Color4B::RED, 100, 100);
    player1->setPosition(Vec2(visibleSize.width / 2 - 100, visibleSize.height / 2 + 100));
    addChild(player1);
    
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->onTouchBegan = [](Touch* t, Event* e)->bool {
        log("成功检测到点击了");
       
        
        return true;
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener1, player1);



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