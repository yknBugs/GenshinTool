#pragma once

#include <string>
#include "Option.h"

using namespace std;

class Data
{
private:
	vector<string> star3Item;		//三星物品
	vector<string> star4Person;		//四星角色
	vector<string> star4Weapon;		//四星武器
	vector<string> star5Person;		//五星角色
	vector<string> star5Weapon;		//五星武器
	vector<string> star4UpWeapon;	//四星up武器
	vector<string> star5UpWeapon;	//五星up武器
	vector<vector<string>> star4UpPerson;	//四星up角色，外层为卡池序号
	vector<string> star4NoPerson;	//四星up池不出现的常驻角色
	vector<vector<string>> star5UpPerson;	//五星up角色，外层为卡池序号

public:
	Data();

	vector<string> getArtifactHouseList();
	vector<string> getArtifactCraftList();
	vector<vector<string>> getArtifactsList(short star = 5);
	vector<string> getArtifactList(string listName);

	vector<string> getLimitWishList(short star, bool isLocal = true, int style = 0, int poolId = 1);
	vector<string> getWeaponWishList(short star, bool isLocal = true, int style = 1, int poolId = 1);
	vector<string> getStayWishList(short star, int style = 0);
	vector<string> getFirstWishList(short star);

	vector<string> getItemList(short star, int style = 0);

	unsigned int getLimitWishCount();

	string readText(string fileName, string textName);
	string openFile(string path);
};