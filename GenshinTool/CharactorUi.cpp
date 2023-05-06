#include "CharactorUi.h"

#include "Display.h"
#include "Option.h"

Charactor CharactorUi::inputCharaBaseAttr(string* text, bool hasATK, bool hasHP, bool hasDEF)
{
	Display display;
	int tempI = 0;
	double tempD = 0.0;
	unsigned int charaLevel = 0;
	double baseATK = 800.0;
	double baseHP = 15000.0;
	double baseDEF = 800.0;
	double extraATK = 0.0;
	double extraHP = 0.0;
	double extraDEF = 0.0;

	if (hasATK == true || hasHP == true || hasDEF == true)
	{
		display.clear();
		display.showText(*text);
		display.showText("&7请输入角色等级[1~90]。\n");
		display.showText("&7输入0退出计算。\n");
		tempI = display.getInputInt(90, false);
		if (tempI == 0)
		{
			Charactor temp(0);
			return temp;
		}
		charaLevel = (unsigned int)tempI;
		*text += "&B角色等级: &A";
		*text += display.intToString(tempI);
		*text += "\n";
	}
	else
	{
		display.clear();
		display.showText(*text);
		display.showText("\n&7请输入怪物等级[1~100]。\n");
		display.showText("&7输入0退出计算。\n");
		tempI = display.getInputInt(100, false);
		if (tempI == 0)
		{
			Charactor temp(0);
			return temp;
		}
		charaLevel = (unsigned int)tempI;
		*text += "&B怪物等级: &A";
		*text += display.intToString(tempI);
		*text += "\n";
		*text += "&B怪物防御力: &A";
		*text += display.intToString((int)(5.0 * charaLevel + 500.0));
		*text += "\n";
		Charactor emily(charaLevel, 1000.0, 100000.0, 5.0 * charaLevel + 500.0);
		return emily;
	}

	if (hasATK == true)
	{
		display.clear();
		display.showText(*text);
		display.showText("\n&7请输入角色的&6基础&7攻击力(面板&6白&7字)[1~1200]。\n");
		display.showText("&7输入0退出计算。\n");
		tempI = display.getInputInt(1200, false);
		if (tempI == 0)
		{
			Charactor temp(0);
			return temp;
		}
		baseATK = (double)tempI;
		*text += "&B角色的攻击力: &7";
		*text += display.intToString(tempI);

		display.clear();
		display.showText(*text);
		display.showText("\n\n&7请输入角色的&6额外&7攻击力(面板&6绿&7字)[0~20000]。\n");
		tempI = display.getInputInt(20000, false);
		display.showText("\n");
		extraATK = (double)tempI;
		*text += "&A + ";
		*text += display.intToString(tempI);
		*text += "&6 = ";
		*text += display.intToString(tempI + (int)baseATK);
		*text += "\n";
	}

	if (hasHP == true)
	{
		display.clear();
		display.showText(*text);
		display.showText("\n&7请输入角色的&6基础&7生命值(面板&6白&7字)[1~20000]。\n");
		display.showText("&7输入0退出计算。\n");
		tempI = display.getInputInt(20000, false);
		if (tempI == 0)
		{
			Charactor temp(0);
			return temp;
		}
		baseHP = (double)tempI;
		*text += "&B角色的生命值: &7";
		*text += display.intToString(tempI);

		display.clear();
		display.showText(*text);
		display.showText("\n\n&7请输入角色的&6额外&7生命值(面板&6绿&7字)[0~80000]。\n");
		tempI = display.getInputInt(80000, false);
		display.showText("\n");
		extraHP = (double)tempI;
		*text += "&A + ";
		*text += display.intToString(tempI);
		*text += "&6 = ";
		*text += display.intToString(tempI + (int)baseHP);
		*text += "\n";
	}

	if (hasDEF == true)
	{
		display.clear();
		display.showText(*text);
		display.showText("\n&7请输入角色的&6基础&7防御力(面板&6白&7字)[1~1200]。\n");
		display.showText("&7输入0退出计算。\n");
		tempI = display.getInputInt(1200, false);
		if (tempI == 0)
		{
			Charactor temp(0);
			return temp;
		}
		baseDEF = (double)tempI;
		*text += "&B角色的防御力: &7";
		*text += display.intToString(tempI);

		display.clear();
		display.showText(*text);
		display.showText("\n\n&7请输入角色的&6额外&7防御力(面板&6绿&7字)[0~20000]。\n");
		tempI = display.getInputInt(20000, false);
		display.showText("\n");
		extraDEF = (double)tempI;
		*text += "&A + ";
		*text += display.intToString(tempI);
		*text += "&6 = ";
		*text += display.intToString(tempI + (int)baseDEF);
		*text += "\n";
	}

	Charactor charactor(charaLevel, baseATK, baseHP, baseDEF);
	if (hasATK == true)
	{
		charactor.addBuff("固定攻击力加成", ATTRIBUTE_ATK, extraATK);
	}
	if (hasHP == true)
	{
		charactor.addBuff("固定生命值加成", ATTRIBUTE_HP, extraHP);
	}
	if (hasDEF == true)
	{
		charactor.addBuff("固定防御力加成", ATTRIBUTE_DEF, extraDEF);
	}
	return charactor;
}

void CharactorUi::inputCharaEM(string* text, Charactor* charactor, bool hasTranslate)
{
	Display display;
	int tempI = 0;

	display.clear();
	display.showText(*text);
	display.showText("\n&7请输入角色的元素精通[0~2000]。\n");
	tempI = display.getInputInt(2000, false);
	charactor->addBuff("元素精通", ATTRIBUTE_EM, tempI);
	*text += "&B角色的元素精通: &A";
	*text += display.intToString(tempI);
	*text += "\n";
	if (hasTranslate == true)
	{
		double tempD = 0.0;
		*text += "&3蒸发&7、&3融化&B反应造成伤害时，伤害提升 &6";
		tempD = charactor->translateEM(ELEMENT_DMGBONUS, (double)tempI) * 100;
		*text += display.doubleToString(tempD, 1);
		*text += "%\n&C超载&7、&8超导&7、&D感电&7、碎冰、&A扩散&B反应造成的伤害提升 &6";
		tempD = charactor->translateEM(ELEMENT_EXTRADMG, (double)tempI) * 100;
		*text += display.doubleToString(tempD, 1);
		*text += "%\n&6结晶&B反应形成的晶片护盾，提供的伤害吸收量提升 &6";
		tempD = charactor->translateEM(ELEMENT_SHEILD, (double)tempI) * 100;
		*text += display.doubleToString(tempD, 1);
		*text += "%\n";
	}
}

void CharactorUi::inputCharaCrit(string* text, Charactor* charactor)
{
	Display display;
	double tempD = 0.0;

	display.clear();
	display.showText(*text);
	display.showText("\n&7请输入角色面板上的暴击率。\n");
	display.showText("&7例如面板上是5%就直接输入5，不要输入成0.05。\n");
	tempD = display.getInputDouble(true, 4);
	charactor->addBuff("暴击率", ATTRIBUTE_CRITRATE, tempD / 100 - 0.05);
	*text += "&B角色的暴击率: &A";
	*text += display.doubleToString(tempD, 1);
	*text += "%\n";

	display.clear();
	display.showText(*text);
	display.showText("\n&7请输入角色面板上的暴击伤害。\n");
	display.showText("&7例如面板上是50%就直接输入50，不要输入成0.5。\n");
	tempD = display.getInputDouble(true, 4);
	charactor->addBuff("暴击伤害", ATTRIBUTE_CRITDMG, tempD / 100 - 0.5);
	*text += "&B角色的暴击伤害: &A";
	*text += display.doubleToString(tempD, 1);
	*text += "%\n";
}

void CharactorUi::inputElementDMGBonus(string* text, Charactor* charactor, int elementId)
{
	Display display;
	double tempD = 0.0;

	if (elementId == 0)
	{
		display.clear();
		display.showText(*text);
		display.showText("\n&7请输入角色面板上对应有效的元素伤害加成。\n");
		display.showText("&7例如面板上是46.6%就直接输入46.6，不要输入成0.466。\n");
		tempD = display.getInputDouble(true, 4);
		charactor->addBuff("元素伤害加成", ATTRIBUTE_DMGELEC, tempD / 100);
		*text += "&B角色的元素伤害加成: &A";
		*text += display.doubleToString(tempD, 1);
		*text += "%\n";
	}
	else
	{
		string elementName[] = {"火元素", "水元素" ,"草元素" ,"雷元素" ,"风元素" ,"冰元素" ,"岩元素" ,"物理"};
		display.clear();
		display.showText(*text);
		display.showText("\n&7请输入角色面板上的");
		display.showText(elementName[elementId - 1]);
		display.showText("伤害加成。\n");
		display.showText("&7例如面板上是46.6%就直接输入46.6，不要输入成0.466。\n");
		tempD = display.getInputDouble(true, 4);
		charactor->addBuff(elementName[elementId - 1] + "伤害加成", ATTRIBUTE_DMGPYRO - 1 + elementId, tempD / 100);
		*text += "&B角色的";
		*text += elementName[elementId - 1];
		*text += "伤害加成: &A";
		*text += display.doubleToString(tempD, 1);
		*text += "%\n";
	}
}

double CharactorUi::inputSkillRate(string* text)
{
	Display display;
	double skillRate = 0.0;

	display.clear();
	display.showText(*text);
	display.showText("\n&7请输入角色的技能倍率。\n");
	display.showText("&7例如面板上是100%就直接输入100，不要输入成1。\n");
	display.showText("&7输入0退出计算。\n");
	skillRate = display.getInputDouble(false, 5);
	if (skillRate == 0.0)
	{
		return 0.0;
	}
	*text += "&B技能倍率: &A";
	*text += display.doubleToString(skillRate, 1);
	*text += "%\n";
	skillRate /= 100;
	return skillRate;
}

bool CharactorUi::inputWeaponPurify(string* text, double* weaponPurify)
{
	Display display;
	char opr = '\0';

	display.clear();
	display.showText(*text);
	display.showText("\n\n&7请选择武器的精炼等级:\n");
	display.showButton('1', "精炼1阶");
	display.showButton('2', "精炼2阶");
	display.showButton('3', "精炼3阶");
	display.showButton('4', "精炼4阶");
	display.showButton('5', "精炼5阶");
	display.showButton('0', "退出计算");
	opr = display.selectButton();
	if (opr == '0')
	{
		return false;
	}
	else if (opr == '1')
	{
		*weaponPurify = 1.0;
		*text += "精炼1阶\n";
	}
	else if (opr == '2')
	{
		*weaponPurify = 1.25;
		*text += "精炼2阶\n";
	}
	else if (opr == '3')
	{
		*weaponPurify = 1.5;
		*text += "精炼3阶\n";
	}
	else if (opr == '4')
	{
		*weaponPurify = 1.75;
		*text += "精炼4阶\n";
	}
	else if (opr == '5')
	{
		*weaponPurify = 2.0;
		*text += "精炼5阶\n";
	}
	return true;
}

void CharactorUi::inputExtraATK(string* text, Charactor* charactor, double baseATK)
{
	Display display;
	int tempI = display.getInputInt(5000, false);
	*text += "&B攻击力: &A";
	*text += display.intToString(tempI + (int)baseATK);
	*text += "&B\n";
	string tempS = "固定攻击力加成";
	charactor->addBuff(tempS, ATTRIBUTE_ATK, (double)tempI);
}

void CharactorUi::inputExtraHP(string* text, Charactor* charactor, double baseHP)
{
	Display display;
	int tempI = display.getInputInt(50000, false);
	*text += "&B生命值: &A";
	*text += display.intToString(tempI + (int)baseHP);
	*text += "&B\n";
	string tempS = "固定生命值加成";
	charactor->addBuff(tempS, ATTRIBUTE_HP, (double)tempI);
}

bool CharactorUi::selectWeapon(string* text, int* weaponId, vector<string> weaponList)
{
	Display display;
	unsigned int i = 0;
	char opr = '\0';

	for (i = 0; i < weaponList.size(); i++)
	{
		display.showButton('1' + i, weaponList[i]);
	}
	display.showButton('0', "退出计算");
	opr = display.selectButton();
	if (opr == '0')
	{
		return false;
	}
	else
	{
		*weaponId = opr - '0';
		*text += "&B";
		*text += weaponList[*weaponId - 1];
		return true;
	}
}

