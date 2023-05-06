#include "WishPool.h"

short WishPool::randStar()
{
	RandEngine ran;
	double star5P = this->star5Function[0].setX(this->star5Guar[0] + 1);
	double star4P = this->star4Function[0].setX(this->star4Guar[0] + 1);
	double temp = ran.ran();
	if (temp < star5P)
	{
		return 5;
	}
	else if (temp < star5P + star4P)
	{
		return 4;
	}
	else
	{
		return 3;
	}
}

void WishPool::randStar3Item(string* item, int* style)
{
	unsigned int i = 0;
	RandEngine ran;
	unsigned int temp = (unsigned int)ran.random(0, (int)this->star3.size() - 1);
	*item = this->star3[temp];
	*style = ITEM_TYPE_WEAPON;
	for (i = 0; i < 3; i++)
	{
		this->star4Guar[i]++;
		this->star5Guar[i]++;
	}
}

bool WishPool::randChooseItem(string* item, int* style)
{
	if (this->hasChoose == false)
	{
		return false;
	}
	if (this->star5Choose[0] == "取消定轨")
	{
		return false;
	}

	RandEngine ran;
	double chooseP = this->star5Function[4].setX(this->star5Guar[4] + 1);
	double temp = ran.ran();
	if (temp < chooseP)
	{
		unsigned int tempI = (unsigned int)ran.random(0, (int)this->star5Choose.size() - 1);
		*item = this->star5Choose[tempI];
		*style = this->upItemType;
		this->star5Guar[4] = 0; //命定值清零
		this->star5Guar[3] = 0; //设置为没歪
		this->star5Guar[0] = 0; //5星保底进度清零
		if (this->upItemType == ITEM_TYPE_WEAPON)
		{
			this->star5Guar[1]++;
			this->star5Guar[2] = 0;
		}
		else if (this->upItemType == ITEM_TYPE_PERSON)
		{
			this->star5Guar[1] = 0;
			this->star5Guar[2]++;
		}
		this->star4Guar[0]++;
		this->star4Guar[1]++;
		this->star4Guar[2]++;
		return true;
	}
	return false;
}

bool WishPool::randIs5UpItem()
{
	if (this->hasUp == false)
	{
		return false;
	}

	RandEngine ran;
	double upItemP = this->star5Function[3].setX(this->star5Guar[3] + 1);
	double temp = ran.ran();
	if (temp < upItemP)
	{
		return true;
	}
	return false;
}

bool WishPool::randIs4UpItem()
{
	if (this->hasUp == false)
	{
		return false;
	}

	RandEngine ran;
	double upItemP = this->star4Function[3].setX(this->star4Guar[3] + 1);
	double temp = ran.ran();
	if (temp < upItemP)
	{
		return true;
	}
	return false;
}

int WishPool::randStar5Style()
{
	RandEngine ran;
	double personWeight = this->star5Function[1].setX(this->star5Guar[1] + 1);
	double weaponWeight = this->star5Function[2].setX(this->star5Guar[2] + 1);
	double temp = ran.ran();
	if (personWeight + weaponWeight <= 1.0)
	{
		temp = ran.randBetween(0, personWeight + weaponWeight);
		if (temp < personWeight)
		{
			return ITEM_TYPE_PERSON;
		}
		else
		{
			return ITEM_TYPE_WEAPON;
		}
	}
	else
	{
		if (personWeight >= weaponWeight)
		{
			if (temp < personWeight)
			{
				return ITEM_TYPE_PERSON;
			}
			else
			{
				return ITEM_TYPE_WEAPON;
			}
		}
		else
		{
			if (temp < weaponWeight)
			{
				return ITEM_TYPE_WEAPON;
			}
			else
			{
				return ITEM_TYPE_PERSON;
			}
		}
	}
}

