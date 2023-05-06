#include "WishUi.h"

void WishUi::connectVector(vector<string>* subject, vector<string>* object)
{
	unsigned int i = 0;
	unsigned int length = (unsigned int) object->size();
	for (i = 0; i < length; i++)
	{
		subject->push_back((*object)[i]);
	}
}

string WishUi::showItem(WishHistory item)
{
	string colorlist[] = { "&7","&8","&A","&3","&D","&6","&4" };
	string result = colorlist[item.getStar(0)];
	result = result + item.getItem(0);

	return result;
}

void WishUi::createLimitWishPool()
{
	Data data;
	vector<string> star3 = data.getStayWishList(3);
	vector<string> star4Person = data.getLimitWishList(4, false, ITEM_TYPE_PERSON);
	vector<string> star4Weapon = data.getLimitWishList(4, false, ITEM_TYPE_WEAPON);
	vector<string> star5Person = data.getLimitWishList(5, false, ITEM_TYPE_PERSON);
	vector<string> star5Weapon;
	vector<string> star4Up = data.getLimitWishList(4, true);
	vector<string> star5Up = data.getLimitWishList(5, true);
	//卡池1
	this->wishPool.push_back(WishPool("角色活动祈愿", true, false));
	this->wishPool[0].setBaseItem(star3, star4Person, star4Weapon);
	this->wishPool[0].setUpItem(star4Up, star5Up, ITEM_TYPE_PERSON);
	this->wishPool[0].setStar5Person(star5Person);
	this->wishPool[0].setStar5Weapon(star5Weapon);
	//出货概率
	this->wishPool[0].setTemplatePby(1);
}

void WishUi::createWeaponWishPool()
{
	Data data;
	vector<string> star3 = data.getStayWishList(3);
	vector<string> star4Person = data.getWeaponWishList(4, false, ITEM_TYPE_PERSON);
	vector<string> star4Weapon = data.getWeaponWishList(4, false, ITEM_TYPE_WEAPON);
	vector<string> star5Person;
	vector<string> star5Weapon = data.getWeaponWishList(5, false, ITEM_TYPE_WEAPON);
	vector<string> star4Up = data.getWeaponWishList(4, true);
	vector<string> star5Up = data.getWeaponWishList(5, true);
	//卡池2
	this->wishPool.push_back(WishPool("武器活动祈愿", true, true));
	this->wishPool[1].setBaseItem(star3, star4Person, star4Weapon);
	this->wishPool[1].setUpItem(star4Up, star5Up, ITEM_TYPE_WEAPON);
	this->wishPool[1].setStar5Person(star5Person);
	this->wishPool[1].setStar5Weapon(star5Weapon);
	//出货概率
	this->wishPool[1].setTemplatePby(2);
}

void WishUi::createStayWishPool()
{
	Data data;
	vector<string> star3 = data.getStayWishList(3);
	vector<string> star4Person = data.getStayWishList(4, ITEM_TYPE_PERSON);
	vector<string> star4Weapon = data.getStayWishList(4, ITEM_TYPE_WEAPON);
	vector<string> star5Person = data.getStayWishList(5, ITEM_TYPE_PERSON);
	vector<string> star5Weapon = data.getStayWishList(5, ITEM_TYPE_WEAPON);;
	//卡池3
	this->wishPool.push_back(WishPool("常驻祈愿", false, false));
	this->wishPool[2].setBaseItem(star3, star4Person, star4Weapon);
	this->wishPool[2].setStar5Person(star5Person);
	this->wishPool[2].setStar5Weapon(star5Weapon);
	//出货概率
	this->wishPool[2].setTemplatePby(3);
}

unsigned int WishUi::showHistoryList(string type, unsigned int poolPos, unsigned int minNum, unsigned int maxNum,
	short selectStarMin, short selectStarMax, int itemType, string name,
	unsigned int minDistance, unsigned int maxDistance)
{
	Display display;
	string tempS;
	WishHistory history = this->wishPool[poolPos].getHistory();
	vector<unsigned int> distance;
	vector<unsigned int> tempDistance = { 0,0,0 }; //3星，4星，5星距离
	string listSet = type;
	unsigned int length = history.getLength();
	unsigned int outputCount = 0;
	unsigned int i = 0;

	if (listSet == "自动决定")
	{
		if (maxNum - minNum + 1 <= MAXLOAD_HISTORY)
		{
			listSet = "表格";
		}
		else
		{
			listSet = "列举";
		}
	}
	//计算距离
	for (i = 0; i < length; i++)
	{
		tempDistance[0]++;
		tempDistance[1]++;
		tempDistance[2]++;

		if (history.getStar(i) == 3)
		{
			distance.push_back(tempDistance[0]);
			tempDistance[0] = 0;
		}
		else if (history.getStar(i) == 4)
		{
			distance.push_back(tempDistance[1]);
			tempDistance[1] = 0;

		}
		else if (history.getStar(i) == 5)
		{
			distance.push_back(tempDistance[2]);
			tempDistance[2] = 0;
		}
		else
		{
			distance.push_back(0);
		}
	}
	//显示列表
	if (listSet == "表格")
	{
		for (i = minNum - 1; i < maxNum; i++)
		{
			if (history.getStar(i) >= selectStarMin && history.getStar(i) <= selectStarMax &&
				(itemType == history.getType(i) || itemType == -1) && (name == history.getItem(i) || name == "") 
				&& distance[i] >= minDistance && distance[i] <= maxDistance)
			{
				if (outputCount == 0)
				{
					display.createText("&B序号", 0, display.getCursorPosY());
					display.createText("&B星级", 8, display.getCursorPosY());
					display.createText("&B类型", 14, display.getCursorPosY());
					display.createText("&B名称", 20, display.getCursorPosY());
					display.createText("&B间隔", 35, display.getCursorPosY());
					display.showText("\n");
				}
				outputCount++;
				if (history.getStar(i) == 3)
				{
					tempS = "&3";
					display.showTextI((int)history.getNum(i), 3);
					display.setCursorPos(8, display.getCursorPosY());
					display.showText("&3三星");
				}
				else if (history.getStar(i) == 4)
				{
					tempS = "&D";
					display.showTextI((int)history.getNum(i), 13);
					display.setCursorPos(8, display.getCursorPosY());
					display.showText("&D四星");
				}
				else if (history.getStar(i) == 5)
				{
					tempS = "&6";
					display.showTextI((int)history.getNum(i), 6);
					display.setCursorPos(8, display.getCursorPosY());
					display.showText("&6五星");
				}
				else
				{
					tempS = "&7";
					display.showTextI((int)history.getNum(i), 7);
					display.setCursorPos(8, display.getCursorPosY());
					display.showText("&7星级");
				}
				display.setCursorPos(14, display.getCursorPosY());
				display.showText(tempS);
				if (history.getType(i) == ITEM_TYPE_PERSON)
				{
					display.showText("角色");
				}
				else if (history.getType(i) == ITEM_TYPE_WEAPON)
				{
					display.showText("武器");
				}
				else
				{
					display.showText("类型");
				}
				display.setCursorPos(20, display.getCursorPosY());
				display.showText(tempS);
				display.showText(history.getItem(i));
				display.setCursorPos(35, display.getCursorPosY());
				display.showText(tempS);
				display.showTextI(distance[i]);
				display.showText("\n");
			}
		}
	}
	else if (listSet == "列举")
	{
		bool isFirst = true;
		for (i = minNum - 1; i < maxNum; i++)
		{
			if (history.getStar(i) >= selectStarMin && history.getStar(i) <= selectStarMax &&
				(itemType == history.getType(i) || itemType == -1) && (name == history.getItem(i) || name == "")
				&& distance[i] >= minDistance && distance[i] <= maxDistance)
			{
				outputCount++;
				if (isFirst == false)
				{
					display.showText("    ");
				}
				display.showText(this->showItem(history.cut(i)));
				if (history.getStar(i) == 5 || history.getStar(i) == 4)
				{
					display.showTextI("&7[", distance[i], "]");
				}
				isFirst = false;
			}
		}
		if (outputCount > 0)
		{
			display.showText("\n");
		}
	}
	if (outputCount == 0)
	{
		display.showText("&C暂无数据\n");
	}

	return outputCount;
}