void CharactorUi::showUsefulAttr(double hasUsefulAttr, int maxUsefulAttr)
{
	Display display;
	display.showText("&B当前角色拥有 &A");
	display.showText(display.doubleToString(hasUsefulAttr, 1));
	display.showTextI(" &E/ ", maxUsefulAttr, " &B个有效圣遗物词条。");
	if (hasUsefulAttr < 1 || hasUsefulAttr > maxUsefulAttr - 1)
	{
		display.showText("\n");
	}
	else
	{
		display.showText("圣遗物毕业进度:\n");
		display.showLoading(50, '-', '=', hasUsefulAttr / maxUsefulAttr, 0, display.getCursorPosY(), 14);
		display.showText("    &E");

		vector<double> tempDList = { 0.1, 0.25, 0.4, 0.5, 0.55, 0.6, 0.75, 0.9 };
		vector<string> tempSList = { "糟透了", "极差", "很差", "较差", "一般", "良好", "优秀", "完美", "传家宝" };
		display.showStringIfBetween(hasUsefulAttr / maxUsefulAttr, tempDList, tempSList);
		display.showText("\n&B");
	}
}

void CharactorUi::showErrorInfo(double hasUsefulAttr, int maxUsefulAttr)
{
	Display display;
	if (hasUsefulAttr < 1)
	{
		display.showText("\n&c你的面板数值过低，无法显示完整的分析结果。\n");
		display.showText("&c可能是你面板数据输入错误，或圣遗物主词条错误或没有升到满级。\n");
		display.showText("&c正常来讲，只要有一套主词条正确的五星圣遗物，即使不计算副词条\n");
		display.showText("&c计算出来的面板数值都会比你当前输入的面板数值高。\n");
	}
	else if (hasUsefulAttr > maxUsefulAttr - 1)
	{
		display.showText("\n&c你的面板数值过高，无法显示完整的分析结果。\n");
		display.showText("&c可能是你面板数据输入错误，或包含了一些增益效果。\n");
		display.showText("&c正常来讲，即使你的圣遗物每次强化到有用的属性且是最大值\n");
		display.showText("&c计算出来的面板数值也达不到你当前输入的面板数值。\n");
		display.showText("&c如果你只是想计算在一些增益效果下的伤害，建议使用伤害计算器功能。\n");
	}
}

void CharactorUi::listAttr(Charactor charactor, Charactor emily, double skillRate, 
	bool hasEM, bool hasTranEM, int elementId)
{
	Display display;
	double tempD = 0.0;

	display.showText("&B角色属性:           &ALv.");
	display.showTextI((int)charactor.getLevel(), 10);
	display.showText("\n");
	display.showText("&B攻击力:             ");
	display.showTextI((int)charactor.getBaseATK(), 7);
	display.showText(" &A+ ");
	display.showTextI((int)(charactor.getAttrValue(ATTRIBUTE_ATK) - charactor.getBaseATK()), 10);
	display.showText(" &6= ");
	display.showTextI((int)charactor.getAttrValue(ATTRIBUTE_ATK), 6);
	display.showText("\n");
	if (hasEM == true)
	{
		display.showText("&B元素精通:           ");
		display.showTextI((int)charactor.getAttrValue(ATTRIBUTE_EM), 10);
		display.showText("\n");
	}
	if (hasTranEM == true)
	{
		display.showText("&3蒸发&7、&3融化&B反应造成伤害时，伤害提升 &6");
		tempD = charactor.translateEM(ELEMENT_DMGBONUS, charactor.getAttrValue(ATTRIBUTE_EM)) * 100;
		display.showText(display.doubleToString(tempD, 1));
		display.showText("%\n&C超载&7、&8超导&7、&D感电&7、碎冰、&A扩散&B反应造成的伤害提升 &6");
		tempD = charactor.translateEM(ELEMENT_EXTRADMG, charactor.getAttrValue(ATTRIBUTE_EM)) * 100;
		display.showText(display.doubleToString(tempD, 1));
		display.showText("%\n&6结晶&B反应形成的晶片护盾，提供的伤害吸收量提升 &6");
		tempD = charactor.translateEM(ELEMENT_SHEILD, charactor.getAttrValue(ATTRIBUTE_EM)) * 100;
		display.showText(display.doubleToString(tempD, 1));
		display.showText("%\n");
	}
	display.showText("&B暴击率:             &A");
	tempD = charactor.getAttrValue(ATTRIBUTE_CRITRATE) * 100;
	display.showText(display.doubleToString(tempD, 1));
	display.showText("%\n");
	display.showText("&B暴击伤害:           &A");
	tempD = charactor.getAttrValue(ATTRIBUTE_CRITDMG) * 100;
	display.showText(display.doubleToString(tempD, 1));
	display.showText("%\n");
	if (elementId == 0)
	{
		display.showText("&B元素伤害加成:       &A");
		tempD = charactor.getAttrValue(ATTRIBUTE_DMGELEC) * 100;
		display.showText(display.doubleToString(tempD, 1));
		display.showText("%\n");
	}
	else
	{
		string elementName[] = { "火元素", "水元素" ,"草元素" ,"雷元素" ,"风元素" ,"冰元素" ,"岩元素" ,"物理" };
		display.showText(elementName[elementId - 1] + "伤害加成:     &A");
		tempD = charactor.getAttrValue(ATTRIBUTE_DMGPYRO - 1 + elementId) * 100;
		display.showText(display.doubleToString(tempD, 1));
		display.showText("%\n");
	}
	display.showText("&B技能倍率:           &A");
	display.showText(display.doubleToString(skillRate * 100, 1));
	display.showText("%\n");
	display.showText("\n");

	display.showText("&B怪物属性:           &ALv.");
	display.showTextI((int)emily.getLevel(), 10);
	display.showText("\n");
	display.showText("&B元素抗性:           &A");
	tempD = emily.getAttrValue(ATTRIBUTE_RESELEC) * 100;
	display.showText(display.doubleToString(tempD, 1));
	display.showText("%\n");
	display.showText("&B防御力:             &A");
	display.showTextI((int)emily.getAttrValue(ATTRIBUTE_DEF), 10);
	display.showText("\n&7");
}

void CharactorUi::listExpectDMG(Charactor charactor, Charactor emily, double skillRate, int elementId)
{
	Display display;
	int element = elementId;
	double expectDMG = charactor.caculateDMG(skillRate, true, elementId, emily, 2.0);
	double tempD = 0.0;
	
	if (element == 0)
	{
		element = ELEMENTAL_ELECTRO;
	}

	expectDMG = charactor.caculateDMG(skillRate, false, element, emily);
	display.showText("&B造成的伤害若没有暴击，没有参加元素反应，预计为 &A");
	display.showText(display.doubleToString(expectDMG, 1));
	expectDMG = charactor.caculateDMG(skillRate, true, element, emily);
	display.showText("\n&B造成的伤害暴击，但没有参加元素反应，预计为 &A");
	display.showText(display.doubleToString(expectDMG, 1));
	expectDMG = charactor.caculateDMG(skillRate, false, element, emily, 1.5);
	display.showText("\n&B造成的伤害没有暴击，但参加了1.5倍率增幅反应，预计为 &A");
	display.showText(display.doubleToString(expectDMG, 1));
	expectDMG = charactor.caculateDMG(skillRate, true, element, emily, 1.5);
	display.showText("\n&B造成的伤害暴击，且参加了1.5倍率增幅反应，预计为 &A");
	display.showText(display.doubleToString(expectDMG, 1));
	expectDMG = charactor.caculateDMG(skillRate, true, element, emily, 2.0);
	display.showText("\n&B造成的伤害暴击，且参加了2.0倍率增幅反应，预计为 &A");
	display.showText(display.doubleToString(expectDMG, 1));

	display.showText("\n");
	expectDMG = charactor.caculateEMDMG(ELEMENT_SUPERCON, emily, element);
	display.showText("\n&B触发&8超导&B反应造成的超导伤害预计为 &A");
	display.showText(display.doubleToString(expectDMG, 1));
	expectDMG = charactor.caculateEMDMG(ELEMENT_SWIRL, emily, element);
	display.showText("\n&B触发&A扩散&B反应造成的扩散伤害预计为 &A");
	display.showText(display.doubleToString(expectDMG, 1));
	expectDMG = charactor.caculateEMDMG(ELEMENT_ELECHAR, emily, element);
	display.showText("\n&B触发&D感电&B反应造成的感电伤害预计为 &A");
	display.showText(display.doubleToString(expectDMG, 1));
	expectDMG = charactor.caculateEMDMG(ELEMENT_OVERLOAD, emily, element);
	display.showText("\n&B触发&C超载&B反应造成的超载伤害预计为 &A");
	display.showText(display.doubleToString(expectDMG, 1));
	expectDMG = charactor.caculateEMDMG(ELEMENT_SHUTTER, emily, element);
	display.showText("\n&B触发&7碎冰&B反应造成的碎冰伤害预计为 &A");
	display.showText(display.doubleToString(expectDMG, 1));

	display.showText("\n\n");
	display.showText("&62倍增幅反应暴击伤害\n");
	display.showText("&6= &7基础攻击力 * &A攻击力乘区 &7* &E技能倍率乘区 &7* &8暴击伤害乘区 ");
	display.showText("&7* &3增伤乘区 &7* &4元素反应乘区 &7* &D2 &7* 抗性乘区 * &2防御乘区 \n");
	display.showTextI("&6= &7", (int)charactor.getBaseATK(), " * &A");
	tempD = charactor.getDMGBonusRate(DMGPLUSAREA_ATK, element) * 100;
	display.showText(display.doubleToString(tempD, 1));
	display.showText("% &7* &E");
	tempD = charactor.getDMGBonusRate(DMGPLUSAREA_SKILLRATE, element, skillRate) * 100;
	display.showText(display.doubleToString(tempD, 1));
	display.showText("% &7* &8");
	tempD = charactor.getDMGBonusRate(DMGPLUSAREA_CRITDMG, element) * 100;
	display.showText(display.doubleToString(tempD, 1));
	display.showText("% &7* &3");
	tempD = charactor.getDMGBonusRate(DMGPLUSAREA_DMGBONUS, element) * 100;
	display.showText(display.doubleToString(tempD, 1));
	display.showText("% &7* &4");
	tempD = charactor.getDMGBonusRate(DMGPLUSAREA_ELEMENT, element) * 100;
	display.showText(display.doubleToString(tempD, 1));
	display.showText("% &7* &D2 &7* ");
	tempD = charactor.getDMGBonusRate(DMGPLUSAREA_RES, element, emily) * 100;
	display.showText(display.doubleToString(tempD, 1));
	display.showText("% &7* &2");
	tempD = charactor.getDMGBonusRate(DMGPLUSAREA_DEF, element, emily) * 100;
	display.showText(display.doubleToString(tempD, 1));
	display.showText("%\n&6= ");
	expectDMG = charactor.caculateDMG(skillRate, true, element, emily, 2.0);
	display.showText(display.doubleToString(expectDMG, 1));
	display.showText("\n\n&7");
	display.showText("&6超导反应造成的伤害\n");
	display.showText("&6= &E反应基础伤害 &7* &3精通和系数加成 &7* &2怪物抗性 \n");
	display.showText("&6= &E" + display.doubleToString(charactor.getEMBaseDMG(), 1) + " &7* &3");
	tempD = charactor.caculateEMDMG(ELEMENT_EXTRADMG, emily, element) / charactor.getEMBaseDMG() * 100;
	display.showText(display.doubleToString(tempD, 1) + "% &7* &2");
	tempD = charactor.getDMGBonusRate(DMGPLUSAREA_RES, element, emily) * 100;
	display.showText(display.doubleToString(tempD, 1) + "%\n&6= ");
	expectDMG = charactor.caculateEMDMG(ELEMENT_SUPERCON, emily, element);
	display.showText(display.doubleToString(expectDMG, 1));
	display.showText("\n\n&7");
}

void CharactorUi::showUi()
{
	Display display;
	char opr = '\0';

	while (opr != '0')
	{
		display.clear();
		display.showText("&7原神工具 &8>&7 主菜单 &8>&7 练度计算器\n\n");

		display.showText("&B功能说明:\n");
		display.showText("&B本功能可以根据角色面板计算出角色的伤害期望。\n");
		display.showText("&B并据此给出养成建议。&7\n\n");

		display.showButton('1', "传统[攻伤暴]型主C模板");
		display.showButton('9', "伤害计算器");
		display.showButton('a', "甘雨");
		display.showButton('b', "胡桃");
		display.showButton('0', "返回");
		opr = display.selectButton();

		if (opr == '1')
		{
			this->showCPlaceTemplateUi();
		}
		else if (opr == '9')
		{
			this->showDMGCaculatorUi();
		}
		else if (opr == 'a')
		{
			this->showGanYuUi();
		}
		else if (opr == 'b')
		{
			this->showHuTaoUi();
		}
	}
}

