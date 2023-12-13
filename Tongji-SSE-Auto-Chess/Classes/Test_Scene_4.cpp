#include "Test.h"
#include <goldenshovel_hero_design.h>
using namespace std;

#define plaid_width 256
#define plaid_height 200
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
/*从这里开始注释，到最后一行结束
vector <goldenshovel_hero> Hero_on_court_1;
vector <goldenshovel_hero> Hero_on_court_2;
vector <goldenshovel_hero> Hero_select_1;
vector <goldenshovel_hero> Hero_select_2;

//数组大小代表随机刷新的商店个数
string Hero_1[5];
string Hero_2[5];
vector <cocos2d::Sprite*> Sprite_on_court_1;
vector <cocos2d::Sprite*> Sprite_on_court_2;
vector <cocos2d::Sprite*> Sprite_select_1;
vector <cocos2d::Sprite*> Sprite_select_2;

//刷新商店英雄
void make_a_random_hero(int fee[], string Hero_in_shop[]) {
    int i;
    string hero_compose[100];
    for (i = 0; i < fee[1]; i++) {
        //one_fee暂时代表一费英雄池
        //hero_compose[i] = one_fee[std::rand() % sizeof(one_fee) + 1];
    }
    for (; i < fee[1]+fee[2]; i++) {
        //同
    }
    for (; i < fee[1] + fee[2]+fee[3]; i++) {
        //同
    }
    for (; i < fee[1] + fee[2] + fee[3] +fee[4]; i++) {
        //同
    }
    for (; i < fee[1] + fee[2] + fee[3] + fee[4] +fee[5]; i++) {
        //同
    }
    for (int i = 0; i < 5; i++) {
        if (Hero_in_shop[i] == "") {
            Hero_in_shop[i] = hero_compose[std::rand() % 100 + 1];
        }
    }
}


//将一个新英雄从商店中选出
void set_a_hero(string hero_name, string Hero_in_shop[], vector<goldenshovel_hero>& Hero, vector<cocos2d::Sprite*>& Sprite_set) {
    for (int i = 0; i < 5; i++) {
        if (Hero_in_shop[i] == hero_name) {
            Hero_in_shop[i] = "";
        }
    }
    //扣钱

    string filename = hero_name + ".png";
    //goldenshovel_hero set_a_new_hero; 此处报错原因未知
    //缺少new_hero赋值
    auto new_hero_Sprite = Sprite::create(filename);
    //缺少放置
    //Hero.push_back(set_a_new_hero);
    Sprite_set.push_back(new_hero_Sprite);
    //可视化，并给position赋值


}

//英雄索敌
void Seek_the_enemy(goldenshovel_hero hero, vector <goldenshovel_hero>& Hero_on_court, vector <cocos2d::Sprite*>& Sprite_on_court) {
    BOOL find;
    int distance = 1;
    int i;
    int j;
    while (find) {
        for (i = -1; i < 1; i++) {
            for (j = -1; j < 1; j++) {
                if (i == 0 && j == 0) continue;
                if (hero.location_x + distance * i * plaid_width, hero.location_y + j * distance * plaid_height)//这段应该是判断这个像素上有英雄，没写完整
                {
                    hero.attacking_hero = &hero;//此处第二个hero应该改成上面找到的这个英雄
                    find = 1;
                    break;
                }
                if (find == 1)
                    break;
            }
        }
        distance++;
    }
    if (distance > hero.attack_distance) {
        vector<goldenshovel_hero>::iterator it = Hero_on_court.begin();
        for (; it != Hero_on_court.end(); ++it);
        int num = it - Hero_on_court.end();
        Hero_on_court[num].location_x = hero.location_x + (distance - hero.attack_distance) * i * plaid_width, hero.location_y + j * plaid_height * (distance - hero.attack_distance);
        //设计moveby和moveto，还没写
        Sprite_on_court[num];
    }
}


void Test_Scene_4()
{

    auto myScene = Scene::create();//创建新场景
    Director::getInstance()->pushScene(myScene);//将当前运行中的场景暂停并压入到场景栈中，并将传入的场景设置为当前运行场景

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
        myScene->addChild(fight_map, 0);
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
    myScene->addChild(exitMenu, 1);
}*/