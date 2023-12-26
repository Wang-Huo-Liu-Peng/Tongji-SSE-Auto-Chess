#include "HelloWorldScene.h"
#include "Test_Scene_4.h"
#include "goldenshovel_hero_design.h" 
#include "PrepareLayer.h"
#include "GameMap.h"
#include <ui/UILayout.h>
using namespace std;

USING_NS_CC;      

bool PrepareLayer::init(int index)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    player = index;

    /*===================监听器的创建=======================*/
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(PrepareLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(PrepareLayer::onTouchMoved, this);  // Added onTouchMoved
    listener->onTouchEnded = CC_CALLBACK_2(PrepareLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    /*====================商店部分========================*/
    auto my_refresh_button = MenuItemImage::create(
        "refresh_shop.png",
        "refresh_shop.png",
        [&](Ref* sender) {
            for (int i = 1; i <= 4; i++)
            {
                Node* node_with_tag_i = this->getChildByTag(i);
                if (node_with_tag_i) {
                    this->removeChild(node_with_tag_i, true);
                }
            }
            Player[player].refresh_shop(this);
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
            if (Player[player].getmoney() < 4) {
                PopupManager::displayPopup(this, "No enough Money to buy exp");
            }
            else {
                Player[player].increaseexp(4);
                Player[player].decreasemoney(4);
                Player[player].level_up();
            }
            CCLOG("buy_exp按钮被点击");
        });

    auto menu_buy_exp = Menu::create(my_buy_exp_button, nullptr);
    menu_buy_exp->setTag(0); // 设置按钮的tag（这里假设buy_exp按钮的tag为1）
    menu_buy_exp->setContentSize(targetSize);
    menu_buy_exp->setPosition(buyexp_button); // 设置buy_exp按钮的位置
    this->addChild(menu_buy_exp);

   


    Player[player].refresh_shop_free();// 刷新商店
    store_display();// 初始化商店
    /*====================商店部分结束========================*/

    //将英雄加入场景中
    Player[player].copy();
    addHero(player, ON_BENCH, ME);
    addHero(player, FIGHTING, ME);

    Player[player].sprite->setPosition(player1_px);
    this->addChild(Player[player].sprite,1);
    Player[2].sprite->setPosition(player2_px);
    this->addChild(Player[2].sprite, 1);



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

    this->schedule(schedule_selector(PrepareLayer::update));

    ///////////////////////////////
    return true;
}

PrepareLayer* PrepareLayer::create(int index)
{
    PrepareLayer* ret = new (std::nothrow) PrepareLayer();
    if (ret && ret->init(index))
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

void PrepareLayer::addHero(int player, int station, int camp)
{
    if (station == ON_BENCH) {
        CCLOG("%d", Player[player].Hero_on_bench.size());
        for (int i = 0; i < Player[player].Hero_on_bench.size(); i++) {
            if (camp == ME)
                Player[player].Hero_on_bench[i].sprite->setPosition(my_bench_px(i));
            else if (camp == ENEMY)
                Player[player].Hero_on_bench[i].sprite->setPosition(enemy_bench_px(i));
            Player[player].Hero_on_bench[i].sprite->retain();
            Player[player].Hero_on_bench[i].sprite->removeFromParentAndCleanup(false);
            this->addChild(Player[player].Hero_on_bench[i].sprite, 0);
        }
    }
    else if (station == FIGHTING) {
        for (int i = 0; i < Player[player].Hero_fighting.size(); i++) {
            Player[player].Hero_fighting[i].sprite->retain();
            Player[player].Hero_fighting[i].sprite->removeFromParentAndCleanup(false);
            Player[player].Hero_fighting[i].sprite->setPosition(reverse_map_px(Player[player].Hero_fighting[i].location_x, Player[player].Hero_fighting[i].location_y, camp));
            this->addChild(Player[player].Hero_fighting[i].sprite, 0);
        }
    }
}




/*========================================回调函数===========================================================*/
bool PrepareLayer::onTouchBegan(Touch* touch, Event* event)
{
    // 获取触摸点坐标
    Vec2 touchPoint = touch->getLocation();

    // 检查是否点击到英雄，这里假设英雄的sprite是可点击的
    for (int i = 0; i < Player[player].Hero_on_bench.size(); i++)
    {
        Player[player].Hero_on_bench[i].sprite->stopAllActions();
        if (Player[player].Hero_on_bench[i].sprite->getBoundingBox().containsPoint(touchPoint))
        {
            initial_position = Player[player].Hero_on_bench[i].sprite->getPosition();
            select_index = i;
            return true;
        }
    }
    return false;
}
void PrepareLayer::onTouchMoved(Touch* touch, Event* event)
{
    auto touchPoint = touch->getLocation();
    Player[player].Hero_on_bench[select_index].sprite->setPosition(touchPoint);

    /* auto selected_background = Sprite::create("selected_background.png");
     selected_background->setTag(10);
     this->addChild(selected_background);*/
}
void PrepareLayer::onTouchEnded(Touch* touch, Event* event)
{
    /*this->removeChildByTag(10);*/

    auto touchPoint = touch->getLocation();

    if (ifInMap(touchPoint))
    {
        if (Player[player].getlevel() + 2 <= Player[player].Hero_on_court.size()) {
            PopupManager::displayPopup(this, "Too much Hero on court");
            Player[player].Hero_on_bench[select_index].sprite->setPosition(initial_position);
        }
        else {
            int X = Player[player].Hero_on_bench[select_index].location_x = reverse_x(touchPoint.x);
            int Y = Player[player].Hero_on_bench[select_index].location_y = reverse_y(touchPoint.y);
            Player[player].Hero_on_bench[select_index].sprite->setPosition(reverse_map_px(X, Y, ME));
            Player[player].Hero_on_court.push_back(Player[player].Hero_on_bench[select_index]);// 加到court里
            Player[player].Hero_on_bench.erase(Player[player].Hero_on_bench.begin() + select_index);// 从bench里删除
            CCLOG("%d %d", Player[player].Hero_on_court[Player[player].Hero_on_court.size() - 1].location_x, Player[player].Hero_on_court[Player[player].Hero_on_court.size() - 1].location_y);
        }
    }
    else
    {
        Player[player].Hero_on_bench[select_index].sprite->setPosition(initial_position);
    }
}



/*----------------------显示部分-------------------------*/
void PrepareLayer::card_remove(int index)
{
    this->removeChildByTag(index + 1);
}
void PrepareLayer::store_display()
{
    string hero1 = Player[player].Hero_in_shop[0] + ".png";
    string hero2 = Player[player].Hero_in_shop[1] + ".png";
    string hero3 = Player[player].Hero_in_shop[2] + ".png";
    string hero4 = Player[player].Hero_in_shop[3] + ".png";
    string card1 = Player[player].Hero_in_shop[0] + "_Card.png";
    string card2 = Player[player].Hero_in_shop[1] + "_Card.png";
    string card3 = Player[player].Hero_in_shop[2] + "_Card.png";
    string card4 = Player[player].Hero_in_shop[3] + "_Card.png";

    cocos2d::Size targetSize(500, 500);
    auto HeroCard1 = MenuItemImage::create(
        card1,
        card1,
        [&](Ref* sender) {
            MyHero* newHero = set_a_hero(Player[player], Player[player].Hero_in_shop[0], Player[player].Hero_in_shop, Player[player].Hero_on_bench, this);

            if (newHero) {
                // 设置位置
                if (newHero->sprite) {
                    newHero->sprite->setPosition(my_bench_px(Player[player].Hero_on_bench.size()));

                    // 将 Sprite 添加到层中
                    this->addChild(newHero->sprite);
                    Player[player].Hero_on_bench.push_back(*newHero);
                }
                // 移除商店中的卡片
                card_remove(0);
                Player[player].Hero_in_shop[0] = "";
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
            MyHero* newHero = set_a_hero(Player[player], Player[player].Hero_in_shop[1], Player[player].Hero_in_shop, Player[player].Hero_on_bench, this);

            if (newHero) {
                // 设置位置
                if (newHero->sprite) {
                    newHero->sprite->setPosition(my_bench_px(Player[player].Hero_on_bench.size()));

                    // 将 Sprite 添加到层中
                    this->addChild(newHero->sprite);
                    Player[player].Hero_on_bench.push_back(*newHero);
                }
                // 移除商店中的卡片
                card_remove(1);
                Player[player].Hero_in_shop[1] = "";
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
            MyHero* newHero = set_a_hero(Player[player], Player[player].Hero_in_shop[2], Player[player].Hero_in_shop, Player[player].Hero_on_bench, this);

            if (newHero) {
                // 设置位置
                if (newHero->sprite) {
                    newHero->sprite->setPosition(my_bench_px(Player[player].Hero_on_bench.size()));

                    // 将 Sprite 添加到层中
                    this->addChild(newHero->sprite);
                    Player[player].Hero_on_bench.push_back(*newHero);
                }

                // 移除商店中的卡片
                card_remove(2);
                Player[player].Hero_in_shop[2] = "";
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
            MyHero* newHero = set_a_hero(Player[player], Player[player].Hero_in_shop[3], Player[player].Hero_in_shop, Player[player].Hero_on_bench, this);

            if (newHero) {
                // 设置位置
                if (newHero->sprite) {
                    newHero->sprite->setPosition(my_bench_px(Player[player].Hero_on_bench.size()));

                    // 将 Sprite 添加到层中
                    this->addChild(newHero->sprite);
                    Player[player].Hero_on_bench.push_back(*newHero);
                }

                // 移除商店中的卡片
                card_remove(3);
                Player[player].Hero_in_shop[3] = "";
            }
        });
    auto menu4 = Menu::create(HeroCard4, NULL);
    menu4->setTag(4);
    menu4->setContentSize(targetSize);
    menu4->setPosition(card_px(3));
    this->addChild(menu4);
}

<<<<<<< .merge_file_ROi2Rm
=======
void PrepareLayer::update(float dt)
{
    // 获取MySprite类中的信息
    int currentExp = Player[player].getexp();
    int currentMoney = Player[player].getmoney();
    int starLevel = Player[player].getlevel();

    // 更新标签内容
    expLabel->setString(StringUtils::format("Exp: %d", currentExp));
    moneyLabel->setString(StringUtils::format("Money: %d", currentMoney));
    levelLabel->setString(StringUtils::format("Level: %d", starLevel));
}
>>>>>>> .merge_file_qzgphL
