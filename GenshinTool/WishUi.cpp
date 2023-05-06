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
	//����1
	this->wishPool.push_back(WishPool("��ɫ���Ը", true, false));
	this->wishPool[0].setBaseItem(star3, star4Person, star4Weapon);
	this->wishPool[0].setUpItem(star4Up, star5Up, ITEM_TYPE_PERSON);
	this->wishPool[0].setStar5Person(star5Person);
	this->wishPool[0].setStar5Weapon(star5Weapon);
	//��������
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
	//����2
	this->wishPool.push_back(WishPool("�������Ը", true, true));
	this->wishPool[1].setBaseItem(star3, star4Person, star4Weapon);
	this->wishPool[1].setUpItem(star4Up, star5Up, ITEM_TYPE_WEAPON);
	this->wishPool[1].setStar5Person(star5Person);
	this->wishPool[1].setStar5Weapon(star5Weapon);
	//��������
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
	//����3
	this->wishPool.push_back(WishPool("��פ��Ը", false, false));
	this->wishPool[2].setBaseItem(star3, star4Person, star4Weapon);
	this->wishPool[2].setStar5Person(star5Person);
	this->wishPool[2].setStar5Weapon(star5Weapon);
	//��������
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
	vector<unsigned int> tempDistance = { 0,0,0 }; //3�ǣ�4�ǣ�5�Ǿ���
	string listSet = type;
	unsigned int length = history.getLength();
	unsigned int outputCount = 0;
	unsigned int i = 0;

	if (listSet == "�Զ�����")
	{
		if (maxNum - minNum + 1 <= MAXLOAD_HISTORY)
		{
			listSet = "���";
		}
		else
		{
			listSet = "�о�";
		}
	}
	//�������
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
	//��ʾ�б�
	if (listSet == "���")
	{
		for (i = minNum - 1; i < maxNum; i++)
		{
			if (history.getStar(i) >= selectStarMin && history.getStar(i) <= selectStarMax &&
				(itemType == history.getType(i) || itemType == -1) && (name == history.getItem(i) || name == "") 
				&& distance[i] >= minDistance && distance[i] <= maxDistance)
			{
				if (outputCount == 0)
				{
					display.createText("&B���", 0, display.getCursorPosY());
					display.createText("&B�Ǽ�", 8, display.getCursorPosY());
					display.createText("&B����", 14, display.getCursorPosY());
					display.createText("&B����", 20, display.getCursorPosY());
					display.createText("&B���", 35, display.getCursorPosY());
					display.showText("\n");
				}
				outputCount++;
				if (history.getStar(i) == 3)
				{
					tempS = "&3";
					display.showTextI((int)history.getNum(i), 3);
					display.setCursorPos(8, display.getCursorPosY());
					display.showText("&3����");
				}
				else if (history.getStar(i) == 4)
				{
					tempS = "&D";
					display.showTextI((int)history.getNum(i), 13);
					display.setCursorPos(8, display.getCursorPosY());
					display.showText("&D����");
				}
				else if (history.getStar(i) == 5)
				{
					tempS = "&6";
					display.showTextI((int)history.getNum(i), 6);
					display.setCursorPos(8, display.getCursorPosY());
					display.showText("&6����");
				}
				else
				{
					tempS = "&7";
					display.showTextI((int)history.getNum(i), 7);
					display.setCursorPos(8, display.getCursorPosY());
					display.showText("&7�Ǽ�");
				}
				display.setCursorPos(14, display.getCursorPosY());
				display.showText(tempS);
				if (history.getType(i) == ITEM_TYPE_PERSON)
				{
					display.showText("��ɫ");
				}
				else if (history.getType(i) == ITEM_TYPE_WEAPON)
				{
					display.showText("����");
				}
				else
				{
					display.showText("����");
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
	else if (listSet == "�о�")
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
		display.showText("&C��������\n");
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

	string debugSet = option.currentSet[option.getOptionPos("������Ϣ")];
	
	while (opr != '0')
	{
		unsigned int i = 0;
		unsigned int poolNum = 0;
		vector<unsigned int> oprList;

		display.clear();
		display.showText("&7ԭ�񹤾� &8>&7 ���˵� &8> &7��Ը(ģ����)\n\n");

		if (debugSet == "����")
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
		display.showButton('7', "��ʷ��¼");
		display.showButton('8', "ͳ������");
		display.showButton('0', "����");
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
	string debugSet = option.currentSet[option.getOptionPos("������Ϣ")];

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
			display.showText("&7ԭ�񹤾� &8>&7 ���˵� &8> &7��Ը(ģ����) &8>&7 ��ɫ���Ը\n\n");
		}
		else
		{
			display.showText("&7ԭ�񹤾� &8>&7 ���˵� &8> &7��Ը(ģ����) &8>&7 ��ɫ���Ը - ");
			display.showText(data.getLimitWishList(5, true, ITEM_TYPE_PERSON, poolId)[0]);
			display.showText("\n\n");
		}

		if (debugSet == "����")
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

		display.showButton('1', "��Ըһ��");
		display.showButton('2', "��Ըʮ��");
		display.showButton('3', "�Զ�����Ը����");
		display.showButton('8', "��Ʒ�б�");
		display.showButton('0', "����");
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
			display.showText("����������Ҫ��Ը�Ĵ���[1~1000]:\n");
			display.showText("����0���ء�\n");
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
	string debugSet = option.currentSet[option.getOptionPos("������Ϣ")];

	while (opr != '0')
	{
		display.clear();
		display.showText("&7ԭ�񹤾� &8>&7 ���˵� &8> &7��Ը(ģ����) &8>&7 �������Ը\n\n");
		selectItem = this->wishPool[1].getStar5Choose()[0];

		if (debugSet == "����")
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

		if (selectItem == "ȡ������")
		{
			display.showText("&E��ǰδ��������");
		}
		else
		{
			tempS = "&E�Ѷ�������:&6" + selectItem;
			display.showText(tempS);
			display.showTextI("\n&B����ֵ:&A", this->wishPool[1].star5Guar[4], "&B/2");
		}
		display.showText("\n\n");

		display.showButton('1', "��Ըһ��");
		display.showButton('2', "��Ըʮ��");
		display.showButton('3', "�Զ�����Ը����");
		display.showButton('8', "��Ʒ�б�");
		display.showButton('9', "��������");
		display.showButton('0', "����");
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
			display.showText("����������Ҫ��Ը�Ĵ���[1~1000]:\n");
			display.showText("����0���ء�\n");
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
	string debugSet = option.currentSet[option.getOptionPos("������Ϣ")];

	while (opr != '0')
	{
		display.clear();
		display.showText("&7ԭ�񹤾� &8>&7 ���˵� &8> &7��Ը(ģ����) &8>&7 ��פ��Ը\n\n");

		if (debugSet == "����")
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

		display.showButton('1', "��Ըһ��");
		display.showButton('2', "��Ըʮ��");
		display.showButton('3', "�Զ�����Ը����");
		display.showButton('8', "��Ʒ�б�");
		display.showButton('0', "����");
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
			display.showText("����������Ҫ��Ը�Ĵ���[1~1000]:\n");
			display.showText("����0���ء�\n");
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
	string debugSet = option.currentSet[option.getOptionPos("������Ϣ")];

	while (opr != '0')
	{
		display.clear();
		display.showText("&7ԭ�񹤾� &8>&7 ���˵� &8> &7��Ը(ģ����) &8>&7 �������Ը &8>&7 ��������\n\n");

		selectItem[0] = this->wishPool[1].getStar5Choose()[0];
		selectItem[1] = list.getWeaponWishList(5, true)[0];
		selectItem[2] = list.getWeaponWishList(5, true)[1];

		if (debugSet == "����")
		{
			display.showCodeText("(string[3]) selectItem = { \"" + selectItem[0] + "\", \"" +
				selectItem[1] + "\", \"" + selectItem[2] + "\" }\n");

			display.showText("\n");
		}

		if (selectItem[0] == "ȡ������")
		{
			display.showText("&E��ǰδ��������");
		}
		else
		{
			tempS = "&E�Ѷ�������:&6" + selectItem[0];
			display.showText(tempS);
			display.showTextI("\n&B����ֵ:&A", this->wishPool[1].star5Guar[4], "&B/2");
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
		if (selectItem[0] != "ȡ������")
		{
			display.showButton('3', "ȡ������");
		}

		display.showButton('0', "����");
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
			choose.push_back("ȡ������");
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
	string listSet = option.currentSet[option.getOptionPos("��Ը��ʷ��¼��ʾ��ʽ")];
	string debugSet = option.currentSet[option.getOptionPos("������Ϣ")];
	
	for (i = 0; i < length; i++)
	{
		history.push_back(this->wishPool[i].getHistory());
		tempI += this->wishPool[i].getHistory().getLength();
	}
	if (listSet == "�Զ�����")
	{
		if (tempI <= MAXLOAD_HISTORY)
		{
			listSet = "���";
		}
		else
		{
			listSet = "�о�";
		}
	}
	tempI = 0;

	while (opr != '0')
	{
		display.clear();
		if (showStatic == false)
		{
			unsigned int distance[3] = { 0,0,0 };
			display.showText("&7ԭ�񹤾� &8>&7 ���˵� &8> &7��Ը(ģ����) &8>&7 ��ʷ��¼\n\n");

			if (debugSet == "����")
			{
				display.showCodeText("(unsigned int) length = " + display.intToString(length) + "\n");
				display.showCodeText("(vector<WishHistory>) history.size() = " +
					display.intToString((int)history.size()) + "\n");

				display.showText("\n");
			}

			for (i = 0; i < length; i++)
			{
				unsigned int maxSize = 1000; //ͬʱ�����ʾ��ʷ��¼������
				if (listSet == "�о�")
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
					display.showTextI("&Cֻ��ʾ��", maxSize, "����ʷ��¼��\n");
					this->showHistoryList(listSet, i, num - maxSize + 1, num);
				}
				display.showText("\n");
			}
			
			display.showButton('1', "ͳ������");
			if (listSet == "���")
			{
				display.showButton('5', "���оٵķ�ʽ��ʾ");
				display.showButton('9', "ɸѡ");
			}
			else if (listSet == "�о�")
			{
				display.showButton('5', "�Ա�����ʽ��ʾ");
			}
			display.showButton('0', "����");
			opr = display.selectButton();
			if (opr == '1')
			{
				showStatic = true;
				continue;
			}
			else if (opr == '5')
			{
				if (listSet == "���")
				{
					listSet = "�о�";
				}
				else if (listSet == "�о�")
				{
					listSet = "���";
				}
			}
			else if (opr == '9')
			{
				this->showSelectHistoryUi();
			}
		}
		else
		{
			display.showText("&7ԭ�񹤾� &8>&7 ���˵� &8> &7��Ը(ģ����) &8>&7 ͳ������\n\n");

			if (debugSet == "����")
			{
				display.showCodeText("(unsigned int) length = " + display.intToString(length) + "\n");
				display.showCodeText("(vector<WishHistory>) history.size() = " +
					display.intToString((int)history.size()) + "\n");

				display.showText("\n");
			}

			for (i = 0; i < length; i++)
			{
				//��¼�������͵���Ʒ������ʷ��¼�е�λ��
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
					display.showText("&C��������\n\n");
					continue;
				}

				display.showTextI("&B���� &A", num, " &B��\n");
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
				display.showTextI("&B���ۼ� &A", tempI, " &B��δ������\n");
				if (star5.size() > 0)
				{
					paraDouble = { ((double)num - tempI) / (double)star5.size() };
					display.showTextD("&Bƽ�� &A# &B���һ������\n", paraDouble);
				}
				display.showTextI("&B���ǹ� &A", (int)star5.size(), " &Bռ����");
				display.showTextD("&B�� &A", (double)star5.size() / (double)num * 100.0, "&A%\n");
				if (star5Person.size() > 0 && star5Weapon.size() > 0)
				{
					display.showTextI("    &B���ǽ�ɫ�� &A", (int)star5Person.size(), " &Bռ����");
					display.showTextD("&B�� &A", (double)star5Person.size() / (double)num * 100.0, "&A%\n");
					display.showTextI("    &B���������� &A", (int)star5Weapon.size(), " &Bռ����");
					display.showTextD("&B�� &A", (double)star5Weapon.size() / (double)num * 100.0, "&A%\n");
				}
				display.showTextI("&B���ǹ� &A", (int)star4.size(), " &Bռ����");
				display.showTextD("&B�� &A", (double)star4.size() / (double)num * 100.0, "&A%\n");
				if (star4Person.size() > 0 && star4Weapon.size() > 0)
				{
					display.showTextI("    &B���ǽ�ɫ�� &A", (int)star4Person.size(), " &Bռ����");
					display.showTextD("&B�� &A", (double)star4Person.size() / (double)num * 100.0, "&A%\n");
					display.showTextI("    &B���������� &A", (int)star4Weapon.size(), " &Bռ����");
					display.showTextD("&B�� &A", (double)star4Weapon.size() / (double)num * 100.0, "&A%\n");
				}
				display.showTextI("&B���ǹ� &A", num - (int)star5.size() - (int)star4.size(), " &Bռ����");
				paraDouble = { ((double)num - (double)star5.size() - (double)star4.size()) / (double)num * 100.0 };
				display.showTextD("&B�� &A#&A%\n", paraDouble);
				if (star5.size() > 0 && star5.size() <= 100)
				{
					display.showText("&A������ʷ��¼:\n");
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
					display.showText("&A������ʷ��¼[ֻ��ʾ��100������]:\n");
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

			display.showButton('1', "��ʷ��¼");
			display.showButton('0', "����");
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
	string debugSet = option.currentSet[option.getOptionPos("������Ϣ")];

	char opr = '\0';
	int temp = 0;

	while (opr != '0')
	{
		display.clear();
		
		display.showText("&7ԭ�񹤾� &8>&7 ���˵� &8> &7��Ը(ģ����) &8>&7 ��ʷ��¼ɸѡ\n\n");

		if (debugSet == "����")
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

		temp = (int)this->showHistoryList("���", poolPos, (unsigned int)mNum[0], (unsigned int)mNum[1],
			(short)selectStarM[0], (short)selectStarM[1], type, name,
			(unsigned int)distance[0], (unsigned int)distance[1]);
		if (temp > 0)
		{
			display.showTextI("&B�� &A", temp, " &B���������������ݡ�\n");
		}
		display.showText("\n&Bɸѡ����:\n");
		display.showText("&B��������:      &6" + this->wishPool[poolPos].getPoolName() + "\n");
		display.showTextI("&B��Ʒ�Ǽ���Χ:  &6#&B~&6#&B��\n", selectStarM);
		if (this->wishPool[poolPos].getHistory().getLength() > 0)
		{
			display.showTextI("&B��ŷ�Χ:      &6#&B~&6#&B\n", mNum);
		}
		if (type == 0)
		{
			display.showText("&B��Ʒ����:      &6��ɫ&B\n");
		}
		else if (type == 1)
		{
			display.showText("&B��Ʒ����:      &6����&B\n");
		}
		if (name != "")
		{
			display.showText("&B��Ʒ����:      &6" + name + "&B\n");
		}
		display.showTextI("&B���:          &6#&B~&6#&B\n", distance);
		display.showText("\n&7");

		display.showButton('1', "�޸�ɸѡ����:��������");
		display.showButton('2', "�޸�ɸѡ����:��Ʒ�Ǽ���Χ");
		if (this->wishPool[poolPos].getHistory().getLength() > 1)
		{
			display.showButton('3', "�޸�ɸѡ����:��ŷ�Χ");
		}
		display.showButton('4', "�޸�ɸѡ����:��Ʒ����");
		if (selectStarM[0] == selectStarM[1] && type != -1)
		{
			display.showButton('5', "�޸�ɸѡ����:��Ʒ����");
		}
		display.showButton('6', "�޸�ɸѡ����:���");
		display.showButton('0', "����");
		opr = display.selectButton();
		if (opr == '1')
		{
			int i = 0;
			display.clearButton('1', false);
			display.clearAllButton();
			display.showText("&7�޸�ɸѡ����:��������\n");
			display.showText("&B��ǰѡ��Ŀ���:&6" + this->wishPool[poolPos].getPoolName() + "\n\n");
			display.showText("&7��ѡ��һ�����ء�\n");
			for (i = 0; i < (int)this->wishPool.size(); i++)
			{
				display.showButton('1' + i, this->wishPool[i].getPoolName());
			}
			display.showButton('0', "�����޸�");
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
			display.showText("&7�޸�ɸѡ����:��Ʒ�Ǽ���Χ\n");
			display.showTextI("&B��ǰ���õ�ֵ:&6#&B~&6#&B��\n\n", selectStarM);
			display.showText("&7��������Ʒ�Ǽ�����Сֵ[3~5]:\n");
			display.showText("&7����0�����޸ġ�\n");
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
				display.showText("&c�������ֵ��Ч������������[3~5]&7\n");
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
			display.showTextI("&7��������Ʒ�Ǽ������ֵ[", inputMin, "~5]:\n");
			display.showText("&7����0�����޸ġ�\n");
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
				display.showTextI("&c�������ֵ��Ч������������[", inputMin, "~5]&7\n");
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
			display.showText("&7�޸�ɸѡ����:��ŷ�Χ\n");
			display.showTextI("&B��ǰ���õ�ֵ:&6#&B~&6#&B\n\n", mNum);
			display.showTextI("&7��������ŵ���Сֵ[#~#]:\n", inputM);
			display.showText("&7����0�����޸ġ�\n");
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
			display.showTextI("&7��������ŵ����ֵ[#~#]:\n", inputM);
			display.showText("&7����0�����޸ġ�\n");
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
				display.showTextI("&c�������ֵ��Ч������������[#~#]:&7\n", inputM);
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
			display.showText("&7�޸�ɸѡ����:��Ʒ����\n");
			if (type == 0)
			{
				display.showText("&B��ǰɸѡ:&6��ɫ&B\n\n");
			}
			else if (type == 1)
			{
				display.showText("&B��ǰɸѡ:&6����&B\n\n");
			}
			else if (type == -1)
			{
				display.showText("&B��ǰδ����Ʒ���ͽ���ɸѡ\n\n");
			}
			display.showText("&7��ѡ����Ҫɸѡ����Ʒ����:\n");
			display.showButton('1', "ɸѡ��ɫ");
			display.showButton('2', "ɸѡ����");
			display.showButton('3', "ȡ��ɸѡ");
			display.showButton('0', "�����޸�");
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
			display.showText("&7�޸�ɸѡ����:��Ʒ����\n");
			if (name == "")
			{
				display.showText("&B��ǰδ����Ʒ����ɸѡ��\n");
			}
			else
			{
				display.showText("&B��ǰɸѡ����Ʒ����:&6" + name + "&B\n");
			}
			display.showText("\n&7��ѡ������Ҫɸѡ����Ʒ:\n");
			vector<string> chooseList = { "ȡ��ɸѡ" };
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
			if (tempS == "ȡ��ɸѡ")
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
			display.showText("&7�޸�ɸѡ����:��Ʒ���\n");
			display.showTextI("&B��ǰ���õ�ֵ:&6#&B~&6#&B\n\n", distance);
			display.showText("&7������������Сֵ[1~90]:\n");
			display.showText("&7����0�����޸ġ�\n");
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
			display.showTextI("&7�������������ֵ[", inputMin, "~90]:\n");
			display.showText("&7����0�����޸ġ�\n");
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
				display.showTextI("&c�������ֵ��Ч������������[", inputMin, "~90]&7\n");
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
	string listSet = option.currentSet[option.getOptionPos("��Ը��ʷ��¼��ʾ��ʽ")];
	unsigned int length = (unsigned int)this->wishPool.size();
	unsigned int i = 0;
	char opr = '\0';
	if (listSet == "�Զ�����")
	{
		listSet = "���";
	}

	while (opr != '0')
	{
		vector<string> itemList;

		display.clear();
		display.showText("&7ԭ�񹤾� &8>&7 ���˵� &8> &7��Ը(ģ����) &8>&7 ��Ʒ�б�\n\n");
		display.showText(this->wishPool[poolId].getPoolName() + "\n");

		if (listSet == "���")
		{
			display.showText("&B�Ǽ�  ����  ��Ʒ\n");
			if (this->wishPool[poolId].star5Up.size() > 0)
			{
				itemList = this->wishPool[poolId].star5Up;
				if (this->wishPool[poolId].getUpItemType() == ITEM_TYPE_PERSON)
				{
					for (i = 0; i < itemList.size(); i++)
					{
						display.showText("&6����  ��ɫ  " + itemList[i] + "&6[UP]\n");
					}
				}
				else if (this->wishPool[poolId].getUpItemType() == ITEM_TYPE_WEAPON)
				{
					for (i = 0; i < itemList.size(); i++)
					{
						display.showText("&6����  ����  " + itemList[i] + "&6[UP]\n");
					}
				}
			}
			if (this->wishPool[poolId].star5Person.size() > 0)
			{
				itemList = this->wishPool[poolId].star5Person;
				for (i = 0; i < itemList.size(); i++)
				{
					display.showText("&6����  ��ɫ  " + itemList[i] + "\n");
				}
			}
			if (this->wishPool[poolId].star5Weapon.size() > 0)
			{
				itemList = this->wishPool[poolId].star5Weapon;
				for (i = 0; i < itemList.size(); i++)
				{
					display.showText("&6����  ����  " + itemList[i] + "\n");
				}
			}
			if (this->wishPool[poolId].star4Up.size() > 0)
			{
				itemList = this->wishPool[poolId].star4Up;
				if (this->wishPool[poolId].getUpItemType() == ITEM_TYPE_PERSON)
				{
					for (i = 0; i < itemList.size(); i++)
					{
						display.showText("&D����  ��ɫ  " + itemList[i] + "&D[UP]\n");
					}
				}
				else if (this->wishPool[poolId].getUpItemType() == ITEM_TYPE_WEAPON)
				{
					for (i = 0; i < itemList.size(); i++)
					{
						display.showText("&D����  ����  " + itemList[i] + "&D[UP]\n");
					}
				}
			}
			if (this->wishPool[poolId].star4Person.size() > 0)
			{
				itemList = this->wishPool[poolId].star4Person;
				for (i = 0; i < itemList.size(); i++)
				{
					display.showText("&D����  ��ɫ  " + itemList[i] + "\n");
				}
			}
			if (this->wishPool[poolId].star4Weapon.size() > 0)
			{
				itemList = this->wishPool[poolId].star4Weapon;
				for (i = 0; i < itemList.size(); i++)
				{
					display.showText("&D����  ����  " + itemList[i] + "\n");
				}
			}
			if (this->wishPool[poolId].star3.size() > 0)
			{
				itemList = this->wishPool[poolId].star3;
				for (i = 0; i < itemList.size(); i++)
				{
					display.showText("&3����  ����  " + itemList[i] + "\n");
				}
			}
			display.showText("\n");
		}
		else if (listSet == "�о�")
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

		if (listSet == "���")
		{
			display.showButton('5', "���оٵķ�ʽ��ʾ");
		}
		else if (listSet == "�о�")
		{
			display.showButton('5', "�Ա�����ʽ��ʾ");
		}
		display.showButton('0', "����");
		opr = display.selectButton();
		if (opr == '5')
		{
			if (listSet == "���")
			{
				listSet = "�о�";
			}
			else if (listSet == "�о�")
			{
				listSet = "���";
			}
		}
	}
}

void WishUi::singleWishResult(int poolId)
{
	Display display;
	Option option;
	char opr = '\0';
	int animationSpeed = (int)option.currentChoose[option.getOptionPos("��Ը�����ٶ�")];
	double changeColorPos = option.currentChoose[option.getOptionPos("��Ը������ɫλ��")];
	WishHistory result;
	string debugSet = option.currentSet[option.getOptionPos("������Ϣ")];

	while (opr != '0')
	{
		result = this->wishPool[poolId].singleWish();

		display.clear();
		display.createText("&7ԭ�񹤾� &8>&7 ���˵� &8> &7��Ը(ģ����) &8>&7 ��Ը���", 0, 0);
		if (option.currentSet[option.getOptionPos("��Ը����")] == "����")
		{
			//����Ч��
			int colorlist[] = { 7,8,10,3,13,6,4 };
			display.showFakeLoading(50, animationSpeed, '-', '=', 3,
				colorlist[this->wishPool[poolId].getLastItem().getStar(0)], 
				changeColorPos, 0, 2);
		}

		display.setCursorPos(0, 2);
		display.showText(this->showItem(result));
		display.showText("\n\n");

		if (debugSet == "����")
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

		display.showButton('1', "����Ըһ��");
		display.showButton('0', "����");
		opr = display.selectButton();
	}
}

void WishUi::templeWishResult(int poolId)
{
	Display display;
	Option option;
	WishHistory result;
	string animationSet = option.currentSet[option.getOptionPos("��Ը����")];
	string debugSet = option.currentSet[option.getOptionPos("������Ϣ")];
	int animationSpeed = (int)option.currentChoose[option.getOptionPos("��Ը�����ٶ�")];
	double changeColorPos = option.currentChoose[option.getOptionPos("��Ը������ɫλ��")];
	char opr = '\0';
	bool stopAnimation = false;
	int i = 0;

	while (opr != '0')
	{
		display.clear();
		display.createText("&7ԭ�񹤾� &8>&7 ���˵� &8> &7��Ը(ģ����) &8>&7 ��Ը���", 0, 0);
		result = this->wishPool[poolId].templeWish();
		stopAnimation = false;
		if (animationSet == "����")
		{
			//����Ч��
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
			if (animationSet == "����" && stopAnimation == false)
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
		if (animationSet == "����" && stopAnimation == false)
		{
			Sleep(animationSpeed * 20);
		}
		if (animationSet == "����" && stopAnimation == true)
		{
			display.showText("&A��ʾ:�Ѿ�����������&7\n\n");
		}

		if (debugSet == "����")
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

		display.showButton('2', "����Ըʮ��");
		display.showButton('0', "����");
		opr = display.selectButton();
	}
}

void WishUi::nWishResult(int poolId, int n)
{
	Display display;
	Option option;
	WishHistory result;
	string animationSet = option.currentSet[option.getOptionPos("��Ը����")];
	int animationSpeed = (int)option.currentChoose[option.getOptionPos("��Ը�����ٶ�")];
	string debugSet = option.currentSet[option.getOptionPos("������Ϣ")];
	double changeColorPos = option.currentChoose[option.getOptionPos("��Ը������ɫλ��")];
	char opr = '\0';
	bool stopAnimation = false;
	int i = 0;

	while (opr != '0')
	{
		display.clear();
		display.createText("&7ԭ�񹤾� &8>&7 ���˵� &8> &7��Ը(ģ����) &8>&7 ��Ը���", 0, 0);
		result = this->wishPool[poolId].nWish(n);
		stopAnimation = false;
		if (animationSet == "����")
		{
			//����Ч��
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
			if (animationSet == "����" && stopAnimation == false)
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
		if (animationSet == "����" && stopAnimation == false)
		{
			Sleep(animationSpeed * 20);
		}
		if (animationSet == "����" && stopAnimation == true)
		{
			display.showText("&A��ʾ:�Ѿ�����������&7\n\n");
		}

		if (debugSet == "����")
		{
			display.showCodeText("(int) poolId = " + display.intToString(poolId) + "\n");
			display.showCodeText("(int) n = " + display.intToString(n) + "\n");
			display.showText("\n");
		}

		display.showButton('3', "����Ը" + display.intToString(n) + "��");
		display.showButton('0', "����");
		opr = display.selectButton();
	}
}
