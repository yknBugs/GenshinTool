#pragma once

//本文件用于生成随机数

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
	static unsigned int listPos; //已经取走的随机数个数

public:
	RandEngine(bool resetSeed = false);

	//取0~1间的随机数
	double ran();

	double randBetween(double min, double max);
	int random(int min, int max);
	bool randSucceed(double p);
	int randObject(WeightSys list);

	static unsigned long getSeed();
	static unsigned int getListPos();
	void setSeed(unsigned long s);
};