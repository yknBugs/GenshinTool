#pragma once

//���ļ����ڶ���Ȩ�صĸ���

#include <vector>

using namespace std;

class WeightSys
{
private:
	vector<int> objectId;
	vector<int> weight;

public:
	void addObject(int id, int weight);
	void clearObject(int id);
	void clearObject();

	int getObjectId(unsigned int pos);

	int getWeightSum();
	double findP(unsigned int pos);
	double findP(unsigned int pos, int maxWeight);
	double getP(int id);
	double getP(int id, int maxWeight);
	unsigned int getObjectSize();
};
