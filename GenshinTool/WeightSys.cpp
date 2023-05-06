#include "WeightSys.h"

void WeightSys::addObject(int id, int weight)
{
	this->objectId.push_back(id);
	this->weight.push_back(weight);
}

void WeightSys::clearObject(int id)
{
	unsigned int i = 0;
	for (i = 0; i < this->objectId.size(); i++)
	{
		if (this->objectId[i] == id)
		{
			this->objectId.erase(this->objectId.begin() + i, this->objectId.begin() + i + 1);
			this->weight.erase(this->weight.begin() + i, this->weight.begin() + i + 1);
			return;
		}
	}
}

void WeightSys::clearObject()
{
	this->objectId.clear();
	this->weight.clear();
}

int WeightSys::getObjectId(unsigned int pos)
{
	return this->objectId[pos];
}

int WeightSys::getWeightSum()
{
	unsigned int i = 0;
	unsigned int size = (unsigned int)this->objectId.size();
	int result = 0;

	for (i = 0; i < size; i++)
	{
		result += this->weight[i];
	}
	return result;
}

double WeightSys::findP(unsigned int pos)
{
	return (double)this->weight[pos] / (double)this->getWeightSum();
}

double WeightSys::findP(unsigned int pos, int maxWeight)
{
	int sumWeight = this->getWeightSum();
	if (sumWeight <= maxWeight)
	{
		return (double)this->weight[pos] / (double)sumWeight;
	}
	else
	{
		unsigned int i = 0;
		sumWeight = 0;
		for (i = 0; i < pos; i++)
		{
			sumWeight += this->weight[i];
		}

		if (sumWeight + this->weight[pos] <= maxWeight)
		{
			return (double)this->weight[pos] / (double)maxWeight;
		}
		else if (sumWeight >= maxWeight)
		{
			return 0.0;
		}
		else
		{
			return ((double)maxWeight - sumWeight) / (double)maxWeight;
		}
	}
}

double WeightSys::getP(int id)
{
	unsigned int i = 0;
	unsigned int size = (unsigned int)this->objectId.size();

	for (i = 0; i < size; i++)
	{
		if (this->objectId[i] == id)
		{
			return (double)this->weight[i] / (double)this->getWeightSum();
		}
	}

	return 0.0;
}

double WeightSys::getP(int id, int maxWeight)
{
	unsigned int i = 0;
	unsigned int size = (unsigned int)this->objectId.size();

	for (i = 0; i < size; i++)
	{
		if (this->objectId[i] == id)
		{
			int sumWeight = this->getWeightSum();
			if (sumWeight <= maxWeight)
			{
				return (double)this->weight[i] / (double)sumWeight;
			}
			else
			{
				unsigned int j = 0;
				sumWeight = 0;
				for (j = 0; j < i; j++)
				{
					sumWeight += this->weight[j];
				}

				if (sumWeight + this->weight[i] <= maxWeight)
				{
					return (double)this->weight[i] / (double)maxWeight;
				}
				else if (sumWeight >= maxWeight)
				{
					return 0.0;
				}
				else
				{
					return ((double)maxWeight - sumWeight) / (double)maxWeight;
				}
			}
		}
	}

	return 0.0;
}

unsigned int WeightSys::getObjectSize()
{
	return (unsigned int)this->objectId.size();
}
