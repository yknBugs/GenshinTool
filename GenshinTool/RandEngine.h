#pragma once

//���ļ��������������

#include <random>
#include <chrono>
#include <cmath>

#include "WeightSys.h"

using namespace std;
using namespace chrono;

class RandEngine
{
private:
	static unsigned long seed;
	static mt19937 e;
	static uniform_real_distribution<double> ri;
	static unsigned int listPos; //�Ѿ�ȡ�ߵ����������

public:
	RandEngine(bool resetSeed = false);

	//ȡ0~1��������
	double ran();

	double randBetween(double min, double max);
	int random(int min, int max);
	bool randSucceed(double p);
	int randObject(WeightSys list);

	static unsigned long getSeed();
	static unsigned int getListPos();
	void setSeed(unsigned long s);
};