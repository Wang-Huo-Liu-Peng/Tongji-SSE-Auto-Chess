#include "HelloWorldScene.h"
#include "Test_Scene_4.h"
#include "MatchOverScene.h"
#include "goldenshovel_hero_design.h" 
#include "BattleLayer.h"
#include "GameMap.h"
#include <ui/UILayout.h>
#include"Client.h"
#include"hero_simple.h"
using namespace std; 

USING_NS_CC;

bool BattleLayer::init(int Player1,int Player2)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    player1 = Player1;
    player2 = Player2;

    if(Player[player2].Operator==AI)
        AIPlayerBrain(player2);//AI更新场上英雄


    vector<hero_simple>_hero_on_court;
    vector<hero_simple>_hero_on_bench;
    //将我方英雄提取到vector<hero_simple>
    for (auto hero : Player[player1].Hero_on_bench) {
        struct hero_simple temp;
        strcpy(temp.hero_name, hero.name);
    }

    //如果对手不是AI if (Player[player2].Operator== HUMAN)
    if (Player[player2].Operator == HUMAN) {
        //将我方的英雄信息上传，作为对方的Player2
        Client::getInstance()->write_event(SendHero);//写入事件
        
        Client::getInstance()->write_hero_on_court((void*)(&_hero_on_court));//写入信息
        Client::getInstance()->write_hero_on_bench((void*)(&_hero_on_bench));
        Client::getInstance()->set_get_state(0);//设置状态为未接受对面英雄
        Client::getInstance()->send_msg();//发送
        //接受对方的英雄信息，  作为这边的player2
        while (1) {//阻塞等待接受对面英雄信息
            if (Client::getInstance()->get_get_state() == 1)
            {
                break;
            }
        }

        vector<hero_simple>* _hero_on_court = (vector<hero_simple>*)(Client::getInstance()->get_hero_on_court());//读取信息并转换为MyHero的vector
        vector<hero_simple>* _hero_fighting = (vector<hero_simple>*)Client::getInstance()->get_hero_on_bench();
        if(_hero_on_court==NULL)
            CCLOG("bbb");
        CCLOG("aaa");
        CCLOG("%d", (*_hero_on_court).size());
        CCLOG("aaa");
        //std::copy(_hero_on_court->begin(), _hero_on_court->end(), Player[player2].Hero_on_court.begin());//拷贝到当前使用的vector
        //std::copy(_hero_fighting->begin(), _hero_fighting->end(), Player[player2].Hero_fighting.begin());
        Player[player2].Hero_on_court.clear();
        for (int i = 0; i < (*_hero_on_court).size(); i++)
            Player[player2].Hero_on_court.emplace_back((*_hero_on_court)[i]);
       // for (int i = 0; i < (*_hero_fighting).size(); i++)
            //Player[player2].Hero_on_court.push_back((*_hero_on_court)[i]);

    }

    Player[player1].copy();//将court中的英雄复制到fighting上
    Player[player2].copy();//将court中的英雄复制到fighting上

    //将双方的英雄加入场景中
    addHero(player1, ON_BENCH, ME);
    addHero(player2, ON_BENCH, ENEMY);
    addHero(player1, FIGHTING, ME);
    addHero(player2, FIGHTING, ENEMY);

    addSprite(player1, MY_SPRITE);
    addSprite(player2, ENEMY_SPRITE);

    /*====================商店部分========================*/
    auto my_refresh_button = MenuItemImage::create(
        "refresh_shop.png",
        "refresh_shop.png",
        [&](Ref* sender) {
            for(int i=1;i<=4;i++)
            {
                Node* node_with_tag_i = this->getChildByTag(i);
                if (node_with_tag_i) {
                    this->removeChild(node_with_tag_i, true);
                }
            }
            Player[player1].refresh_shop(this);
            store_display();// 初始化商店
        });
    cocos2d::Size targetSize(100, 100);
    auto menu0 = Menu::create(my_refresh_button, NULL);
    menu0->setTag(0);
    menu0->setContentSize(targetSize);
    menu0->setPosition(refresh_button);
    this->addChild(menu0);

    auto my_buy_exp_button = MenuItemImage::create(
        "buy_exp.png", // 设置按钮的背景图
        "buy_exp.png",
        [&](Ref* sender) {
            if (Player[player1].getmoney() < 4) {
                PopupManager::displayPopup(this, "No enough Money to buy exp");
            }
            else {
                Player[player1].increaseexp(4);
                Player[player1].decreasemoney(4);
                Player[player1].level_up();
            }
            CCLOG("buy_exp按钮被点击");
        });

    auto menu_buy_exp = Menu::create(my_buy_exp_button, nullptr);
    menu_buy_exp->setTag(0); // 设置按钮的tag（这里假设buy_exp按钮的tag为1）
    menu_buy_exp->setContentSize(targetSize);
    menu_buy_exp->setPosition(buyexp_button); // 设置buy_exp按钮的位置
    this->addChild(menu_buy_exp);

    Player[player1].refresh_shop_free();// 刷新商店
    store_display();// 初始化商店

    /*====================商店部分结束========================*/

    // 创建用于显示current_exp的标签
    expLabel = Label::createWithTTF("Exp: 0", "fonts/arial.ttf", 30);
    expLabel->setPosition(Vec2(100, 300));
    this->addChild(expLabel);

    // 创建用于显示current_money的标签
    moneyLabel = Label::createWithTTF("Money: 0", "fonts/arial.ttf", 30);
    moneyLabel->setPosition(Vec2(100, 250));
    this->addChild(moneyLabel);

    // 创建用于显示star_level的标签
    levelLabel = Label::createWithTTF("Level: 0", "fonts/arial.ttf", 30);
    levelLabel->setPosition(Vec2(100, 200));
    this->addChild(levelLabel);

    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(BattleLayer::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    //定时器部分
    this->schedule(schedule_selector(BattleLayer::myupdate));
    this->schedule(schedule_selector(BattleLayer::update_attack), 1.0f);

    ///////////////////////////////

    return true;
}

