#include "ArtifactUi.h"

#include "Display.h"
#include "Data.h"

Artifact ArtifactUi::dropArtifact(int selectHouse, short star)
{
	Data data;
	RandEngine randEngine;

	vector<string> tempList = data.getArtifactsList(star)[selectHouse];
	int randArts = randEngine.random(0, (int)tempList.size() - 1);

	tempList = data.getArtifactList(tempList[randArts]);
	int randPos = randEngine.random(0, (int)tempList.size() - 1);

	string randName = tempList[randPos];
	Artifact result(randName, randPos + 1, star, 0.2);
	return result;
}

void ArtifactUi::showArtifact(Artifact artifact, int coordX, int coordY)
{
	unsigned int i = 0;
	Display display;
	string colorlist[] = { "&7","&8","&A","&3","&D","&6","&4" };
	string tempS;

	display.setCursorPos(coordX, coordY);
	tempS = colorlist[artifact.getStar()];
	tempS += artifact.getName();
	display.showText(tempS);

	display.setCursorPos(coordX, coordY + 1);
	tempS = "&8";
	if (artifact.getPos() == ARTIFACTPOS_FLOWER)
	{
		tempS += "��֮��";
	}
	else if (artifact.getPos() == ARTIFACTPOS_WING)
	{
		tempS += "��֮��";
	}
	else if (artifact.getPos() == ARTIFACTPOS_SAND)
	{
		tempS += "ʱ֮ɳ";
	}
	else if (artifact.getPos() == ARTIFACTPOS_CUP)
	{
		tempS += "��֮��";
	}
	else if (artifact.getPos() == ARTIFACTPOS_HEAD)
	{
		tempS += "��֮��";
	}
	tempS += "            &7+";
	tempS += display.intToString((int)artifact.getLevel());
	display.showText(tempS);

	display.setCursorPos(coordX, coordY + 2);
	tempS = "&E";
	tempS += artifact.attrIdToString(artifact.getMainAttrId());
	display.showText(tempS);

	display.setCursorPos(coordX + 18, coordY + 2);
	tempS = "&E";
	if (artifact.getAttrIsPercent(artifact.getMainAttrId()) == true)
	{
		tempS += display.doubleToString(artifact.getMainAttrValue(), 1);
		tempS += "%";
	}
	else
	{
		tempS += display.intToString((int)(artifact.getMainAttrValue() + 0.5));
	}
	display.showText(tempS);

	for (i = 0; i < 4; i++)
	{
		if (artifact.getSubAttrId(i) > 0)
		{
			tempS = "&7";
			tempS += artifact.attrIdToString(artifact.getSubAttrId(i));
			tempS += "+";
			if (artifact.getAttrIsPercent(artifact.getSubAttrId(i)) == true)
			{
				tempS += display.doubleToString(artifact.getSubAttrValue(i), 1);
				tempS += "%";
			}
			else
			{
				tempS += display.intToString((int)(artifact.getSubAttrValue(i) + 0.5));
			}
			display.setCursorPos(coordX, coordY + 3 + i);
			display.showText(tempS);
		}
		else
		{
			break;
		}
	}
}