WishHistory WishUi::selectHistory(unsigned int poolPos, short star)
{
	WishHistory temp = this->wishPool[poolPos].getHistory();
	WishHistory result;
	unsigned int length = temp.getLength();
	unsigned int i = 0;

	for (i = 0; i < length; i++)
	{
		if (temp.getStar(i) == star)
		{
			result.add(temp.getNum(i), temp.getItem(i), temp.getType(i), temp.getStar(i));
		}
	}

	return result;
}

WishHistory WishUi::selectHistory(unsigned int poolPos, short star, int type)
{
	WishHistory temp = this->wishPool[poolPos].getHistory();
	WishHistory result;
	unsigned int length = temp.getLength();
	unsigned int i = 0;

	for (i = 0; i < length; i++)
	{
		if (temp.getStar(i) == star && temp.getType(i) == type)
		{
			result.add(temp.getNum(i), temp.getItem(i), temp.getType(i), temp.getStar(i));
		}
	}

	return result;
}

WishUi::WishUi()
{
	this->createLimitWishPool();
	this->createWeaponWishPool();
	this->createStayWishPool();
}

void WishUi::showUi()
{
	Display display;
	Data data;
	Option option;
	char opr = '\0';

	string debugSet = option.currentSet[option.getOptionPos("调试信息")];
	
	while (opr != '0')
	{
		unsigned int i = 0;
		unsigned int poolNum = 0;
		vector<unsigned int> oprList;

		display.clear();
		display.showText("&7原神工具 &8>&7 主菜单 &8> &7祈愿(模拟器)\n\n");

		if (debugSet == "开启")
		{
			display.showCodeText("(Data)data.(unsigned int)getLimitWishCount() = "
				+ display.intToString((int)data.getLimitWishCount()) + "\n");
			display.showCodeText("this->wishPool.size() = "
				+ display.intToString((int)this->wishPool.size()) + "\n");
			display.showText("\n");
		}

		if (data.getLimitWishCount() > 1)
		{
			for (i = 0; i < data.getLimitWishCount(); i++)
			{
				display.showButton('1' + i, this->wishPool[0].getPoolName()
					+ " - " + data.getLimitWishList(5, true, ITEM_TYPE_PERSON, i + 1)[0]);
				oprList.push_back(10 + i);
			}
		}
		else
		{
			display.showButton('1' + i, this->wishPool[0].getPoolName());
			oprList.push_back(10 + i);
			i++;
		}
		display.showButton('1' + i, this->wishPool[1].getPoolName());
		oprList.push_back(20 + i);
		i++;
		display.showButton('1' + i, this->wishPool[2].getPoolName());
		oprList.push_back(30 + i);
		display.showButton('7', "历史记录");
		display.showButton('8', "统计数据");
		display.showButton('0', "返回");
		opr = display.selectButton();
		poolNum = (unsigned int)opr - '1';

		if (opr == '7')
		{
			this->showHistoryUi(false);
		}
		else if (opr == '8')
		{
			this->showHistoryUi(true);
		}
		else if (opr == '0')
		{
			break;
		}
		else if (oprList[poolNum] / 10 == 1)
		{
			this->showLimitWishPoolUi(oprList[poolNum] % 10 + 1);
		}
		else if (oprList[poolNum] / 10 == 2)
		{
			this->showWeaponWishPoolUi();
		}
		else if (oprList[poolNum] / 10 == 3)
		{
			this->showStayWishPoolUi();
		}
	}
}

void WishUi::showLimitWishPoolUi(int poolId)
{
	Display display;
	Data data;
	Option option;
	char opr = '\0';
	unsigned int poolCount = data.getLimitWishCount();
	string debugSet = option.currentSet[option.getOptionPos("调试信息")];

	if (poolCount > 1)
	{
		vector<string> star4Up = data.getLimitWishList(4, true, ITEM_TYPE_PERSON, poolId);
		vector<string> star5Up = data.getLimitWishList(5, true, ITEM_TYPE_PERSON, poolId);
		this->wishPool[0].setUpItem(star4Up, star5Up, ITEM_TYPE_PERSON);
	}
	
	while (opr != '0')
	{
		display.clear();

		if (poolCount == 1)
		{
			display.showText("&7原神工具 &8>&7 主菜单 &8> &7祈愿(模拟器) &8>&7 角色活动祈愿\n\n");
		}
		else
		{
			display.showText("&7原神工具 &8>&7 主菜单 &8> &7祈愿(模拟器) &8>&7 角色活动祈愿 - ");
			display.showText(data.getLimitWishList(5, true, ITEM_TYPE_PERSON, poolId)[0]);
			display.showText("\n\n");
		}

		if (debugSet == "开启")
		{
			string debugTempS = "(unsigned int) poolCount = ";
			display.showCodeText("this->wishPool.size() = "
				+ display.intToString((int)this->wishPool.size()) + "\n");
			debugTempS += display.intToString((int)poolCount);
			debugTempS += "\n";
			display.showCodeText(debugTempS);
			debugTempS = "(int) poolId = ";
			debugTempS += display.intToString((int)poolId);
			debugTempS += "\n";
			display.showCodeText(debugTempS);
			display.showCodeText("this->wishPool[0].(string)getPoolName() = \""
				+ this->wishPool[0].getPoolName() + "\"\n");

			debugTempS = "this->wishPool[0].(vector<unsigned int>)star5Guar = ";
			debugTempS += display.vectorUIntToString(this->wishPool[0].star5Guar);
			debugTempS += "\n";
			display.showCodeText(debugTempS);

			debugTempS = "this->wishPool[0].(vector<unsigned int>)star4Guar = ";
			debugTempS += display.vectorUIntToString(this->wishPool[0].star4Guar);
			debugTempS += "\n";
			display.showCodeText(debugTempS);

			debugTempS = "RandEngine::(unsigned long)getSeed() = ";
			debugTempS += display.intToString((int)RandEngine::getSeed());
			debugTempS += "\n";
			display.showCodeText(debugTempS);

			debugTempS = "RandEngine::(unsigned int)getListPos() = ";
			debugTempS += display.intToString((int)RandEngine::getListPos());
			debugTempS += "\n";
			display.showCodeText(debugTempS);

			display.showText("\n");
		}

		display.showButton('1', "祈愿一次");
		display.showButton('2', "祈愿十次");
		display.showButton('3', "自定义祈愿次数");
		display.showButton('8', "物品列表");
		display.showButton('0', "返回");
		opr = display.selectButton();

		if (opr == '1')
		{
			this->singleWishResult(0);
		}
		else if (opr == '2')
		{
			this->templeWishResult(0);
		}
		else if (opr == '3')
		{
			int n = 0;
			display.clearButton('1', false);
			display.clearAllButton();
			display.showText("请输入你想要祈愿的次数[1~1000]:\n");
			display.showText("输入0返回。\n");
			n = display.getInputInt(1000, false);
			if (n == 0)
			{
				continue;
			}
			this->nWishResult(0, n);
		}
		else if (opr == '8')
		{
			this->showItemList(0);
		}
	}
}

