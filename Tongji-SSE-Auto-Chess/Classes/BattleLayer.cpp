#include "HelloWorldScene.h"
#include "Test_Scene_4.h"
#include "goldenshovel_hero_design.h" 
#include "BattleLayer.h"
using namespace std;

USING_NS_CC;

bool BattleLayer::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    ///////////////////////////////
    ///////////////////////////////

    return true;
}

void BattleLayer::onEnter()
{
    Layer::onEnter();
    Hero_1[1] = "Annie";
    MyHero new_hero;
    new_hero = set_a_hero("Annie", Hero_1, Hero_on_court_1);
    new_hero.sprite->setPosition(Vec2(1400, 600));
    this->addChild(new_hero.sprite, 0);

    Hero_2[1] = "Evelynn";
    MyHero new_hero_2;
    new_hero_2 = set_a_hero("Evelynn", Hero_2, Hero_on_court_2);
    new_hero_2.sprite->setPosition(Vec2(400, 700));
    this->addChild(new_hero_2.sprite, 0);

    new_hero.current_enemy = &new_hero_2;
    new_hero_2.current_enemy = &new_hero;

    new_hero.hero_attack();
    new_hero_2.hero_attack();

    if (new_hero.gethp() == 0) {
        this->removeChild(new_hero.sprite, true);
    }
    if (new_hero_2.gethp() == 0) {
        this->removeChild(new_hero_2.sprite, true);
    }
}