int WishPool::randStar4Style()
{
	RandEngine ran;
	double personWeight = this->star4Function[1].setX(this->star4Guar[1] + 1);
	double weaponWeight = this->star4Function[2].setX(this->star4Guar[2] + 1);
	double temp = ran.ran();
	if (personWeight + weaponWeight <= 1.0)
	{
		temp = ran.randBetween(0, personWeight + weaponWeight);
		if (temp < personWeight)
		{
			return ITEM_TYPE_PERSON;
		}
		else
		{
			return ITEM_TYPE_WEAPON;
		}
	}
	else
	{
		if (personWeight >= weaponWeight)
		{
			if (temp < personWeight)
			{
				return ITEM_TYPE_PERSON;
			}
			else
			{
				return ITEM_TYPE_WEAPON;
			}
		}
		else
		{
			if (temp < weaponWeight)
			{
				return ITEM_TYPE_WEAPON;
			}
			else
			{
				return ITEM_TYPE_PERSON;
			}
		}
	}
}

void WishPool::randStar5UpItem(string* item, int* style)
{
	unsigned int i = 0;
	RandEngine ran;
	unsigned int temp = (unsigned int)ran.random(0, (int)this->star5Up.size() - 1);
	*item = this->star5Up[temp];
	*style = this->upItemType;
	//如果是定轨的物品
	if (this->isChooseItem(*item) == true)
	{
		this->star5Guar[4] = 0; //命定值清零
	}
	else if(this->hasChoose == true)
	{
		this->star5Guar[4]++;
	}
	this->star5Guar[3] = 0; //设置为没歪
	this->star5Guar[0] = 0; //5星保底进度清零
	if (this->upItemType == ITEM_TYPE_WEAPON)
	{
		this->star5Guar[1]++;
		this->star5Guar[2] = 0;
	}
	else if (this->upItemType == ITEM_TYPE_PERSON)
	{
		this->star5Guar[1] = 0;
		this->star5Guar[2]++;
	}
	this->star4Guar[0]++;
	this->star4Guar[1]++;
	this->star4Guar[2]++;
}

void WishPool::randStar4UpItem(string* item, int* style)
{
	unsigned int i = 0;
	RandEngine ran;
	unsigned int temp = (unsigned int)ran.random(0, (int)this->star4Up.size() - 1);
	*item = this->star4Up[temp];
	*style = this->upItemType;
	this->star4Guar[3] = 0; //设置为没歪
	this->star4Guar[0] = 0; //4星保底进度清零
	if (this->upItemType == ITEM_TYPE_WEAPON)
	{
		this->star4Guar[1]++;
		this->star4Guar[2] = 0;
	}
	else if (this->upItemType == ITEM_TYPE_PERSON)
	{
		this->star4Guar[1] = 0;
		this->star4Guar[2]++;
	}
	this->star5Guar[0]++;
	this->star5Guar[1]++;
	this->star5Guar[2]++;
}

void WishPool::randStar5BasePerson(string* item, int* style)
{
	unsigned int i = 0;
	RandEngine ran;
	unsigned int temp = (unsigned int)ran.random(0, (int)this->star5Person.size() - 1);
	*item = this->star5Person[temp];
	*style = ITEM_TYPE_PERSON;
	this->star5Guar[0] = 0; //5星保底进度清零
	this->star5Guar[1] = 0;
	this->star5Guar[2]++;
	if (this->hasUp == true)
	{
		this->star5Guar[3]++; //歪了
	}
	if (this->hasChoose == true)
	{
		this->star5Guar[4]++; //非定轨
	}
	this->star4Guar[0]++;
	this->star4Guar[1]++;
	this->star4Guar[2]++;
}

void WishPool::randStar5BaseWeapon(string* item, int* style)
{
	unsigned int i = 0;
	RandEngine ran;
	unsigned int temp = (unsigned int)ran.random(0, (int)this->star5Weapon.size() - 1);
	*item = this->star5Weapon[temp];
	*style = ITEM_TYPE_WEAPON;
	this->star5Guar[0] = 0; //5星保底进度清零
	this->star5Guar[1]++;
	this->star5Guar[2] = 0;
	if (this->hasUp == true)
	{
		this->star5Guar[3]++; //歪了
	}
	if (this->hasChoose == true)
	{
		this->star5Guar[4]++; //非定轨
	}
	this->star4Guar[0]++;
	this->star4Guar[1]++;
	this->star4Guar[2]++;
}

