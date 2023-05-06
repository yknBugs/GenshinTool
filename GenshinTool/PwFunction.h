#pragma once

//此文件记录定义函数

#include <vector>

using namespace std;

class PwFunction
{
private:
	vector<double> baseNum; //基数
	vector<double> kNum; //增长率
	vector<int> min; //下界
	vector<int> max; //上界
	int x; //当前x值

public:
	PwFunction();

	//添加一个分段区间
	void add(double baseNum, double kNum, int min, int max);
	void clear();

	double setX(int x);
	double get();
	int getX();
	unsigned int getLength();
};


