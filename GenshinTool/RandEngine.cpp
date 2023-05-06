#include "RandEngine.h"

unsigned long RandEngine::seed = (unsigned long)system_clock::now().time_since_epoch().count();
mt19937 RandEngine::e(seed);
uniform_real_distribution<double> RandEngine::ri(0.0, 1.0);
unsigned int RandEngine::listPos = 0;

RandEngine::RandEngine(bool resetSeed)
{
	if (resetSeed == true)
	{
		seed = (unsigned long)system_clock::now().time_since_epoch().count();
		e = mt19937(seed);
		ri = uniform_real_distribution<double>(0.0, 1.0);
		listPos = 0;
	}
}

double RandEngine::ran()
{
	listPos++;
	return ri(e);
}

double RandEngine::randBetween(double min, double max)
{
	double temp = ri(e);
	listPos++;
	temp = (max - min) * temp + min;
	return temp;
}

int RandEngine::random(int min, int max)
{
	double temp = ri(e);
	listPos++;
	temp = temp * ((double)max - min + 1.0) + min;
	return (int)floor(temp);
}

bool RandEngine::randSucceed(double p)
{
	listPos++;
	if (ri(e) < p)
	{
		return true;
	}
	return false;
}

int RandEngine::randObject(WeightSys list)
{
	double temp = ri(e);
	double sum = 0.0;
	vector<double> pList;
	unsigned int i = 0;
	unsigned int size = list.getObjectSize();

	listPos++;
	for (i = 0; i < size; i++)
	{
		pList.push_back(list.findP(i));
	}
	
	for (i = 0; i < size; i++)
	{
		sum += pList[i];
		if (temp < sum)
		{
			return list.getObjectId(i);
		}
	}

	return 0;
}

unsigned long RandEngine::getSeed()
{
	return seed;
}

unsigned int RandEngine::getListPos()
{
	return listPos;
}

void RandEngine::setSeed(unsigned long s)
{
	seed = s;
	e = mt19937(seed);
	ri = uniform_real_distribution<double>(0.0, 1.0);
	listPos = 0;
}
