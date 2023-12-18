#pragma once
#include"HelloWorldScene.h"
#include "cocos2d.h"
#include "goldenshovel_hero_design.h"
#include <map>
#include <string>
using namespace std;

map<string, MyHero> Hero_list;
int main() {
	//²Î¿¼ÍøÕ¾ https://tftactics.gg/champions  https://lol.qq.com/tft/#/champion
	//°²ÄÝ https://lol.qq.com/tft/#/championDetail/1
	MyHero Annie(0, 1, 1, 40, 70, 7, 0, 4, 0.7, 500, -1, -1);
	Hero_list["Annie"] = Annie;
	//¿âÆæ https://lol.qq.com/tft/#/championDetail/42
	MyHero Corki(0, 1, 1, 48, 80, 8, 0, 4, 0.7, 450, -1, -1);
	Hero_list["Corki"] = Corki;
	//ËþÀï¿Ë https://lol.qq.com/tft/#/championDetail/44
	MyHero Taric(0, 1, 1, 55, 60, 12, 0, 1, 0.55, 650, -1, -1);
	Hero_list["Taric"] = Taric;
	//ÒÁÜ½ÁÕ https://lol.qq.com/tft/#/championDetail/12
	MyHero Evelynn(0, 1, 1, 45, 60, 12, 0, 1, 0.7, 550, -1, -1);
	Hero_list["Evelynn"] = Evelynn;
	MyHero one_fee[4] = { Annie,Corki,Taric,Evelynn };

	//¿­¶û
	MyHero Kayle(0, 2, 1, 35, 100, 12, 0, 3, 0.75, 550, -1, -1);
	Hero_list["Kayle"] = Kayle;
	//¸ÇÂ×
	MyHero Garen(0, 2, 1, 55, 90, 12, 0, 1, 0.7, 750, -1, -1);
	Hero_list["Garen"] = Garen;
	//ÀÏÊó
	MyHero Twitch(0, 2, 1, 50, 100, 12, 0, 5, 0.7, 550, -1, -1);
	Hero_list["Twitch"] = Twitch;
	//ÈûÄÉ
	MyHero Senna(0, 2, 1, 40, 80, 12, 0, 6, 0.7, 600, -1, -1);
	Hero_list["Senna"] = Senna;
	MyHero two_fee[4] = { Kayle,Garen,Twitch,Senna };

	//°¢Ä¾Ä¾ https://tftactics.gg/champions/amumu
	MyHero Amumu(0, 3, 1, 45, 100, 12, 0, 1, 0.65, 550, -1, -1);
	Hero_list["Amumu"] = Amumu;
	//Â¬¿¨Ë¹ https://tftactics.gg/champions/lux
	MyHero Lux(0, 3, 1, 40, 100, 12, 0, 4, 0.7, 700, -1, -1);
	Hero_list["Lux"] = Lux;
	//ÈûÃ×¶û https://tftactics.gg/champions/samira
	MyHero Samira(0, 3, 1, 60, 100, 12, 0, 4, 0.7, 600, -1, -1);
	Hero_list["Samira"] = Samira;
	//Äá¿Ë https://tftactics.gg/champions/neeko
	MyHero Neeko(0, 3, 1, 50, 100, 12, 0, 4, 0.6, 850, -1, -1);
	Hero_list["Neeko"] = Neeko;
	MyHero three_fee[4] = { Amumu,Lux,Samira,Neeko };


	return 0;
}