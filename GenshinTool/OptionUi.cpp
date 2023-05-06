#include "OptionUi.h"

void OptionUi::listOption(unsigned int chooseItem)
{
	Display display;
	Option option;
	unsigned int i = 0;
	unsigned int maxY = 0;
	unsigned int size = option.getLength();
	unsigned int selectY = 0;
	for (i = 0; i < size; i++)
	{
		if (option.isShow[i] == true)
		{
			if (i == chooseItem)
			{
				selectY = maxY + 4;
				display.setCursorPos(0, maxY + 4);
				display.showText("&8");
				display.showText(option.optionList[i]);
				display.setCursorPos(30, maxY + 4);
				if (option.optionType[i] != 1)
				{
					display.showText("&8");
					display.showText(option.currentSet[i]);
				}
				else if (option.optionType[i] == 1)
				{
					display.showLoading(11, '-', '=', option.currentChoose[i], 30, maxY + 4, 8);
				}
			}
			else
			{
				display.setCursorPos(0, maxY + 4);
				display.showText("&7");
				display.showText(option.optionList[i]);
				display.setCursorPos(30, maxY + 4);
				if (option.optionType[i] != 1)
				{
					display.showText("&7");
					display.showText(option.currentSet[i]);
				}
				else if (option.optionType[i] == 1)
				{
					display.showLoading(11, '-', '=', option.currentChoose[i], 30, maxY + 4, 7);
				}
			}
			maxY++;
		}
	}

	if (option.optionType[chooseItem] == 0)
	{
		vector<string> temp = option.getChooseList(option.optionList[chooseItem]);
		for (i = 0; i < temp.size(); i++)
		{
			display.setCursorPos(45, selectY + i);
			if (option.currentSet[chooseItem] == temp[i])
			{
				display.showText("&8");
				display.showText(temp[i]);
			}
			else
			{
				display.showText("&7");
				display.showText(temp[i]);
			}
		}
	}
	else if (option.optionType[chooseItem] == 3)
	{
		display.setCursorPos(45, selectY);
		display.showTextD(option.currentChoose[chooseItem], 8);
	}
	display.setCursorPos(0, maxY + 3);
}

bool OptionUi::canChooseUp(unsigned int chooseItem)
{
	Option option;
	unsigned int i = 0;
	for (i = 0; i < option.getLength(); i++)
	{
		if (option.isShow[i] == true && i < chooseItem)
		{
			return true;
		}
		if (option.isShow[i] == true && i == chooseItem)
		{
			return false;
		}
	}

	return false;
}

bool OptionUi::canChooseDown(unsigned int chooseItem)
{
	Option option;
	unsigned int i = option.getLength() - 1;
	for (i = option.getLength() - 1; i > 0; i--)
	{
		if (option.isShow[i] == true && i > chooseItem)
		{
			return true;
		}
		if (option.isShow[i] == true && i == chooseItem)
		{
			return false;
		}
	}
	return false;
}

unsigned int OptionUi::getChooseUp(unsigned int chooseItem)
{
	if (this->canChooseUp(chooseItem) == false)
	{
		return chooseItem;
	}
	Option option;
	unsigned int result = chooseItem - 1;
	while (option.isShow[result] == false)
	{
		result--;
	}
	return result;
}

unsigned int OptionUi::getChooseDown(unsigned int chooseItem)
{
	if (this->canChooseDown(chooseItem) == false)
	{
		return chooseItem;
	}
	Option option;
	unsigned int result = chooseItem + 1;
	while (option.isShow[result] == false)
	{
		result++;
	}
	return result;
}

void OptionUi::changeSet(unsigned int chooseItem)
{
	Option option;
	unsigned int i = 0;
	vector<string> temp = option.getChooseList(option.optionList[chooseItem]);

	for (i = 0; i < temp.size(); i++)
	{
		if (option.currentSet[chooseItem] == temp[i])
		{
			break;
		}
	}

	i++;
	if (i >= temp.size())
	{
		i = 0;
	}

	option.currentSet[chooseItem] = temp[i];
	option.currentChoose[chooseItem] = option.getChooseNum(option.optionList[chooseItem])[i];
	
	if (option.optionList[chooseItem] == "��Ը����")
	{
		if (option.currentChoose[chooseItem] == 0.0)
		{
			option.isShow[option.getOptionPos("��Ը�����ٶ�")] = false;
			option.isShow[option.getOptionPos("��Ը������ɫλ��")] = false;
		}
		else
		{
			option.isShow[option.getOptionPos("��Ը�����ٶ�")] = true;
			option.isShow[option.getOptionPos("��Ը������ɫλ��")] = true;
		}
	}
}

void OptionUi::changePercent(unsigned int chooseItem, bool isLow)
{
	Option option;
	if (isLow == true && option.currentChoose[chooseItem] >= 0.01)
	{
		option.currentChoose[chooseItem] -= 0.01;
	}
	else if(isLow == false && option.currentChoose[chooseItem] < 0.99)
	{
		option.currentChoose[chooseItem] += 0.01;
	}
}

