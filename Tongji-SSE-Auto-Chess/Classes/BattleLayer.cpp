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

    /*getHero(blueHero, bluePlayer.Hero_on_bench);
    getHero(redHero, redPlayer.Hero_on_bench);

    //bluePlayer.Hero_on_bench[0].sprite->setPosition(500, 500);
    //this->addChild(bluePlayer.Hero_on_bench[0].sprite, 0);

    Player[1].Hero_on_bench[0].sprite->setPosition(500, 500);
    this->addChild(Player[1].Hero_on_bench[0].sprite, 0);

    addHero(blueHero);
    addHero(redHero);*/

    /**/
    ///////////////////////////////
    MyHero hero1 = set_a_hero("Annie", Hero_1, Hero_on_court_1);
    hero1.sprite->setPosition(Vec2(2000, 1000));

    MyHero hero2 = set_a_hero("Evelynn", Hero_2, Hero_on_court_2);
    hero2.sprite->setPosition(Vec2(400, 400));

    MyHero hero3 = set_a_hero("Corki", Hero_1, Hero_on_court_1);
    hero3.sprite->setPosition(Vec2(400, 1200));

    MyHero hero4 = set_a_hero("Taric", Hero_1, Hero_on_court_1);
    hero4.sprite->setPosition(Vec2(1800, 300));

    blueHero.push_back(hero1);
    blueHero.push_back(hero3);
    redHero.push_back(hero2);
    redHero.push_back(hero4);

    redHero[0].current_enemy = nullptr;
    blueHero[0].current_enemy = nullptr;
    redHero[1].current_enemy = nullptr;
    blueHero[1].current_enemy = nullptr;

    //this->addChild(hero1.sprite, 0);
    //this->addChild(hero2.sprite, 0);

    this->addChild(blueHero[0].sprite, 0);
    this->addChild(redHero[0].sprite, 0);
    this->addChild(blueHero[1].sprite, 0);
    this->addChild(redHero[1].sprite, 0);

    this->schedule(schedule_selector(BattleLayer::myupdate));
    this->schedule(schedule_selector(BattleLayer::update_attack), 1.0f);

    //new_hero.hero_attack();
    //new_hero_2.hero_attack();

    ///////////////////////////////

    return true;
}

void BattleLayer::myupdate(float dt)
{
    /*以下为游戏中需要不断更新的东西*/

    checkBullet();        //检查子弹，并扣血
    check_death(redHero); //检查英雄死亡并退场
    check_death(blueHero);//检查英雄死亡并退场
    seekAndMove(redHero, blueHero);
    seekAndMove(blueHero,redHero);

    //血量和蓝量更新显示
    //蓝条满放大招，后续加入
    //有一方场上英雄死完，停止战斗，然后根据胜者剩余英雄数对败者进行扣血
}

void BattleLayer::update_attack(float dt)
{
    auto it = blueHero.begin();
    while (it != blueHero.end()) {
        if (it->current_enemy != nullptr&&it->enemyInDistance()) {
            Bullet b(it->current_enemy, it->sprite->getPosition(), it->attack_power, "basketball");//这里先都用篮球，后续写函数根据英雄名字寻找对应的子弹名字
            bullet.push_back(b);
            this->addChild(b.sprite, 2);//子弹加入场景

            //蓄力论述增加，蓝条增加动画

            auto moveTo = MoveTo::create(it->attack_cd, b.target);//子弹飞行动作
            b.sprite->runAction(moveTo);
        }
        it++;
    }

    auto it2 = redHero.begin();
    while (it2 != redHero.end()) {
        if (it2->current_enemy != nullptr && it2->enemyInDistance()) {
            Bullet b(it2->current_enemy, it2->sprite->getPosition(), it2->attack_power, "basketball");//这里先都用篮球，后续写函数根据英雄名字寻找对应的子弹名字
            bullet.push_back(b);
            this->addChild(b.sprite, 2);

            //蓄力论述增加，蓝条增加动画

            auto moveTo = MoveTo::create(it2->attack_cd, b.target);
            b.sprite->runAction(moveTo);
        }
        it2++;
    }
}

void BattleLayer::check_death(vector<MyHero>& Hero_fighting)
{
    auto it = Hero_fighting.begin();
    while (it != Hero_fighting.end()) {
        if (it->current_enemy!=nullptr&&it->current_enemy->current_hp <= 0)
            it->current_enemy = nullptr;//目标丢失

        if (it->current_hp <= 0) {
            this->removeChild(it->sprite, true);//退场
            it = Hero_fighting.erase(it);//删除
        }
        else {
            ++it;
        }
    }
}

void BattleLayer::checkBullet()
{
    auto it = bullet.begin();
    while (it != bullet.end()) {

        if (it->target_hero != nullptr && it->target_hero->current_hp <= 0)
            it->target_hero = nullptr;

        //if (it->target_hero != nullptr) 
        //    it->target = it->target_hero->sprite->getPosition();//更新目标英雄位置
        

        if (it->Hitted()) {//子弹射中目标位置

            if (it->target_hero != nullptr&&it->HitHero()) {//打中英雄
                it->target_hero->current_hp -= it->hurt;//扣血
                //扣血动画
            }
            //子弹回收动画？
            this->removeChild(it->sprite, true);//退场
            it=bullet.erase(it);
        }
        else {
            ++it;
        }
    }

}

void BattleLayer::seekAndMove(vector<MyHero>& blue,vector<MyHero>& red)
{
    auto it = blue.begin();
    while (it != blue.end()) {
        if (it->current_enemy == nullptr&&!red.empty()) {
            it->seek_enemy(red);
            //CCLOG("seek_enemy successful");
            if (it->current_enemy != nullptr) {
                auto moveTo = MoveTo::create(2, it->current_enemy->sprite->getPosition());
                it->sprite->runAction(moveTo);
            }
        }
        if (it->current_enemy != nullptr) {
            if (it->enemyInDistance())
                it->sprite->stopAllActions();
        }
        it++;
    }
    //it->enemyInDistance()
}

void BattleLayer::allocate(MySprite& player1, MySprite& player2)
{
    //玩家
    bluePlayer = player1;
    redPlayer = player2;
}

void BattleLayer::getHero(vector<MyHero>& Hero,vector<MyHero>& Hero_fighting)
{
    //场上英雄复制
    auto it = Hero_fighting.begin();
    for (; it != Hero_fighting.end(); ++it)
    {
        Hero.push_back(*it);
    }
}
void BattleLayer::addHero(vector<MyHero>& Hero_fighting)
{
    for (int i = 0; i < Hero_fighting.size(); i++) {
        this->addChild(Hero_fighting[i].sprite, 0);
    }
}