void BattleLayer::myupdate(float dt)
{
    /*以下为游戏中需要不断更新的东西*/

    checkBullet();        //检查子弹，并扣血
    check_enemy(Player[player1].Hero_fighting); //检查目标丢失
    check_enemy(Player[player2].Hero_fighting); //检查目标丢失
    check_death(Player[player1].Hero_fighting); //检查英雄死亡并退场
    check_death(Player[player2].Hero_fighting); //检查英雄死亡并退场
    seekAndMove(Player[player1].Hero_fighting, Player[player2].Hero_fighting);
    seekAndMove(Player[player2].Hero_fighting, Player[player1].Hero_fighting);
    attribute_display(Player[player1].Hero_fighting);   //红蓝条
    attribute_display(Player[player2].Hero_fighting);


    // 获取MySprite类中的信息
    int currentExp = Player[player1].getexp();
    int currentMoney = Player[player1].getmoney();
    int starLevel = Player[player1].getlevel();

    // 更新标签内容
    expLabel->setString(StringUtils::format("Exp: %d", currentExp));
    moneyLabel->setString(StringUtils::format("Money: %d", currentMoney));
    levelLabel->setString(StringUtils::format("Level: %d", starLevel));

    //蓝条满放大招，后续加入

    if (gameOver(player1, player2)) {
        //OverShoot(player1, player2);
        //situation = GameOver;
        if (bullet.empty()) {
            this->unschedule(schedule_selector(BattleLayer::myupdate));
            this->unschedule(schedule_selector(BattleLayer::update_attack));
        }
    }
    else if (gameOver(player2, player1)) {
        //OverShoot(player2, player1);
        //situation = GameOver;
        if (bullet.empty()) {
            this->unschedule(schedule_selector(BattleLayer::myupdate));
            this->unschedule(schedule_selector(BattleLayer::update_attack));
        }
    }

    MatchOver(player1, player2);
}

