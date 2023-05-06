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
		display.showText("&7ԭ�񹤾� &8>&7 ���˵�\n\n");
		display.showText("&6ykn &E��Ȩ���С�\n\n");

		display.showButton('1', "��Ը(ģ����)");
		display.showButton('2', "��Ը���ʼ�����");
		display.showButton('3', "�¼�����ԴԤ��");
		display.showButton('4', "ʥ����(ģ����)");
		display.showButton('5', "���ȼ�����");
		display.showButton('7', "С����");
		display.showButton('8', "����");
		display.showButton('9', "����");
		display.showButton('0', "�˳�");
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

		display.showText("&7ԭ�񹤾� &8>&7 ���˵� &8>&7 ����\n\n");
		display.showText("&7�汾: &AV4.1 &6Build 7    &B2022��4��14��\n");
		display.showText("&Cע��:�˰汾Ϊ���԰汾�����ܴ������ص�©����\n");
		display.showText("\n");
		display.showText("&6����:\n");
		display.showText("&6���Ǽ������������Ĺ��ܡ�\n");
		display.showText("&6����ܵ���ĳЩ�汾�������ص�©����\n");
		display.showText("\n", true);
		display.showText("&7��ǰ&6Build&7�汾��������:\n");
		display.showText("&A��������ͬ����V2.6�汾�°롣\n");
		display.showText("\n");
		display.showText("&7��ǰ��汾��������:\n");
		display.showText("&A�����˺������������ȼ��㹦�ܡ�\n");
		display.showText("&A����ʥ����ǿ��ģ�⹦�ܡ�\n");
		display.showText("&A��Ըģ��������֧���Զ�����Ը�����ˡ�\n");
		display.showText("&A����ÿһ�ΰ������붼����кϷ��Լ�顣\n");
		display.showText("&A��Ը�������ڿ���ͨ��ѡ�����ֺ�ȡ��ѡ���������ˡ�\n");
		display.showText("&A��Ը��ʷ��¼���������˵�����ʾ���������ޡ�\n");
		display.showText("&A��������Ը��ʷ��¼��ɸѡ���ܡ�\n");
		display.showText("&A�Ż��˲����ı��������޸���һЩ���⡣\n");
		display.showText("\n");
		display.showButton('0', "����");
		opr = display.selectButton();
	}
}