void CharactorUi::showAddBuffUi(Charactor* charactor, Charactor* emily, int elementId)
{
	Display display;
	Artifact artifact;
	Option option;
	string debugSet = option.currentSet[option.getOptionPos("调试信息")];
	char opr = '\0';
	unsigned int i = 0;
	int tempI = 0;
	double tempD = 0.0;

	while (opr != '0')
	{
		display.clear();
		display.showText("&7原神工具 &8>&7 主菜单 &8>&7 练度计算器 &8>&7 添加效果\n\n");
		if (charactor->getBuffLength() + emily->getBuffLength() > 5)
		{
			display.showText("&B当前已拥有的效果:\n&7");
		}
		else
		{
			display.showText("&C当前没有任何效果\n&7");
		}
		for (i = 5; i < charactor->getBuffLength(); i++)
		{
			display.showText("&6角色:&7");
			display.showText(charactor->getBuffName(i));
			display.showText("    &A");
			if (charactor->getBuffId(i) >= 15 && charactor->getBuffId(i) <= 30 && elementId == 0)
			{
				if (charactor->getBuffId(i) >= 15 && charactor->getBuffId(i) <= 22)
				{
					display.showText("元素伤害加成");
				}
				else
				{
					display.showText("元素抗性");
				}
			}
			else
			{
				display.showText(artifact.attrIdToString(charactor->getBuffId(i)));
			}
			display.showText(" ");
			if (charactor->getBuffValue(i) >= 0)
			{
				display.showText("+");
			}
			if (artifact.getAttrIsPercent(charactor->getBuffId(i)) == true)
			{
				tempD = charactor->getBuffValue(i) * 100;
				display.showText(display.doubleToString(tempD, 1));
				display.showText("%\n&7");
			}
			else
			{
				display.showText(display.intToString((int)charactor->getBuffValue(i)));
				display.showText("\n&7");
			}
		}

		for (i = 0; i < emily->getBuffLength(); i++)
		{
			display.showText("&6怪物:&7");
			display.showText(emily->getBuffName(i));
			display.showText("    &A");
			if (emily->getBuffId(i) >= 15 && emily->getBuffId(i) <= 30 && elementId == 0)
			{
				if (emily->getBuffId(i) >= 15 && emily->getBuffId(i) <= 22)
				{
					display.showText("元素伤害加成");
				}
				else
				{
					display.showText("元素抗性");
				}
			}
			else
			{
				display.showText(artifact.attrIdToString(emily->getBuffId(i)));
			}
			display.showText(" ");
			if (emily->getBuffValue(i) >= 0)
			{
				display.showText("+");
			}
			if (artifact.getAttrIsPercent(emily->getBuffId(i)) == true)
			{
				tempD = emily->getBuffValue(i) * 100;
				display.showText(display.doubleToString(tempD, 1));
				display.showText("%\n&7");
			}
			else
			{
				display.showText(display.intToString((int)emily->getBuffValue(i)));
				display.showText("\n&7");
			}
		}

		string oprList[] = { "提高造成的伤害固定值(技能倍率乘区)" ,"攻击力提高固定值(攻击力乘区)",
		"攻击力提高百分比(攻击力乘区)","暴击伤害提高百分比(暴击伤害乘区)","造成的伤害提高百分比(增伤乘区)",
		"获得元素伤害加成百分比(增伤乘区)","元素精通提高固定值(元素反应乘区)","元素反应系数提高百分比(元素反应乘区)",
		"怪物的抗性提高百分比(抗性乘区)","怪物防御力提高百分比(防御力乘区)" };

		display.showText("\n");

		if (debugSet == "开启")
		{
			display.showCodeText("(Charactor)charactor->(unsigned int)getBuffLength() = "
				+ display.intToString((int)charactor->getBuffLength()) + "\n");
			display.showCodeText("(Charactor)emily->(unsigned int)getBuffLength() = "
				+ display.intToString((int)emily->getBuffLength()) + "\n");
			display.showCodeText("(int) elementId = " + display.intToString(elementId) + "\n");
			display.showText("\n");
		}

		if (charactor->getBuffLength() + emily->getBuffLength() < 31)
		{
			display.showButton('a', oprList[0]);
			display.showButton('b', oprList[1]);
			display.showButton('c', oprList[2]);
			display.showButton('d', oprList[3]);
			display.showButton('e', oprList[4]);
			display.showButton('f', oprList[5]);
			display.showButton('g', oprList[6]);
			display.showButton('h', oprList[7]);
			display.showButton('i', oprList[8]);
			display.showButton('j', oprList[9]);
		}
		else
		{
			display.showText("&C添加的效果数量已经达到上限。\n\n&7");
		}
		display.showButton('0', "完成");
		opr = display.selectButton();
		if (opr == '0')
		{
			return;
		}

		display.clearButton('a', false);
		display.clearAllButton();
		display.showText(oprList[opr - 'a']);
		display.showText("\n请给效果取一个名称:\n");
		string buffName = display.getInputString(32);
		if (opr == 'a')
		{
			display.showText("\n请输入提高造成伤害的具体数值:\n");
			display.showText("输入0放弃添加。\n");
			tempD = display.getInputDouble(false, 5);
			if (tempD == 0.0)
			{
				continue;
			}
			charactor->addBuff(buffName, ATTRIBUTE_BUFF_EXTRADMG, tempD);
		}
		else if (opr == 'b')
		{
			display.showText("\n请输入攻击力提高的具体数值[-20000~20000]:\n");
			display.showText("输入负数代表攻击力降低\n");
			display.showText("输入0放弃添加。\n");
			tempI = display.getInputInt(20000);
			if (tempI == 0)
			{
				continue;
			}
			charactor->addBuff(buffName, ATTRIBUTE_ATK, tempI);
		}
		else if (opr == 'c')
		{
			display.showText("\n请输入攻击力提高的百分比:\n");
			display.showText("例如46.6%直接输入46.6，不要输入成0.466\n");
			display.showText("输入负数代表攻击力降低\n");
			display.showText("输入0放弃添加。\n");
			tempD = display.getInputDouble(true, 4);
			if (tempD == 0.0)
			{
				continue;
			}
			charactor->addBuff(buffName, ATTRIBUTE_ATKPER, tempD / 100);
		}
		else if (opr == 'd')
		{
			display.showText("\n请输入暴击伤害提高的百分比:\n");
			display.showText("例如66.2%直接输入66.2，不要输入成0.662\n");
			display.showText("输入负数代表暴击伤害降低\n");
			display.showText("输入0放弃添加。\n");
			tempD = display.getInputDouble(true, 4);
			if (tempD == 0.0)
			{
				continue;
			}
			charactor->addBuff(buffName, ATTRIBUTE_CRITDMG, tempD / 100);
		}
		else if (opr == 'e')
		{
			display.showText("\n请输入造成的伤害提高的百分比:\n");
			display.showText("例如46.6%直接输入46.6，不要输入成0.466\n");
			display.showText("输入负数代表造成的伤害降低\n");
			display.showText("输入0放弃添加。\n");
			tempD = display.getInputDouble(true, 4);
			if (tempD == 0.0)
			{
				continue;
			}
			charactor->addBuff(buffName, ATTRIBUTE_BUFF_DMGBONUS, tempD / 100);
		}
		else if (opr == 'f')
		{
			display.showText("\n请输入元素伤害加成的百分比:\n");
			display.showText("例如46.6%直接输入46.6，不要输入成0.466\n");
			display.showText("输入负数代表元素伤害加成降低\n");
			display.showText("输入0放弃添加。\n");
			tempD = display.getInputDouble(true, 4);
			if (tempD == 0.0)
			{
				continue;
			}
			
			if (elementId == 0)
			{
				charactor->addBuff(buffName, ATTRIBUTE_DMGELEC, tempD / 100);
			}
			else
			{
				charactor->addBuff(buffName, ATTRIBUTE_DMGPYRO - 1 + elementId, tempD / 100);
			}
		}
		else if (opr == 'g')
		{
			display.showText("\n请输入元素精通提高的具体数值[-2000~2000]:\n");
			display.showText("输入负数代表元素精通降低\n");
			display.showText("输入0放弃添加。\n");
			tempI = display.getInputInt(2000);
			if (tempI == 0)
			{
				continue;
			}
			charactor->addBuff(buffName, ATTRIBUTE_EM, tempI);
		}
		else if (opr == 'h')
		{
			display.showText("\n请输入元素反应系数提高的百分比:\n");
			display.showText("例如46.6%直接输入46.6，不要输入成0.466\n");
			display.showText("输入负数代表元素反应系数降低\n");
			display.showText("输入0放弃添加。\n");
			tempD = display.getInputDouble(true, 4);
			if (tempD == 0.0)
			{
				continue;
			}
			charactor->addBuff(buffName, ATTRIBUTE_BUFF_EXTRAEM, tempD / 100);
		}
		else if (opr == 'i')
		{
			display.showText("\n请输入怪物抗性提高的百分比:\n");
			display.showText("例如-40%直接输入-40，不要输入成-0.4\n");
			display.showText("输入负数代表怪物抗性降低\n");
			display.showText("输入0放弃添加。\n");
			tempD = display.getInputDouble(true, 4);
			if (tempD == 0.0)
			{
				continue;
			}

			if (elementId == 0)
			{
				emily->addBuff(buffName, ATTRIBUTE_RESELEC, tempD / 100);
			}
			else
			{
				emily->addBuff(buffName, ATTRIBUTE_RESPYRO - 1 + elementId, tempD / 100);
			}
		}
		else if (opr == 'j')
		{
			display.showText("\n请输入怪物防御力提高的百分比:\n");
			display.showText("例如-60%直接输入-60，不要输入成-0.6\n");
			display.showText("输入负数代表怪物防御力降低\n");
			display.showText("输入0放弃添加。\n");
			tempD = display.getInputDouble(true, 3);
			if (tempD == 0.0)
			{
				continue;
			}
			emily->addBuff(buffName, ATTRIBUTE_DEFPER, tempD / 100);
		}
	}
}

void CharactorUi::showDeleteBuffUi(Charactor* charactor, Charactor* emily, bool showElement)
{
	Display display;
	Option option;
	string debugSet = option.currentSet[option.getOptionPos("调试信息")];
	char opr = '\0';
	string tempS = "";
	char localChar = 'a';
	unsigned int i = 0;
	Artifact artifact;
	double tempD = 0.0;

	while (opr != '0')
	{
		display.clear();
		display.showText("&7原神工具 &8>&7 主菜单 &8>&7 练度计算器 &8>&7 添加效果\n\n");
		if (charactor->getBuffLength() + emily->getBuffLength() > 5)
		{
			display.showText("&B请选择你想要删除的效果:\n\n&7");
		}
		else
		{
			display.showText("&C当前没有任何效果。\n\n&7");
		}

		if (debugSet == "开启")
		{
			display.showCodeText("(Charactor)charactor->(unsigned int)getBuffLength() = "
				+ display.intToString((int)charactor->getBuffLength()) + "\n");
			display.showCodeText("(Charactor)emily->(unsigned int)getBuffLength() = "
				+ display.intToString((int)emily->getBuffLength()) + "\n");
			display.showCodeText("(bool) showElement = " + display.boolToString(showElement) + "\n");
			display.showText("\n");
		}

		for (i = 5; i < charactor->getBuffLength(); i++)
		{
			tempS = "&6角色:&7";
			tempS += charactor->getBuffName(i);
			tempS += "    &A";
			if (charactor->getBuffId(i) >= 15 && charactor->getBuffId(i) <= 30 && showElement == false)
			{
				if (charactor->getBuffId(i) >= 15 && charactor->getBuffId(i) <= 22)
				{
					tempS += "元素伤害加成";
				}
				else
				{
					tempS += "元素抗性";
				}
			}
			else
			{
				tempS += artifact.attrIdToString(charactor->getBuffId(i));
			}
			tempS += " ";
			if (charactor->getBuffValue(i) >= 0)
			{
				tempS += "+";
			}
			if (artifact.getAttrIsPercent(charactor->getBuffId(i)) == true)
			{
				tempD = charactor->getBuffValue(i) * 100;
				tempS += display.doubleToString(tempD, 1);
				tempS += "%&7";
			}
			else
			{
				tempS += display.intToString((int)charactor->getBuffValue(i));
				tempS += "&7";
			}

			display.showButton(localChar, tempS);
			localChar++;
		}

		for (i = 0; i < emily->getBuffLength(); i++)
		{
			tempS = "&6怪物:&7";
			tempS += emily->getBuffName(i);
			tempS += "    &A";
			if (emily->getBuffId(i) >= 15 && emily->getBuffId(i) <= 30 && showElement == false)
			{
				if (emily->getBuffId(i) >= 15 && emily->getBuffId(i) <= 22)
				{
					tempS += "元素伤害加成";
				}
				else
				{
					tempS += "元素抗性";
				}
			}
			else
			{
				tempS += artifact.attrIdToString(emily->getBuffId(i));
			}
			tempS += " ";
			if (emily->getBuffValue(i) >= 0)
			{
				tempS += "+";
			}
			if (artifact.getAttrIsPercent(emily->getBuffId(i)) == true)
			{
				tempD = emily->getBuffValue(i) * 100;
				tempS += display.doubleToString(tempD, 1);
				tempS += "%&7";
			}
			else
			{
				tempS += display.intToString((int)emily->getBuffValue(i));
				tempS += "&7";
			}

			display.showButton(localChar, tempS);
			localChar++;
		}

		display.showButton('0', "完成");
		opr = display.selectButton();
		if (opr == '0')
		{
			return;
		}

		localChar = 'a';
		for (i = 5; i < charactor->getBuffLength(); i++)
		{
			if (opr == localChar)
			{
				charactor->deleteBuff(i);
			}
			localChar++;
		}
		for (i = 0; i < emily->getBuffLength(); i++)
		{
			if (opr == localChar)
			{
				emily->deleteBuff(i);
			}
			localChar++;
		}

		localChar = 'a';
	}
}

