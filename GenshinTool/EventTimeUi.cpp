#include "EventTimeUi.h"

string EventTimeUi::timeToString(TimeCaculator time, bool includeWeek)
{
	Display display;
	string text = "";
	text += display.intToString(time.getYear());
	text += "��";
	text += display.intToString(time.getMonth());
	text += "��";
	text += display.intToString(time.getDay());
	text += "��";

	if (includeWeek == true)
	{
		string temp[8] = { "��", "һ", "��", "��", "��", "��", "��", "��" };
		text += "   ����";
		text += temp[time.getWeek()];
	}
	
	return text;
}

string EventTimeUi::weekToString(TimeCaculator time)
{
	string temp[8] = { "������", "����һ", "���ڶ�", "������", "������", "������", "������", "������" };
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
	string text = "&7ԭ�񹤾� &8>&7 ���˵� &8>&7 �¼�����ԴԤ��\n\n";

	display.clear();
	display.showText(text);
	display.showTextI("&Eʹ�ñ�����֮ǰ����������һ��ʱ��������", MAXLOAD_TIME, "&E���ʱ��Ρ�\n");
	display.showText("&E���������м��㽫�����ڴ�ʱ��εķ�Χ�ڡ�\n");
	display.showText("&E�����ʱ��εĿ�ʼ���ںͽ�ֹ�������������á�\n");
	display.showText("\n&7���뿪ʼ����[���]:\n");
	display.showButton('1', "2021��");
	display.showButton('2', "2022��");
	display.showButton('3', "2023��");
	display.showButton('0', "�˳�");
	opr = display.selectButton();
	if (opr == '0')
	{
		return;
	}
	else
	{
		year = 2020 + opr - '0';
	}
	text += "&B��ʼ����:&A";
	text += display.intToString(year);
	text += "��";
	display.clear();
	display.showText(text + "\n\n");
	display.showText("&7���뿪ʼ����[�·�][1~12]:\n");
	display.showText("&7����0�˳���\n");
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
	text += "��";
	display.clear();
	display.showText(text + "\n\n");
	display.showTextI("&7���뿪ʼ����[����][1~", tempTime.getDaysInMonth(year, month), "]:\n");
	display.showText("&7����0�˳���\n");
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
	text += "��\t";
	TimeCaculator startTime(year, month, day); 
	text += this->weekToString(startTime);
	text += "\n";
	//������MAXLOAD_TIME���ڵ��¼�
	if (startTime.getYear() == (startTime + MAXLOAD_TIME).getYear())
	{
		year = startTime.getYear();
	}
	else
	{
		display.clear();
		display.showText(text);
		display.showText("\n&E��ʼ�������óɹ���\n");
		display.showText("\n&7�����ֹ����[���]:\n");
		if (startTime.getYear() <= 2021 && (startTime + MAXLOAD_TIME).getYear() >= 2021)
		{
			display.showButton('1', "2021��");
		}
		if (startTime.getYear() <= 2022 && (startTime + MAXLOAD_TIME).getYear() >= 2022)
		{
			display.showButton('2', "2022��");
		}
		if (startTime.getYear() <= 2023 && (startTime + MAXLOAD_TIME).getYear() >= 2023)
		{
			display.showButton('3', "2023��");
		}
		if (startTime.getYear() <= 2024 && (startTime + MAXLOAD_TIME).getYear() >= 2024)
		{
			display.showButton('4', "2024��");
		}
		display.showButton('0', "�˳�");
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
	text += "&B��ֹ����:&A";
	text += display.intToString(year);
	text += "��";
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
		display.showTextI("&7�����ֹ����[�·�][#~#]:\n", tempM);
		display.showText("&7����0�˳���\n");
		temp = display.getInputInt(tempM[1], false);
		if (temp == 0)
		{
			return;
		}
		while (temp < tempM[0] || temp > tempM[1])
		{
			display.clearText(5, 0, 8);
			display.clearText(40, 0, 7);
			display.showText("&C�������ֵ��Ч�����������롣&7\n");
			temp = display.getInputInt(tempM[1], false);
			if (temp == 0)
			{
				return;
			}
		}
		month = temp;
	}
	text += display.intToString(month);
	text += "��";

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
		display.showTextI("&7�����ֹ����[����][#~#]:\n", tempM);
		display.showText("&7����0�˳���\n");
		temp = display.getInputInt(tempM[1], false);
		if (temp == 0)
		{
			return;
		}
		while (temp < tempM[0] || temp > tempM[1])
		{
			display.clearText(5, 0, 8);
			display.clearText(40, 0, 7);
			display.showText("&C�������ֵ��Ч�����������롣&7\n");
			temp = display.getInputInt(tempM[1], false);
			if (temp == 0)
			{
				return;
			}
		}
		day = temp;
	}
	text += display.intToString(day);
	text += "��\t";
	TimeCaculator endTime(year, month, day);
	text += this->weekToString(endTime);
	text += "\n\n";

	while (opr != '0')
	{
		display.clear();
		display.showText(text);
		display.showText("&Eʱ��������óɹ���\n");
		display.showText("&E��ѡ������ҪԤ�����Ŀ��\n\n");

		display.showButton('1', "ԭʯ����Ԥ��");
		display.showButton('2', "����֮Ե����Ԥ��");
		display.showButton('3', "�¼�ʱ��Ԥ��");
		display.showButton('4', "ԭ����֬Ԥ��");
		display.showButton('0', "����");
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
	string text = "&7ԭ�񹤾� &8>&7 ���˵� &8>&7 �¼�����ԴԤ�� &8>&7 ԭʯ����Ԥ��\n\n";
	text += "&B��ʼ����:&A";
	text += this->timeToString(startTime, true);
	text += "&B\n��ֹ����:&A";
	text += this->timeToString(endTime, true);
	text += "&B\n";
	display.showText(text);
	display.showText("\n&E����������ÿ����������ܹ���õ�ԭʯ����[0~600]:\n");
	while (ability < 0 || ability > 600 || ability % 50 != 0)
	{
		ability = display.getInputInt(600, false);
		if (ability % 50 != 0)
		{
			display.clearText(5, 0, 7);
			display.clearText(50, 0, 6);
			display.showText("&C�������ֵ��Ч������Ϊ50�ı�����&7\n");
		}
	}
	text += "&B��ÿ����������ܹ���ȡ &A";
	text += display.intToString(ability);
	text += " &Bԭʯ\n";
	display.clear();
	display.showText(text);
	display.showText("\n&E���Ƿ����˿���ף��\n");
	display.showButton('1', "��");
	display.showButton('2', "��");
	display.showButton('0', "�˳�");
	opr = display.selectButton();
	if (opr == '0')
	{
		return;
	}
	else if (opr == '1')
	{
		text += "û�й������ף����";
		hasWish = false;
	}
	else if (opr == '2')
	{
		text += "ӵ�п���ף����";
		hasWish = true;
	}
	display.clear();
	display.showText(text);
	display.showText("\n\n&E���Ƿ������������\n");
	display.showButton('1', "��");
	display.showButton('2', "��");
	display.showButton('0', "�˳�");
	opr = display.selectButton();
	if (opr == '0')
	{
		return;
	}
	else if (opr == '1')
	{
		text += "û�й���������С�\n\n";
		hasExp = false;
	}
	else if (opr == '2')
	{
		text += "�ѽ���������С�\n\n";
		hasExp = true;
	}

	EventTime eventTime(startTime - 1);

	Option option;
	string listSet = option.currentSet[option.getOptionPos("ԭʯ����Ԥ����")];
	while (opr != '0')
	{
		int coordY = 7;
		int currentSum = 0;
		int lastSum = 0;
		TimeCaculator tempTime = startTime;

		if (listSet == "�Զ�����")
		{
			if (endTime - startTime + 1 > 45)
			{
				listSet = "�ر�";
			}
			else
			{
				listSet = "����";
			}
		}

		display.clear();
		display.showText(text);

		if (listSet == "����")
		{
			display.createText("&B����", 0, coordY);
			display.createText("&B����", 16, coordY);
			display.createText("&B���ջ�ȡ", 25, coordY);
			display.createText("&B�ۼƻ�ȡ", 38, coordY);
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
		
		display.showText("&cע��:Ԥ����������ʷ�汾�Ĺ��ɽ���Ԥ�⣬����һ����ȫ׼ȷ��\n");
		display.showText("&c     Ԥ���������ο���������������ʵ�����Ϊ׼��\n\n");
		display.showTextI("&E���� &A", endTime - startTime + 1, " &E���Ԥ��һ���ܹ���� ");
		display.showTextI("&A", eventTime.keepPrimogemExpect(endTime, ability, hasWish, hasExp), " &Eԭʯ��\n");
		display.showText("&Eԭʯ����Դ�������·���:\n");
		display.showTextI("&B���ÿ��ί���ܼƿɻ�� &A",
			eventTime.getPrimogemExpect(endTime, "ÿ�ջ�Ծ", ability), " &Bԭʯ��\n");
		if (hasWish == true)
		{
			display.showTextI("&Bͨ������ף���ܼƿɻ�� &A",
				eventTime.getPrimogemExpect(endTime, "����ף��", ability), " &Bԭʯ��\n");
		}
		if (hasExp == true && eventTime.getPrimogemExpect(endTime, "�������", ability) > 0)
		{
			display.showTextI("&Bͨ����������ܼƿɻ�� &A",
				eventTime.getPrimogemExpect(endTime, "�������", ability), " &Bԭʯ��\n");
		}
		if (eventTime.getPrimogemExpect(endTime, "�����", ability) > 0)
		{
			vector<int> temp = { eventTime.getPrimogemExpect(endTime, "�����", ability) / ability,
			eventTime.getPrimogemExpect(endTime, "�����", ability) };
			display.showTextI("&B�ڼ������������ &A# &B�Σ�����������ս�ܹ����Ի��&A # &Bԭʯ��\n", temp);
		}
		if (eventTime.getPrimogemExpect(endTime, "��ɫ����", ability) > 0)
		{
			vector<int> temp = { eventTime.getPrimogemExpect(endTime, "��ɫ����", ability) / 20,
				eventTime.getPrimogemExpect(endTime, "��ɫ����", ability) };
			display.showTextI("&B�� &A# &B�ڽ�ɫ���ã�����&A # &Bԭʯ��\n", temp);
		}
		if (eventTime.getPrimogemExpect(endTime, "�����", ability) > 0)
		{
			display.showTextI("&B�������еİ汾��ܹ����Ի�ȡԼ &A",
				eventTime.getPrimogemExpect(endTime, "�����", ability), " &Bԭʯ��\n");
		}
		if (eventTime.getPrimogemExpect(endTime, "ǰհֱ��", ability) > 0)
		{
			display.showTextI("&Bǰհֱ���Ķһ������ &A",
				eventTime.getPrimogemExpect(endTime, "ǰհֱ��", ability), " &Bԭʯ��\n");
		}
		if (eventTime.getPrimogemExpect(endTime, "�汾���²���", ability) > 0)
		{
			display.showTextI("&B�汾���²������� &A",
				eventTime.getPrimogemExpect(endTime, "�汾���²���", ability), " &Bԭʯ��\n");
		}
		display.showText("\n");
		if (listSet == "�ر�")
		{
			display.showButton('5', "��ʾ��ϸ���");
		}
		else if (listSet == "����")
		{
			display.showButton('5', "������ϸ���");
		}
		display.showButton('0', "����");
		opr = display.selectButton();
		if (opr == '5')
		{
			if (listSet == "�ر�")
			{
				listSet = "����";
			}
			else if (listSet == "����")
			{
				listSet = "�ر�";
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
	string text = "&7ԭ�񹤾� &8>&7 ���˵� &8>&7 �¼�����ԴԤ�� &8>&7 ����֮Ե����Ԥ��\n\n";
	text += "&B��ʼ����:&A";
	text += this->timeToString(startTime, true);
	text += "&B\n��ֹ����:&A";
	text += this->timeToString(endTime, true);
	text += "&B\n";
	display.showText(text);
	display.showText("\n&E����������ÿ����������ܹ���õ�ԭʯ����[0~600]:\n");
	while (ability < 0 || ability > 600 || ability % 50 != 0)
	{
		ability = display.getInputInt(600, false);
		if (ability % 50 != 0)
		{
			display.clearText(5, 0, 7);
			display.clearText(50, 0, 6);
			display.showText("&C�������ֵ��Ч������Ϊ50�ı�����&7\n");
		}
	}
	text += "&B��ÿ����������ܹ���ȡ &A";
	text += display.intToString(ability);
	text += " &Bԭʯ\n";
	display.clear();
	display.showText(text);
	display.showText("\n&E���Ƿ����˿���ף��\n");
	display.showButton('1', "��");
	display.showButton('2', "��");
	display.showButton('0', "�˳�");
	opr = display.selectButton();
	if (opr == '0')
	{
		return;
	}
	else if (opr == '1')
	{
		text += "û�й������ף����";
		hasWish = false;
	}
	else if (opr == '2')
	{
		text += "ӵ�п���ף����";
		hasWish = true;
	}
	display.clear();
	display.showText(text);
	display.showText("\n\n&E���Ƿ������������\n");
	display.showButton('1', "��");
	display.showButton('2', "��");
	display.showButton('0', "�˳�");
	opr = display.selectButton();
	if (opr == '0')
	{
		return;
	}
	else if (opr == '1')
	{
		text += "û�й���������С�\n\n";
		hasExp = false;
	}
	else if (opr == '2')
	{
		text += "�ѽ���������С�\n\n";
		hasExp = true;
	}

	EventTime eventTime(startTime - 1);

	Option option;
	string listSet = option.currentSet[option.getOptionPos("ԭʯ����Ԥ����")];
	while (opr != '0')
	{
		int coordY = 7;
		int currentSum = 0;
		int lastSum = 0;
		TimeCaculator tempTime = startTime;

		if (listSet == "�Զ�����")
		{
			if (endTime - startTime + 1 > 45)
			{
				listSet = "�ر�";
			}
			else
			{
				listSet = "����";
			}
		}

		display.clear();
		display.showText(text);

		if (listSet == "����")
		{
			display.createText("&B����", 0, coordY);
			display.createText("&B����", 16, coordY);
			display.createText("&B���ջ�ȡ", 25, coordY);
			display.createText("&B�ۼƻ�ȡ", 38, coordY);
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

		display.showText("&cע��:Ԥ����������ʷ�汾�Ĺ��ɽ���Ԥ�⣬����һ����ȫ׼ȷ��\n");
		display.showText("&c     Ԥ���������ο���������������ʵ�����Ϊ׼��\n\n");
		display.showTextI("&E���� &A", endTime - startTime + 1, " &E�������ԭʯȫ���һ�Ϊ����֮Ե��Ԥ��һ���ܹ����");
		display.showTextI(" &A", eventTime.keepWishExpect(endTime, ability, hasWish, hasExp), " &E����֮Ե��\n");
		display.showText("&E���ǵ���Դ�������·���:\n");
		display.showTextI("&B���ÿ��ί���ܼƿɶһ�Լ &A",
			eventTime.getWishExpect(endTime, "ÿ�ջ�Ծ", ability), " &B����֮Ե��\n");
		if (eventTime.getWishExpect(endTime, "�ǳ��һ�", ability) > 0)
		{
			display.showTextI("&B�³����̵����ʹ���ǳ��һ� &A",
				eventTime.getWishExpect(endTime, "�ǳ��һ�", ability), " &B����֮Ե��\n");
		}
		if (hasWish == true)
		{
			display.showTextI("&Bͨ������ף���ܼƿɶһ�Լ &A",
				eventTime.getWishExpect(endTime, "����ף��", ability), " &B����֮Ե��\n");
		}
		if (hasExp == true && eventTime.getWishExpect(endTime, "�������", ability) > 0)
		{
			display.showTextI("&Bͨ����������ܼƿɻ��Լ &A",
				eventTime.getWishExpect(endTime, "�������", ability), " &B����֮Ե��\n");
		}
		if (eventTime.getWishExpect(endTime, "�����", ability) > 0)
		{
			vector<int> temp = { eventTime.getPrimogemExpect(endTime, "�����", ability) / ability,
			eventTime.getWishExpect(endTime, "�����", ability) };
			string tempS = "&B�ڼ������������ &A# &B�Σ�";
			tempS += "����������ս��õ�ԭʯ�ܹ����Զһ�Լ&A # &B����֮Ե��\n";
			display.showTextI(tempS, temp);
		}
		if (eventTime.getWishExpect(endTime, "��ɫ����", ability) > 0)
		{
			vector<int> temp = { eventTime.getPrimogemExpect(endTime, "��ɫ����", ability) / 20,
				eventTime.getWishExpect(endTime, "��ɫ����", ability) };
			display.showTextI("&B�� &A# &B�ڽ�ɫ���ã����л�õ�ԭʯ�ɶһ�Լ&A # &B����֮Ե��\n", temp);
		}
		if (eventTime.getWishExpect(endTime, "�����", ability) > 0)
		{
			display.showTextI("&B�������еİ汾���õ�ԭʯ�ܹ����Զһ�Լ &A",
				eventTime.getWishExpect(endTime, "�����", ability), " &B����֮Ե��\n");
		}
		if (eventTime.getWishExpect(endTime, "ǰհֱ��", ability) > 0)
		{
			display.showTextI("&Bǰհֱ���Ķһ��������ԭʯ�ɶһ�Լ &A",
				eventTime.getWishExpect(endTime, "ǰհֱ��", ability), " &B����֮Ե��\n");
		}
		if (eventTime.getWishExpect(endTime, "�汾���²���", ability) > 0)
		{
			display.showTextI("&B�汾���²���������ԭʯ�ɶһ�Լ &A",
				eventTime.getWishExpect(endTime, "�汾���²���", ability), " &B����֮Ե��\n");
		}
		display.showText("&cע��:���ڼ���ʱ�Խ���������������봦��");
		display.showText("&c�������������Դ����õ��������������ܲ�����������\n\n");
		if (listSet == "�ر�")
		{
			display.showButton('5', "��ʾ��ϸ���");
		}
		else if (listSet == "����")
		{
			display.showButton('5', "������ϸ���");
		}
		display.showButton('0', "����");
		opr = display.selectButton();
		if (opr == '5')
		{
			if (listSet == "�ر�")
			{
				listSet = "����";
			}
			else if (listSet == "����")
			{
				listSet = "�ر�";
			}
		}
	}
}

void EventTimeUi::newVersionUi(TimeCaculator startTime, TimeCaculator endTime)
{
	Display display;
	char opr = '\0';

	Option option;
	string listSet = option.currentSet[option.getOptionPos("�¼�ʱ��Ԥ����ʾ��ʽ")];
	while (opr != '0')
	{
		EventTime eventTime(startTime);
		TimeCaculator tempTime = eventTime.getCurrentVersionOP();
		eventTime = EventTime(tempTime + 1);
		int coordY = 2;

		display.clear();
		display.showText("&7ԭ�񹤾� &8>&7 ���˵� &8>&7 �¼�����ԴԤ�� &8>&7 �¼�ʱ��Ԥ��\n\n");

		if (listSet == "����˵��")
		{
			while (tempTime <= endTime)
			{
				display.createText("&B" + this->timeToString(tempTime, false), 0, coordY);
				display.createText("&E��", 16, coordY);
				tempTime = eventTime.getNextVersionOP();
				display.createText("&B" + this->timeToString(tempTime - 1, false), 19, coordY);
				display.createText("&E" + eventTime.getVersionId() + "�汾", 35, coordY);
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
				display.showText("&EԤ��&B" + eventTime.getVersionId() + "�汾&E��һ�ڻ��Ը��ʼʱ�� &B"
					+ this->timeToString(tempTime, false) + "\n");
				display.showText("&E           &E�ڶ��ڻ��Ը��ʼʱ�� &B"
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
				display.showText("&EԤ��&B" + eventTime.getVersionId() + "�汾&Eǰհֱ��ʱ�� &B"
					+ this->timeToString(tempTime - 12, false) + "\n");
				tempTime = eventTime.getNextVersionOP();
				eventTime = EventTime(tempTime + 1);
			}
		}
		else if (listSet == "������")
		{
			display.createText("&B�汾��", 0, coordY);
			display.createText("&Bǰհֱ������", 10, coordY);
			display.createText("&B�汾��ʼ����", 26, coordY);
			display.createText("&B�ڶ��ڻ��Ը", 42, coordY);
			display.createText("&B�汾��������", 58, coordY);

			coordY++;
			while (tempTime <= endTime)
			{
				display.createText("&E" + eventTime.getVersionId() + "�汾", 0, coordY);
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
		else if (listSet == "������")
		{
			int coordX = 0;
			display.createText("&B�汾��", coordX, 2);
			display.createText("&Bǰհֱ��", coordX, 3);
			display.createText("&B�½�ɫPV", coordX, 4);
			display.createText("&B����������", coordX, 5);
			display.createText("&B�����ǽ�ɫ", coordX, 6);
			display.createText("&BԤ���ؿ���", coordX, 7);
			display.createText("&B��Ը����", coordX, 8);
			display.createText("&B�½�ɫ��ʾ", coordX, 9);
			display.createText("&B�汾��ʼ", coordX, 10);
			display.createText("&B��һ����Ը", coordX, 11);
			display.createText("&B�½�ɫPV", coordX, 12);
			display.createText("&B����������", coordX, 13);
			display.createText("&B�����ǽ�ɫ", coordX, 14);
			display.createText("&B��Ը����", coordX, 15);
			display.createText("&B�½�ɫ��ʾ", coordX, 16);
			display.createText("&B�ڶ�����Ը", coordX, 17);
			display.createText("&B���йر�", coordX, 18);
			display.createText("&B�汾����", coordX, 19);
			coordX = 12;
			while (tempTime <= endTime)
			{
				display.createText("&E" + eventTime.getVersionId() + "�汾", coordX, 2);
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

		display.showText("\n&cע��:�������õĽ��������ʷ�汾�Ĺ��ɽ���Ԥ�⣬����һ����ȫ׼ȷ��\n");
		display.showText("&c     �������õĽ�������ο�������ʱ������ʵ�����Ϊ׼��\n\n");

		if (listSet == "����˵��")
		{
			display.showButton('5', "�Ժ�����ķ�ʽ��ʾ");
		}
		else if (listSet == "������")
		{
			display.showButton('5', "��������ķ�ʽ��ʾ");
		}
		else if (listSet == "������")
		{
			display.showButton('5', "������˵���ķ�ʽ��ʾ");
		}
		display.showButton('0', "����");
		opr = display.selectButton();
		if (opr == '5')
		{
			if (listSet == "����˵��")
			{
				listSet = "������";
			}
			else if (listSet == "������")
			{
				listSet = "������";
			}
			else if (listSet == "������")
			{
				listSet = "����˵��";
			}
		}
	}
}

void EventTimeUi::sourceExpectUi(TimeCaculator startTime, TimeCaculator endTime)
{
	Display display;
	int worldLevel = 0;
	char opr = '\0';
	string text = "&7ԭ�񹤾� &8>&7 ���˵� &8>&7 �¼�����ԴԤ�� &8>&7 ԭ����֬Ԥ��\n\n";
	text += "&B��ʼ����:&A";
	text += this->timeToString(startTime, true);
	text += "&B\n��ֹ����:&A";
	text += this->timeToString(endTime, true);
	text += "&B\n";

	while (opr != '0')
	{
		vector<int> tempPara;
		vector<int> intPara = { endTime - startTime };
		
		display.clear();
		display.showText(text);
		display.showText("\n&7�������������ȼ�[0~8]:\n");
		worldLevel = display.getInputInt(8, false);
		text += "&B����ȼ�: &A";
		text += display.intToString(worldLevel);
		text += "\n\n";

		intPara.push_back(intPara[0] * 180); //��������
		intPara.push_back(intPara[1] * 5); //��þ���
		tempPara = { 600, 1000, 1400, 1800, 2200, 2600, 3000, 3000, 3000 };
		intPara.push_back(intPara[1] * tempPara[worldLevel]); //ȫ��ˢ���

		display.clear();
		display.showText(text);
		display.showTextI("&E�� &A# &E��ʱ�����ۼƻظ� &A# &Eԭ����֬��\n"
			"��ȫ�����꣬�ɻ���ۼ� &A# &Eð��������\n"
			"��ȫ������ˢĦ�����ۼƿɻ�� &A# &EĦ����\n\n", intPara);

		display.showButton('0', "����");
		opr = display.selectButton();
	}
}
