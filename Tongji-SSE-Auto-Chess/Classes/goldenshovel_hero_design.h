//goldenshovel_hero_design.h
#pragma once
#include<iostream>
#include"HelloWorldScene.h"
#include<vector>
#include "cocos2d.h"
#include "PopupManager.h"

using namespace cocos2d;

USING_NS_CC;

using namespace std;
#define plaid 137
#define max_hero_on_bench 9

#define Fight_MAP_height 520
#define Fight_MAP_width 660

#define attack_ace 1    //攻击性大招
#define treat_ace 2     //治疗型大招

#define map_width 8
#define map_height 6

#define MAX_LEVEL 7

#define ON_BENCH 0
#define FIGHTING 1
#define ON_COURT 2

#define ME       0
#define ENEMY    1

#define Fighting 0
#define GameOver 1

#define HERO_BAR_LENGTH 145
#define SPRITE_BAR_LENGTH 130
#define BAR_HEIGHT 20
#define RED_TAG  0
#define BLUE_TAG 1
#define HERO 10
#define MY_SPRITE    11
#define ENEMY_SPRITE 12

#define    AI 0
#define HUMAN 1

#define SpriteSize Size(177,207)
#define HeroSize   Size(127,150)
#define BulletSize Size(37,37)

#define refresh_button Vec2(498,335)
#define buyexp_button Vec2(498,218)

#define player1_px Vec2(418,774)
#define player2_px Vec2(1895,1455)

#define platform1_px Vec2(418,654)
#define platform2_px Vec2(1895,1335)

class MyHero;
class Equipment;
class MySprite;

extern MyHero* GameMap[map_width][map_height];

/*====================基类====================*/
//注意：该基类为抽象基类，不可直接生成对象
class MyObject {
public:
	MyObject() {};
	MyObject(int hp,/* int xp, int av,*/ int x = -1, int y = -1) :      // 构造函数
		current_hp(hp), location_x(x), location_y(y)
	{
		full_hp = current_hp;
	};

	vector<Equipment> equipment;
	Sprite* sprite;
	int gethp() { return this->current_hp; };     // 指针

	int location_x;			                      // 横坐标
	int location_y;                               // 纵坐标

	int full_hp;                                  // 满血
	int current_hp;                               // 当前血量
};


/*====================英雄类====================*/
class MyHero : public MyObject {
	friend class BattleLayer;
	friend class PrepareLayer;
	friend class PlayeWithAI;
public:
	string name;
	MyHero() {};
	MyHero(int on_court, int gold_cost, int star_level, int attack_power, int ace_attack_power,
		int needed_cooldown_round, int current_cooldown_round, int attack_distance, double attack_cd,
		int hp, int x = -1, int y = -1) : // 构造函数
		MyObject(hp, x, y),
		on_court(on_court), gold_cost(gold_cost), star_level(star_level), attack_power(attack_power), ace_attack_power(ace_attack_power),
		needed_cooldown_round(needed_cooldown_round), current_cooldown_round(current_cooldown_round), attack_distance(attack_distance),
		attack_cd(attack_cd) {};
	inline void seek_enemy(vector<MyHero>& enemy_vec);                       // 索敌函数
	inline void hero_ultimate(int ace_mode);                       // 大招函数
	int getcost() { return this->gold_cost; };
	void decreasehp() { this->current_hp -= 100; };
	int getcurrent_hp() { return current_hp; }
	void increase_hp(int hp) { this->full_hp += hp; }
	void increase_attack(int attack) { this->attack_power += attack; }
	bool enemyInDistance();
	MySprite* get_owner() { return this->owner; }
	MyHero* current_enemy = nullptr;

private:
	MySprite* owner;
	bool on_court;                     // 判断是否在场
	int gold_cost;                     // 英雄花费 
	int star_level;                    // 星级
	int attack_power;                  // 攻击力
	int ace_attack_power;              // 大招攻击力
	int needed_cooldown_round;         // 大招所需冷却轮数
	int current_cooldown_round;        // 当前冷却轮数
	double attack_cd;                  // 攻击cd
	int attack_distance;               // 攻击距离

