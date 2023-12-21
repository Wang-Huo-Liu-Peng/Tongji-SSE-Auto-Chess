#include "HelloWorldScene.h"
#include "Test_Scene_4.h"
#include "goldenshovel_hero_design.h" 
#include "BattleLayer.h"
#include "GameMap.h"
using namespace std;

USING_NS_CC;


bool BattleLayer::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    ///////////////////////////////
    Hero_1[1] = "Annie";
    hero1 = set_a_hero("Annie", Hero_1, Hero_on_court_1);
    hero1.sprite->setPosition(Vec2(1400, 600));
    this->addChild(hero1.sprite, 0);

    Hero_2[1] = "Evelynn";
    hero2 = set_a_hero("Evelynn", Hero_2, Hero_on_court_2);
    hero2.sprite->setPosition(Vec2(400, 700));
    this->addChild(hero2.sprite, 0);

    hero1.current_enemy = &hero2;
    hero2.current_enemy = &hero1;


    GameMap[2][3] = &hero1;
    if (GameMap[2][3] == nullptr)
    {
        CCLOG("GameMap[2][3] is nullptr");
    }
    else
    {
        CCLOG("GameMap[2][3] is not nullptr");
    }
    //new_hero.hero_attack();
    //new_hero_2.hero_attack();

    ///////////////////////////////

        //�˳���ǰ�����İ�ť
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        [&](Ref* sender) {
            /*hero1.decreasehp();
            if (hero1.gethp() <= 0) {
                this->removeChild(hero1.sprite, true);
            }
            Hero_fighting_1.push_back(hero1);
            hero2.hero_attack(Hero_fighting_1);
            if (hero1.gethp() <= 0) {
                this->removeChild(hero1.sprite, true);
            }*/
        });
    float x = origin.x + visibleSize.width - closeItem->getContentSize().width;
    float y = origin.y + closeItem->getContentSize().height+500;
    closeItem->setPosition(Vec2(x, y));

    auto exitMenu = Menu::create(closeItem, NULL);
    exitMenu->setPosition(Vec2::ZERO);
    this->addChild(exitMenu, 1);

    return true;
}

void BattleLayer::update(float dt)
{
    /*����Ϊ��Ϸ����Ҫ���ϸ��µĶ���*/

    //����Ƿ���Ӣ����������

    //��鲢�����ѻ��е��ӵ�
    //�ӵ����в���Ѫ

    //Ӣ�۷��䣿
    //Ӣ�����ߣ�
    //�ӵ����У�
}