void ArtifactUi::showLevelUp(Artifact last, Artifact current, int coordX, int coordY)
{
	Display display;
	unsigned int i = 0;

	int succeedTime = 0;
	display.setCursorPos(coordX, coordY);
	display.showText("&Aǿ���ɹ�!         ");
	display.showTextI((int)last.getLevel());
	display.setCursorPos(coordX + 25, coordY);
	display.showText("&7->&A  ");
	display.showTextI((int)current.getLevel());
	display.setCursorPos(coordX, coordY + 1);
	display.showText("&E");
	display.showText(last.attrIdToString(last.getMainAttrId()));
	display.setCursorPos(coordX + 18, coordY + 1);
	display.showText("&E");
	if (current.getAttrIsPercent(current.getMainAttrId()) == true)
	{
		display.showText(display.doubleToString(last.getMainAttrValue(), 1));
		display.showText("%");
		display.setCursorPos(coordX + 25, coordY + 1);
		display.showText("&7->&E  ");
		display.showText(display.doubleToString(current.getMainAttrValue(), 1));
		display.showText("%");
	}
	else
	{
		display.showText(display.intToString((int)(last.getMainAttrValue() + 0.5)));
		display.setCursorPos(coordX + 25, coordY + 1);
		display.showText("&7->&E  ");
		display.showText(display.intToString((int)(current.getMainAttrValue() + 0.5)));
	}
	for (i = 0; i < 4; i++)
	{
		if (last.getSubAttrValue(i) != current.getSubAttrValue(i))
		{
			succeedTime++;
			display.setCursorPos(coordX, coordY + 1 + succeedTime);
			display.showText("&7");
			display.showText(last.attrIdToString(current.getSubAttrId(i)));
			display.setCursorPos(coordX + 18, coordY + 1 + succeedTime);
			display.showText("&7");
			if (last.getSubAttrId(i) == 0)
			{
				if (current.getAttrIsPercent(current.getSubAttrId(i)) == true)
				{
					display.setCursorPos(coordX + 29, coordY + 1 + succeedTime);
					display.showText("&7");
					display.showText(display.doubleToString(current.getSubAttrValue(i), 1));
					display.showText("%");
				}
				else
				{
					display.setCursorPos(coordX + 29, coordY + 1 + succeedTime);
					display.showText("&7");
					display.showText(display.intToString((int)(current.getSubAttrValue(i) + 0.5)));
				}
			}
			else
			{
				if (current.getAttrIsPercent(current.getSubAttrId(i)) == true)
				{
					display.showText(display.doubleToString(last.getSubAttrValue(i), 1));
					display.showText("%");
					display.setCursorPos(coordX + 25, coordY + 1 + succeedTime);
					display.showText("&7->  ");
					display.showText(display.doubleToString(current.getSubAttrValue(i), 1));
					display.showText("%");
				}
				else
				{
					display.showText(display.intToString((int)(last.getSubAttrValue(i) + 0.5)));
					display.setCursorPos(coordX + 25, coordY + 1 + succeedTime);
					display.showText("&7->  ");
					display.showText(display.intToString((int)(current.getSubAttrValue(i) + 0.5)));
				}
			}
		}
	}
}

void ArtifactUi::showUi()
{
	Display display;
	char opr = '\0';

	while (opr != '0')
	{
		display.clear();
		display.showText("&7ԭ�񹤾� &8>&7 ���˵� &8> &7ʥ����(ģ����)\n\n");
		display.showButton('1', "��ȡ��ǿ��ģ��");
		display.showButton('2', "�ϳ�̨�ϳ�ģ��");
		display.showButton('0', "����");
		opr = display.selectButton();

		if (opr == '1')
		{
			this->showLevelUpUi();
		}
		else if (opr == '2')
		{
			this->showCraftUi();
		}
	}
}

