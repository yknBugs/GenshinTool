#include "MainUi.h"

#include "OptionUi.h"
#include "WishUi.h"
#include "WishCaculatorUi.h"
#include "EventTimeUi.h"
#include "ArtifactUi.h"
#include "CharactorUi.h"
#include "UsefulTool.h"

void MainUi::showUi()
{
	Display display;
	char opr = '\0';
	
	while (opr != '0')
	{
		display.clear();
		display.showText("&7原神工具 &8>&7 主菜单\n\n");
		display.showText("&6ykn &E版权所有。\n\n");

		display.showButton('1', "祈愿(模拟器)");
		display.showButton('2', "祈愿概率计算器");
		display.showButton('3', "事件和资源预测");
		display.showButton('4', "圣遗物(模拟器)");
		display.showButton('5', "练度计算器");
		display.showButton('7', "小工具");
		display.showButton('8', "设置");
		display.showButton('9', "关于");
		display.showButton('0', "退出");
		opr = display.selectButton();

		if (opr == '1')
		{
			WishUi wishUi;
			wishUi.showUi();
		}
		else if (opr == '2')
		{
			WishCaculatorUi wishCaculatorUi;
			wishCaculatorUi.showUi();
		}
		else if (opr == '3')
		{
			EventTimeUi eventTimeUi;
			eventTimeUi.showUi();
		}
		else if (opr == '4')
		{
			ArtifactUi artifactUi;
			artifactUi.showUi();
		}
		else if (opr == '5')
		{
			CharactorUi charactorUi;
			charactorUi.showUi();
		}
		else if (opr == '7')
		{
			UsefulTool usefulTool;
			usefulTool.showUi();
		}
		else if (opr == '8')
		{
			OptionUi optionUi;
			optionUi.showUi();
		}
		else if (opr == '9')
		{
			this->aboutPage();
		}
	}
}

void MainUi::aboutPage()
{
	Display display;
	char opr = '\0';

	while (opr != '0')
	{
		display.clear();

		display.showText("&7原神工具 &8>&7 主菜单 &8>&7 关于\n\n");
		display.showText("&7版本: &AV4.1 &6Build 7    &B2022年4月14日\n");
		display.showText("&C注意:此版本为测试版本，可能存在严重的漏洞。\n");
		display.showText("\n");
		display.showText("&6公告:\n");
		display.showText("&6我们即将新增大量的功能。\n");
		display.showText("&6这可能导致某些版本出现严重的漏洞。\n");
		display.showText("\n", true);
		display.showText("&7当前&6Build&7版本更新内容:\n");
		display.showText("&A卡池内容同步至V2.6版本下半。\n");
		display.showText("\n");
		display.showText("&7当前大版本更新内容:\n");
		display.showText("&A新增伤害计算器与练度计算功能。\n");
		display.showText("&A新增圣遗物强化模拟功能。\n");
		display.showText("&A祈愿模拟器现在支持自定义祈愿次数了。\n");
		display.showText("&A现在每一次按键输入都会进行合法性检查。\n");
		display.showText("&A祈愿动画现在可以通过选择文字后取消选择来跳过了。\n");
		display.showText("&A祈愿历史记录现在增加了单次显示条数的上限。\n");
		display.showText("&A新增对祈愿历史记录的筛选功能。\n");
		display.showText("&A优化了部分文本描述，修复了一些问题。\n");
		display.showText("\n");
		display.showButton('0', "返回");
		opr = display.selectButton();
	}
}
