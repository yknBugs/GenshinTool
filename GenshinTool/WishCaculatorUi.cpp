#include "WishCaculatorUi.h"

void WishCaculatorUi::createTemplatePool(WishPool* wishpool, int templateId)
{
	Data data;
	if (templateId == 1)
	{
		vector<string> star3 = data.getStayWishList(3);
		vector<string> star4Person = data.getLimitWishList(4, false, ITEM_TYPE_PERSON);
		vector<string> star4Weapon = data.getLimitWishList(4, false, ITEM_TYPE_WEAPON);
		vector<string> star5Person = data.getLimitWishList(5, false, ITEM_TYPE_PERSON);
		vector<string> star5Weapon;
		vector<string> star4Up = data.getLimitWishList(4, true);
		vector<string> star5Up = data.getLimitWishList(5, true);
		wishpool->setBaseItem(star3, star4Person, star4Weapon);
		wishpool->setUpItem(star4Up, star5Up, ITEM_TYPE_PERSON);
		wishpool->setStar5Person(star5Person);
		wishpool->setStar5Weapon(star5Weapon);
		wishpool->setTemplatePby(1);
	}
	else if (templateId == 2)
	{
		vector<string> star3 = data.getStayWishList(3);
		vector<string> star4Person = data.getWeaponWishList(4, false, ITEM_TYPE_PERSON);
		vector<string> star4Weapon = data.getWeaponWishList(4, false, ITEM_TYPE_WEAPON);
		vector<string> star5Person;
		vector<string> star5Weapon = data.getWeaponWishList(5, false, ITEM_TYPE_WEAPON);
		vector<string> star4Up = data.getWeaponWishList(4, true);
		vector<string> star5Up = data.getWeaponWishList(5, true);
		wishpool->setBaseItem(star3, star4Person, star4Weapon);
		wishpool->setUpItem(star4Up, star5Up, ITEM_TYPE_WEAPON);
		wishpool->setStar5Person(star5Person);
		wishpool->setStar5Weapon(star5Weapon);
		wishpool->setTemplatePby(2);
	}
	else if (templateId == 3)
	{
		vector<string> star3 = data.getStayWishList(3);
		vector<string> star4Person = data.getStayWishList(4, ITEM_TYPE_PERSON);
		vector<string> star4Weapon = data.getStayWishList(4, ITEM_TYPE_WEAPON);
		vector<string> star5Person = data.getStayWishList(5, ITEM_TYPE_PERSON);
		vector<string> star5Weapon = data.getStayWishList(5, ITEM_TYPE_WEAPON);;
		wishpool->setBaseItem(star3, star4Person, star4Weapon);
		wishpool->setStar5Person(star5Person);
		wishpool->setStar5Weapon(star5Weapon);
		wishpool->setTemplatePby(3);
	}
}

bool WishCaculatorUi::hasSameElement(vector<string> list, string ele)
{
	unsigned int i = 0;
	unsigned int length = (unsigned int) list.size();
	for (i = 0; i < length; i++)
	{
		if (list[i] == ele)
		{
			return true;
		}
	}
	return false;
}

void WishCaculatorUi::connectVector(vector<string>* subject, vector<string>* object)
{
	unsigned int i = 0;
	unsigned int length = (unsigned int) object->size();
	for (i = 0; i < length; i++)
	{
		subject->push_back((*object)[i]);
	}
}