void WishUi::showWeaponWishPoolUi()
{
	Display display;
	char opr = '\0';
	string selectItem;
	Option option;
	string tempS;
	string debugSet = option.currentSet[option.getOptionPos("调试信息")];

	while (opr != '0')
	{
		display.clear();
		display.showText("&7原神工具 &8>&7 主菜单 &8> &7祈愿(模拟器) &8>&7 武器活动祈愿\n\n");
		selectItem = this->wishPool[1].getStar5Choose()[0];

		if (debugSet == "开启")
		{
			string debugTempS;
			display.showCodeText("this->wishPool.size() = "
				+ display.intToString((int)this->wishPool.size()) + "\n");
			display.showCodeText("this->wishPool[1].(string)getPoolName() = \""
				+ this->wishPool[1].getPoolName() + "\"\n");
			display.showCodeText("(string) selectItem = \"" + selectItem + "\"\n");

			debugTempS = "this->wishPool[1].(vector<unsigned int>)star5Guar = ";
			debugTempS += display.vectorUIntToString(this->wishPool[1].star5Guar);
			debugTempS += "\n";
			display.showCodeText(debugTempS);

			debugTempS = "this->wishPool[1].(vector<unsigned int>)star4Guar = ";
			debugTempS += display.vectorUIntToString(this->wishPool[1].star4Guar);
			debugTempS += "\n";
			display.showCodeText(debugTempS);

			debugTempS = "RandEngine::(unsigned long)getSeed() = ";
			debugTempS += display.intToString((int)RandEngine::getSeed());
			debugTempS += "\n";
			display.showCodeText(debugTempS);

			debugTempS = "RandEngine::(unsigned int)getListPos() = ";
			debugTempS += display.intToString((int)RandEngine::getListPos());
			debugTempS += "\n";
			display.showCodeText(debugTempS);

			display.showText("\n");
		}

		if (selectItem == "取消定轨")
		{
			display.showText("&E当前未定轨武器");
		}
		else
		{
			tempS = "&E已定轨武器:&6" + selectItem;
			display.showText(tempS);
			display.showTextI("\n&B命定值:&A", this->wishPool[1].star5Guar[4], "&B/2");
		}
		display.showText("\n\n");

		display.showButton('1', "祈愿一次");
		display.showButton('2', "祈愿十次");
		display.showButton('3', "自定义祈愿次数");
		display.showButton('8', "物品列表");
		display.showButton('9', "神铸定轨");
		display.showButton('0', "返回");
		opr = display.selectButton();

		if (opr == '1')
		{
			this->singleWishResult(1);
		}
		else if (opr == '2')
		{
			this->templeWishResult(1);
		}
		else if (opr == '3')
		{
			int n = 0;
			display.clearButton('1', false);
			display.clearAllButton();
			display.showText("请输入你想要祈愿的次数[1~1000]:\n");
			display.showText("输入0返回。\n");
			n = display.getInputInt(1000, false);
			if (n == 0)
			{
				continue;
			}
			this->nWishResult(1, n);
		}
		else if (opr == '8')
		{
			this->showItemList(1);
		}
		else if (opr == '9')
		{
			this->showChooseUi();
		}
	}
}

void WishUi::showStayWishPoolUi()
{
	Display display;
	Option option;
	char opr = '\0';
	string debugSet = option.currentSet[option.getOptionPos("调试信息")];

	while (opr != '0')
	{
		display.clear();
		display.showText("&7原神工具 &8>&7 主菜单 &8> &7祈愿(模拟器) &8>&7 常驻祈愿\n\n");

		if (debugSet == "开启")
		{
			string debugTempS;
			display.showCodeText("this->wishPool.size() = "
				+ display.intToString((int)this->wishPool.size()) + "\n");
			display.showCodeText("this->wishPool[2].(string)getPoolName() = \""
				+ this->wishPool[2].getPoolName() + "\"\n");

			debugTempS = "this->wishPool[2].(vector<unsigned int>)star5Guar = ";
			debugTempS += display.vectorUIntToString(this->wishPool[2].star5Guar);
			debugTempS += "\n";
			display.showCodeText(debugTempS);

			debugTempS = "this->wishPool[2].(vector<unsigned int>)star4Guar = ";
			debugTempS += display.vectorUIntToString(this->wishPool[2].star4Guar);
			debugTempS += "\n";
			display.showCodeText(debugTempS);

			debugTempS = "RandEngine::(unsigned long)getSeed() = ";
			debugTempS += display.intToString((int)RandEngine::getSeed());
			debugTempS += "\n";
			display.showCodeText(debugTempS);

			debugTempS = "RandEngine::(unsigned int)getListPos() = ";
			debugTempS += display.intToString((int)RandEngine::getListPos());
			debugTempS += "\n";
			display.showCodeText(debugTempS);

			display.showText("\n");
		}

		display.showButton('1', "祈愿一次");
		display.showButton('2', "祈愿十次");
		display.showButton('3', "自定义祈愿次数");
		display.showButton('8', "物品列表");
		display.showButton('0', "返回");
		opr = display.selectButton();

		if (opr == '1')
		{
			this->singleWishResult(2);
		}
		else if (opr == '2')
		{
			this->templeWishResult(2);
		}
		else if (opr == '3')
		{
			int n = 0;
			display.clearButton('1', false);
			display.clearAllButton();
			display.showText("请输入你想要祈愿的次数[1~1000]:\n");
			display.showText("输入0返回。\n");
			n = display.getInputInt(1000, false);
			if (n == 0)
			{
				continue;
			}
			this->nWishResult(2, n);
		}
		else if (opr == '8')
		{
			this->showItemList(2);
		}
	}
}