void CharactorUi::showDMGCaculatorUi()
{
	Display display;
	char opr = '\0';
	string text = "&7原神工具 &8>&7 主菜单 &8>&7 练度计算器 &8>&7 伤害计算器\n\n";
	Charactor charactor = this->inputCharaBaseAttr(&text, true, false, false);
	if (charactor.getLevel() == 0)
	{
		return;
	}
	this->inputCharaEM(&text, &charactor, true);
	this->inputCharaCrit(&text, &charactor);
	this->inputElementDMGBonus(&text, &charactor);
	double skillRate = this->inputSkillRate(&text);
	if (skillRate == 0.0)
	{
		return;
	}
	Charactor emily = this->inputCharaBaseAttr(&text, false, false, false);
	if (emily.getLevel() == 0)
	{
		return;
	}
	emily.addBuff("怪物默认的抗性", ATTRIBUTE_RESELEC, 0.1);

	while (opr != '0')
	{
		display.clear();
		display.showText("&7原神工具 &8>&7 主菜单 &8>&7 练度计算器 &8>&7 伤害计算器 &8>&7 计算结果\n\n");
		this->listAttr(charactor, emily, skillRate, true, true);
		display.showText("\n");
		this->listExpectDMG(charactor, emily, skillRate, 0);

		if (charactor.getBuffLength() + emily.getBuffLength() < 31)
		{
			display.showButton('1', "添加效果");
		}
		if (charactor.getBuffLength() + emily.getBuffLength() > 5)
		{
			display.showButton('2', "删除效果");
		}
		display.showButton('0', "退出计算");
		opr = display.selectButton();
		if (opr == '1')
		{
			this->showAddBuffUi(&charactor, &emily, 0);
		}
		else if (opr == '2')
		{
			this->showDeleteBuffUi(&charactor, &emily, false);
		}
	}
}

void CharactorUi::showCPlaceTemplateUi()
{
	Display display;
	char opr = '\0';
	string text = "&7原神工具 &8>&7 主菜单 &8>&7 练度计算器 &8>&7 [攻伤暴]\n\n";
	Charactor charactor = this->inputCharaBaseAttr(&text, true, false, false);
	vector<double> tempDList;
	
	if (charactor.getLevel() == 0)
	{
		return;
	}
	this->inputCharaCrit(&text, &charactor);
	this->inputElementDMGBonus(&text, &charactor);

	int weaponAttr = 0;
	double weaponAttrValue = 0.0;
	double skillRate = this->inputSkillRate(&text);
	if (skillRate == 0.0)
	{
		return;
	}

	display.clear();
	display.showText(text);
	display.showText("\n&7请选择角色携带武器的副属性。\n");
	display.showButton('1', "攻击力");
	display.showButton('2', "暴击率");
	display.showButton('3', "暴击伤害");
	display.showButton('4', "其它");
	display.showButton('0', "退出计算");
	opr = display.selectButton();
	if (opr == '0')
	{
		return;
	}
	else if (opr == '1')
	{
		weaponAttr = ATTRIBUTE_ATKPER;
		text += "&B武器副属性: &A攻击力";
	}
	else if (opr == '2')
	{
		weaponAttr = ATTRIBUTE_CRITRATE;
		text += "&B武器副属性: &A暴击率";
	}
	else if (opr == '3')
	{
		weaponAttr = ATTRIBUTE_CRITDMG;
		text += "&B武器副属性: &A暴击伤害";
	}
	else if (opr == '4')
	{
		weaponAttr = 0;
		weaponAttrValue = 0.0;
	}

	if (opr != '4')
	{
		display.clear();
		display.showText(text);
		display.showText("\n\n&7请输入角色携带武器的&6副属性&7加成的数值。\n");
		display.showText("&7例如面板上是41.3%就直接输入41.3，不要输入成0.413。\n");
		weaponAttrValue = display.getInputDouble(false, 3);
		text += " + ";
		text += display.doubleToString(weaponAttrValue, 1);
		text += "%\n";
		weaponAttrValue /= 100;
	}

	while (opr != '0')
	{
		vector<int> usefulAttr = { ATTRIBUTE_ATKPER, ATTRIBUTE_CRITRATE, ATTRIBUTE_CRITDMG };
		Charactor enimy(charactor.getLevel(), 100.0, 1000.0, 5.0 * charactor.getLevel() + 500.0);
		enimy.addBuff("怪物默认的抗性", ATTRIBUTE_RESELEC, 0.1);
		double expectDMG = charactor.caculateDMG(skillRate, true, ELEMENTAL_ELECTRO, enimy);
		if (weaponAttr != 0)
		{
			charactor.addBuff("暂时去除主词条", weaponAttr, -weaponAttrValue);
		}
		charactor.addBuff("暂时去除主词条", ATTRIBUTE_ATKPER, -0.466);
		charactor.addBuff("暂时去除主词条", ATTRIBUTE_CRITRATE, -0.331);
		charactor.addBuff("暂时去除主词条", ATTRIBUTE_ATK, -311.0);
		double hasUsefulAttr = charactor.getUsefulAttrCount(usefulAttr);
		charactor.clearBuff("暂时去除主词条");

		display.clear();
		display.showText(text);
		display.showText("\n");
		
		this->showUsefulAttr(hasUsefulAttr, 38);

		display.showText("&B造成的伤害暴击后预计为 &A");
		display.showText(display.doubleToString(expectDMG, 1));
		expectDMG *= charactor.getAttrValue(ATTRIBUTE_CRITRATE);
		expectDMG += (charactor.caculateDMG(skillRate, false, ELEMENTAL_ELECTRO, enimy) *
			(1 - charactor.getAttrValue(ATTRIBUTE_CRITRATE)));
		display.showText("\n&B平均伤害的数学期望为 &A");
		display.showText(display.doubleToString(expectDMG, 1));
		display.showText("\n\n&7");

		tempDList.clear();
		tempDList.push_back(charactor.getDMGBonusRate(DMGPLUSAREA_ATK, ELEMENTAL_ELECTRO) * 100);
		tempDList.push_back(charactor.getDMGBonusRate(DMGPLUSAREA_CRITDMG, ELEMENTAL_ELECTRO) * 100);
		tempDList.push_back(charactor.getDMGBonusRate(DMGPLUSAREA_DMGBONUS, ELEMENTAL_ELECTRO) * 100);
		display.showText("&B乘区平衡参考:\n");
		display.showText("&E攻击力乘区 &8| &E暴击伤害 &8| &E增伤乘区\n");
		display.showTextD("&8= &A#% &8| &A#% &8| &A#%\n", tempDList, false, 1);
		
		tempDList = { charactor.caculateDMG(skillRate, true, ELEMENTAL_ELECTRO, enimy), 0.0, 0.0 };
		if (hasUsefulAttr > 1 && hasUsefulAttr < 37)
		{
			charactor.addBuff("多一个词条", ATTRIBUTE_ATKPER, 0.0583);
			tempDList[1] = charactor.caculateDMG(skillRate, true, ELEMENTAL_ELECTRO, enimy);
			tempDList[2] = (tempDList[1] / tempDList[0] - 1.0) * 100;
			display.showTextD("&B多&A 5.8% &B的攻击力，伤害由&A # &B提升至&A # &B", tempDList, false, 1);
			display.showTextD("，提升约&A ", tempDList[2], "%\n");
			charactor.clearBuff("多一个词条");

			charactor.addBuff("多一个词条", ATTRIBUTE_CRITDMG, 0.0777);
			tempDList[1] = charactor.caculateDMG(skillRate, true, ELEMENTAL_ELECTRO, enimy);
			tempDList[2] = (tempDList[1] / tempDList[0] - 1.0) * 100;
			display.showTextD("&B多&A 7.8% &B的暴击伤害，伤害由&A # &B提升至&A # &B", tempDList, false, 1);
			display.showTextD("，提升约&A ", tempDList[2], "%\n");
			charactor.clearBuff("多一个词条");
		}

		display.showText("\n");
		display.showButton('0', "退出");
		opr = display.selectButton();
	}
}