	inline BOOL IsInMap(int x, int y); // 坐标判断
	inline void Find_Way_To_attack(int X, int Y, int& HX, int& HY, int distance); // 索敌
};
inline BOOL IsInMap(int x, int y) {
	if (x < map_width && x >= 0 && y < map_height && y >= 0) {
		return 1;
	}
	return 0;
}

inline void Find_Way_To_attack(int X, int Y, int& HX, int& HY, int distance) {
	int deltaX = X - HX;
	int deltaY = Y - HY;

	// 计算对角线距离
	int distanceToTarget = std::max(std::abs(deltaX), std::abs(deltaY));

	if (distanceToTarget <= distance) {
		// 如果当前距离已经小于等于攻击距离，无需移动
		return;
	}

	// 计算插值比例
	float t = static_cast<float>(distance) / distanceToTarget;

	// 使用插值计算新的位置
	HX = static_cast<int>(HX + t * deltaX);
	HY = static_cast<int>(HY + t * deltaY);
}

inline void MyHero::seek_enemy(vector<MyHero>& enemy_vec) {
	vector<float> distance_vec;
	if (current_enemy == NULL)              // 无攻击目标时进行索敌
	{
		for (int index = 0; index < enemy_vec.size(); index++)
		{
			float distance_x = sprite->getPositionX() - enemy_vec[index].sprite->getPositionX();
			float distance_y = sprite->getPositionY() - enemy_vec[index].sprite->getPositionY();
			float distance = distance_x * distance_x + distance_y * distance_y;
			distance_vec.push_back(distance);
		}
		// 使用 std::min_element 找到 vector 中的最小值的迭代器
		auto minElementIterator = min_element(distance_vec.begin(), distance_vec.end());
		// 获取最小值的下标
		size_t minIndex = distance(distance_vec.begin(), minElementIterator);
		current_enemy = &enemy_vec[minIndex];
	}
}

inline void MyHero::hero_ultimate(int ace_mode)                        // 大招函数
{
	if (current_enemy == NULL) {
		return;
		//seek_enemy();  //调用索敌函数
	}
	//this->Sprite->perform_ace();//释放大招的动画，如果有
	if (ace_mode == attack_ace)
	{
		if (!(ace_attack_power < current_enemy->current_hp)) {  //直接击杀
			current_enemy->current_hp = 0;
			//attacking_hero->sprite->minus_hp_animation();//掉血条动画
		}
		else {      //未直接击杀
			current_enemy->current_hp -= ace_attack_power;
			//attacking_hero->sprite->minus_hp_animation();//掉血条动画
		}
	}
	else if (ace_mode == treat_ace) {
		if (ace_attack_power < (current_enemy->full_hp - current_hp)) {     //回满血
			current_enemy->current_hp += ace_attack_power;
			//attacking_hero->sprite->add_hp_animation();//回血条动画
		}
		else {      //不够回满血
			current_enemy->current_hp = full_hp;
			//attacking_hero->sprite->add_hp_animation();//回血条动画
		}
	}
}

class MySprite;
extern vector<MySprite> Player;
extern std::map<std::string, MyHero> Hero_list;
extern int Posibility_Of_Hero[MAX_LEVEL][5];
extern string one_fee[4];
extern string two_fee[4];
extern string three_fee[4];
extern string four_fee[4];
extern string five_fee[4];
extern int level_up_exp[6];


/*====================精灵类====================*/
class MySprite :public MyObject {
	friend class BattleLayer;
	friend class PrepareLayer;
	friend class PrepareScene;
	friend class PlayWithAI;
	friend class SelectModeScene;
	friend class HelloWorld;
public:
	MySprite() {};
	MySprite(int level, int hp, int money, int x = -1, int y = -1) :        // 构造函数
		MyObject(hp/*, xp, av*/, x, y), star_level(level), current_exp(0), money(money) {};
	//virtual void my_move(int new_x, int new_y);                                  // 移动函数

