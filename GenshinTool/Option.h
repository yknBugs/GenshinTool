#pragma once

#include <vector>
#include <string>

using namespace std;

class Option
{
public:
	static vector<string> optionList;	//ѡ���б�
	static vector<bool> isShow;	//�Ƿ���ʾ�������ѡ��
	static vector<string> currentSet;	//��ǰ���õ��ַ�������
	static vector<double> currentChoose;	//��ǰ���õľ�����ֵ
	static vector<int> optionType;	//ѡ������[0:��ѡһ��1:�ٷֱ��������ã�2:�û��ַ����룬3:�û���������]
	static vector<string> tipList;	//��ʾ��Ϣ

	unsigned int getLength();
	unsigned int getVisibleLength();
	vector<string> getChooseList(string name);
	vector<double> getChooseNum(string name);
	unsigned int getOptionPos(string name);
};