void CharactorUi::showGanYuUi()
{
	Display display;
	char opr = '\0';
	string text = "&7原神工具 &8>&7 主菜单 &8>&7 练度计算器 &8>&7 [甘雨]\n\n";
	Charactor ganYu;

	unsigned int level = 0;
	double baseATK = 0.0;
	double baseHP = 0.0;
	double baseDEF = 0.0;
	double skillRate[3] = { 0.0, 0.0, 0.0 };
	int levelId = 0;
	int weaponLevel = 0;
	int skillLevel = 0;
	int weaponId = 0;
	int artifactId = 0;
	int tempI = 0;
	double weaponPurify = 0.0;
	vector<double> tempDList;
	vector<string> tempSList;
	double tempD = 0.0;

	vector<string> weaponList =
	{
		"阿莫斯之弓",
		"天空之翼",
		"冬极白星",
		"试做澹月",
		"破魔之弓"
	};
	vector<vector<double>> weaponBaseATK =
	{
		{0.0, 0.0, 0.0},
		{0.0, 532.0, 608.0},
		{0.0, 590.0, 674.0},
		{0.0, 532.0, 608.0},
		{0.0, 449.0, 510.0},
		{0.0, 401.0, 454.0}
	};
	vector<int> weaponAttr =
	{
		1,
		ATTRIBUTE_ATKPER,
		ATTRIBUTE_CRITRATE,
		ATTRIBUTE_CRITRATE,
		ATTRIBUTE_ATKPER,
		ATTRIBUTE_ATKPER
	};
	vector<vector<double>> weaponAttrValue =
	{
		{0.0, 0.0, 0.0},
		{0.0, 0.453, 0.496},
		{0.0, 0.201, 0.221},
		{0.0, 0.302, 0.331},
		{0.0, 0.377, 0.413},
		{0.0, 0.503, 0.551}
	};

	display.clear();
	display.showText(text);
	display.showText("&7请选择甘雨的等级:\n");
	display.showButton('1', "80级未突破");
	display.showButton('2', "80级已突破");
	display.showButton('3', "90级");
	display.showButton('0', "退出计算");
	opr = display.selectButton();
	if (opr == '0')
	{
		return;
	}
	else if (opr == '1')
	{
		levelId = 1;
		text += "&B甘雨80级未突破\n";
		level = 80;
		baseATK = 296.0;
		baseHP = 8643.0;
		baseDEF = 556.0;
	}
	else if (opr == '2')
	{
		levelId = 2;
		text += "&B甘雨80级已突破\n";
		level = 80;
		baseATK = 312.0;
		baseHP = 9108.0;
		baseDEF = 586.0;
	}
	else if (opr == '3')
	{
		levelId = 3;
		text += "&B甘雨90级\n";
		level = 90;
		baseATK = 335.0;
		baseHP = 9797.0;
		baseDEF = 630.0;
	}

	display.clear();
	display.showText(text);
	display.showText("\n&7请选择甘雨所携带的武器:\n");
	if (this->selectWeapon(&text, &weaponId, weaponList) == false)
	{
		return;
	}

	display.clear();
	display.showText(text);
	display.showText("\n\n&7请选择武器的等级:\n");
	display.showButton('1', "80级未突破");
	display.showButton('2', "90级");
	display.showButton('0', "退出计算");
	opr = display.selectButton();
	if (opr == '0')
	{
		return;
	}
	else if (opr == '1')
	{
		baseATK += weaponBaseATK[weaponId][1];
		ganYu = Charactor(level, baseATK, baseHP, baseDEF);
		text += "80级未突破  ";
		ganYu.addBuff("暂时去除", weaponAttr[weaponId], -weaponAttrValue[weaponId][1]);
		weaponLevel = 80;
	}
	else if (opr == '2')
	{
		baseATK += weaponBaseATK[weaponId][2];
		ganYu = Charactor(level, baseATK, baseHP, baseDEF);
		text += "90级  ";
		ganYu.addBuff("暂时去除", weaponAttr[weaponId], -weaponAttrValue[weaponId][2]);
		weaponLevel = 90;
	}

	if (this->inputWeaponPurify(&text, &weaponPurify) == false)
	{
		return;
	}

	display.clear();
	display.showText(text);
	display.showText("\n&7请选择圣遗物的套装:\n");
	display.showButton('1', "冰风迷途的勇士");
	display.showButton('2', "流浪大地的乐团");
	display.showButton('0', "退出计算");
	opr = display.selectButton();
	if (opr == '0')
	{
		return;
	}
	else if (opr == '1')
	{
		artifactId = 1;
		text += "冰风迷途的勇士\n";
		ganYu.addBuff("圣遗物套装效果", ATTRIBUTE_DMGCRYO, 0.15);
	}
	else if (opr == '2')
	{
		artifactId = 2;
		text += "流浪大地的乐团\n";
		ganYu.addBuff("圣遗物套装效果", ATTRIBUTE_BUFF_DMGBONUS, 0.35);
	}

	display.clear();
	display.showText(text);
	display.showText("\n&7请输入甘雨单人在队伍中的&6额外&7攻击力(面板&6绿&7字)[0~5000]。\n");
	this->inputExtraATK(&text, &ganYu, baseATK);

	this->inputCharaCrit(&text, &ganYu);

	if (artifactId == 2)
	{
		this->inputCharaEM(&text, &ganYu);
	}

	display.clear();
	display.showText(text);
	display.showText("\n&7请输入甘雨普通攻击天赋等级。\n");
	display.showButton('6', "6级");
	display.showButton('7', "7级");
	display.showButton('8', "8级");
	display.showButton('9', "9级");
	display.showButton('1', "10级");
	display.showButton('0', "退出计算");
	opr = display.selectButton();
	if (opr == '0')
	{
		return;
	}
	else if (opr == '6')
	{
		text += "&B普通攻击天赋等级&A 6 &B级\n";
		skillRate[0] = 1.79;
		skillRate[1] = 3.05;
		skillLevel = 6;
	}
	else if (opr == '7')
	{
		text += "&B普通攻击天赋等级&A 7 &B级\n";
		skillRate[0] = 1.92;
		skillRate[1] = 3.26;
		skillLevel = 7;
	}
	else if (opr == '8')
	{
		text += "&B普通攻击天赋等级&A 8 &B级\n";
		skillRate[0] = 2.05;
		skillRate[1] = 3.48;
		skillLevel = 8;
	}
	else if (opr == '9')
	{
		text += "&B普通攻击天赋等级&A 9 &B级\n";
		skillRate[0] = 2.18;
		skillRate[1] = 3.70;
		skillLevel = 9;
	}
	else if (opr == '1')
	{
		text += "&B普通攻击天赋等级&A 10 &B级\n";
		skillRate[0] = 2.30;
		skillRate[1] = 3.92;
		skillLevel = 10;
	}
	skillRate[2] = skillRate[0] + skillRate[1];

	ganYu.addBuff("冰元素伤害加成", ATTRIBUTE_DMGCRYO, 0.466);
	//突破属性
	if (levelId == 1)
	{
		ganYu.addBuff("暂时去除", ATTRIBUTE_CRITDMG, -0.288);
	}
	else if (levelId == 2 || levelId == 3)
	{
		ganYu.addBuff("暂时去除", ATTRIBUTE_CRITDMG, -0.384);
	}

	vector<int> usefulAttr = { ATTRIBUTE_ATKPER, ATTRIBUTE_CRITRATE, ATTRIBUTE_CRITDMG };
	int maxUsefulAttr = 38;
	if (artifactId == 2)
	{
		usefulAttr.push_back(ATTRIBUTE_EM);
		maxUsefulAttr = 43;
		ganYu.addBuff("暂时去除", ATTRIBUTE_EM, -80.0);
	}
	Charactor emily(ganYu.getLevel(), 100.0, 1000.0, 5.0 * ganYu.getLevel() + 500.0);
	emily.addBuff("怪物默认的抗性", ATTRIBUTE_RESCRYO, 0.1);
	ganYu.addBuff("暂时去除", ATTRIBUTE_ATKPER, -0.466);
	ganYu.addBuff("暂时去除", ATTRIBUTE_CRITRATE, -0.331);
	ganYu.addBuff("暂时去除", ATTRIBUTE_ATK, -311.0);
	if (weaponId == 2)
	{
		ganYu.addBuff("暂时去除", ATTRIBUTE_CRITDMG, -0.2 * weaponPurify);
	}
	double hasUsefulAttr = ganYu.getUsefulAttrCount(usefulAttr);
	ganYu.clearBuff("暂时去除");

	display.clear();
	display.showText(text);
	display.showText("\n");

	this->showUsefulAttr(hasUsefulAttr, maxUsefulAttr);

	tempDList = { 0.0, 0.0, 0.0, 0.0 };
	while (tempDList[3] < 9.5)
	{
		if (weaponId == 1)
		{
			if (tempDList[3] > 0.5 && tempDList[3] < 1.5)
			{
				break;
			}
			else if (tempDList[3] > -0.5 && tempDList[3] < 0.5)
			{
				ganYu.addBuff("武器被动", ATTRIBUTE_BUFF_DMGBONUS, 0.36 * weaponPurify);
				display.showText("&B若吃到武器的三层被动，");
			}
		}
		else if (weaponId == 2)
		{
			if (tempDList[3] > 0.5 && tempDList[3] < 1.5)
			{
				break;
			}
		}
		else if (weaponId == 3)
		{
			if (tempDList[3] > 0.5 && tempDList[3] < 1.5)
			{
				break;
			}
			else if (tempDList[3] > -0.5 && tempDList[3] < 0.5)
			{
				ganYu.addBuff("武器被动", ATTRIBUTE_ATKPER, 0.20 * weaponPurify);
				display.showText("&B若吃到武器的两层被动，");
			}
		}
		else if (weaponId == 4)
		{
			if (tempDList[3] > 1.5 && tempDList[3] < 2.5)
			{
				break;
			}
			else if (tempDList[3] > 0.5 && tempDList[3] < 1.5)
			{
				ganYu.addBuff("武器被动", ATTRIBUTE_ATKPER, 0.36 * weaponPurify);
				display.showText("&B射中敌人的弱点后，");
			}
			else if (tempDList[3] > -0.5 && tempDList[3] < 0.5)
			{
				display.showText("&B若不触发武器被动，");
			}
		}
		else if (weaponId == 5)
		{
			if (tempDList[3] > 1.5 && tempDList[3] < 2.5)
			{
				break;
			}
			else if (tempDList[3] > 0.5 && tempDList[3] < 1.5)
			{
				ganYu.clearBuff("武器被动");
				ganYu.addBuff("武器被动", ATTRIBUTE_BUFF_DMGBONUS, 0.24 * weaponPurify);
				display.showText("&B若元素能量满，则");
			}
			else if (tempDList[3] > -0.5 && tempDList[3] < 0.5)
			{
				ganYu.addBuff("武器被动", ATTRIBUTE_BUFF_DMGBONUS, 0.12 * weaponPurify);
				display.showText("&B若元素能量不满，则");
			}
		}

		tempDList[0] = ganYu.caculateDMG(skillRate[0], true, ELEMENTAL_CRYO, emily);
		tempDList[1] = ganYu.caculateDMG(skillRate[1], true, ELEMENTAL_CRYO, emily);
		tempDList[2] = ganYu.caculateDMG(skillRate[2], true, ELEMENTAL_CRYO, emily);
		display.showTextD("射出的霜华矢的总伤害预计为 &A# &8+ &A# &8= &A#\n", tempDList, true, 1);
		if (artifactId == 2)
		{
			tempDList[0] = ganYu.caculateDMG(skillRate[0], true, ELEMENTAL_CRYO, emily, 1.5);
			tempDList[1] = ganYu.caculateDMG(skillRate[1], true, ELEMENTAL_CRYO, emily, 1.5);
			tempDList[2] = ganYu.caculateDMG(skillRate[2], true, ELEMENTAL_CRYO, emily, 1.5);
			display.showTextD("&B触发融化反应的伤害为 &A# &8+ &A# &8= &A#\n", tempDList, true, 1);
		}

		tempDList[3] += 1.0;
	}
	display.showText("\n");

	tempDList.clear();
	tempDList.push_back(ganYu.getDMGBonusRate(DMGPLUSAREA_ATK, ELEMENTAL_CRYO) * 100);
	tempDList.push_back(ganYu.getDMGBonusRate(DMGPLUSAREA_CRITDMG, ELEMENTAL_CRYO) * 100);
	tempDList.push_back(ganYu.getDMGBonusRate(DMGPLUSAREA_DMGBONUS, ELEMENTAL_CRYO) * 100);
	tempDList.push_back(ganYu.getDMGBonusRate(DMGPLUSAREA_ELEMENT, ELEMENTAL_CRYO) * 100);
	display.showText("&B乘区平衡参考:\n");
	if (artifactId == 1)
	{
		display.showText("&E攻击力乘区 &8| &E暴击伤害 &8| &E增伤乘区\n");
		display.showTextD("&8= &A#% &8| &A#% &8| &A#%\n", tempDList, false, 1);

		tempDList = { ganYu.caculateDMG(skillRate[2], true, ELEMENTAL_CRYO, emily), 0.0, 0.0 };

		if (hasUsefulAttr > 1 && hasUsefulAttr < maxUsefulAttr - 1)
		{
			ganYu.addBuff("多一个词条", ATTRIBUTE_ATKPER, 0.0583);
			tempDList[1] = ganYu.caculateDMG(skillRate[2], true, ELEMENTAL_CRYO, emily);
			tempDList[2] = (tempDList[1] / tempDList[0] - 1.0) * 100;
			display.showTextD("&B多&A 5.8% &B的攻击力，伤害由&A # &B提升至&A # &B", tempDList, false, 1);
			display.showTextD("，提升约&A ", tempDList[2], "%\n");
			ganYu.clearBuff("多一个词条");

			ganYu.addBuff("多一个词条", ATTRIBUTE_CRITDMG, 0.0777);
			tempDList[1] = ganYu.caculateDMG(skillRate[2], true, ELEMENTAL_CRYO, emily);
			tempDList[2] = (tempDList[1] / tempDList[0] - 1.0) * 100;
			display.showTextD("&B多&A 7.8% &B的暴击伤害，伤害由&A # &B提升至&A # &B", tempDList, false, 1);
			display.showTextD("，提升约&A ", tempDList[2], "%\n");
			ganYu.clearBuff("多一个词条");
		}
	}
	else if (artifactId == 2)
	{
		display.showText("&E攻击力乘区 &8| &E暴击伤害 &8| &E增伤乘区 &8| &E元素反应乘区\n");
		display.showTextD("&8= &A#% &8| &A#% &8| &A#% &8| &A#%\n", tempDList, false, 1);

		tempDList = { ganYu.caculateDMG(skillRate[2], true, ELEMENTAL_CRYO, emily, 1.5), 0.0, 0.0 };

		if (hasUsefulAttr > 1 && hasUsefulAttr < maxUsefulAttr - 1)
		{
			ganYu.addBuff("多一个词条", ATTRIBUTE_ATKPER, 0.0583);
			tempDList[1] = ganYu.caculateDMG(skillRate[2], true, ELEMENTAL_CRYO, emily, 1.5);
			tempDList[2] = (tempDList[1] / tempDList[0] - 1.0) * 100;
			display.showTextD("&B多&A 5.8% &B的攻击力，融化伤害由&A # &B提升至&A # &B", tempDList, false, 1);
			display.showTextD("，提升约&A ", tempDList[2], "%\n");
			ganYu.clearBuff("多一个词条");

			ganYu.addBuff("多一个词条", ATTRIBUTE_CRITDMG, 0.0777);
			tempDList[1] = ganYu.caculateDMG(skillRate[2], true, ELEMENTAL_CRYO, emily, 1.5);
			tempDList[2] = (tempDList[1] / tempDList[0] - 1.0) * 100;
			display.showTextD("&B多&A 7.8% &B的暴击伤害，融化伤害由&A # &B提升至&A # &B", tempDList, false, 1);
			display.showTextD("，提升约&A ", tempDList[2], "%\n");
			ganYu.clearBuff("多一个词条");

			ganYu.addBuff("多一个词条", ATTRIBUTE_EM, 23.31);
			tempDList[1] = ganYu.caculateDMG(skillRate[2], true, ELEMENTAL_CRYO, emily, 1.5);
			tempDList[2] = (tempDList[1] / tempDList[0] - 1.0) * 100;
			display.showTextD("&B多&A 23 &B点元素精通，融化伤害由&A # &B提升至&A # &B", tempDList, false, 1);
			display.showTextD("，提升约&A ", tempDList[2], "%\n");
			ganYu.clearBuff("多一个词条");
		}
	}

	if (hasUsefulAttr < maxUsefulAttr - 1)
	{
		if (artifactId == 1)
		{
			ganYu.addBuff("额外暴击率buff", ATTRIBUTE_CRITRATE, 0.75);
			tempDList = { ganYu.caculateAveDMG(skillRate[2], ELEMENTAL_CRYO, emily) };

			//评分计算[可能需要更好的分数计算方式]
			tempD = hasUsefulAttr / maxUsefulAttr * 100 + levelId * 4 + weaponLevel + skillLevel * 3 - 100;
		}
		else if (artifactId == 2)
		{
			ganYu.addBuff("额外暴击率buff", ATTRIBUTE_CRITRATE, 0.2);
			tempDList = { ganYu.caculateAveDMG(skillRate[2], ELEMENTAL_CRYO, emily, 1.5) };

			//评分计算[可能需要更好的分数计算方式]
			tempD = hasUsefulAttr / maxUsefulAttr * 100 + levelId * 4 + weaponLevel + skillLevel * 3 - 100;
		}

		display.showText("\n&B总体练度评价:&E");
		if (hasUsefulAttr < 1)
		{
			display.showText("待培养\n");
		}
		else
		{
			tempDList = { 20, 40, 50, 60, 70, 75, 80, 85, 90, 95, 100 };
			tempSList = { "未毕业", "刚入门", "及格", "良好", "幼儿园毕业", "小学毕业",
				"初中毕业", "高中毕业", "大学毕业", "成功毕业", "完美毕业", "终结" };
			display.showStringIfBetween(tempD, tempDList, tempSList);
			display.showText("\n");
		}

		tempI = 1;
		display.showText("&B提升建议:\n");
		if (hasUsefulAttr < 1)
		{
			display.showTextI("&B", tempI, ".&E刷取一套主词条正确的圣遗物并升到20级。\n");
			tempI++;
		}
		if (levelId == 1)
		{
			display.showTextI("&B", tempI, ".&E让甘雨进行80级突破。\n");
			tempI++;
		}
		if (weaponLevel < 90)
		{
			display.showTextI("&B", tempI, ".&E将甘雨的武器升级到90级。\n");
			tempI++;
		}
		if (skillLevel < 8)
		{
			display.showTextI("&B", tempI, ".&E将甘雨的普通攻击天赋升级到8级。\n");
			tempI++;
		}
		if (hasUsefulAttr / maxUsefulAttr < 0.4)
		{
			if (artifactId == 1 || ganYu.getAttrValue(ATTRIBUTE_CRITRATE) >= 0.76)
			{
				display.showTextI("&B", tempI, ".&E通过圣遗物副词条获取更多暴击伤害、百分比攻击力属性。\n");
				tempI++;
			}
			else if (artifactId == 2)
			{
				display.showTextI("&B", tempI, ".&E通过圣遗物副词条获取更多暴击率、暴击伤害、百分比攻击力属性。\n");
				tempI++;
			}
		}
		if (hasUsefulAttr / maxUsefulAttr >= 0.4)
		{
			if (skillLevel == 8)
			{
				display.showTextI("&B", tempI, ".&E将甘雨的普通攻击天赋升级到9级。\n");
				tempI++;
			}
			if (artifactId == 1)
			{
				ganYu.addBuff("永冻队buff可能", ATTRIBUTE_ATKPER, 0.2);

				tempDList = { ganYu.caculateAveDMG(skillRate[2], ELEMENTAL_CRYO, emily), 0.0, 0.0, 0.0 };

				ganYu.addBuff("多一个词条", ATTRIBUTE_ATKPER, 0.0583);
				tempDList[1] = ganYu.caculateAveDMG(skillRate[2], ELEMENTAL_CRYO, emily);
				tempDList[1] = (tempDList[1] / tempDList[0] - 1.0) * 100;
				ganYu.clearBuff("多一个词条");

				ganYu.addBuff("多一个词条", ATTRIBUTE_CRITDMG, 0.0777);
				tempDList[2] = ganYu.caculateAveDMG(skillRate[2], ELEMENTAL_CRYO, emily);
				tempDList[2] = (tempDList[2] / tempDList[0] - 1.0) * 100;
				ganYu.clearBuff("多一个词条");
			}
			if (artifactId == 2)
			{
				ganYu.addBuff("融化队buff可能", ATTRIBUTE_ATK, 400);

				tempDList = { ganYu.caculateAveDMG(skillRate[2], ELEMENTAL_CRYO, emily, 1.5), 0.0, 0.0, 0.0 };

				ganYu.addBuff("多一个词条", ATTRIBUTE_ATKPER, 0.0583);
				tempDList[1] = ganYu.caculateAveDMG(skillRate[2], ELEMENTAL_CRYO, emily, 1.5);
				tempDList[1] = (tempDList[1] / tempDList[0] - 1.0) * 100;
				ganYu.clearBuff("多一个词条");

				ganYu.addBuff("多一个词条", ATTRIBUTE_CRITDMG, 0.0777);
				tempDList[2] = ganYu.caculateAveDMG(skillRate[2], ELEMENTAL_CRYO, emily, 1.5);
				tempDList[2] = (tempDList[2] / tempDList[0] - 1.0) * 100;
				ganYu.clearBuff("多一个词条");

				ganYu.addBuff("多一个词条", ATTRIBUTE_EM, 23.31);
				tempDList[3] = ganYu.caculateAveDMG(skillRate[2], ELEMENTAL_CRYO, emily, 1.5);
				tempDList[3] = (tempDList[3] / tempDList[0] - 1.0) * 100;
				ganYu.clearBuff("多一个词条");
			}
		}
		if (hasUsefulAttr / maxUsefulAttr >= 0.4 && hasUsefulAttr / maxUsefulAttr < 0.6)
		{
			if (ganYu.getAttrValue(ATTRIBUTE_CRITRATE) < 0.76)
			{
				display.showTextI("&B", tempI, ".&E通过圣遗物副词条获取更多暴击率属性。\n");
				tempI++;
			}

			if (artifactId == 2 && tempDList[3] > tempDList[1] * 1.1 && tempDList[3] > tempDList[2] * 1.1)
			{
				display.showTextI("&B", tempI, ".&E通过圣遗物副词条获取更多元素精通属性。\n");
				tempI++;
			}
			else if (tempDList[1] > tempDList[2] * 1.04)
			{
				display.showTextI("&B", tempI, ".&E通过圣遗物副词条获取更多百分比攻击力属性。\n");
				tempI++;
			}
			else if (tempDList[2] > tempDList[1] * 1.04)
			{
				display.showTextI("&B", tempI, ".&E通过圣遗物副词条获取更多暴击伤害属性。\n");
				tempI++;
			}
			else
			{
				display.showTextI("&B", tempI, ".&E通过圣遗物副词条获取更多暴击伤害和百分比攻击力属性。\n");
				tempI++;
			}
		}
		if (skillLevel == 9 && hasUsefulAttr / maxUsefulAttr >= 0.6)
		{
			display.showTextI("&B", tempI, ".&E将甘雨的普通攻击天赋升级到10级。\n");
			tempI++;
		}
		if (levelId == 2 && hasUsefulAttr / maxUsefulAttr >= 0.6)
		{
			display.showTextI("&B", tempI, ".&E将甘雨升级到90级。\n");
			tempI++;
		}
		if (hasUsefulAttr / maxUsefulAttr >= 0.6 && skillLevel == 10 && levelId == 3)
		{
			tempSList = { "多余的属性", "缺少的属性" };
			if (ganYu.getAttrValue(ATTRIBUTE_CRITRATE) < 0.76)
			{
				tempSList[1] = "暴击率";
			}
			else
			{
				if (artifactId == 2 && tempDList[3] > tempDList[1] * 1.2 && tempDList[3] > tempDList[2] * 1.2)
				{
					tempSList[1] = "元素精通";
				}
				else if (tempDList[1] > tempDList[2] * 1.07)
				{
					tempSList[1] = "百分比攻击力";
				}
				else if (tempDList[2] > tempDList[1] * 1.14)
				{
					tempSList[1] = "暴击伤害";
				}
			}

			if (tempSList[1] != "缺少的属性")
			{
				if (artifactId == 1 && ganYu.getAttrValue(ATTRIBUTE_CRITRATE) > 1.3)
				{
					tempSList[0] = "暴击率";
				}
				else if (artifactId == 2 && ganYu.getAttrValue(ATTRIBUTE_CRITRATE) > 0.98)
				{
					tempSList[0] = "暴击率";
				}
				else
				{
					if (artifactId == 2 && tempDList[3] < tempDList[1] * 0.9 && tempDList[3] < tempDList[2] * 0.9)
					{
						tempSList[0] = "元素精通";
					}
					else if (tempDList[1] < tempDList[2] * 0.94)
					{
						tempSList[0] = "百分比攻击力";
					}
					else if (tempDList[2] < tempDList[1] * 0.86)
					{
						tempSList[0] = "暴击伤害";
					}
					else
					{
						tempSList[0] = "元素精通";
						if (tempSList[1] == "元素精通")
						{
							tempSList[0] = "百分比攻击力";
						}
					}
				}

				if (tempSList[0] != tempSList[1])
				{
					display.showTextI("&B", tempI, ".&E调整圣遗物的副词条，将部分" +
						tempSList[0] + "属性分配给" + tempSList[1] + "属性。\n");
					tempI++;
				}
			}
		}
		if (tempI == 1)
		{
			display.showTextI("&B", tempI, ".&E甘雨已经毕业了，去培养其他的角色吧。\n");
		}
	}

	this->showErrorInfo(hasUsefulAttr, maxUsefulAttr);

	display.showText("\n&7");
	display.showButton('0', "退出");
	opr = display.selectButton();
}