void ArtifactUi::showLevelUpUi()
{
	Display display;
	Data data;
	RandEngine randEngine;
	Option option;
	vector<string> oprList = data.getArtifactHouseList();
	string debugSet = option.currentSet[option.getOptionPos("������Ϣ")];
	string text = "&7ԭ�񹤾� &8>&7 ���˵� &8> &7ʥ����(ģ����) &8> &7��ȡ��ǿ��ģ��\n\n";
	unsigned int i = 0;
	char opr = '\0';

	int selectHouse = 0; //ѡ��ĸ���
	int selectArts = 0; //ѡ���ˢ������Ʒ
	int useItem = 0; //ʹ�õĵ���
	int totalTime = 0; //�ۼ�ˢȡ�Ĵ���

	display.clear();
	display.showText(text);
	display.showText("&7��ѡ������Ҫˢȡ�ĸ�����\n\n");

	for (i = 0; i < oprList.size(); i++)
	{
		display.showButton('a' + i, oprList[i]);
	}
	display.showButton('0', "�˳�");
	opr = display.selectButton();
	if (opr == '0')
	{
		return;
	}
	else
	{
		selectHouse = (int)opr - 'a';
		text += "&B";
		text += oprList[selectHouse];
		text += "\n";
	}

	display.clear();
	display.showText(text);
	display.showText("\n&7������Ҫ���ĵĵ��ߡ�\n\n");
	display.showButton('1', "ԭ����֬");
	display.showButton('2', "Ũ����֬");
	display.showButton('0', "�˳�");
	opr = display.selectButton();
	if (opr == '0')
	{
		return;
	}
	else if (opr == '1')
	{
		useItem = 1;
		text += "&Bԭ����֬\n";
	}
	else if (opr == '2')
	{
		useItem = 2;
		text += "&BŨ����֬\n";
	}

	while (opr != '0')
	{
		opr = '\0';
		totalTime++;
		selectArts = 0;
		vector<Artifact> artifactList; //ˢ���Ķ���
		Artifact tempArt; //����ȷ��������ı��˵�����
		if (useItem == 1 || useItem == 2)
		{
			//����
			for (i = 0; i < (unsigned int)useItem; i++)
			{
				artifactList.push_back(this->dropArtifact(selectHouse, 5));
				if (randEngine.randSucceed(0.07) == true)
				{
					artifactList.push_back(this->dropArtifact(selectHouse, 5));
				}
			}
			//����
			for (i = 0; i < (unsigned int)useItem; i++)
			{
				artifactList.push_back(this->dropArtifact(selectHouse, 4));
				artifactList.push_back(this->dropArtifact(selectHouse, 4));
				if (randEngine.randSucceed(0.48) == true)
				{
					artifactList.push_back(this->dropArtifact(selectHouse, 4));
				}
			}
			//����
			for (i = 0; i < (unsigned int)useItem; i++)
			{
				artifactList.push_back(this->dropArtifact(selectHouse, 3));
				artifactList.push_back(this->dropArtifact(selectHouse, 3));
				artifactList.push_back(this->dropArtifact(selectHouse, 3));
				if (randEngine.randSucceed(0.55) == true)
				{
					artifactList.push_back(this->dropArtifact(selectHouse, 3));
				}
			}
		}

		while (opr != '0' && opr != '1')
		{
			int tempCoordY = 0;

			display.clear();
			display.showText(text);
			display.showTextI("&B���ۼ�ˢȡ &A", totalTime, " &B�Ρ�\n");
			display.showText("\n");
			for (i = 0; i < artifactList.size(); i++)
			{
				if (i == selectArts)
				{
					display.showText("&8");
					display.showText(artifactList[i].getName());
					display.showText("\n");
				}
				else
				{
					string colorlist[] = { "&7","&8","&A","&3","&D","&6","&4" };
					display.showText(colorlist[artifactList[i].getStar()]);
					display.showText(artifactList[i].getName());
					display.showText("\n");
				}
			}
			display.showText("\n&7");
			tempCoordY = display.getCursorPosY();
			this->showArtifact(artifactList[selectArts], 30, 3);

			if (opr == '7' || opr == '8' || opr == '9')
			{
				this->showLevelUp(tempArt, artifactList[selectArts], 20, 11);
			}

			display.setCursorPos(0, tempCoordY);

			if (selectArts > 0)
			{
				display.showButton('w', "����");
			}
			if (selectArts < (int)artifactList.size() - 1)
			{
				display.showButton('s', "����");
			}
			if (artifactList[selectArts].getLevel() < (unsigned int)artifactList[selectArts].getStar() * 4)
			{
				string tempS = "ǿ����";
				tempS += display.intToString((int)artifactList[selectArts].getLevel() + 1);
				tempS += "��";
				display.showButton('7', tempS);
			}
			if (artifactList[selectArts].getLevel() < (unsigned int)artifactList[selectArts].getStar() * 4 - 1
				&& artifactList[selectArts].getLevel() % 4 != 3)
			{
				string tempS = "ǿ����";
				tempS += display.intToString((int)artifactList[selectArts].getLevel() / 4 * 4 + 4);
				tempS += "��";
				display.showButton('8', tempS);
			}
			if (artifactList[selectArts].getLevel() < (unsigned int)artifactList[selectArts].getStar() * 4 - 4)
			{
				string tempS = "ǿ����";
				tempS += display.intToString((int)artifactList[selectArts].getStar() * 4);
				tempS += "��";
				display.showButton('9', tempS);
			}
			display.showButton('1', "����ˢȡ");
			display.showButton('0', "�˳�");

			if (debugSet == "����")
			{
				if (display.getCursorPosY() < 17)
				{
					display.setCursorPos(0, 17);
				}
				display.showText("\n");
				display.showCodeText("(int) tempCoordY = " + display.intToString(tempCoordY) + "\n");
				display.showCodeText("(RandEngine)randEngine.(unsigned long)getSeed() = "
					+ display.intToString((int)randEngine.getSeed()) + "\n");
				display.showCodeText("(RandEngine)randEngine.(unsigned int)getListPos() = "
					+ display.intToString((int)randEngine.getListPos()) + "\n");
				display.showCodeText("(int) selectHouse = " + display.intToString(selectHouse) + "\n");
				display.showCodeText("(int) selectArts = " + display.intToString(selectArts) + "\n");
				display.showCodeText("(int) useItem = " + display.intToString(useItem) + "\n");
				display.showCodeText("(vector<Artifact>)artifactList.size() = " +
					display.intToString((int)artifactList.size()) + "\n");
			}

			opr = display.selectButton();
			if (opr == 'w')
			{
				selectArts--;
			}
			else if (opr == 's')
			{
				selectArts++;
			}
			else if (opr == '7')
			{
				tempArt = artifactList[selectArts];
				artifactList[selectArts].levelUp();
			}
			else if (opr == '8')
			{
				int currentLevel = (int)artifactList[selectArts].getLevel();
				int flagLevel = (int)artifactList[selectArts].getLevel() / 4 * 4 + 4;
				tempArt = artifactList[selectArts];
				for (i = 0; (int)i < flagLevel - currentLevel; i++)
				{
					artifactList[selectArts].levelUp();
				}
			}
			else if (opr == '9')
			{
				int currentLevel = (int)artifactList[selectArts].getLevel();
				int flagLevel = (int)artifactList[selectArts].getStar() * 4;
				tempArt = artifactList[selectArts];
				for (i = 0; (int)i < flagLevel - currentLevel; i++)
				{
					artifactList[selectArts].levelUp();
				}
			}
		}
	}
}