	bool operator==(const MySprite& other) const {
		// 在这里判断两个 MySprite 对象是否相等
		return this->location_x == other.location_x && this->location_y == other.location_y;
	}
	inline int  getlevel() { return this->star_level; }
	inline int  getexp() { return this->current_exp; }
	inline void increaseexp(int i) { this->current_exp += i; }
	inline void decreasemoney(int x) { this->money -= x; }
	inline int  getmoney() { return this->money; }
	inline void refresh_shop_free();
	inline void refresh_shop(cocos2d::Layer* parentLayer);//刷新商店英雄
	inline void make_a_random_hero();   //补充商店英雄
	inline void erase_a_player();//删除死了个玩家
	inline void set_a_hero(string hero_name);//将一个英雄从商店选出
	inline void level_up() { if (this->current_exp >= level_up_exp[this->star_level - 1] && this->star_level < MAX_LEVEL) { this->current_exp = 0; this->star_level++; } }//小小英雄升级判断
	inline void copy();//将court上的英雄复制到fighting上
	inline void RecoverData();//恢复数据便于进行下一次游戏
	int MAP[8][3] = { 0 };//判断位置是否被占用
private:
	int star_level;     // 星级
	int max_hero = star_level + 2;//最多英雄人数
	int money;          //当前的钱数
	vector<MyHero> Hero_on_court;//当前所拥有的英雄（在场上的）
	vector<MyHero> Hero_on_bench;//当前备战席上的英雄
	vector<MyHero> Hero_fighting;//战斗时用于存放英雄的临时空间
	vector<MyHero> Hero_benching;//用于存放备战席英雄的临时空间
	string Hero_in_shop[4];      //商店中的英雄
	MySprite* current_enemy;
	int current_exp;    //当前有的经验值
	int Operator;       //操作者为AI或人类
};



inline void MySprite::erase_a_player() {
	auto it = std::find(Player.begin(), Player.end(), *this);

	// 检查是否找到当前对象
	if (it != Player.end() && it->gethp() == 0) {
		// 使用迭代器删除元素
		Player.erase(it);
	}
}
inline void MySprite::make_a_random_hero() {
	int i;
	string hero_compose[100];

	for (i = 0; i < Posibility_Of_Hero[this->star_level - 1][0]; i++)
		hero_compose[i] = one_fee[int(rand() % 4)];
	for (; i < Posibility_Of_Hero[this->star_level - 1][0] + Posibility_Of_Hero[this->star_level - 1][1]; i++)
		hero_compose[i] = two_fee[int(rand() % 4)];
	for (; i < Posibility_Of_Hero[this->star_level - 1][0] + Posibility_Of_Hero[this->star_level - 1][1] + Posibility_Of_Hero[this->star_level - 1][2]; i++)
		hero_compose[i] = three_fee[int(rand() % 4)];
	for (; i < Posibility_Of_Hero[this->star_level - 1][4] + Posibility_Of_Hero[this->star_level - 1][2] + Posibility_Of_Hero[this->star_level - 1][3] + Posibility_Of_Hero[this->star_level - 1][0]; i++)
		hero_compose[i] = four_fee[int(rand() % 4)];
	for (; i < 100; i++)
		hero_compose[i] = five_fee[int(rand() % 4)];

	for (i = 0; i < 4; i++) {
		if (this->Hero_in_shop[i] == "") {
			this->Hero_in_shop[i] = hero_compose[int(rand() % 100)];
			CCLOG("Player[].Hero_in_shop[%d]: %s", i, this->Hero_in_shop[i].c_str());
		}
	}
}



inline void MySprite::refresh_shop_free() {
	for (int i = 0; i < 4; i++) {
		this->Hero_in_shop[i] = "";
	}
	make_a_random_hero();
}

inline void MySprite::refresh_shop(cocos2d::Layer* parentLayer) {
	if (this->money < 2) {
		CCLOG("Money_left%d", this->money);
		PopupManager::displayPopup(parentLayer, "No enough Money to refresh the shop");

	}
	else {
		this->money -= 2;//刷新扣除金额
		for (int i = 0; i < 4; i++) {
			this->Hero_in_shop[i] = "";
		}
		make_a_random_hero();
	}
}