void WishUi::showChooseUi()
{
	Display display;
	char opr = '\0';
	string selectItem[3];
	string tempS;
	Data list;
	Option option;
	string debugSet = option.currentSet[option.getOptionPos("调试信息")];

	while (opr != '0')
	{
		display.clear();
		display.showText("&7原神工具 &8>&7 主菜单 &8> &7祈愿(模拟器) &8>&7 武器活动祈愿 &8>&7 神铸定轨\n\n");

		selectItem[0] = this->wishPool[1].getStar5Choose()[0];
		selectItem[1] = list.getWeaponWishList(5, true)[0];
		selectItem[2] = list.getWeaponWishList(5, true)[1];

		if (debugSet == "开启")
		{
			display.showCodeText("(string[3]) selectItem = { \"" + selectItem[0] + "\", \"" +
				selectItem[1] + "\", \"" + selectItem[2] + "\" }\n");

			display.showText("\n");
		}

		if (selectItem[0] == "取消定轨")
		{
			display.showText("&E当前未定轨武器");
		}
		else
		{
			tempS = "&E已定轨武器:&6" + selectItem[0];
			display.showText(tempS);
			display.showTextI("\n&B命定值:&A", this->wishPool[1].star5Guar[4], "&B/2");
		}
		display.showText("\n\n");

		if (selectItem[0] != selectItem[1])
		{
			display.showButton('1', "&6" + selectItem[1], true, 6);
		}
		if (selectItem[0] != selectItem[2])
		{
			display.showButton('2', "&6" + selectItem[2], true, 6);
		}
		if (selectItem[0] != "取消定轨")
		{
			display.showButton('3', "取消定轨");
		}

		display.showButton('0', "返回");
		opr = display.selectButton();

		if (opr == '1')
		{
			vector<string> choose;
			choose.push_back(selectItem[1]);
			this->wishPool[1].setStar5Choose(choose);
		}
		else if (opr == '2')
		{
			vector<string> choose;
			choose.push_back(selectItem[2]);
			this->wishPool[1].setStar5Choose(choose);
		}
		else if (opr == '3')
		{
			vector<string> choose;
			choose.push_back("取消定轨");
			this->wishPool[1].setStar5Choose(choose);
		}
	}
}

void WishUi::showHistoryUi(bool isStatic)
{
	Display display;
	Option option;
	char opr = '\0';
	bool showStatic = isStatic;
	int tempI = 0;
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int length = (unsigned int)this->wishPool.size();
	unsigned int num = 0;
	vector<WishHistory> history;
	string listSet = option.currentSet[option.getOptionPos("祈愿历史记录显示方式")];
	string debugSet = option.currentSet[option.getOptionPos("调试信息")];
	
	for (i = 0; i < length; i++)
	{
		history.push_back(this->wishPool[i].getHistory());
		tempI += this->wishPool[i].getHistory().getLength();
	}
	if (listSet == "自动决定")
	{
		if (tempI <= MAXLOAD_HISTORY)
		{
			listSet = "表格";
		}
		else
		{
			listSet = "列举";
		}
	}
	tempI = 0;

	while (opr != '0')
	{
		display.clear();
		if (showStatic == false)
		{
			unsigned int distance[3] = { 0,0,0 };
			display.showText("&7原神工具 &8>&7 主菜单 &8> &7祈愿(模拟器) &8>&7 历史记录\n\n");

			if (debugSet == "开启")
			{
				display.showCodeText("(unsigned int) length = " + display.intToString(length) + "\n");
				display.showCodeText("(vector<WishHistory>) history.size() = " +
					display.intToString((int)history.size()) + "\n");

				display.showText("\n");
			}

			for (i = 0; i < length; i++)
			{
				unsigned int maxSize = 1000; //同时最多显示历史记录的条数
				if (listSet == "列举")
				{
					maxSize = 5000;
				}

				num = history[i].getLength();
				display.showText("&7");
				display.showText(this->wishPool[i].getPoolName());
				display.showText("\n");
				if (num <= maxSize)
				{
					this->showHistoryList(listSet, i, 1, num);
				}
				else
				{
					display.showTextI("&C只显示后", maxSize, "条历史记录。\n");
					this->showHistoryList(listSet, i, num - maxSize + 1, num);
				}
				display.showText("\n");
			}
			
			display.showButton('1', "统计数据");
			if (listSet == "表格")
			{
				display.showButton('5', "以列举的方式显示");
				display.showButton('9', "筛选");
			}
			else if (listSet == "列举")
			{
				display.showButton('5', "以表格的形式显示");
			}
			display.showButton('0', "返回");
			opr = display.selectButton();
			if (opr == '1')
			{
				showStatic = true;
				continue;
			}
			else if (opr == '5')
			{
				if (listSet == "表格")
				{
					listSet = "列举";
				}
				else if (listSet == "列举")
				{
					listSet = "表格";
				}
			}
			else if (opr == '9')
			{
				this->showSelectHistoryUi();
			}
		}
		else
		{
			display.showText("&7原神工具 &8>&7 主菜单 &8> &7祈愿(模拟器) &8>&7 统计数据\n\n");

			if (debugSet == "开启")
			{
				display.showCodeText("(unsigned int) length = " + display.intToString(length) + "\n");
				display.showCodeText("(vector<WishHistory>) history.size() = " +
					display.intToString((int)history.size()) + "\n");

				display.showText("\n");
			}

			for (i = 0; i < length; i++)
			{
				//记录各个类型的物品的在历史记录中的位置
				vector<unsigned int> star5;
				vector<unsigned int> star5Person;
				vector<unsigned int> star5Weapon;
				vector<unsigned int> star4;
				vector<unsigned int> star4Person;
				vector<unsigned int> star4Weapon;

				vector<double> paraDouble;

				display.showText("&7");
				display.showText(this->wishPool[i].getPoolName());
				display.showText("\n");
				num = history[i].getLength();
				if (num == 0)
				{
					display.showText("&C暂无数据\n\n");
					continue;
				}

				display.showTextI("&B共计 &A", num, " &B抽\n");
				tempI = 0;
				for (j = 0; j < num; j++)
				{
					tempI++;
					if (history[i].getStar(j) == 5)
					{
						tempI = 0;
						star5.push_back(j);
						if (history[i].getType(j) == ITEM_TYPE_PERSON)
						{
							star5Person.push_back(j);
						}
						else
						{
							star5Weapon.push_back(j);
						}
					}
					if (history[i].getStar(j) == 4)
					{
						star4.push_back(j);
						if (history[i].getType(j) == ITEM_TYPE_PERSON)
						{
							star4Person.push_back(j);
						}
						else
						{
							star4Weapon.push_back(j);
						}
					}
				}
				display.showTextI("&B已累计 &A", tempI, " &B抽未出五星\n");
				if (star5.size() > 0)
				{
					paraDouble = { ((double)num - tempI) / (double)star5.size() };
					display.showTextD("&B平均 &A# &B抽出一个五星\n", paraDouble);
				}
				display.showTextI("&B五星共 &A", (int)star5.size(), " &B占总数");
				display.showTextD("&B的 &A", (double)star5.size() / (double)num * 100.0, "&A%\n");
				if (star5Person.size() > 0 && star5Weapon.size() > 0)
				{
					display.showTextI("    &B五星角色共 &A", (int)star5Person.size(), " &B占总数");
					display.showTextD("&B的 &A", (double)star5Person.size() / (double)num * 100.0, "&A%\n");
					display.showTextI("    &B五星武器共 &A", (int)star5Weapon.size(), " &B占总数");
					display.showTextD("&B的 &A", (double)star5Weapon.size() / (double)num * 100.0, "&A%\n");
				}
				display.showTextI("&B四星共 &A", (int)star4.size(), " &B占总数");
				display.showTextD("&B的 &A", (double)star4.size() / (double)num * 100.0, "&A%\n");
				if (star4Person.size() > 0 && star4Weapon.size() > 0)
				{
					display.showTextI("    &B四星角色共 &A", (int)star4Person.size(), " &B占总数");
					display.showTextD("&B的 &A", (double)star4Person.size() / (double)num * 100.0, "&A%\n");
					display.showTextI("    &B四星武器共 &A", (int)star4Weapon.size(), " &B占总数");
					display.showTextD("&B的 &A", (double)star4Weapon.size() / (double)num * 100.0, "&A%\n");
				}
				display.showTextI("&B三星共 &A", num - (int)star5.size() - (int)star4.size(), " &B占总数");
				paraDouble = { ((double)num - (double)star5.size() - (double)star4.size()) / (double)num * 100.0 };
				display.showTextD("&B的 &A#&A%\n", paraDouble);
				if (star5.size() > 0 && star5.size() <= 100)
				{
					display.showText("&A五星历史记录:\n");
					tempI = -1;
					for (j = 0; j < star5.size() - 1; j++)
					{
						display.showTextI("&6" + history[i].getItem(star5[j]) + "&7[", star5[j] - tempI, "&7]    ");
						tempI = star5[j];
					}
					display.showTextI("&6" + history[i].getItem(star5[j]) + "&7[", star5[j] - tempI, "&7]\n");
				}
				else if (star5.size() > 100)
				{
					display.showText("&A五星历史记录[只显示后100个五星]:\n");
					tempI = star5[star5.size() - 101];
					for (j = (unsigned int) star5.size() - 100; j < star5.size() - 1; j++)
					{
						display.showTextI("&6" + history[i].getItem(star5[j]) + "&7[", star5[j] - tempI, "&7]    ");
						tempI = star5[j];
					}
					display.showTextI("&6" + history[i].getItem(star5[j]) + "&7[", star5[j] - tempI, "&7]\n");
				}
				display.showText("\n");
			}

			display.showButton('1', "历史记录");
			display.showButton('0', "返回");
			opr = display.selectButton();
			if (opr == '1')
			{
				showStatic = false;
				continue;
			}
		}
	}
}

