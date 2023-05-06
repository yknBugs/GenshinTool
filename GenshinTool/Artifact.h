#pragma once

//本文件定义圣遗物系统
//为方便，所有的百分比词条全部显示为显示的数值，如52%就写做52而不是0.52

#include <string>
#include <vector>

#include "RandEngine.h"

using namespace std;

#define ARTIFACTPOS_FLOWER 1 //花部位
#define ARTIFACTPOS_WING 2 //羽毛部位
#define ARTIFACTPOS_SAND 3 //沙漏部位
#define ARTIFACTPOS_CUP 4 //杯子部位
#define ARTIFACTPOS_HEAD 5 //头部位

#define ATTRIBUTE_HP 1 //生命值
#define ATTRIBUTE_ATK 2 //攻击力
#define ATTRIBUTE_DEF 3 //防御力
#define ATTRIBUTE_HPPER 4 //百分比生命值
#define ATTRIBUTE_ATKPER 5 //百分比攻击力
#define ATTRIBUTE_DEFPER 6 //百分比防御力
#define ATTRIBUTE_ER 7 //元素充能效率
#define ATTRIBUTE_EM 8 //元素精通
#define ATTRIBUTE_CRITRATE 9 //暴击率
#define ATTRIBUTE_CRITDMG 10 //暴击伤害
#define ATTRIBUTE_HB 11 //治疗加成
#define ATTRIBUTE_IHB 12 //受治疗加成
#define ATTRIBUTE_CDRE 13 //冷却缩减
#define ATTRIBUTE_SS 14 //护盾强效
#define ATTRIBUTE_DMGPYRO 15 //火元素伤害加成
#define ATTRIBUTE_DMGHYDRO 16 //水元素伤害加成
#define ATTRIBUTE_DMGDENDRO 17 //草元素伤害加成
#define ATTRIBUTE_DMGELEC 18 //雷元素伤害加成
#define ATTRIBUTE_DMGANEMO 19 //风元素伤害加成
#define ATTRIBUTE_DMGCRYO 20 //冰元素伤害加成
#define ATTRIBUTE_DMGGEO 21 //岩元素伤害加成
#define ATTRIBUTE_DMGPHY 22 //物理伤害加成
#define ATTRIBUTE_RESPYRO 23 //火元素抗性
#define ATTRIBUTE_RESHYDRO 24 //水元素抗性
#define ATTRIBUTE_RESDENDRO 25 //草元素抗性
#define ATTRIBUTE_RESELEC 26 //雷元素抗性
#define ATTRIBUTE_RESANEMO 27 //风元素抗性
#define ATTRIBUTE_RESCRYO 28 //冰元素抗性
#define ATTRIBUTE_RESGEO 29 //岩元素抗性
#define ATTRIBUTE_RESPHY 30 //物理抗性

#define ATTRIBUTE_BUFF_EXTRADMG 31 //技能倍率乘区buff
#define ATTRIBUTE_BUFF_DMGBONUS 32 //增伤乘区buff
#define ATTRIBUTE_BUFF_EXTRAEM 33  //元素反应系数提高
#define ATTRIBUTE_BUFF_CHANGEDMG 34//独立乘区buff

class Artifact
{
private:
	short star;
	unsigned int level;
	string name;
	int pos; //部位[花，羽毛，沙漏，杯子，头]

	int mainAttrId;
	double mainAttrValue;

	vector<int> subAttrId;
	vector<double> subAttrValue;

	int randMainAttr(int pos);
	int randSubAttr(int mainAttr, vector<int> subAttr);

public:
	Artifact(string name = "奇怪的圣遗物", int pos = ARTIFACTPOS_FLOWER, short star = 5, double fullSubAttrP = 0.25);

	void levelUp();

	string getName();
	unsigned int getLevel();
	int getPos();
	short getStar();
	int getMainAttrId();
	double getMainAttrValue();
	int getSubAttrId(unsigned int num);
	double getSubAttrValue(unsigned int num);

	bool operator < (Artifact object);
	bool operator > (Artifact object);

	bool getAttrIsPercent(int attrId);
	string attrIdToString(int attrId);
	double getMainAttrBaseValue(int mainAttr, short star);
	double getMainAttrLvUpValue(int mainAttr, short star);
	vector<double> getSubAttrValueList(int subAttr, short star);
};