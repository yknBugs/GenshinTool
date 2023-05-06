#include "Option.h"

vector<string> Option::optionList =
{
	"祈愿卡池版本",
	"祈愿动画",
	"祈愿动画速度",
	"祈愿动画变色位置",
	"原石数量预测表格",
	"祈愿历史记录显示方式",
	"事件时间预测显示方式",
	"调试信息"
};

vector<bool> Option::isShow =
{
	true,	//祈愿卡池版本
	true,	//祈愿动画
	false,	//祈愿动画速度
	false,	//祈愿动画变色位置
	true,	//原石数量预测表格	
	true,	//祈愿历史记录显示方式
	true,	//事件时间预测显示方式
	true	//调试信息
};

vector<string> Option::currentSet = 
{
	"V2.7 上半",		//祈愿卡池版本
	"关闭",			//祈愿动画
	"2.0s + 0.4s",	//祈愿动画速度
	"40%处",			//祈愿动画变色位置
	"自动决定",		//原石数量预测表格	
	"自动决定",		//祈愿历史记录显示方式
	"文字说明",		//事件时间预测显示方式
	"关闭"			//调试信息
};

vector<double> Option::currentChoose =
{
	2.71,	//祈愿卡池版本
	0.0,	//祈愿动画
	20.0,	//祈愿动画速度
	0.4,	//祈愿动画变色位置
	2.0,	//原石数量预测表格	
	2.0,	//祈愿历史记录显示方式
	2.0,	//事件时间预测显示方式
	0.0		//调试信息
};

vector<int> Option::optionType =
{
	0,	//祈愿卡池版本
	0,	//祈愿动画
	3,	//祈愿动画速度
	1,	//祈愿动画变色位置
	0,	//原石数量预测表格	
	0,	//祈愿历史记录显示方式
	0,	//事件时间预测显示方式
	0	//调试信息
};

vector<string> Option::tipList =
{
	"&CV2.7 下半的卡池内容为预测内容，仅供参考，具体以官方公告为准。",//祈愿卡池版本
	"&A开启后，祈愿显示结果前会显示一个简单的动画。",//祈愿动画
	"&A修改显示祈愿结果的动画速度。",	//祈愿动画速度
	"&A修改显示祈愿结果前，动画变色时，进度所处的百分比。",	//祈愿动画变色位置
	"&A在原石数量预测界面以表格的形式显示每日可获取的具体数量。",	//原石数量预测表格	
	"&A以列表的形式显示可以让屏幕上同时显示更多条历史记录。",	//祈愿历史记录显示方式
	"&A在小屏幕上以表格的形式展示事件的日期时，文字布局可能出现问题。",	//事件时间预测显示方式
	"&E本功能仅供测试软件功能是否能正常运行时使用。"	//调试信息
};

unsigned int Option::getLength()
{
	return (unsigned int)optionList.size();
}

unsigned int Option::getVisibleLength()
{
	unsigned int i = 0;
	unsigned int result = 0;
	for (i = 0; i < optionList.size(); i++)
	{
		if (isShow[i] == true)
		{
			result++;
		}
	}

	return result;
}

vector<string> Option::getChooseList(string name)
{
	if (name == "祈愿卡池版本")
	{
		vector<string> temp = { "V2.6 下半", "V2.7 上半", "V2.7 下半" };
		return temp;
	}
	else if (name == "祈愿动画")
	{
		vector<string> temp = { "关闭","开启" };
		return temp;
	}
	else if (name == "原石数量预测表格")
	{
		vector<string> temp = { "自动决定","开启","关闭", };
		return temp;
	}
	else if (name == "祈愿历史记录显示方式")
	{
		vector<string> temp = { "自动决定","表格","列举" };
		return temp;
	}
	else if (name == "事件时间预测显示方式")
	{
		vector<string> temp = { "文字说明","横向表格","纵向表格" };
		return temp;
	}
	else if (name == "调试信息")
	{
		vector<string> temp = { "关闭","开启" };
		return temp;
	}
	vector<string> temp;
	return temp;
}

vector<double> Option::getChooseNum(string name)
{
	if (name == "祈愿卡池版本")
	{
		vector<double> temp = { 2.62, 2.71, 2.72 };
		return temp;
	}
	else if (name == "祈愿动画")
	{
		vector<double> temp = { 0.0, 1.0 };
		return temp;
	}
	else if (name == "原石数量预测表格")
	{
		vector<double> temp = { 2.0, 1.0, 0.0 };
		return temp;
	}
	else if (name == "祈愿历史记录显示方式")
	{
		vector<double> temp = { 2.0, 1.0, 0.0 };
		return temp;
	}
	else if (name == "事件时间预测显示方式")
	{
		vector<double> temp = { 2.0, 1.0, 0.0 };
		return temp;
	}
	else if (name == "调试信息")
	{
		vector<double> temp = { 0.0, 1.0 };
		return temp;
	}
	vector<double> temp;
	return temp;
}

unsigned int Option::getOptionPos(string name)
{
	unsigned int i = 0;
	for (i = 0; i < optionList.size(); i++)
	{
		if (optionList[i] == name)
		{
			return i;
		}
	}

	return 0;
}