void WishUi::showSelectHistoryUi()
{
	Display display;
	Data data;
	unsigned int poolPos = 0;
	vector<int> mNum = { 1,(int)this->wishPool[poolPos].getHistory().getLength() };
	if (mNum[1] > 3000)
	{
		mNum[0] = mNum[1] - 2999;
	}
	vector<int> selectStarM = { 3,5 };
	int type = -1;
	string name = "";
	vector<int> distance = { 1, 90 };
	Option option;
	string debugSet = option.currentSet[option.getOptionPos("调试信息")];

	char opr = '\0';
	int temp = 0;

	while (opr != '0')
	{
		display.clear();
		
		display.showText("&7原神工具 &8>&7 主菜单 &8> &7祈愿(模拟器) &8>&7 历史记录筛选\n\n");

		if (debugSet == "开启")
		{
			display.showCodeText("(vector<int>) mNum = { " + display.intToString(mNum[0])
				+ ", " + display.intToString(mNum[1]) + " }\n");
			display.showCodeText("(vector<int>) selectStarM = { " + display.intToString(selectStarM[0])
				+ ", " + display.intToString(selectStarM[1]) + " }\n");
			display.showCodeText("(vector<int>) distance = { " + display.intToString(distance[0])
				+ ", " + display.intToString(distance[1]) + " }\n");
			display.showCodeText("(int) type = " + display.intToString(type) + "\n");
			display.showCodeText("(unsigned int) poolPos = " + display.intToString((int)poolPos) + "\n");
			display.showCodeText("(string) name = \"" + name + "\"\n");

			display.showText("\n");
		}

		temp = (int)this->showHistoryList("表格", poolPos, (unsigned int)mNum[0], (unsigned int)mNum[1],
			(short)selectStarM[0], (short)selectStarM[1], type, name,
			(unsigned int)distance[0], (unsigned int)distance[1]);
		if (temp > 0)
		{
			display.showTextI("&B共 &A", temp, " &B条符合条件的数据。\n");
		}
		display.showText("\n&B筛选条件:\n");
		display.showText("&B卡池名称:      &6" + this->wishPool[poolPos].getPoolName() + "\n");
		display.showTextI("&B物品星级范围:  &6#&B~&6#&B星\n", selectStarM);
		if (this->wishPool[poolPos].getHistory().getLength() > 0)
		{
			display.showTextI("&B序号范围:      &6#&B~&6#&B\n", mNum);
		}
		if (type == 0)
		{
			display.showText("&B物品类型:      &6角色&B\n");
		}
		else if (type == 1)
		{
			display.showText("&B物品类型:      &6武器&B\n");
		}
		if (name != "")
		{
			display.showText("&B物品名称:      &6" + name + "&B\n");
		}
		display.showTextI("&B间隔:          &6#&B~&6#&B\n", distance);
		display.showText("\n&7");

		display.showButton('1', "修改筛选条件:卡池名称");
		display.showButton('2', "修改筛选条件:物品星级范围");
		if (this->wishPool[poolPos].getHistory().getLength() > 1)
		{
			display.showButton('3', "修改筛选条件:序号范围");
		}
		display.showButton('4', "修改筛选条件:物品类型");
		if (selectStarM[0] == selectStarM[1] && type != -1)
		{
			display.showButton('5', "修改筛选条件:物品名称");
		}
		display.showButton('6', "修改筛选条件:间隔");
		display.showButton('0', "返回");
		opr = display.selectButton();
		if (opr == '1')
		{
			int i = 0;
			display.clearButton('1', false);
			display.clearAllButton();
			display.showText("&7修改筛选条件:卡池名称\n");
			display.showText("&B当前选择的卡池:&6" + this->wishPool[poolPos].getPoolName() + "\n\n");
			display.showText("&7请选择一个卡池。\n");
			for (i = 0; i < (int)this->wishPool.size(); i++)
			{
				display.showButton('1' + i, this->wishPool[i].getPoolName());
			}
			display.showButton('0', "放弃修改");
			opr = display.selectButton();
			if (opr >= '1' && opr <= (char)this->wishPool.size() + '0')
			{
				poolPos = (unsigned int)opr - '1';
				mNum = { 1,(int)this->wishPool[poolPos].getHistory().getLength() };
				if (mNum[1] > 3000)
				{
					mNum[0] = mNum[1] - 2999;
				}
			}
			else if (opr == '0')
			{
				opr = '\0';
				continue;
			}
		}
		else if (opr == '2')
		{
			int inputMin = 3;
			display.clearButton('1', false);
			display.clearAllButton();
			display.showText("&7修改筛选条件:物品星级范围\n");
			display.showTextI("&B当前设置的值:&6#&B~&6#&B星\n\n", selectStarM);
			display.showText("&7请输入物品星级的最小值[3~5]:\n");
			display.showText("&7输入0放弃修改。\n");
			temp = display.getInputInt(5, false);
			if (temp == 0)
			{
				continue;
			}
			display.showText("\n");
			while (temp < 3 || temp > 5)
			{
				display.clearText(5, 0, display.getCursorPosY() - 1);
				display.clearText(40, 0, display.getCursorPosY() - 1);
				display.showText("&c输入的数值无效，请重新输入[3~5]&7\n");
				temp = display.getInputInt(5, false);
				if (temp == 0)
				{
					break;
				}
			}
			if (temp == 0)
			{
				continue;
			}
			inputMin = temp;
			if (inputMin == 5)
			{
				selectStarM[0] = inputMin;
				selectStarM[1] = 5;
				name = "";
				continue;
			}
			display.clearText(5, 0, display.getCursorPosY() - 1);
			display.clearText(40, 0, display.getCursorPosY() - 1);
			display.clearText(40, 0, display.getCursorPosY() - 1);
			display.clearText(40, 0, display.getCursorPosY() - 1);
			display.showTextI("&7请输入物品星级的最大值[", inputMin, "~5]:\n");
			display.showText("&7输入0放弃修改。\n");
			temp = display.getInputInt(5, false);
			if (temp == 0)
			{
				continue;
			}
			display.showText("\n");
			while (temp < inputMin || temp > 5)
			{
				display.clearText(5, 0, display.getCursorPosY() - 1);
				display.clearText(40, 0, display.getCursorPosY() - 1);
				display.showTextI("&c输入的数值无效，请重新输入[", inputMin, "~5]&7\n");
				temp = display.getInputInt(5, false);
				if (temp == 0)
				{
					break;
				}
			}
			if (temp == 0)
			{
				continue;
			}
			name = "";
			selectStarM[0] = inputMin;
			selectStarM[1] = temp;
		}
		else if (opr == '3')
		{
			vector<int> inputM = { 1, (int)this->wishPool[poolPos].getHistory().getLength() };
			display.clearButton('1', false);
			display.clearAllButton();
			display.showText("&7修改筛选条件:序号范围\n");
			display.showTextI("&B当前设置的值:&6#&B~&6#&B\n\n", mNum);
			display.showTextI("&7请输入序号的最小值[#~#]:\n", inputM);
			display.showText("&7输入0放弃修改。\n");
			temp = display.getInputInt(inputM[1], false);
			if (temp == 0)
			{
				continue;
			}
			inputM[0] = temp;
			if (inputM[0] == inputM[1])
			{
				mNum[0] = inputM[0];
				mNum[1] = inputM[1];
				continue;
			}
			if(inputM[0] + 2999 < inputM[1])
			{
				inputM[1] = inputM[0] + 2999;
			}
			display.clearText(5, 0, display.getCursorPosY() - 1);
			display.clearText(40, 0, display.getCursorPosY() - 1);
			display.clearText(40, 0, display.getCursorPosY() - 1);
			display.showTextI("&7请输入序号的最大值[#~#]:\n", inputM);
			display.showText("&7输入0放弃修改。\n");
			temp = display.getInputInt(inputM[1], false);
			if (temp == 0)
			{
				continue;
			}
			display.showText("\n");
			while (temp < inputM[0] || temp > inputM[1])
			{
				display.clearText(5, 0, display.getCursorPosY() - 1);
				display.clearText(40, 0, display.getCursorPosY() - 1);
				display.showTextI("&c输入的数值无效，请重新输入[#~#]:&7\n", inputM);
				temp = display.getInputInt(inputM[1], false);
				if (temp == 0)
				{
					break;
				}
			}
			if (temp == 0)
			{
				continue;
			}
			inputM[1] = temp;
			mNum[0] = inputM[0];
			mNum[1] = inputM[1];
		}
		else if (opr == '4')
		{
			display.clearButton('1', false);
			display.clearAllButton();
			display.showText("&7修改筛选条件:物品类型\n");
			if (type == 0)
			{
				display.showText("&B当前筛选:&6角色&B\n\n");
			}
			else if (type == 1)
			{
				display.showText("&B当前筛选:&6武器&B\n\n");
			}
			else if (type == -1)
			{
				display.showText("&B当前未对物品类型进行筛选\n\n");
			}
			display.showText("&7请选择你要筛选的物品类型:\n");
			display.showButton('1', "筛选角色");
			display.showButton('2', "筛选武器");
			display.showButton('3', "取消筛选");
			display.showButton('0', "放弃修改");
			opr = display.selectButton();
			if (opr == '1')
			{
				type = 0;
				name = "";
			}
			if (opr == '2')
			{
				type = 1;
				name = "";
			}
			if (opr == '3')
			{
				type = -1;
				name = "";
			}
			else if (opr == '0')
			{
				opr = '\0';
				continue;
			}
		}
		else if (opr == '5')
		{
			display.clearButton('1', false);
			display.clearAllButton();
			display.showText("&7修改筛选条件:物品名称\n");
			if (name == "")
			{
				display.showText("&B当前未对物品进行筛选。\n");
			}
			else
			{
				display.showText("&B当前筛选的物品内容:&6" + name + "&B\n");
			}
			display.showText("\n&7请选择你想要筛选的物品:\n");
			vector<string> chooseList = { "取消筛选" };
			vector<string> tempVector = data.getItemList((short)selectStarM[0], type);
			int i = 0;
			this->connectVector(&chooseList, &tempVector);
			if (name != "")
			{
				for (i = 0; i < (int)chooseList.size(); i++)
				{
					if (name == chooseList[i])
					{
						break;
					}
				}
			}
			if (i >= (int)chooseList.size())
			{
				i = (int)chooseList.size() - 1;
			}
			string tempS = display.selectString(chooseList, i);
			if (tempS == "取消筛选")
			{
				name = "";
			}
			else
			{
				name = tempS;
			}
		}
		else if (opr == '6')
		{
			int inputMin = 3;
			display.clearButton('1', false);
			display.clearAllButton();
			display.showText("&7修改筛选条件:物品间隔\n");
			display.showTextI("&B当前设置的值:&6#&B~&6#&B\n\n", distance);
			display.showText("&7请输入间隔的最小值[1~90]:\n");
			display.showText("&7输入0放弃修改。\n");
			temp = display.getInputInt(90, false);
			if (temp == 0)
			{
				continue;
			}
			inputMin = temp;
			if (inputMin == 90)
			{
				distance[0] = inputMin;
				distance[1] = 90;
				continue;
			}
			display.clearText(5, 0, display.getCursorPosY() - 1);
			display.clearText(40, 0, display.getCursorPosY() - 1);
			display.clearText(40, 0, display.getCursorPosY() - 1);
			display.showTextI("&7请输入间隔的最大值[", inputMin, "~90]:\n");
			display.showText("&7输入0放弃修改。\n");
			temp = display.getInputInt(90, false);
			if (temp == 0)
			{
				continue;
			}
			display.showText("\n");
			while (temp < inputMin || temp > 90)
			{
				display.clearText(5, 0, display.getCursorPosY() - 1);
				display.clearText(40, 0, display.getCursorPosY() - 1);
				display.showTextI("&c输入的数值无效，请重新输入[", inputMin, "~90]&7\n");
				temp = display.getInputInt(90, false);
				if (temp == 0)
				{
					break;
				}
			}
			if (temp == 0)
			{
				continue;
			}
			distance[0] = inputMin;
			distance[1] = temp;
		}
	}
}