void BattleLayer::update_attack(float dt)
{
    auto it = Player[player1].Hero_fighting.begin();
    while (it != Player[player1].Hero_fighting.end()) {
        if (it->current_enemy != nullptr&&it->enemyInDistance()) {
            it->current_cooldown_round++;//蓝条增加
            Bullet b(it->current_enemy, it->sprite->getPosition(), it->attack_power, "bullet_1");//这里先都用篮球，后续写函数根据英雄名字寻找对应的子弹名字
            bullet.push_back(b);
            this->addChild(b.sprite, 2);//子弹加入场景
            auto moveTo = MoveTo::create(it->attack_cd, b.target);//子弹飞行动作
            b.sprite->runAction(moveTo);
        }
        it++;
    }

    auto it2 = Player[player2].Hero_fighting.begin();
    while (it2 != Player[player2].Hero_fighting.end()) {
        if (it2->current_enemy != nullptr && it2->enemyInDistance()) {
            it2->current_cooldown_round++;//蓝条增加
            Bullet b(it2->current_enemy, it2->sprite->getPosition(), it2->attack_power, "bullet_1");//这里先都用篮球，后续写函数根据英雄名字寻找对应的子弹名字
            bullet.push_back(b);
            this->addChild(b.sprite, 2);//子弹加入场景
            auto moveTo = MoveTo::create(it2->attack_cd, b.target);//子弹飞行动作
            b.sprite->runAction(moveTo);
        }
        it2++;
    }
}

void BattleLayer::check_death(vector<MyHero>& Hero_fighting)
{
    auto it = Hero_fighting.begin();
    while (it != Hero_fighting.end()) {
        //if (it->current_enemy!=nullptr&&it->current_enemy->current_hp <= 0)
        //    it->current_enemy = nullptr;//目标丢失
        if (it->current_hp <= 0) {
            this->removeChild(it->sprite, true);//退场
            it = Hero_fighting.erase(it);//删除
        }
        else {
            ++it;
        }
    }
}

