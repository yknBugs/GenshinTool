#pragma once

//���ļ���¼���庯��

#include <vector>

using namespace std;

class PwFunction
{
private:
	vector<double> baseNum; //����
	vector<double> kNum; //������
	vector<int> min; //�½�
	vector<int> max; //�Ͻ�
	int x; //��ǰxֵ

public:
	PwFunction();

	//���һ���ֶ�����
	void add(double baseNum, double kNum, int min, int max);
	void clear();

	double setX(int x);
	double get();
	int getX();
	unsigned int getLength();
};