void WishUi::showItemList(int poolId)
{
	Display display;
	Option option;
	string listSet = option.currentSet[option.getOptionPos("祈愿历史记录显示方式")];
	unsigned int length = (unsigned int)this->wishPool.size();
	unsigned int i = 0;
	char opr = '\0';
	if (listSet == "自动决定")
	{
		listSet = "表格";
	}

	while (opr != '0')
	{
		vector<string> itemList;

		display.clear();
		display.showText("&7原神工具 &8>&7 主菜单 &8> &7祈愿(模拟器) &8>&7 物品列表\n\n");
		display.showText(this->wishPool[poolId].getPoolName() + "\n");

		if (listSet == "表格")
		{
			display.showText("&B星级  类型  物品\n");
			if (this->wishPool[poolId].star5Up.size() > 0)
			{
				itemList = this->wishPool[poolId].star5Up;
				if (this->wishPool[poolId].getUpItemType() == ITEM_TYPE_PERSON)
				{
					for (i = 0; i < itemList.size(); i++)
					{
						display.showText("&6五星  角色  " + itemList[i] + "&6[UP]\n");
					}
				}
				else if (this->wishPool[poolId].getUpItemType() == ITEM_TYPE_WEAPON)
				{
					for (i = 0; i < itemList.size(); i++)
					{
						display.showText("&6五星  武器  " + itemList[i] + "&6[UP]\n");
					}
				}
			}
			if (this->wishPool[poolId].star5Person.size() > 0)
			{
				itemList = this->wishPool[poolId].star5Person;
				for (i = 0; i < itemList.size(); i++)
				{
					display.showText("&6五星  角色  " + itemList[i] + "\n");
				}
			}
			if (this->wishPool[poolId].star5Weapon.size() > 0)
			{
				itemList = this->wishPool[poolId].star5Weapon;
				for (i = 0; i < itemList.size(); i++)
				{
					display.showText("&6五星  武器  " + itemList[i] + "\n");
				}
			}
			if (this->wishPool[poolId].star4Up.size() > 0)
			{
				itemList = this->wishPool[poolId].star4Up;
				if (this->wishPool[poolId].getUpItemType() == ITEM_TYPE_PERSON)
				{
					for (i = 0; i < itemList.size(); i++)
					{
						display.showText("&D四星  角色  " + itemList[i] + "&D[UP]\n");
					}
				}
				else if (this->wishPool[poolId].getUpItemType() == ITEM_TYPE_WEAPON)
				{
					for (i = 0; i < itemList.size(); i++)
					{
						display.showText("&D四星  武器  " + itemList[i] + "&D[UP]\n");
					}
				}
			}
			if (this->wishPool[poolId].star4Person.size() > 0)
			{
				itemList = this->wishPool[poolId].star4Person;
				for (i = 0; i < itemList.size(); i++)
				{
					display.showText("&D四星  角色  " + itemList[i] + "\n");
				}
			}
			if (this->wishPool[poolId].star4Weapon.size() > 0)
			{
				itemList = this->wishPool[poolId].star4Weapon;
				for (i = 0; i < itemList.size(); i++)
				{
					display.showText("&D四星  武器  " + itemList[i] + "\n");
				}
			}
			if (this->wishPool[poolId].star3.size() > 0)
			{
				itemList = this->wishPool[poolId].star3;
				for (i = 0; i < itemList.size(); i++)
				{
					display.showText("&3三星  武器  " + itemList[i] + "\n");
				}
			}
			display.showText("\n");
		}
		else if (listSet == "列举")
		{
			if (this->wishPool[poolId].star5Up.size() > 0)
			{
				itemList = this->wishPool[poolId].star5Up;
				if (this->wishPool[poolId].getUpItemType() == ITEM_TYPE_PERSON)
				{
					for (i = 0; i < itemList.size(); i++)
					{
						display.showText("&6" + itemList[i] + "&6[UP]    ");
					}
				}
				else if (this->wishPool[poolId].getUpItemType() == ITEM_TYPE_WEAPON)
				{
					for (i = 0; i < itemList.size(); i++)
					{
						display.showText("&6" + itemList[i] + "&6[UP]    ");
					}
				}
			}
			if (this->wishPool[poolId].star5Person.size() > 0)
			{
				itemList = this->wishPool[poolId].star5Person;
				for (i = 0; i < itemList.size(); i++)
				{
					display.showText("&6" + itemList[i] + "    ");
				}
			}
			if (this->wishPool[poolId].star5Weapon.size() > 0)
			{
				itemList = this->wishPool[poolId].star5Weapon;
				for (i = 0; i < itemList.size(); i++)
				{
					display.showText("&6" + itemList[i] + "    ");
				}
			}
			if (this->wishPool[poolId].star4Up.size() > 0)
			{
				itemList = this->wishPool[poolId].star4Up;
				if (this->wishPool[poolId].getUpItemType() == ITEM_TYPE_PERSON)
				{
					for (i = 0; i < itemList.size(); i++)
					{
						display.showText("&D" + itemList[i] + "&D[UP]    ");
					}
				}
				else if (this->wishPool[poolId].getUpItemType() == ITEM_TYPE_WEAPON)
				{
					for (i = 0; i < itemList.size(); i++)
					{
						display.showText("&D" + itemList[i] + "&D[UP]    ");
					}
				}
			}
			if (this->wishPool[poolId].star4Person.size() > 0)
			{
				itemList = this->wishPool[poolId].star4Person;
				for (i = 0; i < itemList.size(); i++)
				{
					display.showText("&D" + itemList[i] + "    ");
				}
			}
			if (this->wishPool[poolId].star4Weapon.size() > 0)
			{
				itemList = this->wishPool[poolId].star4Weapon;
				for (i = 0; i < itemList.size(); i++)
				{
					display.showText("&D" + itemList[i] + "    ");
				}
			}
			if (this->wishPool[poolId].star3.size() > 0)
			{
				itemList = this->wishPool[poolId].star3;
				for (i = 0; i < itemList.size(); i++)
				{
					display.showText("&3" + itemList[i] + "    ");
				}
			}
			display.showText("\n\n");
		}

		if (listSet == "表格")
		{
			display.showButton('5', "以列举的方式显示");
		}
		else if (listSet == "列举")
		{
			display.showButton('5', "以表格的形式显示");
		}
		display.showButton('0', "返回");
		opr = display.selectButton();
		if (opr == '5')
		{
			if (listSet == "表格")
			{
				listSet = "列举";
			}
			else if (listSet == "列举")
			{
				listSet = "表格";
			}
		}
	}
}

