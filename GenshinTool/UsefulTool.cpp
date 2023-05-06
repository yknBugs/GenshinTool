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
		display.showText("&7原神工具 &8>&7 主菜单 &8> &7小工具\n\n");
		display.showButton('1', "获取祈愿历史记录网址");
		display.showButton('2', "获取上次游戏的信息");
		display.showButton('0', "返回");
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
	string debugSet = option.currentSet[option.getOptionPos("调试信息")];
	char opr = '\0';

	while (opr != '0')
	{
		vector<unsigned int> oprList;
		bool isFirst = true;

		display.clear();
		display.showText("&7原神工具 &8>&7 主菜单 &8> &7小工具 &8> &7获取祈愿历史记录网址\n\n");
		display.showText("&E加载中......");

		string fileStr = data.openFile("C:\\Users\\" + display.getSystemUserName() +
			"\\AppData\\LocalLow\\miHoYo\\原神\\output_log.txt");
		
		if (fileStr == "")
		{
			display.clear();
			display.showText("&7原神工具 &8>&7 主菜单 &8> &7小工具 &8> &7获取祈愿历史记录网址\n\n");
			display.showText("&C没有找到游戏文件，请确保此计算机上已经安装并打开过游戏。\n\n");
			display.showButton('1', "重新获取");
			display.showButton('0', "返回");
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
						display.showText("&7原神工具 &8>&7 主菜单 &8> &7小工具 &8> &7获取祈愿历史记录网址\n\n");
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
			display.showText("&7原神工具 &8>&7 主菜单 &8> &7小工具 &8> &7获取祈愿历史记录网址\n\n");
			display.showText("&C未找到祈愿历史记录网址，请在游戏中打开祈愿历史记录后重试。\n\n");
		}

		if (debugSet == "开启")
		{
			display.showCodeText("(Display)display.(string)getSystemUserName() = \""
				+ display.getSystemUserName() + "\"\n");
			display.showCodeText("(string)fileStr.size() = "
				+ display.intToString((int)fileStr.size()) + "\n");
			display.showText("\n");
		}

		display.showButton('1', "重新获取");
		display.showButton('0', "返回");
		opr = display.selectButton();
	}
	//%UserProfile%\AppData\LocalLow\miHoYo\原神\output_log.txt
	//%UserProfile%\AppData\LocalLow\miHoYo\Genshin Impact\output_log.txt
}

void UsefulTool::getGameInfo()
{
	Display display;
	Data data;
	Option option;
	string debugSet = option.currentSet[option.getOptionPos("调试信息")];
	char opr = '\0';

	while (opr != '0')
	{
		vector<unsigned int> oprList;

		display.clear();
		display.showText("&7原神工具 &8>&7 主菜单 &8> &7小工具 &8> &7获取上次游戏的信息\n\n");
		display.showText("&E加载中......");

		string fileStr = data.openFile("C:\\Users\\" + display.getSystemUserName() +
			"\\AppData\\LocalLow\\miHoYo\\原神\\info.txt");

		if (fileStr == "")
		{
			display.clear();
			display.showText("&7原神工具 &8>&7 主菜单 &8> &7小工具 &8> &7获取上次游戏的信息\n\n");
			display.showText("&C没有找到游戏文件，请确保此计算机上已经安装并打开过游戏。\n\n");
			display.showButton('1', "重新获取");
			display.showButton('0', "返回");
			opr = display.selectButton();
			continue;
		}

		display.clear();
		display.showText("&7原神工具 &8>&7 主菜单 &8> &7小工具 &8> &7获取上次游戏的信息\n\n");
		display.out(fileStr);
		display.showText("\n");

		if (debugSet == "开启")
		{
			display.showCodeText("(Display)display.(string)getSystemUserName() = \""
				+ display.getSystemUserName() + "\"\n");
			display.showCodeText("(string)fileStr.size() = "
				+ display.intToString((int)fileStr.size()) + "\n");
			display.showText("\n");
		}

		display.showButton('1', "重新获取");
		display.showButton('0', "返回");
		opr = display.selectButton();
	}
}
