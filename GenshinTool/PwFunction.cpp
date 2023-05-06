#include "PwFunction.h"

PwFunction::PwFunction()
{
	this->x = 0;
}

void PwFunction::add(double baseNum, double kNum, int min, int max)
{
	this->baseNum.push_back(baseNum);
	this->kNum.push_back(kNum);
	this->min.push_back(min);
	this->max.push_back(max);
}

void PwFunction::clear()
{
	this->baseNum.clear();
	this->kNum.clear();
	this->min.clear();
	this->max.clear();
}

double PwFunction::setX(int x)
{
	unsigned int i = 0;
	unsigned int size = (unsigned int)this->min.size();

	this->x = x;
	for (i = 0; i < size; i++)
	{
		if (x >= this->min[i] && x <= this->max[i])
		{
			return this->kNum[i] * ((double)x - this->min[i]) + this->baseNum[i];
		}
	}

	return 0;
}

double PwFunction::get()
{
	unsigned int i = 0;
	unsigned int size = (unsigned int)this->min.size();

	for (i = 0; i < size; i++)
	{
		if (this->x >= this->min[i] && this->x <= this->max[i])
		{
			return this->kNum[i] * ((double)this->x - this->min[i]) + this->baseNum[i];
		}
	}

	return 0;
}

int PwFunction::getX()
{
	return this->x;
}

unsigned int PwFunction::getLength()
{
	return (unsigned int)this->min.size();
}