void BattleLayer::check_enemy(vector<MyHero>& Hero_fighting)
{
    auto it = Hero_fighting.begin();
    while (it != Hero_fighting.end()) {
        if (it->current_enemy != nullptr && it->current_enemy->current_hp <= 0)
            it->current_enemy = nullptr;//目标丢失
        ++it;
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
            if (it->target_sprite != nullptr) {//打中小小英雄
                it->target_sprite->current_hp -= it->hurt;//扣血
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
}

bool BattleLayer::gameOver(int index1,int index2)
{
    if (Player[index1].Hero_fighting.empty()) {//玩家1的英雄死完了
        if (situation == Fighting) {
            //Player[index1].current_hp -= Player[index2].Hero_fighting.size();
            OverShoot(index1, index2);
            //加金币和经验
            Player[index1].money += 10;
            Player[index2].money += 10;
            Player[index1].current_exp += 2;
            Player[index1].level_up();
            Player[index2].current_exp += 2;
            Player[index2].level_up();
            situation = GameOver;
        }
        return true;//返回true，表明本次战斗结束
    }
    return false;
}

void BattleLayer::MatchOver(int index1, int index2)
{
    if (Player[index1].current_hp <= 0) {
        MatchOverScene* over = MatchOverScene::create(index2);
        Director::getInstance()->replaceScene(over);
    }
    if (Player[index2].current_hp <= 0) {
        MatchOverScene* over = MatchOverScene::create(index1);
        Director::getInstance()->replaceScene(over);
    }
}

void BattleLayer::OverShoot(int index1, int index2)
{
    if (situation == Fighting) {
        auto it = Player[index2].Hero_fighting.begin();
        while (it != Player[index2].Hero_fighting.end()) {
            Bullet b(&Player[index1], it->sprite->getPosition(), 1, "bullet_1");
            bullet.push_back(b);
            this->addChild(b.sprite, 2);//子弹加入场景
            auto moveTo = MoveTo::create(it->attack_cd, b.target);//子弹飞行动作
            b.sprite->runAction(moveTo);
            it++;
        }
    }
}

void BattleLayer::addHero(int player,int station,int camp)
{
    if (station == ON_BENCH) {
        if (!Player[player].Hero_on_bench.empty()) {
            auto it = Player[player].Hero_on_bench.begin();
            for (; it != Player[player].Hero_on_bench.end(); it++) {
                if (camp == ME)
                    it->sprite->setPosition(my_bench_px(it - Player[player].Hero_on_bench.begin()));
                else if (camp == ENEMY)
                    it->sprite->setPosition(enemy_bench_px(it - Player[player].Hero_on_bench.begin()));
                it->sprite->retain();
                it->sprite->removeFromParentAndCleanup(false);
                this->addChild(it->sprite, 0);
                it->sprite->getChildByTag(RED_TAG)->setContentSize(Size(HERO_BAR_LENGTH, BAR_HEIGHT));
                it->sprite->getChildByTag(BLUE_TAG)->setContentSize(Size(HERO_BAR_LENGTH, BAR_HEIGHT));
            }
        }
    }
    else if (station == FIGHTING) {
        if (!Player[player].Hero_fighting.empty()) {
            auto it = Player[player].Hero_fighting.begin();
            for (; it != Player[player].Hero_fighting.end(); it++) {
                //Player[player].sprite->setPosition(reverse_map_px(Player[player].Hero_fighting[i].location_x, Player[player].Hero_fighting[i].location_y, camp));
                it->sprite->retain();
                it->sprite->removeFromParentAndCleanup(false);
                it->sprite->setPosition(reverse_map_px(it->location_x, it->location_y, camp));
                this->addChild(it->sprite, 0);
                it->sprite->getChildByTag(RED_TAG)->setScaleX(float(it->full_hp) / float(it->current_hp));
                it->sprite->getChildByTag(BLUE_TAG)->setScaleX(float(it->needed_cooldown_round) / float(it->current_cooldown_round));
            }
        }
    }
}

void BattleLayer::addSprite(int index,int camp)
{
    char num = index + '0';
    string picture = "Player_";
    picture += num;
    picture += ".png";
    Player[index].sprite = Sprite::create(picture);
    attribute(Player[index].sprite, SPRITE_BAR_LENGTH, camp);
    if(camp==MY_SPRITE)
        Player[index].sprite->setPosition(player1_px);
    else if(camp==ENEMY_SPRITE)
        Player[index].sprite->setPosition(player2_px);
    Player[index].sprite->getChildByTag(RED_TAG)->setScaleX(float(Player[index].current_hp) / float(Player[index].full_hp));
    this->addChild(Player[index].sprite, 1, camp);
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

/*----------------------显示部分-------------------------*/
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
            MyHero* newHero = set_a_hero(Player[player1], Player[player1].Hero_in_shop[0], Player[player1].Hero_in_shop, Player[player1].Hero_on_bench, this);

            if (newHero) {
                // 设置位置
                if (newHero->sprite) {
                    newHero->sprite->setPosition(my_bench_px(Player[player1].Hero_on_bench.size()));

                    // 将 Sprite 添加到层中
                    this->addChild(newHero->sprite);
                    Player[player1].Hero_on_bench.push_back(*newHero);
                }
                // 移除商店中的卡片
                card_remove(0);
                Player[player1].Hero_in_shop[0] = "";
            }
        });
    auto menu1 = Menu::create(HeroCard1, NULL);
    menu1->setTag(1);
    menu1->setContentSize(targetSize);
    menu1->setPosition(card_px(0));
    this->addChild(menu1, 0);

    auto HeroCard2 = MenuItemImage::create(
        card2,
        card2,
        [&](Ref* sender) {
            MyHero* newHero = set_a_hero(Player[player1], Player[player1].Hero_in_shop[1], Player[player1].Hero_in_shop, Player[player1].Hero_on_bench, this);

            if (newHero) {
                // 设置位置
                if (newHero->sprite) {
                    newHero->sprite->setPosition(my_bench_px(Player[player1].Hero_on_bench.size()));

                    // 将 Sprite 添加到层中
                    this->addChild(newHero->sprite);
                    Player[player1].Hero_on_bench.push_back(*newHero);
                }
                // 移除商店中的卡片
                card_remove(1);
                Player[player1].Hero_in_shop[1] = "";
            }
        });
    auto menu2 = Menu::create(HeroCard2, NULL);
    menu2->setTag(2);
    menu2->setContentSize(targetSize);
    menu2->setPosition(card_px(1));
    this->addChild(menu2);

    auto HeroCard3 = MenuItemImage::create(
        card3,
        card3,
        [&](Ref* sender) {
            // 假设 set_a_hero 函数的原型是 MyHero* set_a_hero(...)
            MyHero* newHero = set_a_hero(Player[player1], Player[player1].Hero_in_shop[2], Player[player1].Hero_in_shop, Player[player1].Hero_on_bench, this);

            if (newHero) {
                // 设置位置
                if (newHero->sprite) {
                    newHero->sprite->setPosition(my_bench_px(Player[player1].Hero_on_bench.size()));

                    // 将 Sprite 添加到层中
                    this->addChild(newHero->sprite);
                    Player[player1].Hero_on_bench.push_back(*newHero);
                }

                // 移除商店中的卡片
                card_remove(2);
                Player[player1].Hero_in_shop[2] = "";
            }

        });
    auto menu3 = Menu::create(HeroCard3, NULL);
    menu3->setTag(3);
    menu3->setContentSize(targetSize);
    menu3->setPosition(card_px(2));
    this->addChild(menu3);

    auto HeroCard4 = MenuItemImage::create(
        card4,
        card4,
        [&](Ref* sender) {
            MyHero* newHero = set_a_hero(Player[player1], Player[player1].Hero_in_shop[3], Player[player1].Hero_in_shop, Player[player1].Hero_on_bench, this);

            if (newHero) {
                // 设置位置
                if (newHero->sprite) {
                    newHero->sprite->setPosition(my_bench_px(Player[player1].Hero_on_bench.size()));

                    // 将 Sprite 添加到层中
                    this->addChild(newHero->sprite);
                    Player[player1].Hero_on_bench.push_back(*newHero);
                }

                // 移除商店中的卡片
                card_remove(3);
                Player[player1].Hero_in_shop[3] = "";
            }
        });
    auto menu4 = Menu::create(HeroCard4, NULL);
    menu4->setTag(4);
    menu4->setContentSize(targetSize);
    menu4->setPosition(card_px(3));
    this->addChild(menu4);
}
void BattleLayer::attribute_display(vector<MyHero>& Hero_fighting)
{
    auto it = Hero_fighting.begin();
    while (it != Hero_fighting.end()) {
        it->sprite->getChildByTag(RED_TAG)->setScaleX(float(it->current_hp) / float(it->full_hp) );
        it->sprite->getChildByTag(BLUE_TAG)->setScaleX(float(it->current_cooldown_round) / float(it->needed_cooldown_round) );
        if(float(it->current_cooldown_round) / float(it->needed_cooldown_round)==1)
            it->current_cooldown_round=0;
        it++;
    }
    Player[player1].sprite->getChildByTag(RED_TAG)->setScaleX(float(Player[player1].current_hp) / float(Player[player1].full_hp));
    Player[player2].sprite->getChildByTag(RED_TAG)->setScaleX(float(Player[player2].current_hp) / float(Player[player2].full_hp));
}

