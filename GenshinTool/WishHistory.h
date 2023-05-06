#pragma once

#define ITEM_TYPE_PERSON 0
#define ITEM_TYPE_WEAPON 1

#include <string>
#include <vector>

using namespace std;

class WishHistory
{
private:
	vector<unsigned int> num;
	vector<string> item;
	vector<int> type;
	vector<short> star;

public:
	void add(unsigned int num, string item, int type, short star);
	void clearFirst();
	void clear();
	void clear(unsigned int startPos, unsigned int endPos);

	WishHistory cut(unsigned int pos);
	WishHistory cut(unsigned int startPos, unsigned int endPos);
	WishHistory cutFinal();

	unsigned int findPos(unsigned int num);

	unsigned int getLength();
	unsigned int getNum(unsigned int pos);
	string getItem(unsigned int pos);
	int getType(unsigned int pos);
	short getStar(unsigned int pos);
};