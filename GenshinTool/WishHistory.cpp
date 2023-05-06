#include "WishHistory.h"

void WishHistory::add(unsigned int num, string item, int type, short star)
{
	this->num.push_back(num);
	this->item.push_back(item);
	this->type.push_back(type);
	this->star.push_back(star);
}

void WishHistory::clearFirst()
{
	if (this->num.size() > 0)
	{
		this->num.erase(this->num.begin(), this->num.begin() + 1);
		this->item.erase(this->item.begin(), this->item.begin() + 1);
		this->type.erase(this->type.begin(), this->type.begin() + 1);
		this->star.erase(this->star.begin(), this->star.begin() + 1);
	}
}

void WishHistory::clear()
{
	this->num.clear();
	this->item.clear();
	this->type.clear();
	this->star.clear();
}

void WishHistory::clear(unsigned int startPos, unsigned int endPos)
{
	this->num.erase(this->num.begin() + startPos, this->num.begin() + endPos +1);
	this->item.erase(this->item.begin() + startPos, this->item.begin() + endPos + 1);
	this->type.erase(this->type.begin() + startPos, this->type.begin() + endPos + 1);
	this->star.erase(this->star.begin() + startPos, this->star.begin() + endPos + 1);
}

WishHistory WishHistory::cut(unsigned int pos)
{
	WishHistory temp;
	temp.add(this->num[pos], this->item[pos], this->type[pos], this->star[pos]);
	
	return temp;
}

WishHistory WishHistory::cut(unsigned int startPos, unsigned int endPos)
{
	WishHistory temp;
	unsigned int i = startPos;
	while (i <= endPos)
	{
		temp.add(this->num[i], this->item[i], this->type[i], this->star[i]);
		i++;
	}

	return temp;
}

WishHistory WishHistory::cutFinal()
{
	WishHistory temp;
	unsigned int pos = (unsigned int)this->num.size() - 1;
	temp.add(this->num[pos], this->item[pos], this->type[pos], this->star[pos]);

	return temp;
}

unsigned int WishHistory::findPos(unsigned int num)
{
	unsigned int i = 0;
	for (i = 0; i < this->num.size(); i++)
	{
		if (this->num[i] == num)
		{
			return i;
		}
	}
	return 0;
}

unsigned int WishHistory::getLength()
{
	return (unsigned int)this->num.size();
}

unsigned int WishHistory::getNum(unsigned int pos)
{
	return this->num[pos];
}

string WishHistory::getItem(unsigned int pos)
{
	return this->item[pos];
}

int WishHistory::getType(unsigned int pos)
{
	return this->type[pos];
}

short WishHistory::getStar(unsigned int pos)
{
	return this->star[pos];
}