void CharactorUi::showHuTaoUi()
{
	Display display;
	char opr = '\0';
	string text = "&7原神工具 &8>&7 主菜单 &8>&7 练度计算器 &8>&7 [胡桃]\n\n";
	Charactor huTao;

	unsigned int level = 0;
	double baseATK = 0.0;
	double baseHP = 0.0;
	double baseDEF = 0.0;
	double skillRate[3] = { 0.0, 0.0, 0.0 };
	int levelId = 0;
	int weaponLevel = 0;
	vector<int> skillLevel = { 0, 0, 0 };
	int weaponId = 0;
	int artifactId = 0;
	int tempI = 0;
	double weaponPurify = 0.0;
	vector<double> tempDList;
	vector<string> tempSList;
	double tempD = 0.0;

	vector<string> weaponList =
	{
		"护摩之杖",
		"和璞鸢",
		"匣里灭辰",
		"决斗之枪",
	};
	vector<vector<double>> weaponBaseATK =
	{
		{0.0, 0.0, 0.0},
		{0.0, 532.0, 608.0},
		{0.0, 590.0, 674.0},
		{0.0, 401.0, 454.0},
		{0.0, 401.0, 454.0},
	};
	vector<int> weaponAttr =
	{
		1,
		ATTRIBUTE_CRITDMG,
		ATTRIBUTE_CRITRATE,
		ATTRIBUTE_EM,
		ATTRIBUTE_CRITRATE,
	};
	vector<vector<double>> weaponAttrValue =
	{
		{0.0, 0.0, 0.0},
		{0.0, 0.603, 0.662},
		{0.0, 0.201, 0.221},
		{0.0, 201.0, 221.0},
		{0.0, 0.335, 0.368},
	};

	display.clear();
	display.showText(text);
	display.showText("&7请选择胡桃的等级:\n");
	display.showButton('1', "80级未突破");
	display.showButton('2', "80级已突破");
	display.showButton('3', "90级");
	display.showButton('0', "退出计算");
	opr = display.selectButton();
	if (opr == '0')
	{
		return;
	}
	else if (opr == '1')
	{
		levelId = 1;
		text += "&B胡桃80级未突破\n";
		level = 80;
		baseATK = 94.0;
		baseHP = 13721.0;
		baseDEF = 773.0;
	}
	else if (opr == '2')
	{
		levelId = 2;
		text += "&B胡桃80级已突破\n";
		level = 80;
		baseATK = 99.0;
		baseHP = 14459.0;
		baseDEF = 815.0;
	}
	else if (opr == '3')
	{
		levelId = 3;
		text += "&B胡桃90级\n";
		level = 90;
		baseATK = 106.0;
		baseHP = 15552.0;
		baseDEF = 876.0;
	}

	display.clear();
	display.showText(text);
	display.showText("\n&7请选择胡桃所携带的武器:\n");
	if (this->selectWeapon(&text, &weaponId, weaponList) == false)
	{
		return;
	}

	display.clear();
	display.showText(text);
	display.showText("\n\n&7请选择武器的等级:\n");
	display.showButton('1', "80级未突破");
	display.showButton('2', "90级");
	display.showButton('0', "退出计算");
	opr = display.selectButton();
	if (opr == '0')
	{
		return;
	}
	else if (opr == '1')
	{
		baseATK += weaponBaseATK[weaponId][1];
		huTao = Charactor(level, baseATK, baseHP, baseDEF);
		text += "80级未突破  ";
		huTao.addBuff("暂时去除", weaponAttr[weaponId], -weaponAttrValue[weaponId][1]);
		weaponLevel = 80;
	}
	else if (opr == '2')
	{
		baseATK += weaponBaseATK[weaponId][2];
		huTao = Charactor(level, baseATK, baseHP, baseDEF);
		text += "90级  ";
		huTao.addBuff("暂时去除", weaponAttr[weaponId], -weaponAttrValue[weaponId][2]);
		weaponLevel = 90;
	}

	if (this->inputWeaponPurify(&text, &weaponPurify) == false)
	{
		return;
	}

	display.clear();
	display.showText(text);
	display.showText("\n&7请选择圣遗物的套装:\n");
	display.showButton('1', "炽烈的炎之魔女");
	display.showButton('2', "追忆之注连");
	display.showButton('0', "退出计算");
	opr = display.selectButton();
	if (opr == '0')
	{
		return;
	}
	else if (opr == '1')
	{
		artifactId = 1;
		text += "炽烈的炎之魔女\n";
		huTao.addBuff("圣遗物套装效果", ATTRIBUTE_DMGPYRO, 0.225);
		huTao.addBuff("圣遗物套装效果", ATTRIBUTE_BUFF_EXTRAEM, 0.15);
	}
	else if (opr == '2')
	{
		artifactId = 2;
		text += "追忆之注连\n";
		huTao.addBuff("圣遗物套装效果", ATTRIBUTE_BUFF_DMGBONUS, 0.5);
	}

	for (tempI = 0; tempI < 3; tempI++)
	{
		display.clear();
		display.showText(text);
		if (tempI == 0)
		{
			display.showText("\n&7请输入胡桃普通攻击天赋等级。\n");
			text += "&B普通攻击天赋等级";
		}
		else if (tempI == 1)
		{
			display.showText("\n&7请输入胡桃元素战技天赋等级。\n");
			text += "&B元素战技天赋等级";
		}
		else if (tempI == 2)
		{
			display.showText("\n&7请输入胡桃元素爆发天赋等级。\n");
			text += "&B元素爆发天赋等级";
		}
		display.showButton('6', "6级");
		display.showButton('7', "7级");
		display.showButton('8', "8级");
		display.showButton('9', "9级");
		display.showButton('1', "10级");
		display.showButton('0', "退出计算");
		opr = display.selectButton();
		if (opr == '0')
		{
			return;
		}
		else if (opr == '6')
		{
			text += "&A 6 &B级\n";
			tempDList = { 1.869, 0.0506, 4.99 };
			skillRate[tempI] = tempDList[tempI];
			skillLevel[tempI] = 6;
		}
		else if (opr == '7')
		{
			text += "&A 7 &B级\n";
			tempDList = { 2.009, 0.0536, 5.29 };
			skillRate[tempI] = tempDList[tempI];
			skillLevel[tempI] = 7;
		}
		else if (opr == '8')
		{
			text += "&A 8 &B级\n";
			tempDList = { 2.148, 0.0566, 5.58 };
			skillRate[tempI] = tempDList[tempI];
			skillLevel[tempI] = 8;
		}
		else if (opr == '9')
		{
			text += "&A 9 &B级\n";
			tempDList = { 2.287, 0.0596, 5.88 };
			skillRate[tempI] = tempDList[tempI];
			skillLevel[tempI] = 9;
		}
		else if (opr == '1')
		{
			text += "&A 10 &B级\n";
			tempDList = { 2.426, 0.0626, 6.17 };
			skillRate[tempI] = tempDList[tempI];
			skillLevel[tempI] = 10;
		}
	}

	display.clear();
	display.showText(text);
	display.showText("\n&7请输入胡桃的&6额外&7生命值(面板&6绿&7字)[0~50000]。\n");
	this->inputExtraHP(&text, &huTao, baseHP);

	display.clear();
	display.showText(text);
	display.showText("\n&7请输入胡桃的&6额外&7攻击力(面板&6绿&7字)[0~5000]。\n");	
	tempI = display.getInputInt(5000, false);
	//判断是否开了E技能
	tempD = huTao.getAttrValue(ATTRIBUTE_HP) * skillRate[1];
	if (tempD > baseATK * 4)
	{
		tempD = baseATK * 4;
	}
	tempD = (double)tempI - tempD;
	if (weaponId == 1)
	{
		tempD -= (huTao.getAttrValue(ATTRIBUTE_HP) * (0.016 * weaponPurify + 0.002));
	}
	if (tempD > 311)
	{
		text += "&B开E技能后的攻击力: &A";
		text += display.intToString((int)baseATK + tempI);
		text += "\n&B";
		huTao.addBuff("固定攻击力加成", ATTRIBUTE_ATK, tempD);
	}
	else
	{
		text += "&B攻击力: &A";
		text += display.intToString((int)baseATK + tempI);
		text += "\n&B";

		if (weaponId == 1)
		{
			display.clear();
			display.showText(text);
			display.showText("\n&7刚刚输入的攻击力面板是在哪种情况下得到的\n\n");
			display.showText("说明:如果胡桃不在队伍里，则护摩之杖的被动效果不会生效。\n");
			display.showText("因此需要确认来减少计算结果的误差。\n\n");
			display.showButton('1', "胡桃不在队伍里面");
			display.showButton('2', "胡桃半血以上且在队伍里面");
			display.showButton('3', "胡桃半血以下且在队伍里面");
			display.showButton('0', "退出计算");
			opr = display.selectButton();
			if (opr == '0')
			{
				return;
			}
			else if (opr == '1')
			{
				huTao.addBuff("固定攻击力加成", ATTRIBUTE_ATK, (double)tempI);
			}
			else if (opr == '2')
			{
				huTao.addBuff("固定攻击力加成", ATTRIBUTE_ATK,
					(double)tempI - huTao.getAttrValue(ATTRIBUTE_HP) * 0.008 * weaponPurify);
			}
			else if (opr == '3')
			{
				huTao.addBuff("固定攻击力加成", ATTRIBUTE_ATK, 
					(double)tempI - huTao.getAttrValue(ATTRIBUTE_HP) * (0.016 * weaponPurify + 0.002));
			}
		}
		else
		{
			huTao.addBuff("固定攻击力加成", ATTRIBUTE_ATK, (double)tempI);
		}
	}

	this->inputCharaCrit(&text, &huTao);
	this->inputCharaEM(&text, &huTao);

	huTao.addBuff("火元素伤害加成", ATTRIBUTE_DMGPYRO, 0.466);
	//突破属性
	if (levelId == 1)
	{
		huTao.addBuff("暂时去除", ATTRIBUTE_CRITDMG, -0.288);
	}
	else if (levelId == 2 || levelId == 3)
	{
		huTao.addBuff("暂时去除", ATTRIBUTE_CRITDMG, -0.384);
	}
	//半血天赋
	huTao.addBuff("火元素伤害加成", ATTRIBUTE_DMGPYRO, 0.33);

	vector<int> usefulAttr = { ATTRIBUTE_HPPER, ATTRIBUTE_CRITRATE, ATTRIBUTE_CRITDMG, ATTRIBUTE_EM };
	int maxUsefulAttr = 43;
	Charactor emily(huTao.getLevel(), 100.0, 1000.0, 5.0 * huTao.getLevel() + 500.0);
	emily.addBuff("怪物默认的抗性", ATTRIBUTE_RESPYRO, 0.1);
	huTao.addBuff("暂时去除", ATTRIBUTE_HPPER, -0.466);
	huTao.addBuff("暂时去除", ATTRIBUTE_CRITRATE, -0.331);
	huTao.addBuff("暂时去除", ATTRIBUTE_HP, -4780.0);
	if (weaponId == 1)
	{
		huTao.addBuff("暂时去除", ATTRIBUTE_HPPER, -0.2 * weaponPurify);
	}
	double hasUsefulAttr = huTao.getUsefulAttrCount(usefulAttr);
	huTao.clearBuff("暂时去除");

	display.clear();
	display.showText(text);
	display.showText("\n");

	this->showUsefulAttr(hasUsefulAttr, maxUsefulAttr);

	tempDList = { 0.0, 0.0, 0.0, 0.0 };
	while (tempDList[3] < 9.5)
	{
		if (weaponId == 1)
		{
			if (tempDList[3] > 0.5 && tempDList[3] < 1.5)
			{
				break;
			}
			else if (tempDList[3] > -0.5 && tempDList[3] < 0.5)
			{
				tempD = huTao.getAttrValue(ATTRIBUTE_HP) * (0.016 * weaponPurify + 0.002);
				huTao.addBuff("武器被动", ATTRIBUTE_ATK, tempD);
			}
		}
		else if (weaponId == 2)
		{
			if (tempDList[3] > 1.5 && tempDList[3] < 2.5)
			{
				break;
			}
			else if (tempDList[3] > 0.5 && tempDList[3] < 1.5)
			{
				huTao.clearBuff("武器被动");
				huTao.addBuff("武器被动", ATTRIBUTE_BUFF_DMGBONUS, 0.12 * weaponPurify);
				huTao.addBuff("武器被动", ATTRIBUTE_ATKPER, 0.196 * weaponPurify + 0.028);
				display.showText("&B若吃到武器的满层被动，");
			}
			else if (tempDList[3] > -0.5 && tempDList[3] < 0.5)
			{
				huTao.addBuff("武器被动", ATTRIBUTE_ATKPER, 0.028 * weaponPurify + 0.004);
				display.showText("&B若不计算武器的被动，");
			}
		}
		else if (weaponId == 3)
		{
			if (tempDList[3] > 0.5 && tempDList[3] < 1.5)
			{
				break;
			}
			else if (tempDList[3] > -0.5 && tempDList[3] < 0.5)
			{
				huTao.addBuff("武器被动", ATTRIBUTE_BUFF_DMGBONUS, 0.16 * weaponPurify + 0.04);
			}
		}
		else if (weaponId == 4)
		{
			if (tempDList[3] > 0.5 && tempDList[3] < 1.5)
			{
				break;
			}
		}

		tempD = huTao.getAttrValue(ATTRIBUTE_HP) * skillRate[1];
		if (tempD > baseATK * 4)
		{
			tempD = baseATK * 4;
		}
		huTao.addBuff("开E技能", ATTRIBUTE_ATK, tempD);
		tempDList[0] = huTao.caculateDMG(skillRate[0], true, ELEMENTAL_PYRO, emily, 1.5);
		if (artifactId == 2)
		{
			huTao.clearBuff("圣遗物套装效果");
		}
		tempDList[1] = huTao.caculateDMG(skillRate[2], true, ELEMENTAL_PYRO, emily, 1.5);
		if (artifactId == 2)
		{
			huTao.addBuff("圣遗物套装效果", ATTRIBUTE_BUFF_DMGBONUS, 0.5);
		}
		display.showTextD("&B半血以下开E后，重击裸蒸发伤害预计为 &A# ，&B大招伤害预计为 &A#\n", tempDList, true, 1);
		huTao.addBuff("钟离双岩", ATTRIBUTE_BUFF_DMGBONUS, 0.15);
		emily.addBuff("钟离双岩", ATTRIBUTE_RESPYRO, -0.2);
		tempDList[0] = huTao.caculateDMG(skillRate[0], true, ELEMENTAL_PYRO, emily, 1.5);
		if (artifactId == 2)
		{
			huTao.clearBuff("圣遗物套装效果");
		}
		tempDList[1] = huTao.caculateDMG(skillRate[2], true, ELEMENTAL_PYRO, emily, 1.5);
		if (artifactId == 2)
		{
			huTao.addBuff("圣遗物套装效果", ATTRIBUTE_BUFF_DMGBONUS, 0.5);
		}
		display.showTextD("&B若吃到钟离护盾减抗和双岩共鸣，则重击蒸发伤害预计为 &A# ，&B大招伤害预计为 &A#\n",
			tempDList, true, 1);
		huTao.clearBuff("钟离双岩");
		emily.clearBuff("钟离双岩");
		huTao.clearBuff("开E技能");

		tempDList[3] += 1.0;
	}
	display.showText("\n");

	tempDList.clear();
	huTao.addBuff("开E技能", ATTRIBUTE_ATK, tempD);
	tempDList.push_back(huTao.getDMGBonusRate(DMGPLUSAREA_ATK, ELEMENTAL_PYRO) * 100);
	tempDList.push_back(huTao.getDMGBonusRate(DMGPLUSAREA_CRITDMG, ELEMENTAL_PYRO) * 100);
	tempDList.push_back(huTao.getDMGBonusRate(DMGPLUSAREA_DMGBONUS, ELEMENTAL_PYRO) * 100);
	tempDList.push_back(huTao.getDMGBonusRate(DMGPLUSAREA_ELEMENT, ELEMENTAL_PYRO) * 100);
	display.showText("&B乘区平衡参考:\n");
	display.showText("&E攻击力乘区 &8| &E暴击伤害 &8| &E增伤乘区 &8| &E元素反应乘区\n");
	display.showTextD("&8= &A#% &8| &A#% &8| &A#% &8| &A#%\n", tempDList, false, 1);
	tempDList = { huTao.caculateDMG(skillRate[0], true, ELEMENTAL_PYRO, emily, 1.5), 0.0, 0.0 };

	if (hasUsefulAttr > 1 && hasUsefulAttr < maxUsefulAttr - 1)
	{
		huTao.addBuff("多一个词条", ATTRIBUTE_ATKPER, 0.0583);
		tempDList[1] = huTao.caculateDMG(skillRate[0], true, ELEMENTAL_PYRO, emily, 1.5);
		tempDList[2] = (tempDList[1] / tempDList[0] - 1.0) * 100;
		display.showTextD("&B多&A 5.8% &B的攻击力，蒸发伤害由&A # &B提升至&A # &B", tempDList, false, 1);
		display.showTextD("，提升约&A ", tempDList[2], "%\n");
		huTao.clearBuff("多一个词条");

		huTao.addBuff("多一个词条", ATTRIBUTE_CRITDMG, 0.0777);
		tempDList[1] = huTao.caculateDMG(skillRate[0], true, ELEMENTAL_PYRO, emily, 1.5);
		tempDList[2] = (tempDList[1] / tempDList[0] - 1.0) * 100;
		display.showTextD("&B多&A 7.8% &B的暴击伤害，蒸发伤害由&A # &B提升至&A # &B", tempDList, false, 1);
		display.showTextD("，提升约&A ", tempDList[2], "%\n");
		huTao.clearBuff("多一个词条");

		huTao.addBuff("多一个词条", ATTRIBUTE_EM, 23.31);
		tempDList[1] = huTao.caculateDMG(skillRate[0], true, ELEMENTAL_PYRO, emily, 1.5);
		tempDList[2] = (tempDList[1] / tempDList[0] - 1.0) * 100;
		display.showTextD("&B多&A 23 &B点元素精通，蒸发伤害由&A # &B提升至&A # &B", tempDList, false, 1);
		display.showTextD("，提升约&A ", tempDList[2], "%\n");
		huTao.clearBuff("多一个词条");
		//计算生命值的提升需要更新武器被动和E技能转化
		huTao.clearBuff("开E技能");
		if (weaponId == 1)
		{
			huTao.clearBuff("武器被动");
		}
		huTao.addBuff("多一个词条", ATTRIBUTE_HPPER, 0.0583);
		tempD = huTao.getAttrValue(ATTRIBUTE_HP) * skillRate[1];
		if (tempD > baseATK * 4)
		{
			tempD = baseATK * 4;
		}
		huTao.addBuff("开E技能", ATTRIBUTE_ATK, tempD);
		if (weaponId == 1)
		{
			tempD = huTao.getAttrValue(ATTRIBUTE_HP) * (0.016 * weaponPurify + 0.002);
			huTao.addBuff("武器被动", ATTRIBUTE_ATK, tempD);
		}
		tempDList[1] = huTao.caculateDMG(skillRate[0], true, ELEMENTAL_PYRO, emily, 1.5);
		tempDList[2] = (tempDList[1] / tempDList[0] - 1.0) * 100;
		display.showTextD("&B多&A 5.8% &B的生命值，蒸发伤害由&A # &B提升至&A # &B", tempDList, false, 1);
		display.showTextD("，提升约&A ", tempDList[2], "%\n");
		huTao.clearBuff("开E技能");
		if (weaponId == 1)
		{
			huTao.clearBuff("武器被动");
		}
		huTao.clearBuff("多一个词条");
		tempD = huTao.getAttrValue(ATTRIBUTE_HP) * skillRate[1];
		if (tempD > baseATK * 4)
		{
			tempD = baseATK * 4;
		}
		huTao.addBuff("开E技能", ATTRIBUTE_ATK, tempD);
		if (weaponId == 1)
		{
			tempD = huTao.getAttrValue(ATTRIBUTE_HP) * (0.016 * weaponPurify + 0.002);
			huTao.addBuff("武器被动", ATTRIBUTE_ATK, tempD);
		}
	}

	if (hasUsefulAttr < maxUsefulAttr - 1)
	{
		display.showText("\n&B总体练度评价:&E");

		//评分计算[可能需要更好的分数计算方式]
		tempD = hasUsefulAttr / maxUsefulAttr * 90 + levelId * 5 + weaponLevel +
			skillLevel[0] + skillLevel[1] * 2 + skillLevel[2] - 105;
		if (hasUsefulAttr < 1)
		{
			display.showText("待培养\n");
		}
		else
		{
			tempDList = { 20, 40, 50, 60, 70, 75, 80, 85, 90, 95, 100 };
			tempSList = { "未毕业", "刚入门", "及格", "良好", "幼儿园毕业", "小学毕业",
				"初中毕业", "高中毕业", "大学毕业", "成功毕业", "完美毕业", "终结" };
			display.showStringIfBetween(tempD, tempDList, tempSList);
			display.showText("\n");
		}

		tempI = 1;
		display.showText("&B提升建议:\n");
		if (hasUsefulAttr < 1)
		{
			display.showTextI("&B", tempI, ".&E刷取一套主词条正确的圣遗物并升到20级。\n");
			tempI++;
		}
		if (levelId == 1)
		{
			display.showTextI("&B", tempI, ".&E让胡桃进行80级突破。\n");
			tempI++;
		}
		if (weaponLevel < 90)
		{
			display.showTextI("&B", tempI, ".&E将胡桃的武器升级到90级。\n");
			tempI++;
		}
		if (skillLevel[0] < 8 || skillLevel[1] < 8 || skillLevel[2] < 8)
		{
			display.showTextI("&B", tempI, ".&E将胡桃的所有天赋升级到8级。\n");
			tempI++;
		}
		if (hasUsefulAttr / maxUsefulAttr < 0.4)
		{
			if (weaponId == 3)
			{
				display.showTextI("&B", tempI, ".&E通过圣遗物副词条获取更多暴击率、暴击伤害、百分比生命值属性。\n");
				tempI++;
			}
			else
			{
				display.showTextI("&B", tempI, ".&E通过圣遗物副词条获取更多暴击率、暴击伤害、元素精通属性。\n");
				tempI++;
			}
		}
		if (hasUsefulAttr / maxUsefulAttr >= 0.4 && skillLevel[1] == 8)
		{
			display.showTextI("&B", tempI, ".&E将胡桃的元素战技天赋升级到9级。\n");
			tempI++;	
		}
		if (hasUsefulAttr / maxUsefulAttr >= 0.4 && hasUsefulAttr / maxUsefulAttr < 0.6)
		{
			if (huTao.getAttrValue(ATTRIBUTE_CRITRATE) < 0.56)
			{
				display.showTextI("&B", tempI, ".&E通过圣遗物副词条获取更多暴击率属性。\n");
				tempI++;
			}
			if (huTao.getAttrValue(ATTRIBUTE_HP) < 26000)
			{
				display.showTextI("&B", tempI, ".&E通过圣遗物副词条获取更多百分比生命值属性。\n");
				tempI++;
			}
			if (huTao.caSingleAttrAdv(ATTRIBUTE_EM, ELEMENTAL_PYRO, false, 1.5) >
				huTao.caSingleAttrAdv(ATTRIBUTE_CRITDMG, ELEMENTAL_PYRO, false, 1.5) * 1.05)
			{
				display.showTextI("&B", tempI, ".&E通过圣遗物副词条获取更多元素精通属性。\n");
				tempI++;
			}
			if (huTao.caSingleAttrAdv(ATTRIBUTE_CRITDMG, ELEMENTAL_PYRO, false, 1.5) >
				huTao.caSingleAttrAdv(ATTRIBUTE_EM, ELEMENTAL_PYRO, false, 1.5) * 1.1)
			{
				display.showTextI("&B", tempI, ".&E通过圣遗物副词条获取更多暴击伤害属性。\n");
				tempI++;
			}
		}
		if (hasUsefulAttr / maxUsefulAttr >= 0.6 && skillLevel[0] == 8)
		{
			display.showTextI("&B", tempI, ".&E将胡桃的普通攻击天赋升级到9级。\n");
			tempI++;
		}
		if (hasUsefulAttr / maxUsefulAttr >= 0.6 && skillLevel[2] == 8)
		{
			display.showTextI("&B", tempI, ".&E将胡桃的元素爆发天赋升级到9级。\n");
			tempI++;
		}
		if (levelId == 2 && hasUsefulAttr / maxUsefulAttr >= 0.6)
		{
			display.showTextI("&B", tempI, ".&E将胡桃升级到90级。\n");
			tempI++;
		}
		if (hasUsefulAttr / maxUsefulAttr >= 0.6 && levelId == 3)
		{
			tempSList = { "多余的属性", "缺少的属性" };
			if (huTao.getAttrValue(ATTRIBUTE_CRITRATE) < 0.6)
			{
				tempSList[1] = "暴击率";
			}
			else if (huTao.getAttrValue(ATTRIBUTE_HP) < 27000)
			{
				tempSList[1] = "生命值";
			}
			else if (huTao.caSingleAttrAdv(ATTRIBUTE_EM, ELEMENTAL_PYRO, false, 1.5) >
				huTao.caSingleAttrAdv(ATTRIBUTE_CRITDMG, ELEMENTAL_PYRO, false, 1.5) * 1.1)
			{
				tempSList[1] = "元素精通";
			}
			else if (huTao.caSingleAttrAdv(ATTRIBUTE_CRITDMG, ELEMENTAL_PYRO, false, 1.5) >
				huTao.caSingleAttrAdv(ATTRIBUTE_EM, ELEMENTAL_PYRO, false, 1.5) * 1.2)
			{
				tempSList[1] = "暴击伤害";
			}

			if (tempSList[1] != "缺少的属性")
			{
				if (huTao.getAttrValue(ATTRIBUTE_CRITRATE) > 0.99)
				{
					tempSList[0] = "暴击率";
				}
				else if (huTao.getAttrValue(ATTRIBUTE_HP) > 34000)
				{
					tempSList[0] = "生命值";
				}
				else if (huTao.caSingleAttrAdv(ATTRIBUTE_EM, ELEMENTAL_PYRO, false, 1.5) <
					huTao.caSingleAttrAdv(ATTRIBUTE_CRITDMG, ELEMENTAL_PYRO, false, 1.5) * 0.8)
				{
					tempSList[0] = "元素精通";
				}
				else if (huTao.caSingleAttrAdv(ATTRIBUTE_CRITDMG, ELEMENTAL_PYRO, false, 1.5) <
					huTao.caSingleAttrAdv(ATTRIBUTE_EM, ELEMENTAL_PYRO, false, 1.5) * 0.8)
				{
					tempSList[0] = "暴击伤害";
				}
				else
				{
					tempSList[0] = "生命值";
					if (tempSList[1] == "生命值")
					{
						tempSList[0] = "元素精通";
					}
				}

				if (tempSList[0] != tempSList[1])
				{
					display.showTextI("&B", tempI, ".&E调整圣遗物的词条，将部分" +
						tempSList[0] + "属性分配给" + tempSList[1] + "属性。\n");
					tempI++;
				}
			}
			else if (skillLevel[0] < 10 || skillLevel[1] < 10 || skillLevel[2] < 10)
			{
				display.showTextI("&B", tempI, ".&E将胡桃的天赋升级到10级。\n");
				tempI++;
			}
		}
		if (tempI == 1)
		{
			display.showTextI("&B", tempI, ".&E胡桃已经毕业了，去培养其他的角色吧。\n");
		}
	}

	this->showErrorInfo(hasUsefulAttr, maxUsefulAttr);

	display.showText("\n&7");
	display.showButton('0', "退出");
	opr = display.selectButton();
}