/*----------------AI操作部分-----------------*/
void BattleLayer::AIPlayerBrain(int ai) {
    while (Player[ai].Hero_on_court.size() < Player[ai].max_hero) {
        int max_pos = -1;
        int max_cost = 0;

        for (int i = 0; i < 4; i++) {
            if (Hero_list[Player[ai].Hero_in_shop[i]].getcost() > max_cost && Hero_list[Player[ai].Hero_in_shop[i]].getcost() < Player[ai].money) {
                max_cost = Hero_list[Player[ai].Hero_in_shop[i]].getcost();
                max_pos = i;
            }
        }

        if (max_pos > -1) {
            MyHero* New;
            //改接口
            New = set_a_hero(Player[ai], Player[ai].Hero_in_shop[max_pos], Player[ai].Hero_in_shop, Player[ai].Hero_on_court, this);

            while (1) {
                //随机落子
                int x = rand() % 8;
                int y = rand() % 3;
                if (Player[ai].MAP[x][y] == 0) {
                    New->location_x = x;
                    New->location_y = y;
                    break;
                }
            }

            // 将 New 放置到 Hero_on_court 中
            Player[ai].Hero_on_court.push_back(*New);
            Player[ai].make_a_random_hero();  // 重新生成商店英雄
        }

    }
}

/*----------------监听器-----------------*/
void BattleLayer::onMouseDown(EventMouse* event)
{
    if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
        Vec2 mousePos = event->getLocation();
        mousePos = Director::getInstance()->convertToGL(mousePos);
        mousePos = this->convertToNodeSpace(mousePos);//转化为世界坐标
        // 处理鼠标右键按下事件和鼠标位置
        auto sprite = this->getChildByTag(MY_SPRITE);
        auto moveTo = MoveTo::create(2, mousePos);
        sprite->stopAllActions();
        sprite->runAction(moveTo);
    }
}