void WishPool::randStar4BasePerson(string* item, int* style)
{
	unsigned int i = 0;
	RandEngine ran;
	unsigned int temp = (unsigned int)ran.random(0, (int)this->star4Person.size() - 1);
	*item = this->star4Person[temp];
	*style = ITEM_TYPE_PERSON;
	this->star5Guar[0]++;
	this->star5Guar[1]++;
	this->star5Guar[2]++;
	this->star4Guar[0] = 0;
	this->star4Guar[1] = 0;
	this->star4Guar[2]++;
	if (this->hasUp == true)
	{
		this->star4Guar[3]++; //歪了
	}
}

void WishPool::randStar4BaseWeapon(string* item, int* style)
{
	unsigned int i = 0;
	RandEngine ran;
	unsigned int temp = (unsigned int)ran.random(0, (int)this->star4Weapon.size() - 1);
	*item = this->star4Weapon[temp];
	*style = ITEM_TYPE_WEAPON;
	this->star5Guar[0]++;
	this->star5Guar[1]++;
	this->star5Guar[2]++;
	this->star4Guar[0] = 0;
	this->star4Guar[1]++;
	this->star4Guar[2] = 0;
	if (this->hasUp == true)
	{
		this->star4Guar[3]++; //歪了
	}
}

bool WishPool::isChooseItem(string item)
{
	if (this->hasChoose == false)
	{
		return false;
	}

	unsigned int i = 0;
	unsigned int size = (unsigned int)this->star5Choose.size();
	for (i = 0; i < size; i++)
	{
		if (item == this->star5Choose[i])
		{
			return true;
		}
	}
	return false;
}

WishPool::WishPool(string name, bool hasUp, bool hasChoose)
{
	int i = 0;
	PwFunction temp;

	this->name = name;
	this->hasUp = hasUp;
	this->hasChoose = hasChoose;

	this->num = 0;
	this->upItemType = ITEM_TYPE_PERSON;

	for (i = 0; i < 3; i++)
	{
		this->star4Guar.push_back(0);
		this->star5Guar.push_back(0);
		this->star4Function.push_back(temp);
		this->star5Function.push_back(temp);
	}

	if (hasUp == true)
	{
		this->star4Guar.push_back(0);
		this->star5Guar.push_back(0);
		this->star4Function.push_back(temp);
		this->star5Function.push_back(temp);
	}
	if (hasChoose == true)
	{
		this->star5Guar.push_back(0);
		this->star5Choose.push_back("取消定轨");
		this->star5Function.push_back(temp);
	}
}

void WishPool::setBaseItem(vector<string> star3, vector<string> star4Person, vector<string> star4Weapon)
{
	this->star3 = star3;
	this->star4Person = star4Person;
	this->star4Weapon = star4Weapon;
}

void WishPool::setUpItem(vector<string> star4Up, vector<string> star5Up, int upItemType)
{
	if (this->hasUp == true)
	{
		this->star4Up = star4Up;
		this->star5Up = star5Up;
		this->upItemType = upItemType;
	}
}

void WishPool::setStar5Person(vector<string> star5Person)
{
	this->star5Person = star5Person;
}

void WishPool::setStar5Weapon(vector<string> star5Weapon)
{
	this->star5Weapon = star5Weapon;
}