inline int getHeroCost(const string& heroName) {
	for (const auto& hero : one_fee) {
		if (hero == heroName) {
			return 1;
		}
	}
	for (const auto& hero : two_fee) {
		if (hero == heroName) {
			return 2;
		}
	}
	for (const auto& hero : three_fee) {
		if (hero == heroName) {
			return 3;
		}
	}
	for (const auto& hero : four_fee) {
		if (hero == heroName) {
			return 4;
		}
	}
	for (const auto& hero : five_fee) {
		if (hero == heroName) {
			return 5;
		}
	}
	return 0;
}

inline void attribute(Sprite* mySprite, int length, int object) // 血量与蓝条的展示
{
	auto grey1 = Sprite::create("grey_bar.png");
	auto grey2 = Sprite::create("grey_bar.png");
	auto red = Sprite::create("red_bar.png");
	auto blue = Sprite::create("blue_bar.png");
	grey1->setAnchorPoint(Vec2(0, 0));
	grey2->setAnchorPoint(Vec2(0, 0));
	red->setAnchorPoint(Vec2(0, 0));
	blue->setAnchorPoint(Vec2(0, 0));
	cocos2d::Size targetSize(length, BAR_HEIGHT); // 调整血条的大小
	grey1->setContentSize(targetSize);
	grey2->setContentSize(targetSize);
	red->setContentSize(targetSize);
	blue->setContentSize(targetSize);
	grey1->setPosition(mySprite->getPosition() + Vec2(0, mySprite->getContentSize().height + BAR_HEIGHT));
	if (object == HERO)
		red->setPosition(mySprite->getPosition() + Vec2(0, mySprite->getContentSize().height + BAR_HEIGHT));
	else
		red->setPosition(mySprite->getPosition() + Vec2(0, mySprite->getContentSize().height));
	grey2->setPosition(mySprite->getPosition() + Vec2(0, mySprite->getContentSize().height));
	blue->setPosition(mySprite->getPosition() + Vec2(0, mySprite->getContentSize().height));
	cocos2d::Size red_targetSize(length, BAR_HEIGHT);
	cocos2d::Size blue_targetSize(length, BAR_HEIGHT);
	red->setContentSize(red_targetSize);
	blue->setContentSize(blue_targetSize);

	if (object == HERO) {
		mySprite->addChild(grey1);
		mySprite->addChild(grey2);
		mySprite->addChild(red, 1, RED_TAG);
		mySprite->addChild(blue, 1, BLUE_TAG);
	}
	else {
		mySprite->addChild(red, 1, RED_TAG);
		mySprite->addChild(grey2);
	}
}

inline MyHero* set_a_hero(MySprite& player, string hero_name, string Hero_in_shop[], vector<MyHero>& Hero, cocos2d::Layer* parentLayer) {

	// 扣钱
	int i = getHeroCost(hero_name);
	if (player.getmoney() < i) {
		PopupManager::displayPopup(parentLayer, "No enough Money to buy the hero");
		return nullptr;
	}
	else if (Hero.size() >= max_hero_on_bench) {
		PopupManager::displayPopup(parentLayer, "Too much Hero on bench");
		return nullptr;
	}
	else {

		CCLOG("decreasemoney %d", i);

		player.decreasemoney(i);
		CCLOG("money %d", player.getmoney());

		string filename = hero_name + "1.png";

		// 分配在堆上
		MyHero* set_a_new_hero = new MyHero(Hero_list.at(hero_name));

		set_a_new_hero->name = hero_name;

		auto new_hero_Sprite = Sprite::create(filename);

		new_hero_Sprite->setContentSize(HeroSize);

		attribute(new_hero_Sprite, HERO_BAR_LENGTH, HERO);//红蓝条加入子节点

		set_a_new_hero->sprite = new_hero_Sprite;

		// 可视化，并给position赋值

		return set_a_new_hero;
	}
}

