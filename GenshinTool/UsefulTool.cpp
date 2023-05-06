#include "UsefulTool.h"

#include "Display.h"
#include "Data.h"

void UsefulTool::showUi()
{
	Display display;
	Data data;
	char opr = '\0';

	while (opr != '0')
	{
		unsigned int i = 0;
		vector<unsigned int> oprList;

		display.clear();
		display.showText("&7ԭ�񹤾� &8>&7 ���˵� &8> &7С����\n\n");
		display.showButton('1', "��ȡ��Ը��ʷ��¼��ַ");
		display.showButton('2', "��ȡ�ϴ���Ϸ����Ϣ");
		display.showButton('0', "����");
		opr = display.selectButton();

		if (opr == '1')
		{
			this->getWishNet();
		}
		else if (opr == '2')
		{
			this->getGameInfo();
		}
	}
}

void UsefulTool::getWishNet()
{
	Display display;
	Data data;
	Option option;
	string debugSet = option.currentSet[option.getOptionPos("������Ϣ")];
	char opr = '\0';

	while (opr != '0')
	{
		vector<unsigned int> oprList;
		bool isFirst = true;

		display.clear();
		display.showText("&7ԭ�񹤾� &8>&7 ���˵� &8> &7С���� &8> &7��ȡ��Ը��ʷ��¼��ַ\n\n");
		display.showText("&E������......");

		string fileStr = data.openFile("C:\\Users\\" + display.getSystemUserName() +
			"\\AppData\\LocalLow\\miHoYo\\ԭ��\\output_log.txt");
		
		if (fileStr == "")
		{
			display.clear();
			display.showText("&7ԭ�񹤾� &8>&7 ���˵� &8> &7С���� &8> &7��ȡ��Ը��ʷ��¼��ַ\n\n");
			display.showText("&Cû���ҵ���Ϸ�ļ�����ȷ���˼�������Ѿ���װ���򿪹���Ϸ��\n\n");
			display.showButton('1', "���»�ȡ");
			display.showButton('0', "����");
			opr = display.selectButton();
			continue;
		}

		int i = 0;
		int j = 0;
		bool isOutput = false;
		bool hasFind = false;
		int matcher = 0;
		string output = "";
		while (fileStr[i] != '\0')
		{
			if (isOutput == false)
			{
				string matches = "webstatic.mihoyo.com";
				if (matches[matcher] == fileStr[i])
				{
					matcher++;
				}
				else
				{
					matcher = 0;
				}

				if (matcher > 19)
				{
					output += "https:";
					output += "//webstatic.mihoyo.com";
					isOutput = true;
					matcher = 0;
				}
			}
			else
			{
				output.push_back(fileStr[i]);
				string matches = "#/log";
				if (matches[matcher] == fileStr[i])
				{
					matcher++;
				}
				else
				{
					matcher = 0;
				}

				if (fileStr[i] == '\n' || fileStr[i] == '\r')
				{
					isOutput = false;
					matcher = 0;
					output = "";
				}

				if (matcher > 4)
				{
					isOutput = false;
					hasFind = true;
					matcher = 0;
					if (isFirst == true)
					{
						display.clear();
						display.showText("&7ԭ�񹤾� &8>&7 ���˵� &8> &7С���� &8> &7��ȡ��Ը��ʷ��¼��ַ\n\n");
						isFirst = false;
					}
					display.out(output);
					display.showText("\n\n");
					output = "";
				}
			}

			i++;
		}

		if (hasFind == false)
		{
			display.clear();
			display.showText("&7ԭ�񹤾� &8>&7 ���˵� &8> &7С���� &8> &7��ȡ��Ը��ʷ��¼��ַ\n\n");
			display.showText("&Cδ�ҵ���Ը��ʷ��¼��ַ��������Ϸ�д���Ը��ʷ��¼�����ԡ�\n\n");
		}

		if (debugSet == "����")
		{
			display.showCodeText("(Display)display.(string)getSystemUserName() = \""
				+ display.getSystemUserName() + "\"\n");
			display.showCodeText("(string)fileStr.size() = "
				+ display.intToString((int)fileStr.size()) + "\n");
			display.showText("\n");
		}

		display.showButton('1', "���»�ȡ");
		display.showButton('0', "����");
		opr = display.selectButton();
	}
	//%UserProfile%\AppData\LocalLow\miHoYo\ԭ��\output_log.txt
	//%UserProfile%\AppData\LocalLow\miHoYo\Genshin Impact\output_log.txt
}

void UsefulTool::getGameInfo()
{
	Display display;
	Data data;
	Option option;
	string debugSet = option.currentSet[option.getOptionPos("������Ϣ")];
	char opr = '\0';

	while (opr != '0')
	{
		vector<unsigned int> oprList;

		display.clear();
		display.showText("&7ԭ�񹤾� &8>&7 ���˵� &8> &7С���� &8> &7��ȡ�ϴ���Ϸ����Ϣ\n\n");
		display.showText("&E������......");

		string fileStr = data.openFile("C:\\Users\\" + display.getSystemUserName() +
			"\\AppData\\LocalLow\\miHoYo\\ԭ��\\info.txt");

		if (fileStr == "")
		{
			display.clear();
			display.showText("&7ԭ�񹤾� &8>&7 ���˵� &8> &7С���� &8> &7��ȡ�ϴ���Ϸ����Ϣ\n\n");
			display.showText("&Cû���ҵ���Ϸ�ļ�����ȷ���˼�������Ѿ���װ���򿪹���Ϸ��\n\n");
			display.showButton('1', "���»�ȡ");
			display.showButton('0', "����");
			opr = display.selectButton();
			continue;
		}

		display.clear();
		display.showText("&7ԭ�񹤾� &8>&7 ���˵� &8> &7С���� &8> &7��ȡ�ϴ���Ϸ����Ϣ\n\n");
		display.out(fileStr);
		display.showText("\n");

		if (debugSet == "����")
		{
			display.showCodeText("(Display)display.(string)getSystemUserName() = \""
				+ display.getSystemUserName() + "\"\n");
			display.showCodeText("(string)fileStr.size() = "
				+ display.intToString((int)fileStr.size()) + "\n");
			display.showText("\n");
		}

		display.showButton('1', "���»�ȡ");
		display.showButton('0', "����");
		opr = display.selectButton();
	}
}