void WishUi::singleWishResult(int poolId)
{
	Display display;
	Option option;
	char opr = '\0';
	int animationSpeed = (int)option.currentChoose[option.getOptionPos("祈愿动画速度")];
	double changeColorPos = option.currentChoose[option.getOptionPos("祈愿动画变色位置")];
	WishHistory result;
	string debugSet = option.currentSet[option.getOptionPos("调试信息")];

	while (opr != '0')
	{
		result = this->wishPool[poolId].singleWish();

		display.clear();
		display.createText("&7原神工具 &8>&7 主菜单 &8> &7祈愿(模拟器) &8>&7 祈愿结果", 0, 0);
		if (option.currentSet[option.getOptionPos("祈愿动画")] == "开启")
		{
			//动画效果
			int colorlist[] = { 7,8,10,3,13,6,4 };
			display.showFakeLoading(50, animationSpeed, '-', '=', 3,
				colorlist[this->wishPool[poolId].getLastItem().getStar(0)], 
				changeColorPos, 0, 2);
		}

		display.setCursorPos(0, 2);
		display.showText(this->showItem(result));
		display.showText("\n\n");

		if (debugSet == "开启")
		{
			display.showCodeText("(int) poolId = " + display.intToString(poolId) + "\n");
			string debugTempS = "RandEngine::(unsigned long)getSeed() = ";
			debugTempS += display.intToString((int)RandEngine::getSeed());
			debugTempS += "\n";
			display.showCodeText(debugTempS);

			debugTempS = "RandEngine::(unsigned int)getListPos() = ";
			debugTempS += display.intToString((int)RandEngine::getListPos());
			debugTempS += "\n";
			display.showCodeText(debugTempS);

			display.showText("\n");
		}

		display.showButton('1', "再祈愿一次");
		display.showButton('0', "返回");
		opr = display.selectButton();
	}
}