inline MyHero* set_a_hero(string hero_name, int X, int Y) {

	string filename = hero_name + "1.png";

	MyHero* set_a_new_hero = new MyHero(Hero_list.at(hero_name));

	set_a_new_hero->name = hero_name;

	auto new_hero_Sprite = Sprite::create(filename);

	new_hero_Sprite->setContentSize(HeroSize);

	attribute(new_hero_Sprite, HERO_BAR_LENGTH, HERO);//红蓝条加入子节点

	set_a_new_hero->sprite = new_hero_Sprite;

	// 可视化，并给position赋值
	set_a_new_hero->location_x = X;
	set_a_new_hero->location_y = Y;

	return set_a_new_hero;

}

inline void MySprite::copy()
{
	Hero_fighting.clear();
	for (int i = 0; i < Hero_on_court.size(); i++) {
		Hero_fighting.push_back(Hero_on_court[i]);
	}
	Hero_benching.clear();
	for (int i = 0; i < Hero_on_bench.size(); i++) {
		//Hero_benching.push_back(Hero_on_bench[i]);
	}
}

inline void MySprite::RecoverData()
{
	current_hp = full_hp;
	current_exp = 0;
	money = 5;
	star_level = 1;
	Hero_on_bench.clear();
	Hero_on_court.clear();
}

class Equipment {
public:
	Equipment(int turn_up_hp, int turn_up_attack) :turn_up_hp(turn_up_hp), turn_up_attack(turn_up_attack) {};
	void Equip_on() {
		if (MyHero* Hero_equiping = dynamic_cast<MyHero*>(Hero_equiping)) {
			Hero_equiping->increase_hp(turn_up_hp);
			Hero_equiping->increase_attack(turn_up_attack);
		}
	}
private:
	MyObject* Hero_equiping;
	int turn_up_hp;
	int turn_up_attack;
	cocos2d::Sprite* equip_pic;
};

extern std::map<std::string, Equipment> Equipment_list;

inline Vec2 reverse_map_px(int x, int y, int camp) {
	Vec2 pos;
	int X, Y;
	if (camp == ME)
		X = x, Y = y;
	else if (camp == ENEMY)
		X = 7 - x, Y = 5 - y;

	pos.x = plaid / 2 + plaid * X + Fight_MAP_width;
	pos.y = plaid / 2 + plaid * Y + Fight_MAP_height;
	return pos;
}

inline Vec2 my_bench_px(int i)
{
	float x = 510 + i * 168;
	float y = 465;
	return Vec2(x, y);
}

inline Vec2 enemy_bench_px(int i)
{
	float x = 1774 - i * 125;
	float y = 1375;
	return Vec2(x, y);
}

inline Vec2 card_px(int i)
{
	float x = 770 + i * 340;
	float y = 250;
	return Vec2(x, y);
}

inline int reverse_x(float x)
{
	return (x - Fight_MAP_width) / plaid;
}
inline int reverse_y(float y)
{
	return (y - Fight_MAP_height) / plaid;
}
inline bool ifInMap(Vec2 pos)
{
	return (pos.x >= Fight_MAP_width && pos.x <= Fight_MAP_width + 8 * plaid) &&
		(pos.y >= Fight_MAP_height && pos.y <= Fight_MAP_height + 3 * plaid);
}
inline bool ifInBench(Vec2 pos)
{
	float x1 = 510 - 84;
	float x2 = 510 + 9 * 168;
	float y1 = 465 - 84;
	float y2 = 465 + 84;
	float x = pos.x;
	float y = pos.y;
	return (x >= x1 && x <= x2) && (y >= y1 && y <= y2);
}
inline bool ifInWholeMap(Vec2 pos)
{
	return (pos.x >= Fight_MAP_width - plaid && pos.x <= Fight_MAP_width + 9 * plaid) &&
		(pos.y >= Fight_MAP_height && pos.y <= Fight_MAP_height + 6 * plaid);
}
inline bool ifHasHero(Vec2 pos, MySprite& my)
{
	return my.MAP[reverse_x(pos.x)][reverse_y(pos.y)] == 1;
}
