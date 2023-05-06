#pragma once

#include <vector>
#include <string>

using namespace std;

class Option
{
public:
	static vector<string> optionList;	//选项列表
	static vector<bool> isShow;	//是否显示这个设置选项
	static vector<string> currentSet;	//当前设置的字符串描述
	static vector<double> currentChoose;	//当前设置的具体数值
	static vector<int> optionType;	//选项类型[0:多选一，1:百分比数字设置，2:用户字符输入，3:用户数字输入]
	static vector<string> tipList;	//提示信息

	unsigned int getLength();
	unsigned int getVisibleLength();
	vector<string> getChooseList(string name);
	vector<double> getChooseNum(string name);
	unsigned int getOptionPos(string name);
};