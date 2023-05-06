#include "EventTimeUi.h"

string EventTimeUi::timeToString(TimeCaculator time, bool includeWeek)
{
	Display display;
	string text = "";
	text += display.intToString(time.getYear());
	text += "年";
	text += display.intToString(time.getMonth());
	text += "月";
	text += display.intToString(time.getDay());
	text += "日";

	if (includeWeek == true)
	{
		string temp[8] = { "零", "一", "二", "三", "四", "五", "六", "日" };
		text += "   星期";
		text += temp[time.getWeek()];
	}
	
	return text;
}

string EventTimeUi::weekToString(TimeCaculator time)
{
	string temp[8] = { "星期零", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六", "星期日" };
	return temp[time.getWeek()];
}

void EventTimeUi::showUi()
{
	Display display;
	TimeCaculator tempTime(2021, 11, 25);
	vector<int> tempM = { 1,12 };
	int year = 2021;
	int month = 11;
	int day = 25;
	int temp = 0;
	char opr = '\0';
	string text = "&7原神工具 &8>&7 主菜单 &8>&7 事件和资源预测\n\n";

	display.clear();
	display.showText(text);
	display.showTextI("&E使用本功能之前，请先设置一个时长不超过", MAXLOAD_TIME, "&E天的时间段。\n");
	display.showText("&E后续的所有计算将限制在此时间段的范围内。\n");
	display.showText("&E输入该时间段的开始日期和截止日期来进行设置。\n");
	display.showText("\n&7输入开始日期[年份]:\n");
	display.showButton('1', "2021年");
	display.showButton('2', "2022年");
	display.showButton('3', "2023年");
	display.showButton('0', "退出");
	opr = display.selectButton();
	if (opr == '0')
	{
		return;
	}
	else
	{
		year = 2020 + opr - '0';
	}
	text += "&B开始日期:&A";
	text += display.intToString(year);
	text += "年";
	display.clear();
	display.showText(text + "\n\n");
	display.showText("&7输入开始日期[月份][1~12]:\n");
	display.showText("&7输入0退出。\n");
	temp = 0;
	while (temp < 1 || temp > 12)
	{
		temp = display.getInputInt(12, false);
		if (temp == 0)
		{
			return;
		}
	}
	month = temp;
	text += display.intToString(month);
	text += "月";
	display.clear();
	display.showText(text + "\n\n");
	display.showTextI("&7输入开始日期[日期][1~", tempTime.getDaysInMonth(year, month), "]:\n");
	display.showText("&7输入0退出。\n");
	temp = 0;
	while (temp < 1 || temp > tempTime.getDaysInMonth(year, month))
	{
		temp = display.getInputInt(tempTime.getDaysInMonth(year, month), false);
		if (temp == 0)
		{
			return;
		}
	}
	day = temp;
	text += display.intToString(day);
	text += "日\t";
	TimeCaculator startTime(year, month, day); 
	text += this->weekToString(startTime);
	text += "\n";
	//最多计算MAXLOAD_TIME天内的事件
	if (startTime.getYear() == (startTime + MAXLOAD_TIME).getYear())
	{
		year = startTime.getYear();
	}
	else
	{
		display.clear();
		display.showText(text);
		display.showText("\n&E开始日期设置成功。\n");
		display.showText("\n&7输入截止日期[年份]:\n");
		if (startTime.getYear() <= 2021 && (startTime + MAXLOAD_TIME).getYear() >= 2021)
		{
			display.showButton('1', "2021年");
		}
		if (startTime.getYear() <= 2022 && (startTime + MAXLOAD_TIME).getYear() >= 2022)
		{
			display.showButton('2', "2022年");
		}
		if (startTime.getYear() <= 2023 && (startTime + MAXLOAD_TIME).getYear() >= 2023)
		{
			display.showButton('3', "2023年");
		}
		if (startTime.getYear() <= 2024 && (startTime + MAXLOAD_TIME).getYear() >= 2024)
		{
			display.showButton('4', "2024年");
		}
		display.showButton('0', "退出");
		opr = display.selectButton();
		if (opr == '0')
		{
			return;
		}
		else
		{
			year = 2020 + opr - '0';
		}
	}
	text += "&B截止日期:&A";
	text += display.intToString(year);
	text += "年";
	tempM[0] = 1;
	if (TimeCaculator(year, 1, 31) < startTime)
	{
		tempM[0] = startTime.getMonth();
	}
	tempM[1] = 12;
	if (TimeCaculator(year, 12, 1) > startTime + MAXLOAD_TIME)
	{
		tempM[1] = (startTime + MAXLOAD_TIME).getMonth();
	}

	if (tempM[0] == tempM[1])
	{
		month = tempM[0];
	}
	else
	{
		display.clear();
		display.showText(text + "\n\n");
		display.showTextI("&7输入截止日期[月份][#~#]:\n", tempM);
		display.showText("&7输入0退出。\n");
		temp = display.getInputInt(tempM[1], false);
		if (temp == 0)
		{
			return;
		}
		while (temp < tempM[0] || temp > tempM[1])
		{
			display.clearText(5, 0, 8);
			display.clearText(40, 0, 7);
			display.showText("&C输入的数值无效，请重新输入。&7\n");
			temp = display.getInputInt(tempM[1], false);
			if (temp == 0)
			{
				return;
			}
		}
		month = temp;
	}
	text += display.intToString(month);
	text += "月";

	tempM[0] = 1;
	if (TimeCaculator(year, month, 1) < startTime)
	{
		tempM[0] = startTime.getDay();
	}
	tempM[1] = tempTime.getDaysInMonth(year, month);
	if (TimeCaculator(year, month, tempM[1]) > startTime + MAXLOAD_TIME)
	{
		tempM[1] = (startTime + MAXLOAD_TIME).getDay();
	}

	if (tempM[0] == tempM[1])
	{
		day = tempM[0];
	}
	else
	{
		display.clear();
		display.showText(text + "\n\n");
		display.showTextI("&7输入截止日期[日期][#~#]:\n", tempM);
		display.showText("&7输入0退出。\n");
		temp = display.getInputInt(tempM[1], false);
		if (temp == 0)
		{
			return;
		}
		while (temp < tempM[0] || temp > tempM[1])
		{
			display.clearText(5, 0, 8);
			display.clearText(40, 0, 7);
			display.showText("&C输入的数值无效，请重新输入。&7\n");
			temp = display.getInputInt(tempM[1], false);
			if (temp == 0)
			{
				return;
			}
		}
		day = temp;
	}
	text += display.intToString(day);
	text += "日\t";
	TimeCaculator endTime(year, month, day);
	text += this->weekToString(endTime);
	text += "\n\n";

	while (opr != '0')
	{
		display.clear();
		display.showText(text);
		display.showText("&E时间段已设置成功。\n");
		display.showText("&E请选择你想要预测的项目。\n\n");

		display.showButton('1', "原石数量预测");
		display.showButton('2', "纠缠之缘数量预测");
		display.showButton('3', "事件时间预测");
		display.showButton('4', "原粹树脂预测");
		display.showButton('0', "返回");
		opr = display.selectButton();
		if (opr == '1')
		{
			this->primogemExpectUi(startTime, endTime);
		}
		else if (opr == '2')
		{
			this->wishExpectUi(startTime, endTime);
		}
		else if (opr == '3')
		{
			this->newVersionUi(startTime, endTime);
		}
		else if (opr == '4')
		{
			this->sourceExpectUi(startTime, endTime);
		}
	}
}

void EventTimeUi::primogemExpectUi(TimeCaculator startTime, TimeCaculator endTime)
{
	Display display;
	char opr = '\0';
	int ability = -1;
	bool hasWish = false;
	bool hasExp = false;
	display.clear();
	string text = "&7原神工具 &8>&7 主菜单 &8>&7 事件和资源预测 &8>&7 原石数量预测\n\n";
	text += "&B开始日期:&A";
	text += this->timeToString(startTime, true);
	text += "&B\n截止日期:&A";
	text += this->timeToString(endTime, true);
	text += "&B\n";
	display.showText(text);
	display.showText("\n&E请输入你在每期深境螺旋中能够获得的原石数量[0~600]:\n");
	while (ability < 0 || ability > 600 || ability % 50 != 0)
	{
		ability = display.getInputInt(600, false);
		if (ability % 50 != 0)
		{
			display.clearText(5, 0, 7);
			display.clearText(50, 0, 6);
			display.showText("&C输入的数值无效，必须为50的倍数。&7\n");
		}
	}
	text += "&B在每期深境螺旋中能够获取 &A";
	text += display.intToString(ability);
	text += " &B原石\n";
	display.clear();
	display.showText(text);
	display.showText("\n&E你是否购买了空月祝福\n");
	display.showButton('1', "否");
	display.showButton('2', "是");
	display.showButton('0', "退出");
	opr = display.selectButton();
	if (opr == '0')
	{
		return;
	}
	else if (opr == '1')
	{
		text += "没有购买空月祝福，";
		hasWish = false;
	}
	else if (opr == '2')
	{
		text += "拥有空月祝福，";
		hasWish = true;
	}
	display.clear();
	display.showText(text);
	display.showText("\n\n&E你是否购买了珍珠纪行\n");
	display.showButton('1', "否");
	display.showButton('2', "是");
	display.showButton('0', "退出");
	opr = display.selectButton();
	if (opr == '0')
	{
		return;
	}
	else if (opr == '1')
	{
		text += "没有购买珍珠纪行。\n\n";
		hasExp = false;
	}
	else if (opr == '2')
	{
		text += "已解锁珍珠纪行。\n\n";
		hasExp = true;
	}

	EventTime eventTime(startTime - 1);

	Option option;
	string listSet = option.currentSet[option.getOptionPos("原石数量预测表格")];
	while (opr != '0')
	{
		int coordY = 7;
		int currentSum = 0;
		int lastSum = 0;
		TimeCaculator tempTime = startTime;

		if (listSet == "自动决定")
		{
			if (endTime - startTime + 1 > 45)
			{
				listSet = "关闭";
			}
			else
			{
				listSet = "开启";
			}
		}

		display.clear();
		display.showText(text);

		if (listSet == "开启")
		{
			display.createText("&B日期", 0, coordY);
			display.createText("&B星期", 16, coordY);
			display.createText("&B当日获取", 25, coordY);
			display.createText("&B累计获取", 38, coordY);
			coordY++;
			while (tempTime <= endTime)
			{
				currentSum = eventTime.keepPrimogemExpect(tempTime, ability, hasWish, hasExp);
				display.createText("&6" + this->timeToString(tempTime, false), 0, coordY);
				display.createText("&6" + this->weekToString(tempTime), 16, coordY);
				display.createText("&6" + display.intToString(currentSum - lastSum), 25, coordY);
				display.createText("&6" + display.intToString(currentSum), 38, coordY);

				coordY++;
				tempTime = tempTime + 1;
				lastSum = currentSum;
			}
			display.showText("\n");
		}
		
		display.showText("&c注意:预测结果根据历史版本的规律进行预测，并不一定完全准确。\n");
		display.showText("&c     预测结果仅供参考，具体数量请以实际情况为准。\n\n");
		display.showTextI("&E在这 &A", endTime - startTime + 1, " &E天里，预计一共能够获得 ");
		display.showTextI("&A", eventTime.keepPrimogemExpect(endTime, ability, hasWish, hasExp), " &E原石。\n");
		display.showText("&E原石的来源包括以下方面:\n");
		display.showTextI("&B完成每日委托总计可获得 &A",
			eventTime.getPrimogemExpect(endTime, "每日活跃", ability), " &B原石。\n");
		if (hasWish == true)
		{
			display.showTextI("&B通过空月祝福总计可获得 &A",
				eventTime.getPrimogemExpect(endTime, "空月祝福", ability), " &B原石。\n");
		}
		if (hasExp == true && eventTime.getPrimogemExpect(endTime, "珍珠纪行", ability) > 0)
		{
			display.showTextI("&B通过珍珠纪行总计可获得 &A",
				eventTime.getPrimogemExpect(endTime, "珍珠纪行", ability), " &B原石。\n");
		}
		if (eventTime.getPrimogemExpect(endTime, "深境螺旋", ability) > 0)
		{
			vector<int> temp = { eventTime.getPrimogemExpect(endTime, "深境螺旋", ability) / ability,
			eventTime.getPrimogemExpect(endTime, "深境螺旋", ability) };
			display.showTextI("&B期间深境螺旋共重置 &A# &B次，完成深境螺旋挑战总共可以获得&A # &B原石。\n", temp);
		}
		if (eventTime.getPrimogemExpect(endTime, "角色试用", ability) > 0)
		{
			vector<int> temp = { eventTime.getPrimogemExpect(endTime, "角色试用", ability) / 20,
				eventTime.getPrimogemExpect(endTime, "角色试用", ability) };
			display.showTextI("&B共 &A# &B期角色试用，包含&A # &B原石。\n", temp);
		}
		if (eventTime.getPrimogemExpect(endTime, "活动奖励", ability) > 0)
		{
			display.showTextI("&B参与所有的版本活动总共可以获取约 &A",
				eventTime.getPrimogemExpect(endTime, "活动奖励", ability), " &B原石。\n");
		}
		if (eventTime.getPrimogemExpect(endTime, "前瞻直播", ability) > 0)
		{
			display.showTextI("&B前瞻直播的兑换码包含 &A",
				eventTime.getPrimogemExpect(endTime, "前瞻直播", ability), " &B原石。\n");
		}
		if (eventTime.getPrimogemExpect(endTime, "版本更新补偿", ability) > 0)
		{
			display.showTextI("&B版本更新补偿包含 &A",
				eventTime.getPrimogemExpect(endTime, "版本更新补偿", ability), " &B原石。\n");
		}
		display.showText("\n");
		if (listSet == "关闭")
		{
			display.showButton('5', "显示详细表格");
		}
		else if (listSet == "开启")
		{
			display.showButton('5', "隐藏详细表格");
		}
		display.showButton('0', "返回");
		opr = display.selectButton();
		if (opr == '5')
		{
			if (listSet == "关闭")
			{
				listSet = "开启";
			}
			else if (listSet == "开启")
			{
				listSet = "关闭";
			}
		}
	}
}

void EventTimeUi::wishExpectUi(TimeCaculator startTime, TimeCaculator endTime)
{
	Display display;
	char opr = '\0';
	int ability = -1;
	bool hasWish = false;
	bool hasExp = false;
	display.clear();
	string text = "&7原神工具 &8>&7 主菜单 &8>&7 事件和资源预测 &8>&7 纠缠之缘数量预测\n\n";
	text += "&B开始日期:&A";
	text += this->timeToString(startTime, true);
	text += "&B\n截止日期:&A";
	text += this->timeToString(endTime, true);
	text += "&B\n";
	display.showText(text);
	display.showText("\n&E请输入你在每期深境螺旋中能够获得的原石数量[0~600]:\n");
	while (ability < 0 || ability > 600 || ability % 50 != 0)
	{
		ability = display.getInputInt(600, false);
		if (ability % 50 != 0)
		{
			display.clearText(5, 0, 7);
			display.clearText(50, 0, 6);
			display.showText("&C输入的数值无效，必须为50的倍数。&7\n");
		}
	}
	text += "&B在每期深境螺旋中能够获取 &A";
	text += display.intToString(ability);
	text += " &B原石\n";
	display.clear();
	display.showText(text);
	display.showText("\n&E你是否购买了空月祝福\n");
	display.showButton('1', "否");
	display.showButton('2', "是");
	display.showButton('0', "退出");
	opr = display.selectButton();
	if (opr == '0')
	{
		return;
	}
	else if (opr == '1')
	{
		text += "没有购买空月祝福，";
		hasWish = false;
	}
	else if (opr == '2')
	{
		text += "拥有空月祝福，";
		hasWish = true;
	}
	display.clear();
	display.showText(text);
	display.showText("\n\n&E你是否购买了珍珠纪行\n");
	display.showButton('1', "否");
	display.showButton('2', "是");
	display.showButton('0', "退出");
	opr = display.selectButton();
	if (opr == '0')
	{
		return;
	}
	else if (opr == '1')
	{
		text += "没有购买珍珠纪行。\n\n";
		hasExp = false;
	}
	else if (opr == '2')
	{
		text += "已解锁珍珠纪行。\n\n";
		hasExp = true;
	}

	EventTime eventTime(startTime - 1);

	Option option;
	string listSet = option.currentSet[option.getOptionPos("原石数量预测表格")];
	while (opr != '0')
	{
		int coordY = 7;
		int currentSum = 0;
		int lastSum = 0;
		TimeCaculator tempTime = startTime;

		if (listSet == "自动决定")
		{
			if (endTime - startTime + 1 > 45)
			{
				listSet = "关闭";
			}
			else
			{
				listSet = "开启";
			}
		}

		display.clear();
		display.showText(text);

		if (listSet == "开启")
		{
			display.createText("&B日期", 0, coordY);
			display.createText("&B星期", 16, coordY);
			display.createText("&B当日获取", 25, coordY);
			display.createText("&B累计获取", 38, coordY);
			coordY++;
			while (tempTime <= endTime)
			{
				currentSum = eventTime.keepWishExpect(tempTime, ability, hasWish, hasExp);
				display.createText("&6" + this->timeToString(tempTime, false), 0, coordY);
				display.createText("&6" + this->weekToString(tempTime), 16, coordY);
				display.createText("&6" + display.intToString(currentSum - lastSum), 25, coordY);
				display.createText("&6" + display.intToString(currentSum), 38, coordY);

				coordY++;
				tempTime = tempTime + 1;
				lastSum = currentSum;
			}
			display.showText("\n");
		}

		display.showText("&c注意:预测结果根据历史版本的规律进行预测，并不一定完全准确。\n");
		display.showText("&c     预测结果仅供参考，具体数量请以实际情况为准。\n\n");
		display.showTextI("&E在这 &A", endTime - startTime + 1, " &E天里，若将原石全部兑换为纠缠之缘，预计一共能够获得");
		display.showTextI(" &A", eventTime.keepWishExpect(endTime, ability, hasWish, hasExp), " &E纠缠之缘。\n");
		display.showText("&E它们的来源包括以下方面:\n");
		display.showTextI("&B完成每日委托总计可兑换约 &A",
			eventTime.getWishExpect(endTime, "每日活跃", ability), " &B纠缠之缘。\n");
		if (eventTime.getWishExpect(endTime, "星尘兑换", ability) > 0)
		{
			display.showTextI("&B月初在商店里可使用星尘兑换 &A",
				eventTime.getWishExpect(endTime, "星尘兑换", ability), " &B纠缠之缘。\n");
		}
		if (hasWish == true)
		{
			display.showTextI("&B通过空月祝福总计可兑换约 &A",
				eventTime.getWishExpect(endTime, "空月祝福", ability), " &B纠缠之缘。\n");
		}
		if (hasExp == true && eventTime.getWishExpect(endTime, "珍珠纪行", ability) > 0)
		{
			display.showTextI("&B通过珍珠纪行总计可获得约 &A",
				eventTime.getWishExpect(endTime, "珍珠纪行", ability), " &B纠缠之缘。\n");
		}
		if (eventTime.getWishExpect(endTime, "深境螺旋", ability) > 0)
		{
			vector<int> temp = { eventTime.getPrimogemExpect(endTime, "深境螺旋", ability) / ability,
			eventTime.getWishExpect(endTime, "深境螺旋", ability) };
			string tempS = "&B期间深境螺旋共重置 &A# &B次，";
			tempS += "完成深境螺旋挑战获得的原石总共可以兑换约&A # &B纠缠之缘。\n";
			display.showTextI(tempS, temp);
		}
		if (eventTime.getWishExpect(endTime, "角色试用", ability) > 0)
		{
			vector<int> temp = { eventTime.getPrimogemExpect(endTime, "角色试用", ability) / 20,
				eventTime.getWishExpect(endTime, "角色试用", ability) };
			display.showTextI("&B共 &A# &B期角色试用，其中获得的原石可兑换约&A # &B纠缠之缘。\n", temp);
		}
		if (eventTime.getWishExpect(endTime, "活动奖励", ability) > 0)
		{
			display.showTextI("&B参与所有的版本活动获得的原石总共可以兑换约 &A",
				eventTime.getWishExpect(endTime, "活动奖励", ability), " &B纠缠之缘。\n");
		}
		if (eventTime.getWishExpect(endTime, "前瞻直播", ability) > 0)
		{
			display.showTextI("&B前瞻直播的兑换码包含的原石可兑换约 &A",
				eventTime.getWishExpect(endTime, "前瞻直播", ability), " &B纠缠之缘。\n");
		}
		if (eventTime.getWishExpect(endTime, "版本更新补偿", ability) > 0)
		{
			display.showTextI("&B版本更新补偿包含的原石可兑换约 &A",
				eventTime.getWishExpect(endTime, "版本更新补偿", ability), " &B纠缠之缘。\n");
		}
		display.showText("&c注意:由于计算时对结果进行了四舍五入处理，");
		display.showText("&c因此上述所有来源所获得的数量加起来可能不等于总数。\n\n");
		if (listSet == "关闭")
		{
			display.showButton('5', "显示详细表格");
		}
		else if (listSet == "开启")
		{
			display.showButton('5', "隐藏详细表格");
		}
		display.showButton('0', "返回");
		opr = display.selectButton();
		if (opr == '5')
		{
			if (listSet == "关闭")
			{
				listSet = "开启";
			}
			else if (listSet == "开启")
			{
				listSet = "关闭";
			}
		}
	}
}

void EventTimeUi::newVersionUi(TimeCaculator startTime, TimeCaculator endTime)
{
	Display display;
	char opr = '\0';

	Option option;
	string listSet = option.currentSet[option.getOptionPos("事件时间预测显示方式")];
	while (opr != '0')
	{
		EventTime eventTime(startTime);
		TimeCaculator tempTime = eventTime.getCurrentVersionOP();
		eventTime = EventTime(tempTime + 1);
		int coordY = 2;

		display.clear();
		display.showText("&7原神工具 &8>&7 主菜单 &8>&7 事件和资源预测 &8>&7 事件时间预测\n\n");

		if (listSet == "文字说明")
		{
			while (tempTime <= endTime)
			{
				display.createText("&B" + this->timeToString(tempTime, false), 0, coordY);
				display.createText("&E到", 16, coordY);
				tempTime = eventTime.getNextVersionOP();
				display.createText("&B" + this->timeToString(tempTime - 1, false), 19, coordY);
				display.createText("&E" + eventTime.getVersionId() + "版本", 35, coordY);
				eventTime = EventTime(tempTime + 1);
				coordY++;
			}
			coordY++;
			display.setCursorPos(0, coordY);
			eventTime = EventTime(startTime);
			tempTime = eventTime.getCurrentVersionOP();
			eventTime = EventTime(tempTime + 1);
			while (tempTime <= endTime)
			{
				display.showText("&E预计&B" + eventTime.getVersionId() + "版本&E第一期活动祈愿开始时间 &B"
					+ this->timeToString(tempTime, false) + "\n");
				display.showText("&E           &E第二期活动祈愿开始时间 &B"
					+ this->timeToString(tempTime + 20, false) + "\n");

				tempTime = eventTime.getNextVersionOP();
				eventTime = EventTime(tempTime + 1);
				coordY += 2;
			}

			coordY++;
			display.setCursorPos(0, coordY);
			eventTime = EventTime(startTime);
			tempTime = eventTime.getCurrentVersionOP();
			eventTime = EventTime(tempTime + 1);
			while (tempTime <= endTime)
			{
				display.showText("&E预计&B" + eventTime.getVersionId() + "版本&E前瞻直播时间 &B"
					+ this->timeToString(tempTime - 12, false) + "\n");
				tempTime = eventTime.getNextVersionOP();
				eventTime = EventTime(tempTime + 1);
			}
		}
		else if (listSet == "横向表格")
		{
			display.createText("&B版本号", 0, coordY);
			display.createText("&B前瞻直播日期", 10, coordY);
			display.createText("&B版本开始日期", 26, coordY);
			display.createText("&B第二期活动祈愿", 42, coordY);
			display.createText("&B版本结束日期", 58, coordY);

			coordY++;
			while (tempTime <= endTime)
			{
				display.createText("&E" + eventTime.getVersionId() + "版本", 0, coordY);
				display.createText("&A" + this->timeToString(tempTime - 12, false), 10, coordY);
				display.createText("&A" + this->timeToString(tempTime, false), 26, coordY);
				display.createText("&A" + this->timeToString(tempTime + 20, false), 42, coordY);
				display.createText("&A" + this->timeToString(tempTime + 41, false), 58, coordY);
				
				tempTime = eventTime.getNextVersionOP();
				eventTime = EventTime(tempTime + 1);
				coordY++;
			}
			display.showText("\n");
		}
		else if (listSet == "纵向表格")
		{
			int coordX = 0;
			display.createText("&B版本号", coordX, 2);
			display.createText("&B前瞻直播", coordX, 3);
			display.createText("&B新角色PV", coordX, 4);
			display.createText("&B新武器介绍", coordX, 5);
			display.createText("&B新四星角色", coordX, 6);
			display.createText("&B预下载开启", coordX, 7);
			display.createText("&B祈愿公布", coordX, 8);
			display.createText("&B新角色演示", coordX, 9);
			display.createText("&B版本开始", coordX, 10);
			display.createText("&B第一期祈愿", coordX, 11);
			display.createText("&B新角色PV", coordX, 12);
			display.createText("&B新武器介绍", coordX, 13);
			display.createText("&B新四星角色", coordX, 14);
			display.createText("&B祈愿公布", coordX, 15);
			display.createText("&B新角色演示", coordX, 16);
			display.createText("&B第二期祈愿", coordX, 17);
			display.createText("&B纪行关闭", coordX, 18);
			display.createText("&B版本结束", coordX, 19);
			coordX = 12;
			while (tempTime <= endTime)
			{
				display.createText("&E" + eventTime.getVersionId() + "版本", coordX, 2);
				display.createText("&A" + this->timeToString(tempTime - 12, false), coordX, 3);
				display.createText("&A" + this->timeToString(tempTime - 6, false), coordX, 4);
				display.createText("&A" + this->timeToString(tempTime - 3, false), coordX, 5);
				display.createText("&A" + this->timeToString(tempTime - 3, false), coordX, 6);
				display.createText("&A" + this->timeToString(tempTime - 2, false), coordX, 7);
				display.createText("&A" + this->timeToString(tempTime - 2, false), coordX, 8);
				display.createText("&A" + this->timeToString(tempTime - 1, false), coordX, 9);
				display.createText("&A" + this->timeToString(tempTime, false), coordX, 10);
				display.createText("&A" + this->timeToString(tempTime, false), coordX, 11);
				display.createText("&A" + this->timeToString(tempTime + 14, false), coordX, 12);
				display.createText("&A" + this->timeToString(tempTime + 16, false), coordX, 13);
				display.createText("&A" + this->timeToString(tempTime + 17, false), coordX, 14);
				display.createText("&A" + this->timeToString(tempTime + 18, false), coordX, 15);
				display.createText("&A" + this->timeToString(tempTime + 19, false), coordX, 16);
				display.createText("&A" + this->timeToString(tempTime + 20, false), coordX, 17);
				display.createText("&A" + this->timeToString(tempTime + 39, false), coordX, 18);
				display.createText("&A" + this->timeToString(tempTime + 41, false), coordX, 19);

				tempTime = eventTime.getNextVersionOP();
				eventTime = EventTime(tempTime + 1);
				coordX += 16;
			}
			display.showText("\n");
		}

		display.showText("\n&c注意:以上所得的结果根据历史版本的规律进行预测，并不一定完全准确。\n");
		display.showText("&c     以上所得的结果仅供参考，具体时间请以实际情况为准。\n\n");

		if (listSet == "文字说明")
		{
			display.showButton('5', "以横向表格的方式显示");
		}
		else if (listSet == "横向表格")
		{
			display.showButton('5', "以纵向表格的方式显示");
		}
		else if (listSet == "纵向表格")
		{
			display.showButton('5', "以文字说明的方式显示");
		}
		display.showButton('0', "返回");
		opr = display.selectButton();
		if (opr == '5')
		{
			if (listSet == "文字说明")
			{
				listSet = "横向表格";
			}
			else if (listSet == "横向表格")
			{
				listSet = "纵向表格";
			}
			else if (listSet == "纵向表格")
			{
				listSet = "文字说明";
			}
		}
	}
}

void EventTimeUi::sourceExpectUi(TimeCaculator startTime, TimeCaculator endTime)
{
	Display display;
	int worldLevel = 0;
	char opr = '\0';
	string text = "&7原神工具 &8>&7 主菜单 &8>&7 事件和资源预测 &8>&7 原粹树脂预测\n\n";
	text += "&B开始日期:&A";
	text += this->timeToString(startTime, true);
	text += "&B\n截止日期:&A";
	text += this->timeToString(endTime, true);
	text += "&B\n";

	while (opr != '0')
	{
		vector<int> tempPara;
		vector<int> intPara = { endTime - startTime };
		
		display.clear();
		display.showText(text);
		display.showText("\n&7请输入你的世界等级[0~8]:\n");
		worldLevel = display.getInputInt(8, false);
		text += "&B世界等级: &A";
		text += display.intToString(worldLevel);
		text += "\n\n";

		intPara.push_back(intPara[0] * 180); //总体力量
		intPara.push_back(intPara[1] * 5); //获得经验
		tempPara = { 600, 1000, 1400, 1800, 2200, 2600, 3000, 3000, 3000 };
		intPara.push_back(intPara[1] * tempPara[worldLevel]); //全部刷金币

		display.clear();
		display.showText(text);
		display.showTextI("&E这 &A# &E天时间里累计回复 &A# &E原粹树脂。\n"
			"若全部用完，可获得累计 &A# &E冒险阅历。\n"
			"若全部用来刷摩拉，累计可获得 &A# &E摩拉。\n\n", intPara);

		display.showButton('0', "返回");
		opr = display.selectButton();
	}
}