string WishCaculatorUi::showCaculatingUi(WishPool wishpool,string text, vector<string> wantItem,
	int wantCount, int hasCount, int simTime)
{
	Display display;
	WishPool tempPool = wishpool;
	string result = text;
	string warning = "";
	int i = 0;
	char opr = '\0';
	int maxCoordY = 0;//Y坐标
	int succeedTime = 0;//成功次数
	int failTime = 0;//超时次数
	double aveWishTime = 0.0;//平均抽数
	double varianceWish = 0.0;//抽数方差
	bool caculateAve = true;//是否计算平均数

	double pauseTime = 0.0;//暂停计算的时长
	int lastSec = 0;//上次刷新总用时的秒数
	double lastISec = 0;//上次循环的时刻
	int lastPercent = 0;//上次刷新的进度条位置
	double lastRefresh = 0.0;//上次更新临时计算结果的时刻
	bool hasPause = false;//上次更新临时计算结果后有没有暂停
	int lastI = -1;//上次更新临时计算结果时模拟的次数
	bool isStop = false;//是否停止计算

	vector<unsigned int> star4Guar = wishpool.star4Guar;
	vector<unsigned int> star5Guar = wishpool.star5Guar;

	Option option;
	string debugSet = option.currentSet[option.getOptionPos("调试信息")];
	
	display.clear();
	display.showText("&7原神工具 &8>&7 主菜单 &8>&7 祈愿概率计算器 &8>&7 计算中，请耐心等待");
	display.showLoading(50, '-', '=', 0.0, 0, 2, 14);
	display.setCursorPos(0, 5);
	display.showText(text);
	display.showTextI("&B正在模拟 &A", simTime, " &B次抽卡情况。\n\n");
	maxCoordY = display.getCursorPosY();
	display.clearText(60, 0, 5);

	if (wantCount > hasCount)
	{
		warning += "&a提示:想抽到的个数大于预算抽数，达成目标的概率必为0%。\n";
		display.setCursorPos(0, maxCoordY);
		display.showText(warning);
	}

	display.clockStart();
	for (i = 0; i < simTime; i++)
	{
		//总共模拟simTime次
		int wishTime = 0;//已经花费的抽数
		int getCount = 0;//已经抽到的个数
		tempPool = wishpool;
		//tempPool.star4Guar = star4Guar;//复制卡池信息
		//tempPool.star5Guar = star5Guar;

		for (wishTime = 0; wishTime < 1000000; wishTime++)
		{
			//抽卡，直到满足目标后中止
			string wishItem = tempPool.singleWish().getItem(0);
			if (this->hasSameElement(wantItem, wishItem) == true)
			{
				getCount++;
			}
			tempPool.clearHistory();

			//计算暂停
			if (display.getLastSec() - lastISec > RUNTIME_INTERRUPT)
			{
				hasPause = true;
				display.clearText(60, 0, 5);
				display.clearText(60, 0, 4);
				display.clearText(60, 0, 3);
				display.showText("&7计算已经暂停。请选择需要进行的操作。\n");
				display.showButton('1', "继续计算");
				display.showButton('0', "退出计算");
				opr = display.selectButton();
				if (opr == '0')
				{
					warning += "&a提示:计算在中途被手动中止。\n";
					isStop = true;
					pauseTime += (display.getLastSec() - lastISec);
					break;
				}
				warning += "&a提示:计算被暂停了 ";
				warning += display.microsecToTime(display.getLastSec() - lastISec);
				warning += "\n";
				display.setCursorPos(0, maxCoordY);
				display.showText(warning);
				display.clearAllButton();
				display.clearText(60, 0, 3);
				pauseTime += (display.getLastSec() - lastISec);
			}
			//计时
			lastISec = display.getLastSec();
			if ((int)(lastISec - pauseTime) != lastSec)
			{
				lastSec = (int)(lastISec - pauseTime);
				display.setCursorPos(0, 4);
				display.showText("&E计算已经耗时 &A");
				display.showText(display.secondsToTime(lastSec));
				display.showText("                 \n");

				if (debugSet == "开启")
				{
					display.setCursorPos(0, maxCoordY);

					display.clearText(100, 0, maxCoordY);
					display.showCodeText("(vector<string>)wantItem.size() = "
						+ display.intToString((int)wantItem.size()) + "\n");
					display.clearText(100, 0, maxCoordY + 1);
					display.showCodeText("(int) i = " + display.intToString(i) + "\n");
					display.clearText(100, 0, maxCoordY + 2);
					display.showCodeText("(int) succeedTime = " + display.intToString(succeedTime) + "\n");
					display.clearText(100, 0, maxCoordY + 3);
					display.showCodeText("(WishPool)tempPool.(vector<unsigned int>)star5Guar = "
						+ display.vectorUIntToString(tempPool.star5Guar) + "\n");
					display.clearText(100, 0, maxCoordY + 4);
					display.showCodeText("(WishPool)tempPool.(vector<unsigned int>)star4Guar = "
						+ display.vectorUIntToString(tempPool.star4Guar) + "\n");
					display.clearText(100, 0, maxCoordY + 5);
					display.showCodeText("(string) wishItem = \"" + wishItem + "\"\n");
					display.clearText(100, 0, maxCoordY + 6);
					display.showCodeText("(int) wishTime = " + display.intToString(wishTime) + "\n");
					display.clearText(100, 0, maxCoordY + 7);
					display.showCodeText("(int) getCount = " + display.intToString(getCount) + "\n");
					display.clearText(100, 0, maxCoordY + 9);
					display.clearText(100, 0, maxCoordY + 8);
					if (aveWishTime < 1000000000.0)
					{
						display.showCodeText("(double) aveWishTime = "
							+ display.doubleToString(aveWishTime, 1) + "\n");
						if (varianceWish < 1000000000.0)
						{
							display.showCodeText("(double) varianceWish = "
								+ display.doubleToString(varianceWish, 1) + "\n");
						}
					}

					display.showText("\n");
					display.showText(warning);
				}
			}

			//判断是否满足目标
			if (getCount >= wantCount)
			{
				wishTime++;
				break;
			}
			if (caculateAve == false && wishTime + 1 >= hasCount)
			{
				wishTime++;
				break;
			}
		}
		if (isStop == true)
		{
			break;
		}
		if (wishTime >= 1000000 && caculateAve == true)
		{
			warning += "&e警告:无法在合理的抽数内达成目标，因此无法计算花费抽数的平均值。\n";
			display.setCursorPos(0, maxCoordY);
			display.showText(warning);
			caculateAve = false;
		}
		//计算平均数和方差
		if (caculateAve == true)
		{
			aveWishTime += wishTime;
			varianceWish += ((double)wishTime * wishTime);
			if (wishTime <= hasCount)
			{
				succeedTime++;
			}
		}
		else
		{
			if (getCount >= wantCount)
			{
				succeedTime++;
			}
		}

		//刷新进度条
		if (lastPercent != (int)(((long long)i + 1) * 100 / simTime))
		{
			lastPercent = (int)(((long long)i + 1) * 100 / simTime);
			display.showLoading(50, '-', '=', ((double)i + 1) / simTime, 0, 2, 14);
		}
		//显示临时计算结果
		if (display.getLastSec() - lastRefresh > RUNTIME_CHANGERESULT)
		{
			string tempS = display.doubleToString((double)succeedTime * 100 / ((double)i + 1), 2);
			double expectTime = display.getLastSec() - lastRefresh;
			display.setCursorPos(0, 3);
			display.showText("&E估计实现目标的成功率约为 &A");
			display.showText(tempS);
			display.showText("%  ");
			if (hasPause == false)
			{
				expectTime /= ((double)i - lastI);
				expectTime *= ((double)simTime - i - 1);
				if (expectTime > 999999)
				{
					failTime++;
					if (failTime == 3)
					{
						warning += "&c错误:完成计算需要花费的时间过长。\n";
						display.setCursorPos(0, maxCoordY);
						display.showText(warning);
						isStop = true;
						i++;
						break;
					}
					if (expectTime < 999999998)
					{
						warning += "&e警告:完成计算预计需要花费 ";
						warning += display.secondsToTime((int)expectTime + 1);
						warning += "\n";
					}
					else
					{
						warning += "&e警告:完成计算需要花费的时间过长。\n";
					}
					display.setCursorPos(0, maxCoordY);
					display.showText(warning);
				}
				else
				{
					display.setCursorPos(0, 5);
					display.showText("&E预计计算剩余时间 &A");
					display.showText(display.secondsToTime((int)expectTime + 1));
					display.showText("                 ");
				}
			}
			hasPause = false;
			lastRefresh = display.getLastSec();
			lastI = i;
		}
	}

	if (i == 0)
	{
		result += "计算用时 &A";
		result += display.microsecToTime(display.getLastSec() - pauseTime);
		warning += "&c错误:已有的计算数据不足，无法估计出计算结果。\n";
		result += "\n\n";
		result += warning;
		result += "\n";
		return result;
	}

	aveWishTime /= i;
	varianceWish = varianceWish / i - aveWishTime * aveWishTime;

	result += "模拟了 &A";
	result += display.intToString(i);
	result += "&B 次祈愿情况，";
	result += "用时 &A";
	result += display.microsecToTime(display.getLastSec() - pauseTime);
	result += "\n&B其中有 &A";
	result += display.intToString(succeedTime);
	result += " &B次成功在预算之内达成目标。\n";
	result += "&B据此可以估计出以下结果:\n\n";

	if (caculateAve == true)
	{
		if (aveWishTime > 999999999)
		{
			warning += "&e警告:花费抽数的平均值超过上限，无法显示。\n";
		}
		else
		{
			result += "&B平均每人大约需要花费 &6";
			result += display.doubleToString(aveWishTime, 3);
			result += " &B抽达到目标。\n";
		}

		if (varianceWish > 999999999)
		{
			warning += "&e警告:花费抽数的方差超过上限，无法显示。\n";
		}
		else
		{
			result += "&B所花费抽数的方差约为 &6";
			result += display.doubleToString(varianceWish, 3);
			result += " &B。\n";
		}
	}

	result += "&B实现目标的成功率约为 &6";
	result += display.doubleToString((double)succeedTime * 100 / (double)i, 3);
	result += "% &B。\n\n";

	result += warning;
	result += "\n";

	return result;
}

