#pragma once

//本文件定义角色
//为方便，所有的百分比全部显示为真实数值，如52%就写做0.52而不是52

#include "Artifact.h"

#define ELEMENT_DMGBONUS 1  //增幅反应
#define ELEMENT_EXTRADMG 2  //剧变反应
#define ELEMENT_SHEILD 3    //结晶反应
#define ELEMENT_SUPERCON 11 //超导反应
#define ELEMENT_SWIRL 12	//扩散反应
#define ELEMENT_ELECHAR 13  //感电反应
#define ELEMENT_OVERLOAD 14 //超载反应
#define ELEMENT_SHUTTER 15	//碎冰反应
#define ELEMENT_SWIRL_PYRO 51		//火扩散反应
#define ELEMENT_SWIRL_HYDRO 52		//水扩散反应
#define ELEMENT_SWIRL_ELECTRO 53	//雷扩散反应
#define ELEMENT_SWIRL_CRYO 54		//冰扩散反应

#define DMGPLUSAREA_ATK 1 //攻击力乘区
#define DMGPLUSAREA_SKILLRATE 2 //技能倍率乘区
#define DMGPLUSAREA_CRITDMG 3 //暴击乘区
#define DMGPLUSAREA_DMGBONUS 4 //增伤乘区
#define DMGPLUSAREA_ELEMENT 5 //元素反应乘区
#define DMGPLUSAREA_RES 6 //抗性乘区
#define DMGPLUSAREA_DEF 7 //防御力乘区

#define ELEMENTAL_PYRO 1 //火元素
#define ELEMENTAL_HYDRO 2 //水元素
#define ELEMENTAL_DENDRO 3 //草元素
#define ELEMENTAL_ELECTRO 4 //雷元素
#define ELEMENTAL_ANEMO 5 //风元素
#define ELEMENTAL_CRYO 6 //冰元素
#define ELEMENTAL_GEO 7 //岩元素
#define ELEMENTAL_PHYSICAL 8 //物理

class Charactor
{
private:
	unsigned int level;
	double baseATK;  //基础攻击力
	double baseHP;   //基础生命值
	double baseDEF;  //基础防御力
	vector<double> extraAttr;  //额外的属性

	vector<string> buffName;
	vector<int> buffId;
	vector<double> buffValue;

public:
	Charactor(unsigned int level = 1, double baseATK = 10.0, double baseHP = 1000.0, double baseDEF = 100.0);

	//将元素精通属性转化为具体的伤害提示百分比
	double translateEM(int id, double EM);
	//计算指定属性在面板上显示的具体数值
	double getAttrValue(int attrId);
	//计算伤害，参数为:技能倍率，是否暴击，伤害的元素类型，敌人，元素反应基础倍率[1.5或2]
	double caculateDMG(double skillRate, bool hasCritDMG, int elementId, Charactor enimy, double elementType = 1.0);
	//计算平均伤害期望（暴击率为权重），参数为:技能倍率，伤害的元素类型，敌人，元素反应基础倍率[1.5或2]
	double caculateAveDMG(double skillRate, int elementId, Charactor enimy, double elementType = 1.0);
	//计算一个圣遗物副词条带来的伤害提升，参数为:属性id，伤害的元素类型，是否考虑暴击伤害期望，元素反应基础倍率[1.5或2]
	double caSingleAttrAdv(int attrId, int elementId, bool considerBurst = false, double elementType = 1.0);
	//计算元素反应造成的额外伤害，参数为元素反应类型，敌人
	double caculateEMDMG(int elementId, Charactor enimy);
	//计算元素反应造成的额外伤害，参数为元素反应类型，敌人，伤害的元素类型
	double caculateEMDMG(int elementId, Charactor enimy, int elementType);

	void addBuff(string buffName, int buffId, double buffValue);
	void clearBuff(string buffName);
	int getBuffAttrId(string buffName);
	double getBuffAttrValue(string buffName);
	unsigned int getBuffLength();
	string getBuffName(unsigned int pos);
	int getBuffId(unsigned int pos);
	double getBuffValue(unsigned int pos);
	void deleteBuff(unsigned int pos);

	//获取各个乘区的数值，参数为:乘区id，玩家造成伤害的元素id
	double getDMGBonusRate(int areaId, int elementId);
	//获取各个乘区的数值，参数为:乘区id，玩家造成伤害的元素id，技能倍率
	double getDMGBonusRate(int areaId, int elementId, double skillRate);
	//获取各个乘区的数值，参数为:乘区id，玩家造成伤害的元素id，敌人
	double getDMGBonusRate(int areaId, int elementId, Charactor enimy);
	//获取剧变元素反应的基础伤害
	double getEMBaseDMG(unsigned int level = 0);

	//获取buff中转化成圣遗物的有效词条的个数
	double getUsefulAttrCount(vector<int> attrList);
	double getUsefulAttrCount(int attrList);

	//获取buff和装备提供的额外属性
	double getExtraAttr(int attrId);
	unsigned int getLevel();
	double getBaseATK();
	double getBaseHP();
	double getBaseDEF();
};