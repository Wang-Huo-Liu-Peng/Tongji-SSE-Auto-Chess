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

    /**/
    ///////////////////////////////
    hero1 = set_a_hero("Annie", Hero_1, Hero_on_court_1);
    hero1.sprite->setPosition(Vec2(1400, 600));
    //this->addChild(hero1.sprite, 0);

    hero2 = set_a_hero("Evelynn", Hero_2, Hero_on_court_2);
    hero2.sprite->setPosition(Vec2(400, 700));
    //this->addChild(hero2.sprite, 0);

    blueHero.push_back(hero1);
    redHero.push_back(hero2);

    redHero[0].current_enemy = &blueHero[0];
    blueHero[0].current_enemy = &redHero[0];

    //this->addChild(hero1.sprite, 0);
    //this->addChild(hero2.sprite, 0);

    this->addChild(blueHero[0].sprite, 0);
    this->addChild(redHero[0].sprite, 0);
    
    //player_blue->Hero_fighting[1].current_enemy = &hero2;
    //player_red->Hero_fighting[1].current_enemy = &hero1;

    this->schedule(schedule_selector(BattleLayer::myupdate));
    this->schedule(schedule_selector(BattleLayer::update_attack), 1.0f);

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

    return true;
}

void BattleLayer::myupdate(float dt)
{
    /*以下为游戏中需要不断更新的东西*/

    checkBullet();                          //检查子弹，并扣血
    check_death(blueHero);//检查英雄死亡并退场
    check_death(redHero); //检查英雄死亡并退场

    //英雄自走，函数已写，后续加入
    //蓝条满放大招，后续加入
    //有一方场上英雄死完，停止战斗，然后根据胜者剩余英雄数对败者进行扣血
}

void BattleLayer::update_attack(float dt)
{
    auto it = blueHero.begin();
    while (it!= blueHero.end()) {
        if (it->current_enemy != NULL) {
            Bullet b(it->current_enemy, it->sprite->getPosition(), it->attack_power, "basketball");//这里先都用篮球，后续写函数根据英雄名字寻找对应的子弹名字
            bullet.push_back(b);
            this->addChild(b.sprite, 2);//子弹加入场景

            //蓄力论述增加，蓝条增加动画

            auto moveTo = MoveTo::create(it->attack_cd, it->current_enemy->sprite->getPosition());//子弹飞行动作
            b.sprite->runAction(moveTo);
        }
        it++;
    }
    auto it2 = redHero.begin();
    while (it2 != redHero.end()) {
        if (it2->current_enemy != NULL) {
            Bullet b(it2->current_enemy, it2->sprite->getPosition(), it2->attack_power, "basketball");//这里先都用篮球，后续写函数根据英雄名字寻找对应的子弹名字
            bullet.push_back(b);
            this->addChild(b.sprite, 2);

            //蓄力论述增加，蓝条增加动画

            auto moveTo = MoveTo::create(it2->attack_cd, it2->current_enemy->sprite->getPosition());
            b.sprite->runAction(moveTo);
        }
        it2++;
    }
    /*
    if (hero1.current_enemy != NULL) {
        Bullet b(hero1.current_enemy, hero1.sprite->getPosition(), hero1.attack_power, "basketball");
        bullet.push_back(b);
        this->addChild(b.sprite, 2);
        auto moveTo = MoveTo::create(2, hero1.current_enemy->sprite->getPosition());
        b.sprite->runAction(moveTo);
        //b.target_hero->current_hp -= b.hurt;
    }*/
}

void BattleLayer::check_death(vector<MyHero>& Hero_fighting)
{
    auto it = Hero_fighting.begin();
    while (it != Hero_fighting.end()) {
        if (it->current_enemy->current_hp <= 0)
            it->current_enemy = NULL;//目标丢失

        if (it->current_hp <= 0) {
            this->removeChild(it->sprite, true);//退场
            it = Hero_fighting.erase(it);//删除
        }
        else {
            ++it;
        }
    }
    /*
    if (hero2.current_hp <= 0)
        hero1.current_enemy = NULL;//目标丢失
    if (hero2.current_hp <= 0) {
        this->removeChild(hero2.sprite, true);//退场
    }*/
}

void BattleLayer::checkBullet()
{
    auto it = bullet.begin();
    while (it != bullet.end()) {

        it->target = it->target_hero->sprite->getPosition();//更新目标英雄位置

        if (it->target_hero->current_hp <= 0)
            it->target_hero = NULL;

        if (it->Hitted()) {//子弹射中目标位置

            if (it->target_hero != NULL) {
                it->target_hero->current_hp -= it->hurt;//扣血
                //扣血动画
            }
            //子弹回收动画？
            this->removeChild(it->sprite, true);//退场
            it=bullet.erase(it);
        }
        else {
            it++;
        }
    }
}

/*
void BattleLayer::HeroMove(vector<MyHero>& vec)
{
    auto it = vec.begin();
    
    while (it != vec.end()) {
        if (it->current_enemy != NULL)
            it->seek_enemy();//没有目标就索敌
        else//有目标就朝他移动
            it->sprite->setPosition(it->current_enemy->sprite->getPosition());
    }
}*/

void BattleLayer::allocate(MySprite& player1, MySprite& player2)
{
    //玩家
    bluePlayer = player1;
    redPlayer = player2;

    //场上英雄复制
    auto it1 = player1.Hero_fighting.begin();
    for (; it1 != player1.Hero_fighting.end(); ++it1)
    {
        blueHero.push_back(*it1);
    }
    auto it2 = player2.Hero_fighting.begin();
    for (; it2 != player2.Hero_fighting.end(); ++it2)
    {
        redHero.push_back(*it2);
    }
}