void WishUi::templeWishResult(int poolId)
{
	Display display;
	Option option;
	WishHistory result;
	string animationSet = option.currentSet[option.getOptionPos("祈愿动画")];
	string debugSet = option.currentSet[option.getOptionPos("调试信息")];
	int animationSpeed = (int)option.currentChoose[option.getOptionPos("祈愿动画速度")];
	double changeColorPos = option.currentChoose[option.getOptionPos("祈愿动画变色位置")];
	char opr = '\0';
	bool stopAnimation = false;
	int i = 0;

	while (opr != '0')
	{
		display.clear();
		display.createText("&7原神工具 &8>&7 主菜单 &8> &7祈愿(模拟器) &8>&7 祈愿结果", 0, 0);
		result = this->wishPool[poolId].templeWish();
		stopAnimation = false;
		if (animationSet == "开启")
		{
			//动画效果
			int colorlist[] = { 7,8,10,3,13,6,4 };
			display.showFakeLoading(50, animationSpeed, '-', '=', 3,
				colorlist[this->wishPool[poolId].getLast10MaxStar()], 
				changeColorPos, 0, 2);
		}

		display.setCursorPos(0, 2);
		display.clockStart();
		for (i = 0; i < 9; i++)
		{
			display.showText(this->showItem(result.cut(i)));
			display.showText("    ");
			if (animationSet == "开启" && stopAnimation == false)
			{
				Sleep(animationSpeed * 20);
				if (display.getLastSec() > (double)animationSpeed / 50 + 0.5)
				{
					stopAnimation = true;
				}
			}
			display.clockStart();
		}
		display.showText(this->showItem(result.cut(i)));
		display.showText("\n\n");
		if (animationSet == "开启" && stopAnimation == false)
		{
			Sleep(animationSpeed * 20);
		}
		if (animationSet == "开启" && stopAnimation == true)
		{
			display.showText("&A提示:已经跳过动画。&7\n\n");
		}

		if (debugSet == "开启")
		{
			display.showCodeText("(int) poolId = " + display.intToString(poolId) + "\n");

			string debugTempS = "RandEngine::(unsigned long)getSeed() = ";
			debugTempS += display.intToString((int)RandEngine::getSeed());
			debugTempS += "\n";
			display.showCodeText(debugTempS);

			debugTempS = "RandEngine::(unsigned int)getListPos() = ";
			debugTempS += display.intToString((int)RandEngine::getListPos());
			debugTempS += "\n";
			display.showCodeText(debugTempS);

			display.showText("\n");
		}

		display.showButton('2', "再祈愿十次");
		display.showButton('0', "返回");
		opr = display.selectButton();
	}
}

void WishUi::nWishResult(int poolId, int n)
{
	Display display;
	Option option;
	WishHistory result;
	string animationSet = option.currentSet[option.getOptionPos("祈愿动画")];
	int animationSpeed = (int)option.currentChoose[option.getOptionPos("祈愿动画速度")];
	string debugSet = option.currentSet[option.getOptionPos("调试信息")];
	double changeColorPos = option.currentChoose[option.getOptionPos("祈愿动画变色位置")];
	char opr = '\0';
	bool stopAnimation = false;
	int i = 0;

	while (opr != '0')
	{
		display.clear();
		display.createText("&7原神工具 &8>&7 主菜单 &8> &7祈愿(模拟器) &8>&7 祈愿结果", 0, 0);
		result = this->wishPool[poolId].nWish(n);
		stopAnimation = false;
		if (animationSet == "开启")
		{
			//动画效果
			int colorlist[] = { 7,8,10,3,13,6,4 };
			display.showFakeLoading(50, animationSpeed, '-', '=', 3,
				colorlist[this->wishPool[poolId].getLastNMaxStar(n)],
				changeColorPos, 0, 2);
		}

		display.setCursorPos(0, 2);
		display.clockStart();
		for (i = 0; i < n - 1; i++)
		{
			display.showText(this->showItem(result.cut(i)));
			display.showText("    ");
			if (animationSet == "开启" && stopAnimation == false)
			{
				Sleep(animationSpeed * 20);
				if (display.getLastSec() > (double)animationSpeed / 50 + 0.5)
				{
					stopAnimation = true;
				}
			}
			display.clockStart();
		}
		display.showText(this->showItem(result.cut(i)));
		display.showText("\n\n");
		if (animationSet == "开启" && stopAnimation == false)
		{
			Sleep(animationSpeed * 20);
		}
		if (animationSet == "开启" && stopAnimation == true)
		{
			display.showText("&A提示:已经跳过动画。&7\n\n");
		}

		if (debugSet == "开启")
		{
			display.showCodeText("(int) poolId = " + display.intToString(poolId) + "\n");
			display.showCodeText("(int) n = " + display.intToString(n) + "\n");
			display.showText("\n");
		}

		display.showButton('3', "再祈愿" + display.intToString(n) + "次");
		display.showButton('0', "返回");
		opr = display.selectButton();
	}
}
