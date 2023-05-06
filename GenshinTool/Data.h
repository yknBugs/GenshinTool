#pragma once

#include <string>
#include "Option.h"

using namespace std;

class Data
{
private:
	vector<string> star3Item;		//������Ʒ
	vector<string> star4Person;		//���ǽ�ɫ
	vector<string> star4Weapon;		//��������
	vector<string> star5Person;		//���ǽ�ɫ
	vector<string> star5Weapon;		//��������
	vector<string> star4UpWeapon;	//����up����
	vector<string> star5UpWeapon;	//����up����
	vector<vector<string>> star4UpPerson;	//����up��ɫ�����Ϊ�������
	vector<string> star4NoPerson;	//����up�ز����ֵĳ�פ��ɫ
	vector<vector<string>> star5UpPerson;	//����up��ɫ�����Ϊ�������

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