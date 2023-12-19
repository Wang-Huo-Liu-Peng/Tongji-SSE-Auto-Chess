#include "HelloWorldScene.h"
#include "Test_Scene_4.h"
#include "goldenshovel_hero_design.h" 
using namespace std;

#define plaid_width 256
#define plaid_height 200

USING_NS_CC;

Scene* Test_Scene_4::createScene()
{
    return Test_Scene_4::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}



//刷新商店英雄
void make_a_random_hero(int fee[], string Hero_in_shop[]) {
    int i;
    string hero_compose[100];
    for (i = 0; i < fee[1]; i++) {
        //one_fee暂时代表一费英雄池
        hero_compose[i] = one_fee[std::rand() % sizeof(one_fee) + 1];
    }
    for (; i < fee[1]+fee[2]; i++) {
        //同
        hero_compose[i] = two_fee[std::rand() % sizeof(two_fee) + 1];
    }
    for (; i < fee[1] + fee[2]+fee[3]; i++) {
        //同
        hero_compose[i] = three_fee[std::rand() % sizeof(three_fee) + 1];
    }
    for (; i < fee[1] + fee[2] + fee[3] +fee[4]; i++) {
        //同
        hero_compose[i] = four_fee[std::rand() % sizeof(four_fee) + 1];
    }
    for (; i < fee[1] + fee[2] + fee[3] + fee[4] +fee[5]; i++) {
        //同
        hero_compose[i] = five_fee[std::rand() % sizeof(five_fee) + 1];
    }
    for (int i = 0; i < 5; i++) {
        if (Hero_in_shop[i] == "") {
            Hero_in_shop[i] = hero_compose[std::rand() % 100 + 1];
        }
    }
}


//将一个新英雄从商店中选出
MyHero set_a_hero(string hero_name, string Hero_in_shop[], vector<MyHero>& Hero) {
    for (int i = 0; i < 5; i++) {
        if (Hero_in_shop[i] == hero_name) {
            Hero_in_shop[i] = "";
        }
    }

    //扣钱

    string filename = hero_name + ".png";
    MyHero set_a_new_hero= Hero_list.at(hero_name);
    Hero.push_back(set_a_new_hero);
    auto new_hero_Sprite = Sprite::create(filename);
    set_a_new_hero.sprite = new_hero_Sprite;

    Hero.push_back(set_a_new_hero);
    //可视化，并给position赋值

    return set_a_new_hero;
}



bool Test_Scene_4::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //以下为你的测试代码（场景为myScene）
    auto fight_map = Sprite::create("fight_map.png");
    if (fight_map == nullptr)
    {
        problemLoading("'fight_map.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        fight_map->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(fight_map, 0);
    }

    //添加新英雄
    {
        Hero_1[1] = "Annie";
        MyHero new_hero;
        new_hero=set_a_hero("Annie", Hero_1, Hero_on_court_1);
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
        if(new_hero_2.gethp() == 0) {
            this->removeChild(new_hero_2.sprite, true);
        }
    }
    
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

void Test_Scene_4::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}