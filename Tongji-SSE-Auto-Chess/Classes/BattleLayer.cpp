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

    this->schedule(schedule_selector(BattleLayer::myupdate));
    this->schedule(schedule_selector(BattleLayer::update_attack), 0.5f);

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

        //退出当前场景的按钮
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

void BattleLayer::myupdate(float dt)
{
    /*以下为游戏中需要不断更新的东西*/

    //check_death(player_blue->Hero_fighting,player_red->Hero_fighting);//检查英雄死亡并退场
    //BulletMove();  //子弹飞行
    BulletDelete();//打中回收子弹，并扣血

    //check_death有误，先用这个测试代替一下
    if (hero2.current_hp <= 0) {
        this->removeChild(hero2.sprite, true);
    }

    //英雄自走，函数已写，后续加入
    //蓝条满放大招，后续加入
    //有一方场上英雄死完，停止战斗，然后根据胜者剩余英雄数对败者进行扣血
}

void BattleLayer::update_attack(float dt)
{
    if (hero1.current_enemy != NULL) {
        Bullet b(hero1.current_enemy, hero1.sprite->getPosition(), hero1.attack_power, "basketball");
        bullet.push_back(b);
        this->addChild(b.sprite, 2);
        auto moveTo = MoveTo::create(2, hero1.current_enemy->sprite->getPosition());
        b.sprite->runAction(moveTo);
        b.target_hero->current_hp -= b.hurt;
    }
}

/*
bool BattleLayer::IsZeroHp(MyHero& hero)
{
    if (hero.gethp() <= 0)
    {
        this->removeChild(hero.sprite, true);  //移出场景
        return 1;
    }
    else
        return 0;
}
void BattleLayer::check_death(vector<MyHero>& my_vec, vector<MyHero>& enemy_vec)
{
    // 使用 remove_if + erase 结合的方式移除符合条件的元素
    my_vec.erase(std::remove_if(my_vec.begin(), my_vec.end(), IsZeroHp), my_vec.end());
    enemy_vec.erase(std::remove_if(enemy_vec.begin(), enemy_vec.end(), IsZeroHp), enemy_vec.end());
}*/

void BattleLayer::BulletMove()
{
    auto it = bullet.begin();
    while (it != bullet.end()) {
        if (it->target_hero!=NULL) {
            //移动到目标位置
            it->sprite->setPosition(it->target_hero->sprite->getPosition());
        }
        else {
            //目标已死但子弹还在飞，先设定为直接飞过去（或者直接删除退场）
            it->sprite->setPosition(it->target);
        }
        it++;
    }
}
void BattleLayer::BulletDelete()
{
    auto it = bullet.begin();
    while (it != bullet.end()) {
        if (it->position==it->target) {//子弹射中目标位置

            if (it->target_hero != NULL) {
                it->target_hero->current_hp -= it->hurt;//扣血
                //扣血动画
            }
            //子弹回收动画？
            this->removeChild(it->sprite, true);//退场
            bullet.erase(it++);
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
