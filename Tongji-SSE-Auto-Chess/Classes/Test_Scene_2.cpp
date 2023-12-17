//#include <goldenshovel_hero_design.h>
#include "HelloWorldScene.h"
#include "Test_Scene_2.h"

USING_NS_CC;




Scene* Test_Scene_2::createScene()
{
    return Test_Scene_2::create();
}

bool Test_Scene_2::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    ///////////////////////////////
    //...
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

void Test_Scene_2::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

#define attack_ace 1    //攻击性大招
#define treat_ace 2     //治疗型大招

//void MyHero::hero_ultimate(int ace_mode)                        // 大招函数
//{
//    MyHero* attacking_hero;  //假想敌,日后完善
//    
//    bool is_attacking = (attacking_hero != NULL);
//    if (!is_attacking) {
//        //seek_enemy();  //调用索敌函数
//    }
//    //this->Sprite->perform_ace();//释放大招的动画，如果有
//    if(ace_mode==attack_ace)
//    {
//        if (!(ace_attack_power < attacking_hero->current_hp)) {  //直接击杀
//            attacking_hero->current_hp = 0;
//            attacking_hero->sprite->minus_hp_animation();//掉血条动画
//            //attacking_hero->to_death();//死亡效果(如果有)
//            battle_secne->removeChild(attacking_hero); //在对战场景中移除对已死亡精灵的渲染
//        }
//        else {      //未直接击杀
//            attacking_hero->current_hp -= ace_attack_power;
//            attacking_hero->sprite->minus_hp_animation();//掉血条动画
//        }
//    }
//    else if (ace_mode == treat_ace) {        
//        if (ace_attack_power < (attacking_hero->full_hp - current_hp)) {     //回满血
//            attacking_hero->current_hp +=ace_attack_power;
//            attacking_hero->sprite->add_hp_animation();//回血条动画
//        }
//        else {      //不够回满血
//            attacking_hero->current_hp = full_hp;
//            attacking_hero->sprite->add_hp_animation();//回血条动画
//        }
//    }
//}