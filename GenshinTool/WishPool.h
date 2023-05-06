#pragma once

#include <string>
#include <vector>

#include "WishHistory.h"
#include "RandEngine.h"
#include "PwFunction.h"

using namespace std;

class WishPool
{
private:
	WishHistory history; //历史记录
	string name; //卡池名称
	unsigned int num; //总抽数

	vector<string> star5Choose;  //定轨的5星物品

	bool hasChoose; //有无定轨保底
	bool hasUp; //有无大保底
	int upItemType; //up物品类型

	//计算下一抽出货概率并随机出一种星级
	short randStar();
	//随机一个3星物品
	void randStar3Item(string* item, int* style);
	//随机一个定轨的物品
	bool randChooseItem(string* item, int* style);
	//歪没歪
	bool randIs5UpItem();
	bool randIs4UpItem();
	//出货类型
	int randStar5Style();
	int randStar4Style();
	//随机一个up物品
	void randStar5UpItem(string* item, int* style);
	void randStar4UpItem(string* item, int* style);
	//随机一个常驻物品
	void randStar5BasePerson(string* item, int* style);
	void randStar5BaseWeapon(string* item, int* style);
	void randStar4BasePerson(string* item, int* style);
	void randStar4BaseWeapon(string* item, int* style);
	//判断是否定轨的物品
	bool isChooseItem(string item);

public:
	vector<string> star3;
	vector<string> star4Person;
	vector<string> star4Weapon;
	vector<string> star5Person;
	vector<string> star5Weapon;
	vector<string> star4Up;
	vector<string> star5Up;

	vector<unsigned int> star4Guar; //4星保底计数[未出抽数、角色抽数、武器抽数、歪与否]
	vector<unsigned int> star5Guar; //5星保底计数[未出抽数、角色抽数、武器抽数、歪与否、定轨]

	vector<PwFunction> star4Function; //4星出货保底计算函数[未出抽数、角色抽数、武器抽数、歪与否]
	vector<PwFunction> star5Function; //5星出货保底计算函数[未出抽数、角色抽数、武器抽数、歪与否、定轨]

	WishPool(string name = "祈愿", bool hasUp = false, bool hasChoose = false);

	void setBaseItem(vector<string> star3, vector<string> star4Person, vector<string> star4Weapon);
	void setUpItem(vector<string> star4Up, vector<string> star5Up, int upItemType);
	void setStar5Person(vector<string> star5Person);
	void setStar5Weapon(vector<string> star5Weapon);
	void setTemplatePby(int id);  //以预设好的模板设置出货概率[id:1为限定角色，2为武器，3为常驻]
	void clearHistory();  //清除历史记录
	void resetPool();  //重置卡池

	vector<string> getStar5Choose();
	string getPoolName();
	int getUpItemType();

	WishHistory getHistory();
	WishHistory getLastItem();
	WishHistory getLastNItem(int endPos);
	WishHistory getLast10Item();
	WishHistory getCenterItem(int startPos, int endPos);
	short getLast10MaxStar();
	short getLastNMaxStar(unsigned int n);

	void setStar5Choose(vector<string> item); //定轨
	WishHistory singleWish(); //单抽
	WishHistory templeWish(); //十连抽
	WishHistory nWish(unsigned int n); //n连抽
};