void ArtifactUi::showCraftUi()
{
	Display display;
	Data data;
	Option option;
	RandEngine randEngine;
	string debugSet = option.currentSet[option.getOptionPos("������Ϣ")];
	vector<string> oprList = data.getArtifactCraftList();
	unsigned int i = 0;
	char opr = '\0';

	int selectCraft = 0; //ѡ��ĺϳ���װ
	int selectArts = 0; //ѡ���ˢ������Ʒ
	int totalTime = 0; //�ۼƺϳɵĴ���
	int useItem = 0; //���κϳɵĴ���

	while (opr != '0')
	{
		string text = "&7ԭ�񹤾� &8>&7 ���˵� &8> &7ʥ����(ģ����) &8> &7�ϳ�̨�ϳ�ģ��\n\n";

		display.clear();
		display.showText(text);
		display.showText("&7��ѡ������Ҫ�ϳɵ���װ��\n\n");

		for (i = 0; i < oprList.size(); i++)
		{
			display.showButton('a' + i, oprList[i]);
		}
		display.showButton('0', "�˳�");
		opr = display.selectButton();
		if (opr == '0')
		{
			return;
		}
		else
		{
			selectCraft = (int)opr - 'a';
			text += "&B";
			text += oprList[selectCraft];
			text += "\n";
		}

		display.clear();
		display.showText(text);
		display.showText("\n&7����������Ҫ�ϳɵ�����[1~13]��\n");
		display.showText("����0�˳���\n");
		useItem = display.getInputInt(13, false);
		if (useItem == 0)
		{
			return;
		}

		while (opr != '0' && opr != '1')
		{
			opr = '\0';
			totalTime += useItem;
			selectArts = 0;
			vector<Artifact> artifactList; //ˢ���Ķ���
			Artifact tempArt; //����ȷ��������ı��˵�����

			for (i = 0; i < (unsigned int)useItem; i++)
			{
				int randPos = randEngine.random(0, (int)data.getArtifactList(oprList[selectCraft]).size() - 1);
				tempArt = Artifact(data.getArtifactList(oprList[selectCraft])[randPos], randPos + 1, 5, 0.25);
				artifactList.push_back(tempArt);
			}

			while (opr != '0' && opr != '1' && opr != '2')
			{
				int tempCoordY = 0;

				display.clear();
				display.showText(text);
				display.showTextI("&B���ۼƺϳ� &A", totalTime, " &B�Ρ�\n");
				display.showText("\n");
				for (i = 0; i < artifactList.size(); i++)
				{
					if (i == selectArts)
					{
						display.showText("&8");
						display.showText(artifactList[i].getName());
						display.showText("\n");
					}
					else
					{
						string colorlist[] = { "&7","&8","&A","&3","&D","&6","&4" };
						display.showText(colorlist[artifactList[i].getStar()]);
						display.showText(artifactList[i].getName());
						display.showText("\n");
					}
				}
				display.showText("\n&7");
				tempCoordY = display.getCursorPosY();
				this->showArtifact(artifactList[selectArts], 30, 3);

				if (opr == '7' || opr == '8' || opr == '9')
				{
					this->showLevelUp(tempArt, artifactList[selectArts], 20, 11);
				}

				display.setCursorPos(0, tempCoordY);

				if (selectArts > 0)
				{
					display.showButton('w', "����");
				}
				if (selectArts < (int)artifactList.size() - 1)
				{
					display.showButton('s', "����");
				}
				if (artifactList[selectArts].getLevel() < (unsigned int)artifactList[selectArts].getStar() * 4)
				{
					string tempS = "ǿ����";
					tempS += display.intToString((int)artifactList[selectArts].getLevel() + 1);
					tempS += "��";
					display.showButton('7', tempS);
				}
				if (artifactList[selectArts].getLevel() < (unsigned int)artifactList[selectArts].getStar() * 4 - 1
					&& artifactList[selectArts].getLevel() % 4 != 3)
				{
					string tempS = "ǿ����";
					tempS += display.intToString((int)artifactList[selectArts].getLevel() / 4 * 4 + 4);
					tempS += "��";
					display.showButton('8', tempS);
				}
				if (artifactList[selectArts].getLevel() < (unsigned int)artifactList[selectArts].getStar() * 4 - 4)
				{
					string tempS = "ǿ����";
					tempS += display.intToString((int)artifactList[selectArts].getStar() * 4);
					tempS += "��";
					display.showButton('9', tempS);
				}
				display.showButton('1', "���ºϳ�");
				display.showButton('2', "�ٺϳ�" + display.intToString(useItem) + "��");
				display.showButton('0', "�˳�");

				if (debugSet == "����")
				{
					if (display.getCursorPosY() < 17)
					{
						display.setCursorPos(0, 17);
					}
					display.showText("\n");
					display.showCodeText("(int) tempCoordY = " + display.intToString(tempCoordY) + "\n");
					display.showCodeText("(RandEngine)randEngine.(unsigned long)getSeed() = "
						+ display.intToString((int)randEngine.getSeed()) + "\n");
					display.showCodeText("(RandEngine)randEngine.(unsigned int)getListPos() = "
						+ display.intToString((int)randEngine.getListPos()) + "\n");
					display.showCodeText("(int) selectCraft = " + display.intToString(selectCraft) + "\n");
					display.showCodeText("(int) selectArts = " + display.intToString(selectArts) + "\n");
					display.showCodeText("(int) useItem = " + display.intToString(useItem) + "\n");
					display.showCodeText("(vector<Artifact>)artifactList.size() = " +
						display.intToString((int)artifactList.size()) + "\n");
				}

				opr = display.selectButton();
				if (opr == 'w')
				{
					selectArts--;
				}
				else if (opr == 's')
				{
					selectArts++;
				}
				else if (opr == '7')
				{
					tempArt = artifactList[selectArts];
					artifactList[selectArts].levelUp();
				}
				else if (opr == '8')
				{
					int currentLevel = (int)artifactList[selectArts].getLevel();
					int flagLevel = (int)artifactList[selectArts].getLevel() / 4 * 4 + 4;
					tempArt = artifactList[selectArts];
					for (i = 0; (int)i < flagLevel - currentLevel; i++)
					{
						artifactList[selectArts].levelUp();
					}
				}
				else if (opr == '9')
				{
					int currentLevel = (int)artifactList[selectArts].getLevel();
					int flagLevel = (int)artifactList[selectArts].getStar() * 4;
					tempArt = artifactList[selectArts];
					for (i = 0; (int)i < flagLevel - currentLevel; i++)
					{
						artifactList[selectArts].levelUp();
					}
				}
			}
		}
	}
}
