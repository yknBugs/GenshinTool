#pragma once

#include <string>
#include "TimeCaculator.h"

using namespace std;

class EventTime
{
private:
	TimeCaculator time;
	int primogem;

public:
	EventTime();
	EventTime(TimeCaculator time);
	EventTime(int year, int month, int day);

	//计算版本时间
	TimeCaculator getLastVersionOP();
	TimeCaculator getLastVersionED();
	TimeCaculator getCurrentVersionOP();
	TimeCaculator getCurrentVersionED();
	TimeCaculator getNextVersionOP();
	TimeCaculator getNextVersionED();
	//计算卡池时间
	TimeCaculator getNextPoolOP();
	TimeCaculator getNextPoolED();
	//计算纪行时间
	TimeCaculator getNextExpEventED();
	//计算下次直播时间
	TimeCaculator getNextReportTime();
	//计算攒到指定数量原石的估计日期(不算今天)，参数:目标数量，深渊能力，小月卡，大月卡
	TimeCaculator savePrimogemExpect(int count, int ability = 600, bool hasWish = false, bool hasExp = false);
	TimeCaculator saveWishExpect(int count, int ability = 600, bool hasWish = false, bool hasExp = false);
	//计算指定日期原石数量可以到达的量(不算今天)
	int keepPrimogemExpect(TimeCaculator t, int ability = 600, bool hasWish = false, bool hasExp = false);
	int keepWishExpect(TimeCaculator t, int ability = 600, bool hasWish = false, bool hasExp = false);
	//计算指定日期通过指定方式原石数量可以到达的量(不算今天)
	int getPrimogemExpect(TimeCaculator t, string name, int ability = 600);
	int getWishExpect(TimeCaculator t, string name, int ability = 600);
	//计算树脂的量，以及全部用作刷金币
	int allEnergy(TimeCaculator t);
	int allMoney(TimeCaculator t);

	string getVersionId();
};