void WishPool::setTemplatePby(int id)
{
	if (id == 1)
	{
		//出货概率
		this->star4Function[0].add(0.051, 0.0, 0, 8);
		this->star4Function[0].add(0.561, 0.0, 9, 9);
		this->star4Function[0].add(1.0, 0.0, 10, 999999999);
		this->star5Function[0].add(0.006, 0.0, 0, 73);
		this->star5Function[0].add(0.066, 0.06, 74, 89);
		this->star5Function[0].add(1.0, 0.0, 90, 999999999);
		//平均种类
		this->star4Function[1].add(0.0255, 0.0, 0, 17);
		this->star4Function[1].add(0.2805, 0.255, 18, 999999999);
		this->star4Function[2].add(0.0255, 0.0, 0, 17);
		this->star4Function[2].add(0.2805, 0.255, 18, 999999999);
		this->star5Function[1].add(0.003, 0.0, 0, 147);
		this->star5Function[1].add(0.033, 0.03, 148, 999999999);
		this->star5Function[2].add(0.003, 0.0, 0, 147);
		this->star5Function[2].add(0.033, 0.03, 148, 999999999);
		//歪的概率
		this->star4Function[3].add(0.5, 0.0, 0, 1);
		this->star4Function[3].add(1.0, 0.0, 2, 999999999);
		this->star5Function[3].add(0.5, 0.0, 0, 1);
		this->star5Function[3].add(1.0, 0.0, 2, 999999999);
	}
	else if (id == 2)
	{
		//出货概率
		this->star4Function[0].add(0.06, 0.0, 0, 7);
		this->star4Function[0].add(0.66, 0.0, 8, 8);
		this->star4Function[0].add(0.96, 0.0, 9, 9);
		this->star4Function[0].add(1.0, 0.0, 10, 999999999);
		this->star5Function[0].add(0.007, 0.0, 0, 62);
		this->star5Function[0].add(0.077, 0.07, 63, 73);
		this->star5Function[0].add(0.812, 0.035, 74, 79);
		this->star5Function[0].add(1.0, 0, 80, 999999999);
		//平均种类
		this->star4Function[1].add(0.03, 0.0, 0, 15);
		this->star4Function[1].add(0.33, 0.3, 16, 999999999);
		this->star4Function[2].add(0.03, 0.0, 0, 15);
		this->star4Function[2].add(0.33, 0.3, 16, 999999999);
		this->star5Function[1].add(0.003, 0.0, 0, 147);
		this->star5Function[1].add(0.033, 0.03, 148, 999999999);
		this->star5Function[2].add(0.003, 0.0, 0, 147);
		this->star5Function[2].add(0.033, 0.03, 148, 999999999);
		//歪的概率
		this->star4Function[3].add(0.75, 0.0, 0, 1);
		this->star4Function[3].add(1.0, 0.0, 2, 999999999);
		this->star5Function[3].add(0.75, 0.0, 0, 1);
		this->star5Function[3].add(1.0, 0.0, 2, 999999999);
		//定轨
		this->star5Function[4].add(0.0, 0.0, 0, 2);
		this->star5Function[4].add(1.0, 0.0, 3, 999999999);
	}
	else if (id == 3)
	{
		//出货概率
		this->star4Function[0].add(0.051, 0.0, 0, 8);
		this->star4Function[0].add(0.561, 0.0, 9, 9);
		this->star4Function[0].add(1.0, 0.0, 10, 999999999);
		this->star5Function[0].add(0.006, 0.0, 0, 73);
		this->star5Function[0].add(0.066, 0.06, 74, 89);
		this->star5Function[0].add(1.0, 0.0, 90, 999999999);
		//平均种类
		this->star4Function[1].add(0.0255, 0.0, 0, 17);
		this->star4Function[1].add(0.2805, 0.255, 18, 999999999);
		this->star4Function[2].add(0.0255, 0.0, 0, 17);
		this->star4Function[2].add(0.2805, 0.255, 18, 999999999);
		this->star5Function[1].add(0.003, 0.0, 0, 147);
		this->star5Function[1].add(0.033, 0.03, 148, 999999999);
		this->star5Function[2].add(0.003, 0.0, 0, 147);
		this->star5Function[2].add(0.033, 0.03, 148, 999999999);
	}
}

void WishPool::clearHistory()
{
	this->history.clear();
}

void WishPool::resetPool()
{
	unsigned int i = 0;
	this->history.clear();
	this->num = 0;

	for (i = 0; i < this->star4Guar.size(); i++)
	{
		this->star4Guar[i] = 0;
	}
	for (i = 0; i < this->star5Guar.size(); i++)
	{
		this->star5Guar[i] = 0;
	}
	this->star5Choose[0] = "取消定轨";
}

vector<string> WishPool::getStar5Choose()
{
	return this->star5Choose;
}

string WishPool::getPoolName()
{
	return this->name;
}

int WishPool::getUpItemType()
{
	return this->upItemType;
}

WishHistory WishPool::getHistory()
{
	return this->history;
}