void OptionUi::setPercent(unsigned int chooseItem)
{
	Display display;
	Option option;
	int temp = 0;

	display.clearAllButton();
	display.setCursorPos(0, option.getVisibleLength() + 5);
	display.showText("&7����������Ҫ����ѡ������Ϊ�ٷ�֮");
	temp = display.getInputInt(99, false);
	option.currentChoose[chooseItem] = (double)temp / 100;
}

void OptionUi::setStringSet(unsigned int chooseItem)
{
	Display display;
	Option option;
	string temp;

	display.clearAllButton();
	display.setCursorPos(0, option.getVisibleLength() + 5);
	display.showText("&7����������Ҫ���óɵĲ�����\n");
	temp = display.getInputString();
	option.currentSet[chooseItem] = temp;
}

void OptionUi::changeNum(unsigned int chooseItem, bool isLow)
{
	Option option;
	Display display;
	if (option.optionList[chooseItem] == "��Ը�����ٶ�")
	{
		if (isLow == true && option.currentChoose[chooseItem] >= 2.0)
		{
			option.currentChoose[chooseItem] -= 1.0;
			option.currentSet[chooseItem] = display.doubleToString(option.currentChoose[chooseItem] / 10, 1);
			option.currentSet[chooseItem] += "s + ";
			option.currentSet[chooseItem] += display.doubleToString(option.currentChoose[chooseItem] / 50, 1);
			option.currentSet[chooseItem] += "s";
		}
		else if (isLow == false && option.currentChoose[chooseItem] <= 999.0)
		{
			option.currentChoose[chooseItem] += 1.0;
			option.currentSet[chooseItem] = display.doubleToString(option.currentChoose[chooseItem] / 10, 1);
			option.currentSet[chooseItem] += "s + ";
			option.currentSet[chooseItem] += display.doubleToString(option.currentChoose[chooseItem] / 50, 1);
			option.currentSet[chooseItem] += "s";
		}
	}
}

void OptionUi::setNum(unsigned int chooseItem)
{
	Display display;
	Option option;
	double temp = 0.0;
	if (option.optionList[chooseItem] == "��Ը�����ٶ�")
	{
		display.clearAllButton();
		display.setCursorPos(0, option.getVisibleLength() + 5);
		display.showText("&7����������Ҫ���óɵ���ֵ[1~1000]��\n");
		display.showText("&7����0�����޸ġ�\n");
		temp = (double)display.getInputInt(1000, false);
		if (temp == 0)
		{
			return;
		}
		option.currentChoose[chooseItem] = temp;
		option.currentSet[chooseItem] = display.doubleToString(option.currentChoose[chooseItem] / 10, 1);
		option.currentSet[chooseItem] += "s + ";
		option.currentSet[chooseItem] += display.doubleToString(option.currentChoose[chooseItem] / 50, 1);
		option.currentSet[chooseItem] += "s";
	}
}

void OptionUi::showUi()
{
	Display display;
	Option option;
	char opr = '\0';
	unsigned int chooseItem = 0;

	while (opr != '0')
	{
		display.clear();
		display.showText("&7ԭ�񹤾� &8>&7 ���˵� &8>&7 ����\n\n");
		display.showText(option.tipList[chooseItem]);
		this->listOption(chooseItem);
		display.showText("\n\n");
		if (this->canChooseUp(chooseItem) == true)
		{
			display.showButton('w', "����");
		}
		if (this->canChooseDown(chooseItem) == true)
		{
			display.showButton('s', "����");
		}

		if (option.optionType[chooseItem] == 0)
		{
			display.showButton('e', "��������");
		}
		else if (option.optionType[chooseItem] == 1)
		{
			display.showButton('a', "��ֵ��С");
			display.showButton('d', "��ֵ����");
			display.showButton('q', "�ֶ�����");
		}
		else if (option.optionType[chooseItem] == 2)
		{
			display.showButton('q', "�޸�����");
		}
		else if (option.optionType[chooseItem] == 3)
		{
			display.showButton('a', "��ֵ��С");
			display.showButton('d', "��ֵ����");
			display.showButton('q', "�ֶ�����");
		}

		display.showButton('0', "���沢�˳�");
		opr = display.selectButton();
		if (opr == 's')
		{
			chooseItem = this->getChooseDown(chooseItem);
		}
		else if (opr == 'w')
		{
			chooseItem = this->getChooseUp(chooseItem);
		}
		else if (opr == 'e')
		{
			this->changeSet(chooseItem);
		}
		else if (opr == 'a')
		{
			if (option.optionType[chooseItem] == 1)
			{
				this->changePercent(chooseItem, true);
			}
			else if (option.optionType[chooseItem] == 3)
			{
				this->changeNum(chooseItem, true);
			}
		}
		else if (opr == 'd')
		{
			if (option.optionType[chooseItem] == 1)
			{
				this->changePercent(chooseItem, false);
			}
			else if (option.optionType[chooseItem] == 3)
			{
				this->changeNum(chooseItem, false);
			}
		}
		else if (opr == 'q')
		{
			if (option.optionType[chooseItem] == 1)
			{
				this->setPercent(chooseItem);
			}
			else if (option.optionType[chooseItem] == 2)
			{
				this->setStringSet(chooseItem);
			}
			else if (option.optionType[chooseItem] == 3)
			{
				this->setNum(chooseItem);
			}
		}
	}
}