void WishCaculatorUi::showUi()
{
	Display display;
	char opr = '\0';

	while (opr != '0')
	{
		display.clear();
		display.showText("&7原神工具 &8>&7 主菜单 &8>&7 祈愿概率计算器\n\n");
		display.showText("&7请选择你想要计算的内容。\n\n");

		display.showButton('1', "模拟在当前版本的卡池中，获取指定类型物品的概率。");
		display.showButton('0', "返回");
		opr = display.selectButton();
		if (opr == '1')
		{
			this->showTemplateSimUi();
		}
	}
}

void WishCaculatorUi::showTemplateSimUi()
{
	Display display;
	Data data;
	Option option;
	string debugSet = option.currentSet[option.getOptionPos("调试信息")];
	char opr = '\0';

	while (opr != '0')
	{
		string text = "&7原神工具 &8>&7 主菜单 &8>&7 祈愿概率计算器 &8>&7 祈愿模拟\n\n";
		WishPool wishpool;
		vector<bool> guar5ParaNeed = { true, true, true, true };	//对保底参数的需求[抽数，类型，歪，定轨]
		vector<bool> guar4ParaNeed = { true, true, true }; //对保底参数的需求[抽数，类型，歪]
		vector<string> wantItem;
		int wantPoolId = 0;	//卡池id，1角色，2武器，3常驻
		int wantCount = 0; //想要抽到的个数
		int hasCount = 0; //拥有的总抽数
		int simTime = 0; //模拟次数
		//选择卡池
		display.clear();
		display.showText(text);

		display.showText("&B功能说明:\n");
		display.showText("&B本功能通过模拟实验得出许多人的祈愿结果，据此估计出达成目标的概率。\n");
		display.showText("&B本功能只会模拟获得指定类型的物品的概率。\n");
		display.showText("\n");

		display.showText("&7请选择一个祈愿卡池:\n");
		display.showButton('1', "角色活动祈愿");
		display.showButton('2', "武器活动祈愿");
		display.showButton('3', "常驻祈愿");
		display.showButton('0', "退出计算");
		opr = display.selectButton();
		if (opr == '0')
		{
			return;
		}
		else if (opr == '1')
		{
			wishpool = WishPool("角色活动祈愿", true, false);
			this->createTemplatePool(&wishpool, 1);
			text += "&7角色活动祈愿\n&b";
			wantPoolId = 1;
		}
		else if (opr == '2')
		{
			wishpool = WishPool("武器活动祈愿", true, true);
			this->createTemplatePool(&wishpool, 2);
			text += "&7武器活动祈愿\n&b";
			wantPoolId = 2;
		}
		else if (opr == '3')
		{
			wishpool = WishPool("常驻祈愿", false, false);
			this->createTemplatePool(&wishpool, 3);
			text += "&7常驻祈愿\n&b";
			wantPoolId = 3;
		}
		//设定出货目标
		display.clear();
		display.showText(text);
		display.showText("\n&7请选择你想抽取物品的范围:\n\n");
		if (wantPoolId == 1)
		{
			display.showButton('1', "指定up五星角色");
			display.showButton('2', "指定非up五星角色");
			display.showButton('3', "任意非up五星角色");
			display.showButton('4', "任意五星角色");
			display.showButton('5', "指定up四星角色");
			display.showButton('6', "任意up四星角色");
			display.showButton('7', "指定四星武器");
			display.showButton('8', "任意四星武器");
			display.showButton('9', "任意四星物品");
			display.showButton('0', "退出计算");
			opr = display.selectButton();
			if (opr == '0')
			{
				return;
			}
			else if (opr == '1')
			{
				text += "指定up五星角色";
				guar5ParaNeed = { true, false, true, false };
				guar4ParaNeed = { false, false, false };
				wantItem = { wishpool.star5Up[0] };
			}
			else if (opr == '2')
			{
				text += "指定非up五星角色";
				guar5ParaNeed = { true, false, true, false };
				guar4ParaNeed = { false, false, false };
				wantItem = { wishpool.star5Person[0] };
			}
			else if (opr == '3')
			{
				text += "任意非up五星角色";
				guar5ParaNeed = { true, false, true, false };
				guar4ParaNeed = { false, false, false };
				wantItem = wishpool.star5Person;
			}
			else if (opr == '4')
			{
				text += "任意五星角色";
				guar5ParaNeed = { true, false, false, false };
				guar4ParaNeed = { false, false, false };
				vector<string> tempA = wishpool.star5Person;
				vector<string> tempB = wishpool.star5Up;
				this->connectVector(&tempA, &tempB);
				wantItem = tempA;
			}
			else if (opr == '5')
			{
				text += "指定up四星角色";
				guar5ParaNeed = { true, false, false, false };
				guar4ParaNeed = { true, false, true };
				wantItem = { wishpool.star4Up[0] };
			}
			else if (opr == '6')
			{
				text += "任意up四星角色";
				guar5ParaNeed = { true, false, false, false };
				guar4ParaNeed = { true, false, true };
				wantItem = wishpool.star4Up;
			}
			else if (opr == '7')
			{
				text += "指定四星武器";
				guar5ParaNeed = { true, false, false, false };
				guar4ParaNeed = { true, true, true };
				wantItem = { wishpool.star4Weapon[0] };
			}
			else if (opr == '8')
			{
				text += "任意四星武器";
				guar5ParaNeed = { true, false, false, false };
				guar4ParaNeed = { true, true, true };
				wantItem = wishpool.star4Weapon;
			}
			else if (opr == '9')
			{
				text += "任意四星物品";
				guar5ParaNeed = { true, false, false, false };
				guar4ParaNeed = { true, false, false };
				vector<string> tempA = wishpool.star4Person;
				vector<string> tempB = wishpool.star4Weapon;
				vector<string> tempC = wishpool.star4Up;
				this->connectVector(&tempA, &tempB);
				this->connectVector(&tempA, &tempC);
				wantItem = tempA;
			}
		}
		else if (wantPoolId == 2)
		{
			display.showButton('1', "指定up五星武器");
			display.showButton('2', "任意up五星武器");
			display.showButton('3', "任意非up五星武器");
			display.showButton('4', "任意五星武器");
			display.showButton('5', "指定up四星武器");
			display.showButton('6', "任意up四星武器");
			display.showButton('7', "指定四星角色");
			display.showButton('8', "任意四星角色");
			display.showButton('9', "任意四星物品");
			display.showButton('0', "退出计算");
			opr = display.selectButton();
			if (opr == '0')
			{
				return;
			}
			else if (opr == '1')
			{
				text += "指定up五星武器";
				guar5ParaNeed = { true, false, true, true };
				guar4ParaNeed = { false, false, false };
				wantItem = { wishpool.star5Up[0] };
			}
			else if (opr == '2')
			{
				text += "任意up五星武器";
				guar5ParaNeed = { true, false, true, true };
				guar4ParaNeed = { false, false, false };
				wantItem = wishpool.star5Up;
			}
			else if (opr == '3')
			{
				text += "任意非up五星武器";
				guar5ParaNeed = { true, false, true, true };
				guar4ParaNeed = { false, false, false };
				wantItem = wishpool.star5Weapon;
			}
			else if (opr == '4')
			{
				text += "任意五星武器";
				guar5ParaNeed = { true, false, false, false };
				guar4ParaNeed = { false, false, false };
				vector<string> tempA = wishpool.star5Weapon;
				vector<string> tempB = wishpool.star5Up;
				this->connectVector(&tempA, &tempB);
				wantItem = tempA;
			}
			else if (opr == '5')
			{
				text += "指定up四星武器";
				guar5ParaNeed = { true, false, false, false };
				guar4ParaNeed = { true, false, true };
				wantItem = { wishpool.star4Up[0] };
			}
			else if (opr == '6')
			{
				text += "任意up四星武器";
				guar5ParaNeed = { true, false, false, false };
				guar4ParaNeed = { true, false, true };
				wantItem = wishpool.star4Up;
			}
			else if (opr == '7')
			{
				text += "指定四星角色";
				guar5ParaNeed = { true, false, false, false };
				guar4ParaNeed = { true, true, true };
				wantItem = { wishpool.star4Person[0] };
			}
			else if (opr == '8')
			{
				text += "任意四星角色";
				guar5ParaNeed = { true, false, false, false };
				guar4ParaNeed = { true, true, true };
				wantItem = wishpool.star4Person;
			}
			else if (opr == '9')
			{
				text += "任意四星物品";
				guar5ParaNeed = { true, false, false, false };
				guar4ParaNeed = { true, false, false };
				vector<string> tempA = wishpool.star4Person;
				vector<string> tempB = wishpool.star4Weapon;
				vector<string> tempC = wishpool.star4Up;
				this->connectVector(&tempA, &tempB);
				this->connectVector(&tempA, &tempC);
				wantItem = tempA;
			}
		}
		else if (wantPoolId == 3)
		{
			display.showButton('1', "指定五星角色");
			display.showButton('2', "指定五星武器");
			display.showButton('3', "任意五星角色");
			display.showButton('4', "任意五星武器");
			display.showButton('5', "指定四星角色");
			display.showButton('6', "指定四星武器");
			display.showButton('7', "任意四星角色");
			display.showButton('8', "任意四星武器");
			display.showButton('9', "指定三星物品");
			display.showButton('0', "退出计算");
			opr = display.selectButton();
			if (opr == '0')
			{
				return;
			}
			else if (opr == '1')
			{
				text += "指定五星角色";
				guar5ParaNeed = { true, true, false, false };
				guar4ParaNeed = { false, false, false };
				wantItem = { wishpool.star5Person[0] };
			}
			else if (opr == '2')
			{
				text += "指定五星武器";
				guar5ParaNeed = { true, true, false, false };
				guar4ParaNeed = { false, false, false };
				wantItem = { wishpool.star5Weapon[0] };
			}
			else if (opr == '3')
			{
				text += "任意五星角色";
				guar5ParaNeed = { true, true, false, false };
				guar4ParaNeed = { false, false, false };
				wantItem = wishpool.star5Person;
			}
			else if (opr == '4')
			{
				text += "任意五星武器";
				guar5ParaNeed = { true, true, false, false };
				guar4ParaNeed = { false, false, false };
				wantItem = wishpool.star5Weapon;
			}
			else if (opr == '5')
			{
				text += "指定四星角色";
				guar5ParaNeed = { true, false, false, false };
				guar4ParaNeed = { true, true, false };
				wantItem = { wishpool.star4Person[0] };
			}
			else if (opr == '6')
			{
				text += "指定四星武器";
				guar5ParaNeed = { true, false, false, false };
				guar4ParaNeed = { true, true, false };
				wantItem = { wishpool.star4Weapon[0] };
			}
			else if (opr == '7')
			{
				text += "任意四星角色";
				guar5ParaNeed = { true, false, false, false };
				guar4ParaNeed = { true, true, false };
				wantItem = wishpool.star4Person;
			}
			else if (opr == '8')
			{
				text += "任意四星武器";
				guar5ParaNeed = { true, false, false, false };
				guar4ParaNeed = { true, true, false };
				wantItem = wishpool.star4Weapon;
			}
			else if (opr == '9')
			{
				text += "指定三星物品";
				guar5ParaNeed = { true, false, false, false };
				guar4ParaNeed = { true, false, false };
				wantItem = { wishpool.star3[0] };
			}
		}
		//设定预算
		display.clear();
		display.showText(text);

		if (debugSet == "开启")
		{
			display.showText("\n\n");
			display.showCodeText("(vector<bool>) guar5ParaNeed = " 
				+ display.vectorBoolToString(guar5ParaNeed) + "\n");
			display.showCodeText("(vector<bool>) guar4ParaNeed = "
				+ display.vectorBoolToString(guar4ParaNeed) + "\n");
			display.showCodeText("(vector<string>)wantItem.size() = "
				+ display.intToString((int)wantItem.size()) + "\n");
			display.showCodeText("(WishPool)wishpool.(vector<unsigned int>)star5Guar = "
				+ display.vectorUIntToString(wishpool.star5Guar) + "\n");
			display.showCodeText("(WishPool)wishpool.(vector<unsigned int>)star4Guar = "
				+ display.vectorUIntToString(wishpool.star4Guar));
		}

		display.showText("\n\n&7请输入你想要抽到的个数[1~1000]:\n");
		display.showText("&7输入0退出计算。\n");
		wantCount = display.getInputInt(1000, false);
		if (wantCount == 0)
		{
			return;
		}
		text += "\n&b想要抽到 &a";
		text += display.intToString(wantCount);
		text += " &b个\n";

		display.clear();
		display.showText(text);

		if (debugSet == "开启")
		{
			display.showText("\n");
			display.showCodeText("(vector<bool>) guar5ParaNeed = "
				+ display.vectorBoolToString(guar5ParaNeed) + "\n");
			display.showCodeText("(vector<bool>) guar4ParaNeed = "
				+ display.vectorBoolToString(guar4ParaNeed) + "\n");
			display.showCodeText("(vector<string>)wantItem.size() = "
				+ display.intToString((int)wantItem.size()) + "\n");
			display.showCodeText("(WishPool)wishpool.(vector<unsigned int>)star5Guar = "
				+ display.vectorUIntToString(wishpool.star5Guar) + "\n");
			display.showCodeText("(WishPool)wishpool.(vector<unsigned int>)star4Guar = "
				+ display.vectorUIntToString(wishpool.star4Guar) + "\n");
		}

		display.showText("\n&7请输入你预算的总抽数[1~100000]:\n");
		display.showText("&7输入0退出计算。\n");
		hasCount = display.getInputInt(100000, false);
		if (hasCount == 0)
		{
			return;
		}
		text += "&b预算总抽数为 &a";
		text += display.intToString(hasCount);
		text += " &b抽\n";
		//输入相关的保底参数
		if (guar5ParaNeed[0] == true)
		{
			display.clear();
			display.showText(text);
			if (wantPoolId == 1 || wantPoolId == 3)
			{
				display.showText("\n&7请输入你已经连续多少抽没有获得过五星物品[0~89]:\n");
				wishpool.star5Guar[0] = (unsigned int)display.getInputInt(89, false);
				text += "&b已连续 &a";
				text += display.intToString((int)wishpool.star5Guar[0]);
				text += " &b抽未获得五星物品\n";
			}
			else if (wantPoolId == 2)
			{
				display.showText("\n&7请输入你已经连续多少抽没有获得过五星物品[0~79]:\n");
				wishpool.star5Guar[0] = (unsigned int)display.getInputInt(79, false);
				text += "&b已连续 &a";
				text += display.intToString((int)wishpool.star5Guar[0]);
				text += " &b抽未获得五星物品\n";
			}
		}
		if (guar5ParaNeed[1] == true)
		{
			int tempMin = (int)wishpool.star5Guar[0];
			int tempCoordY = 0;

			display.clear();
			display.showText(text);
			display.showTextI("\n&7请输入你已经连续多少抽没有获得过五星角色[", tempMin, "~255]:\n");
			if (tempMin > 0)
			{
				display.showText("&7输入0退出计算。\n");
			}
			wishpool.star5Guar[1] = (unsigned int)display.getInputInt(255, false);
			if (tempMin > 0 && wishpool.star5Guar[1] == 0)
			{
				return;
			}
			tempCoordY = display.getCursorPosY();
			while ((int)wishpool.star5Guar[1] < tempMin || wishpool.star5Guar[1] > 255)
			{
				display.clearText(8, 0, tempCoordY);
				display.clearText(40, 0, tempCoordY - 1);
				display.showTextI("&C输入的数值无效，请重新输入[", tempMin, "~255]。&7\n");
				wishpool.star5Guar[1] = (unsigned int)display.getInputInt(255, false);
				if (tempMin > 0 && wishpool.star5Guar[1] == 0)
				{
					return;
				}
			}
			text += "&b已连续 &a";
			text += display.intToString((int)wishpool.star5Guar[1]);
			text += " &b抽未获得五星角色\n";
			if ((int)wishpool.star5Guar[1] > tempMin)
			{
				wishpool.star5Guar[2] = tempMin;
				text += "&b已连续 &a";
				text += display.intToString((int)wishpool.star5Guar[2]);
				text += " &b抽未获得五星武器\n";
			}
			else if((int)wishpool.star5Guar[1] == tempMin)
			{
				display.clear();
				display.showText(text);
				display.showTextI("\n&7请输入你已经连续多少抽没有获得过五星武器[", tempMin, "~255]:\n");
				if (tempMin > 0)
				{
					display.showText("&7输入0退出计算。\n");
				}
				wishpool.star5Guar[2] = (unsigned int)display.getInputInt(255, false);
				if (tempMin > 0 && wishpool.star5Guar[2] == 0)
				{
					return;
				}
				tempCoordY = display.getCursorPosY();
				while ((int)wishpool.star5Guar[2] < tempMin || wishpool.star5Guar[2] > 255)
				{
					display.clearText(8, 0, tempCoordY);
					display.clearText(40, 0, tempCoordY - 1);
					display.showTextI("&C输入的数值无效，请重新输入[", tempMin, "~255]。&7\n");
					wishpool.star5Guar[2] = (unsigned int)display.getInputInt(255, false);
					if (tempMin > 0 && wishpool.star5Guar[2] == 0)
					{
						return;
					}
				}
				text += "&b已连续 &a";
				text += display.intToString((int)wishpool.star5Guar[2]);
				text += " &b抽未获得五星武器\n";
				if (wishpool.star5Guar[1] == wishpool.star5Guar[2])
				{
					guar5ParaNeed[2] = false;
					text += "&a从来没有&b在该卡池中抽出过五星物品\n";
				}
			}
		}
		if (guar5ParaNeed[2] == true)
		{
			display.clear();
			display.showText(text);
			display.showText("\n&7上次出的五星物品是up物品吗\n");
			display.showButton('1', "是的，是up物品之一");
			display.showButton('2', "不是，是up物品以外的");
			if (guar5ParaNeed[1] == false)
			{
				display.showButton('3', "我从来没有在该卡池中抽出过五星物品");
			}
			display.showButton('0', "退出计算");
			opr = display.selectButton();
			if (opr == '0')
			{
				return;
			}
			else if (opr == '1')
			{
				text += "&b上次出的五星物品&a是&bup物品\n";
				wishpool.star5Guar[3] = 0;
			}
			else if (opr == '2')
			{
				text += "&b上次出的五星物品&a不是&bup物品\n";
				wishpool.star5Guar[3] = 1;
			}
			else if (opr == '3')
			{
				text += "&a从来没有&b在该卡池中抽出过五星物品\n";
				vector<string> chooseItem;
				chooseItem.push_back(wishpool.star5Up[0]);
				wishpool.setStar5Choose(chooseItem);
				wishpool.star5Guar[3] = 0;
				if (wantPoolId == 2)
				{
					if (guar5ParaNeed[3] == true)
					{
						text += "&b已经积累了&a 0 &b命定值\n";
						guar5ParaNeed[3] = false;
					}
				}
			}
		}
		if (guar5ParaNeed[3] == true)
		{
			vector<string> chooseItem = { wishpool.star5Up[0] };
			wishpool.setStar5Choose(chooseItem);
			display.clear();
			display.showText(text);
			display.showText("\n&7请输入你已经积累的命定值[0~2]:\n");
			wishpool.star5Guar[4] = (unsigned int)display.getInputInt(2, false);
			text += "&b已经积累了 &a";
			text += display.intToString((int)wishpool.star5Guar[4]);
			text += " &b命定值\n";
		}
		if (guar4ParaNeed[0] == true)
		{
			if (wishpool.star5Guar[0] == 0)
			{
				display.clear();
				display.showText(text);
				display.showText("\n&7请输入你已经连续多少抽没有获得过四星物品[0~100000]:\n");
				wishpool.star4Guar[0] = (unsigned int)display.getInputInt(100000, false);
				text += "&b已连续 &a";
				text += display.intToString((int)wishpool.star4Guar[0]);
				text += " &b抽未获得四星物品\n";
			}
			else
			{
				display.clear();
				display.showText(text);
				display.showText("\n&7请输入你已经连续多少抽没有获得过四星物品[0~9]:\n");
				wishpool.star4Guar[0] = (unsigned int)display.getInputInt(9, false);
				text += "&b已连续 &a";
				text += display.intToString((int)wishpool.star4Guar[0]);
				text += " &b抽未获得四星物品\n";
			}
			if (wishpool.star5Guar[0] == wishpool.star4Guar[0])
			{
				guar4ParaNeed[1] = false;
				guar4ParaNeed[2] = false;
				wishpool.star4Guar[1] = wishpool.star4Guar[0];
				wishpool.star4Guar[2] = wishpool.star4Guar[0];
				text += "&a从来没有&b在该卡池中抽出过四星物品\n";
			}
		}
		if (guar4ParaNeed[1] == true)
		{
			int tempMin = (int)wishpool.star4Guar[0];
			int tempCoordY = 0;

			display.clear();
			display.showText(text);
			display.showTextI("\n&7请输入你已经连续多少抽没有获得过四星角色[", tempMin, "~100000]:\n");
			if (tempMin > 0)
			{
				display.showText("&7输入0退出计算。\n");
			}
			wishpool.star4Guar[1] = (unsigned int)display.getInputInt(100000, false);
			if (tempMin > 0 && wishpool.star4Guar[1] == 0)
			{
				return;
			}
			tempCoordY = display.getCursorPosY();
			while ((int)wishpool.star4Guar[1] < tempMin || wishpool.star4Guar[1] > 100000)
			{
				display.clearText(8, 0, tempCoordY);
				display.clearText(40, 0, tempCoordY - 1);
				display.showTextI("&C输入的数值无效，请重新输入[", tempMin, "~100000]。&7\n");
				wishpool.star4Guar[1] = (unsigned int)display.getInputInt(100000, false);
				if (tempMin > 0 && wishpool.star4Guar[1] == 0)
				{
					return;
				}
			}
			text += "&b已连续 &a";
			text += display.intToString((int)wishpool.star4Guar[1]);
			text += " &b抽未获得四星角色\n";
			if ((int)wishpool.star4Guar[1] > tempMin)
			{
				wishpool.star4Guar[2] = tempMin;
				text += "&b已连续 &a";
				text += display.intToString((int)wishpool.star4Guar[2]);
				text += " &b抽未获得四星武器\n";
			}
			else if ((int)wishpool.star4Guar[1] == tempMin)
			{
				display.clear();
				display.showText(text);
				display.showTextI("\n&7请输入你已经连续多少抽没有获得过四星武器[", tempMin, "~100000]:\n");
				if (tempMin > 0)
				{
					display.showText("&7输入0退出计算。\n");
				}
				wishpool.star4Guar[2] = (unsigned int)display.getInputInt(100000, false);
				if (tempMin > 0 && wishpool.star4Guar[2] == 0)
				{
					return;
				}
				tempCoordY = display.getCursorPosY();
				while ((int)wishpool.star4Guar[2] < tempMin || wishpool.star4Guar[2] > 100000)
				{
					display.clearText(8, 0, tempCoordY);
					display.clearText(40, 0, tempCoordY - 1);
					display.showTextI("&C输入的数值无效，请重新输入[", tempMin, "~100000]。&7\n");
					wishpool.star4Guar[2] = (unsigned int)display.getInputInt(100000, false);
					if (tempMin > 0 && wishpool.star4Guar[2] == 0)
					{
						return;
					}
				}
				text += "&b已连续 &a";
				text += display.intToString((int)wishpool.star4Guar[2]);
				text += " &b抽未获得四星武器\n";
				if (wishpool.star4Guar[1] == wishpool.star4Guar[2])
				{
					guar4ParaNeed[2] = false;
					text += "&a从来没有&b在该卡池中抽出过四星物品\n";
				}
			}
		}
		if (guar4ParaNeed[2] == true)
		{
			display.clear();
			display.showText(text);
			display.showText("\n&7上次出的四星物品是up物品吗\n");
			display.showButton('1', "是的，是up物品之一");
			display.showButton('2', "不是，是up物品以外的");
			if (guar4ParaNeed[1] == false && wishpool.star5Guar[0] < 10)
			{
				display.showButton('3', "我从来没有在该卡池中抽出过四星物品");
			}
			display.showButton('0', "退出计算");
			opr = display.selectButton();
			if (opr == '0')
			{
				return;
			}
			else if (opr == '1')
			{
				text += "&b上次出的四星物品&a是&bup物品\n";
				wishpool.star4Guar[3] = 0;
			}
			else if (opr == '2')
			{
				text += "&b上次出的四星物品&a不是&bup物品\n";
				wishpool.star4Guar[3] = 1;
			}
			else if (opr == '3')
			{
				text += "&a从来没有&b在该卡池中抽出过四星物品\n";
				wishpool.star4Guar[3] = 0;
			}
		}

		display.clear();
		display.showText(text);

		if (debugSet == "开启")
		{
			display.showText("\n");
			display.showCodeText("(vector<bool>) guar5ParaNeed = "
				+ display.vectorBoolToString(guar5ParaNeed) + "\n");
			display.showCodeText("(vector<bool>) guar4ParaNeed = "
				+ display.vectorBoolToString(guar4ParaNeed) + "\n");
			display.showCodeText("(vector<string>)wantItem.size() = "
				+ display.intToString((int)wantItem.size()) + "\n");
			display.showCodeText("(WishPool)wishpool.(vector<unsigned int>)star5Guar = "
				+ display.vectorUIntToString(wishpool.star5Guar) + "\n");
			display.showCodeText("(WishPool)wishpool.(vector<unsigned int>)star4Guar = "
				+ display.vectorUIntToString(wishpool.star4Guar) + "\n");
		}

		display.showText("\n&7请输入你想要模拟的次数[1~999999999]，建议设置为100000。\n");
		display.showText("&7输入的数字越大，模拟结果会越精确，但会导致计算时间变长。\n");
		display.showText("&7输入0退出计算。\n");
		simTime = display.getInputInt(999999999, false);
		if (simTime == 0)
		{
			return;
		}

		text = this->showCaculatingUi(wishpool, text, wantItem, wantCount, hasCount, simTime);
		display.clear();
		display.showText(text);
		display.showButton('0', "退出计算");
		opr = display.selectButton();
	}
}