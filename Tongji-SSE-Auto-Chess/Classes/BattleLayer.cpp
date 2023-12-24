#include "HelloWorldScene.h"
#include "Test_Scene_4.h"
#include "goldenshovel_hero_design.h" 
#include "BattleLayer.h"
#include "GameMap.h"
using namespace std;

USING_NS_CC;

bool BattleLayer::init(int Player1,int Player2)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    player1 = Player1;
    player2 = Player2;

    Player[player1].refresh_shop_free();// 刷新商店
    store_display();// 初始化商店



    test();
    getHero(blueHero, player1);   //将玩家的英雄复制到场上
    getHero(redHero, player2);

    auto sprite1 = Sprite::create("Annie.png");
    sprite1->setPosition(enemy_bench_px(1));
    this->addChild(sprite1, 1);

    auto sprite2 = Sprite::create("Evelynn.png");
    sprite2->setPosition(enemy_bench_px(2));
    this->addChild(sprite2, 1);

    auto sprite3 = Sprite::create("Evelynn.png");
    sprite3->setPosition(enemy_bench_px(3));
    this->addChild(sprite3, 1);

    addHero(blueHero);            //将场上英雄加入场景（可视化）
    addHero(redHero);

    this->schedule(schedule_selector(BattleLayer::myupdate));
    this->schedule(schedule_selector(BattleLayer::update_attack), 1.0f);

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
void BattleLayer::card_remove(int index)
{
    this->removeChildByTag(index + 1);
}
void BattleLayer::store_display()
{
    string hero1 = Player[player1].Hero_in_shop[0] + ".png";
    string hero2 = Player[player1].Hero_in_shop[1] + ".png";
    string hero3 = Player[player1].Hero_in_shop[2] + ".png";
    string hero4 = Player[player1].Hero_in_shop[3] + ".png";
    string card1 = Player[player1].Hero_in_shop[0] + "_Card.png";
    string card2 = Player[player1].Hero_in_shop[1] + "_Card.png";
    string card3 = Player[player1].Hero_in_shop[2] + "_Card.png";
    string card4 = Player[player1].Hero_in_shop[3] + "_Card.png";


   cocos2d::Size targetSize(500, 500);
     auto HeroCard1 = MenuItemImage::create(
        card1,
        card1,
        [&](Ref* sender) {
            set_a_hero(Player[player1].Hero_in_shop[0], Player[player1].Hero_in_shop, Player[player1].Hero_on_bench);
            Player[player1].Hero_on_bench.back().sprite->setPosition(my_bench_px(Player[player1].Hero_on_bench.size() - 1));
            this->addChild(Player[player1].Hero_on_bench.back().sprite);
            card_remove(0);
            Player[player1].Hero_in_shop[0] = "";
        });
    auto menu1 = Menu::create(HeroCard1, NULL);
    menu1->setTag(1);
    menu1->setContentSize(targetSize);
    menu1->setPosition(500, 250);
    this->addChild(menu1,0);
    
    auto HeroCard2 = MenuItemImage::create(
        card2,
        card2,
		[&](Ref* sender) {
			set_a_hero(Player[player1].Hero_in_shop[1], Player[player1].Hero_in_shop, Player[player1].Hero_on_bench);
			Player[player1].Hero_on_bench.back().sprite->setPosition(my_bench_px(Player[player1].Hero_on_bench.size() - 1));
			this->addChild(Player[player1].Hero_on_bench.back().sprite);
			card_remove(1);
            Player[player1].Hero_in_shop[1] = "";
		});
    auto menu2 = Menu::create(HeroCard2, NULL);
    menu2->setTag(2);
    menu2->setContentSize(targetSize);
    menu2->setPosition(1000, 250);
    this->addChild(menu2);

    auto HeroCard3 = MenuItemImage::create(
        card3,
        card3,
        [&](Ref* sender) {
            set_a_hero(Player[player1].Hero_in_shop[2], Player[player1].Hero_in_shop, Player[player1].Hero_on_bench);
            Player[player1].Hero_on_bench.back().sprite->setPosition(my_bench_px(Player[player1].Hero_on_bench.size() - 1));
            this->addChild(Player[player1].Hero_on_bench.back().sprite);
            card_remove(2);
            Player[player1].Hero_in_shop[2] = "";
        });
    auto menu3 = Menu::create(HeroCard3, NULL);
    menu3->setTag(3);
    menu3->setContentSize(targetSize);
    menu3->setPosition(1500, 250);
    this->addChild(menu3);

    auto HeroCard4 = MenuItemImage::create(
        card4,
        card4,
        [&](Ref* sender) {
            set_a_hero(Player[player1].Hero_in_shop[3], Player[player1].Hero_in_shop, Player[player1].Hero_on_bench);
            Player[player1].Hero_on_bench.back().sprite->setPosition(my_bench_px(Player[player1].Hero_on_bench.size() - 1));
            this->addChild(Player[player1].Hero_on_bench.back().sprite);
            card_remove(3);
            Player[player1].Hero_in_shop[3] = "";
        });
    auto menu4 = Menu::create(HeroCard4, NULL);
    menu4->setTag(4);
    menu4->setContentSize(targetSize);
    menu4->setPosition(2000, 250);
    this->addChild(menu4);
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

void BattleLayer::getHero(vector<MyHero>& Hero,int i)
{
    //场上英雄复制
    auto it = Player[i].Hero_on_bench.begin();
    for (; it != Player[i].Hero_on_bench.end(); ++it)
    {
        MyHero a = *it;
        Hero.push_back(a);
    }
}
void BattleLayer::addHero(vector<MyHero>& Hero_fighting)
{
    for (int i = 0; i < Hero_fighting.size(); i++) {
        this->addChild(Hero_fighting[i].sprite, 0);
    }
}
//用于放置英雄测试
void BattleLayer::test() {
    MyHero hero1;
    hero1.sprite = Sprite::create("Amumu.png");
    hero1.sprite->setPosition(reverse_map_px(2, 3));
    this->addChild(hero1.sprite, 0);
}

BattleLayer* BattleLayer::create(int Player1,int Player2)
{
    BattleLayer* ret = new (std::nothrow) BattleLayer();
    if (ret && ret->init(Player1,Player2))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}