WishHistory WishPool::getLastItem()
{
	WishHistory list;
	unsigned int length = this->history.getLength();
	unsigned int num = this->history.getNum(length - 1);
	string item = this->history.getItem(length - 1);
	int type = this->history.getType(length - 1);
	short star = this->history.getStar(length - 1);
	list.add(num, item, type, star);
	
	return list;
}

WishHistory WishPool::getLastNItem(int endPos)
{
	unsigned int length = this->history.getLength();
	return this->history.cut(length - endPos, length - 1);
}

WishHistory WishPool::getLast10Item()
{
	WishHistory list;
	unsigned int length = this->history.getLength();
	unsigned int i = 0;

	for (i = 0; i < 10; i++)
	{
		unsigned int num = this->history.getNum(length - 10 + i);
		string item = this->history.getItem(length - 10 + i);
		int type = this->history.getType(length - 10 + i);
		short star = this->history.getStar(length - 10 + i);
		list.add(num, item, type, star);
	}

	return list;
}

WishHistory WishPool::getCenterItem(int startPos, int endPos)
{
	return this->history.cut((unsigned int)startPos, (unsigned int)endPos);
}

short WishPool::getLast10MaxStar()
{
	unsigned int length = this->history.getLength();
	unsigned int i = 0;
	short maxStar = 3;

	for (i = 0; i < 10; i++)
	{
		if (maxStar < this->history.getStar(length - 10 + i))
		{
			maxStar = this->history.getStar(length - 10 + i);
		}
	}

	return maxStar;
}

short WishPool::getLastNMaxStar(unsigned int n)
{
	unsigned int length = this->history.getLength();
	unsigned int i = 0;
	short maxStar = 3;

	for (i = 0; i < n; i++)
	{
		if (maxStar < this->history.getStar(length - n + i))
		{
			maxStar = this->history.getStar(length - n + i);
		}
	}

	return maxStar;
}

void WishPool::setStar5Choose(vector<string> item)
{
	if (this->hasChoose == true)
	{
		this->star5Choose = item;
		this->star5Guar[this->star5Guar.size() - 1] = 0;
	}
}

WishHistory WishPool::singleWish()
{
	string item;
	int style = ITEM_TYPE_WEAPON;
	short star;
	bool temp = false;

	this->num++;
	//确定星级
	star = this->randStar();
	
	if (star == 5)
	{
		//是否定轨，没有定轨规则或未定轨返回false
		temp = this->randChooseItem(&item, &style);
		if (temp == false)
		{
			//是否歪，没有up物品返回false
			temp = this->randIs5UpItem();
			if (temp == true)
			{
				//没歪
				this->randStar5UpItem(&item, &style);
			}
			else
			{
				//歪了，判断出货类型
				if (this->hasUp == false)
				{
					style = this->randStar5Style();
				}
				else
				{
					style = this->upItemType;
				}
				
				if (style == ITEM_TYPE_PERSON)
				{
					this->randStar5BasePerson(&item, &style);
				}
				else if(style == ITEM_TYPE_WEAPON)
				{
					this->randStar5BaseWeapon(&item, &style);
				}
			}
		}
	}
	else if (star == 4)
	{
		//是否歪，没有up物品返回false
		temp = this->randIs4UpItem();
		if (temp == true)
		{
			//没歪
			this->randStar4UpItem(&item, &style);
		}
		else
		{
			//歪了，判断出货类型
			style = this->randStar4Style();
			if (style == ITEM_TYPE_PERSON)
			{
				this->randStar4BasePerson(&item, &style);
			}
			else if (style == ITEM_TYPE_WEAPON)
			{
				this->randStar4BaseWeapon(&item, &style);
			}
		}
	}
	else
	{
		this->randStar3Item(&item, &style);
	}
	this->history.add(this->num, item, style, star);
	return this->history.cutFinal();
}

WishHistory WishPool::templeWish()
{
	unsigned int i = 0;
	for (i = 0; i < 10; i++)
	{
		this->singleWish();
	}
	return this->getLast10Item();
}

WishHistory WishPool::nWish(unsigned int n)
{
	unsigned int i = 0;
	for (i = 0; i < n; i++)
	{
		this->singleWish();
	}
	return this->getLastNItem(n);
}
