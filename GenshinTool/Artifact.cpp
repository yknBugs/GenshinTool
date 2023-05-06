#include "Artifact.h"

double Artifact::getMainAttrBaseValue(int mainAttr, short star)
{
	vector<double> resultNum = { 0.0, 0.0, 0.0, 0.0, 0.0 };

	switch (mainAttr)
	{
	case ATTRIBUTE_HP:
		resultNum = { 129.0, 258.0, 430.0, 645.0, 717.0 };
		return resultNum[star - 1];
	case ATTRIBUTE_ATK:
		resultNum = { 0.0, 17.0, 28.0, 42.0, 47.0 };
		return resultNum[star - 1];
	case ATTRIBUTE_ATKPER:
		resultNum = { 3.1, 4.2, 5.2, 6.3, 7.0 };
		return resultNum[star - 1];
	case ATTRIBUTE_DEFPER:
		resultNum = { 0.0, 5.2, 6.6, 7.9, 8.7 };
		return resultNum[star - 1];
	case ATTRIBUTE_HPPER:
		resultNum = { 3.1, 4.2, 5.2, 6.3, 7.0 };
		return resultNum[star - 1];
	case ATTRIBUTE_ER:
		resultNum = { 0.0, 4.7, 5.8, 7.0, 7.8 };
		return resultNum[star - 1];
	case ATTRIBUTE_EM:
		resultNum = { 0.0, 17.0, 21.0, 25.0, 28.0 };
		return resultNum[star - 1];
	case ATTRIBUTE_CRITDMG:
		resultNum = { 0.0, 0.0, 7.0, 8.4, 9.3 };
		return resultNum[star - 1];
	case ATTRIBUTE_CRITRATE:
		resultNum = { 0.0, 0.0, 3.5, 4.2, 4.7 };
		return resultNum[star - 1];
	case ATTRIBUTE_HB:
		resultNum = { 0.0, 0.0, 4.0, 4.8, 5.4 };
		return resultNum[star - 1];
	case ATTRIBUTE_DMGPHY:
		resultNum = { 0.0, 0.0, 6.6, 7.9, 8.7 };
		return resultNum[star - 1];
	case ATTRIBUTE_DMGANEMO:
	case ATTRIBUTE_DMGCRYO:
	case ATTRIBUTE_DMGDENDRO:
	case ATTRIBUTE_DMGELEC:
	case ATTRIBUTE_DMGGEO:
	case ATTRIBUTE_DMGHYDRO:
	case ATTRIBUTE_DMGPYRO:
		resultNum = { 3.1, 4.2, 5.2, 6.3, 7.0 };
		return resultNum[star - 1];
	default:
		return 0.0;
	}
}

double Artifact::getMainAttrLvUpValue(int mainAttr, short star)
{
	vector<double> resultNum = { 0.0, 0.0, 0.0, 0.0, 0.0 };

	switch (mainAttr)
	{
	case ATTRIBUTE_HP:
		resultNum = { 0.0, 0.0, 0.0, 182.875, 203.15 };
		return resultNum[star - 1];
	case ATTRIBUTE_ATK:
		resultNum = { 0.0, 0.0, 0.0, 11.875, 13.2 };
		return resultNum[star - 1];
	case ATTRIBUTE_ATKPER:
		resultNum = { 0.0, 0.0, 0.0, 1.78125, 1.98 };
		return resultNum[star - 1];
	case ATTRIBUTE_DEFPER:
		resultNum = { 0.0, 0.0, 0.0, 2.225, 2.48 };
		return resultNum[star - 1];
	case ATTRIBUTE_HPPER:
		resultNum = { 0.0, 0.0, 0.0, 1.78125, 1.98 };
		return resultNum[star - 1];
	case ATTRIBUTE_ER:
		resultNum = { 0.0, 0.0, 0.0, 1.98125, 2.2 };
		return resultNum[star - 1];
	case ATTRIBUTE_EM:
		resultNum = { 0.0, 0.0, 0.0, 7.125, 7.925 };
		return resultNum[star - 1];
	case ATTRIBUTE_CRITDMG:
		resultNum = { 0.0, 0.0, 0.0, 2.375, 2.645 };
		return resultNum[star - 1];
	case ATTRIBUTE_CRITRATE:
		resultNum = { 0.0, 0.0, 0.0, 1.1875, 1.32 };
		return resultNum[star - 1];
	case ATTRIBUTE_HB:
		resultNum = { 0.0, 0.0, 0.0, 1.375, 1.525 };
		return resultNum[star - 1];
	case ATTRIBUTE_DMGPHY:
		resultNum = { 0.0, 0.0, 0.0, 2.225, 2.48 };
		return resultNum[star - 1];
	case ATTRIBUTE_DMGANEMO:
	case ATTRIBUTE_DMGCRYO:
	case ATTRIBUTE_DMGDENDRO:
	case ATTRIBUTE_DMGELEC:
	case ATTRIBUTE_DMGGEO:
	case ATTRIBUTE_DMGHYDRO:
	case ATTRIBUTE_DMGPYRO:
		resultNum = { 1.2, 0.0, 0.0, 1.78125, 1.98 };
		return resultNum[star - 1];
	default:
		return 0.0;
	}
}

vector<double> Artifact::getSubAttrValueList(int subAttr, short star)
{
	vector<double> result;

	switch (subAttr)
	{
	case ATTRIBUTE_HP:
		switch (star)
		{
		case 1:
			result = { 24.0, 30.0 };
			return result;
		case 2:
			result = { 50.0, 61.0, 72.0 };
			return result;
		case 3:
			result = { 100.0, 115.0, 129.0, 143.0 };
			return result;
		case 4:
			result = { 167.0, 191.0, 215.0, 239.0 };
			return result;
		case 5:
			result = { 209.13, 239.00, 268.88, 298.75 };
			return result;
		default:
			result = { 0.0 };
			return result;
		}
	case ATTRIBUTE_ATK:
		switch (star)
		{
		case 1:
			result = { 2.0 };
			return result;
		case 2:
			result = { 3.0, 4.0, 5.0 };
			return result;
		case 3:
			result = { 7.0, 7.0, 8.0, 9.0 };
			return result;
		case 4:
			result = { 11.0, 12.0, 14.0, 16.0 };
			return result;
		case 5:
			result = { 13.62, 15.56, 17.51, 19.45 };
			return result;
		default:
			result = { 0.0 };
			return result;
		}
	case ATTRIBUTE_DEF:
		switch (star)
		{
		case 1:
			result = { 2.0 };
			return result;
		case 2:
			result = { 4.0, 5.0, 6.0 };
			return result;
		case 3:
			result = { 8.0, 9.0, 10.0, 11.0 };
			return result;
		case 4:
			result = { 13.0, 15.0, 17.0, 19.0 };
			return result;
		case 5:
			result = { 16.20, 18.52, 20.83, 23.15 };
			return result;
		default:
			result = { 0.0 };
			return result;
		}
	case ATTRIBUTE_ATKPER:
	case ATTRIBUTE_HPPER:
		switch (star)
		{
		case 1:
			result = { 1.2, 1.5 };
			return result;
		case 2:
			result = { 1.6, 2.0, 2.3 };
			return result;
		case 3:
			result = { 2.5, 2.8, 3.2, 3.5 };
			return result;
		case 4:
			result = { 3.3, 3.7, 4.2, 4.7 };
			return result;
		case 5:
			result = { 4.08, 4.66, 5.25, 5.83 };
			return result;
		default:
			result = { 0.0 };
			return result;
		}
	case ATTRIBUTE_DEFPER:
		switch (star)
		{
		case 1:
			result = { 1.5, 1.8 };
			return result;
		case 2:
			result = { 2.0, 2.5, 2.9 };
			return result;
		case 3:
			result = { 3.1, 3.5, 3.9, 4.4 };
			return result;
		case 4:
			result = { 4.1, 4.7, 5.3, 5.8 };
			return result;
		case 5:
			result = { 5.10, 5.83, 6.56, 7.29 };
			return result;
		default:
			result = { 0.0 };
			return result;
		}
	case ATTRIBUTE_ER:
		switch (star)
		{
		case 1:
			result = { 1.3, 1.6 };
			return result;
		case 2:
			result = { 1.8, 2.2, 2.6 };
			return result;
		case 3:
			result = { 2.7, 3.1, 3.5, 3.9 };
			return result;
		case 4:
			result = { 3.6, 4.1, 4.7, 5.2 };
			return result;
		case 5:
			result = { 4.53, 5.18, 5.83, 6.48 };
			return result;
		default:
			result = { 0.0 };
			return result;
		}
	case ATTRIBUTE_EM:
		switch (star)
		{
		case 1:
			result = { 5.0, 6.0 };
			return result;
		case 2:
			result = { 7.0, 8.0, 9.0 };
			return result;
		case 3:
			result = { 10.0, 11.0, 13.0, 14.0 };
			return result;
		case 4:
			result = { 13.0, 15.0, 17.0, 19.0 };
			return result;
		case 5:
			result = { 16.32, 18.65, 20.98, 23.31 };
			return result;
		default:
			result = { 0.0 };
			return result;
		}
	case ATTRIBUTE_CRITDMG:
		switch (star)
		{
		case 1:
			result = { 1.6, 1.9 };
			return result;
		case 2:
			result = { 2.2, 2.6, 3.1 };
			return result;
		case 3:
			result = { 3.3, 3.7, 4.2, 4.7 };
			return result;
		case 4:
			result = { 4.4, 5.0, 5.6, 6.2 };
			return result;
		case 5:
			result = { 5.44, 6.22, 6.99, 7.77 };
			return result;
		default:
			result = { 0.0 };
			return result;
		}
	case ATTRIBUTE_CRITRATE:
		switch (star)
		{
		case 1:
			result = { 0.8, 1.0 };
			return result;
		case 2:
			result = { 1.1, 1.3, 1.6 };
			return result;
		case 3:
			result = { 1.6, 1.9, 2.1, 2.3 };
			return result;
		case 4:
			result = { 2.2, 2.5, 2.8, 3.1 };
			return result;
		case 5:
			result = { 2.72, 3.11, 3.50, 3.89 };
			return result;
		default:
			result = { 0.0 };
			return result;
		}
	default:
		result = { 0.0 };
		return result;
	}
}

bool Artifact::getAttrIsPercent(int attrId)
{
	if (attrId == ATTRIBUTE_ATK || attrId == ATTRIBUTE_DEF || attrId == ATTRIBUTE_HP ||
		attrId == ATTRIBUTE_EM  || attrId == ATTRIBUTE_BUFF_EXTRADMG)
	{
		return false;
	}
	else
	{
		return true;
	}
}

string Artifact::attrIdToString(int attrId)
{
	string resultList[] =
	{
		"",
		"生命值",
		"攻击力",
		"防御力",
		"生命值",
		"攻击力",
		"防御力",
		"元素充能效率",
		"元素精通",
		"暴击率",
		"暴击伤害",
		"治疗加成",
		"受治疗加成",
		"冷却缩减",
		"护盾强效",
		"火元素伤害加成",
		"水元素伤害加成",
		"草元素伤害加成",
		"雷元素伤害加成",
		"风元素伤害加成",
		"冰元素伤害加成",
		"岩元素伤害加成",
		"物理伤害加成",
		"火元素抗性",
		"水元素抗性",
		"草元素抗性",
		"雷元素抗性",
		"风元素抗性",
		"冰元素抗性",
		"岩元素抗性",
		"物理抗性",
		"提高造成的伤害",
		"造成的伤害提高",
		"元素反应系数提高",
		"伤害提升"
	};
	return resultList[attrId];
}

int Artifact::randMainAttr(int pos)
{
	WeightSys weightSys;
	RandEngine randEngine;
	if (pos == ARTIFACTPOS_FLOWER)
	{
		return ATTRIBUTE_HP;
	}
	else if (pos == ARTIFACTPOS_WING)
	{
		return ATTRIBUTE_ATK;
	}
	else if (pos == ARTIFACTPOS_SAND)
	{
		weightSys.addObject(ATTRIBUTE_ATKPER, 2666);
		weightSys.addObject(ATTRIBUTE_HPPER, 2668);
		weightSys.addObject(ATTRIBUTE_DEFPER, 2666);
		weightSys.addObject(ATTRIBUTE_ER, 1000);
		weightSys.addObject(ATTRIBUTE_EM, 1000);
		return randEngine.randObject(weightSys);
	}
	else if (pos == ARTIFACTPOS_CUP)
	{
		weightSys.addObject(ATTRIBUTE_ATKPER, 2125);
		weightSys.addObject(ATTRIBUTE_HPPER, 2125);
		weightSys.addObject(ATTRIBUTE_DEFPER, 2000);
		weightSys.addObject(ATTRIBUTE_EM, 250);
		weightSys.addObject(ATTRIBUTE_DMGANEMO, 500);
		weightSys.addObject(ATTRIBUTE_DMGCRYO, 500);
		weightSys.addObject(ATTRIBUTE_DMGPHY, 500);
		weightSys.addObject(ATTRIBUTE_DMGELEC, 500);
		weightSys.addObject(ATTRIBUTE_DMGGEO, 500);
		weightSys.addObject(ATTRIBUTE_DMGHYDRO, 500);
		weightSys.addObject(ATTRIBUTE_DMGPYRO, 500);
		return randEngine.randObject(weightSys);
	}
	else if (pos == ARTIFACTPOS_HEAD)
	{
		weightSys.addObject(ATTRIBUTE_ATKPER, 2200);
		weightSys.addObject(ATTRIBUTE_HPPER, 2200);
		weightSys.addObject(ATTRIBUTE_DEFPER, 2200);
		weightSys.addObject(ATTRIBUTE_HB, 1000);
		weightSys.addObject(ATTRIBUTE_EM, 400);
		weightSys.addObject(ATTRIBUTE_CRITDMG, 1000);
		weightSys.addObject(ATTRIBUTE_CRITRATE, 1000);
		return randEngine.randObject(weightSys);
	}

	return 0;
}

int Artifact::randSubAttr(int mainAttr, vector<int> subAttr)
{
	unsigned int i = 0;
	RandEngine randEngine;
	WeightSys weightSys;
	weightSys.addObject(ATTRIBUTE_ATK, 150);
	weightSys.addObject(ATTRIBUTE_HP, 150);
	weightSys.addObject(ATTRIBUTE_DEF, 150);
	weightSys.addObject(ATTRIBUTE_ATKPER, 100);
	weightSys.addObject(ATTRIBUTE_HPPER, 100);
	weightSys.addObject(ATTRIBUTE_DEFPER, 100);
	weightSys.addObject(ATTRIBUTE_ER, 100);
	weightSys.addObject(ATTRIBUTE_EM, 100);
	weightSys.addObject(ATTRIBUTE_CRITDMG, 75);
	weightSys.addObject(ATTRIBUTE_CRITRATE, 75);
	weightSys.clearObject(mainAttr);
	for (i = 0; i < subAttr.size(); i++)
	{
		weightSys.clearObject(subAttr[i]);
	}
	return randEngine.randObject(weightSys);
}

Artifact::Artifact(string name, int pos, short star, double fullSubAttrP)
{
	unsigned int subAttrSize = 0;
	unsigned int i = 0;
	RandEngine randEngine;

	this->name = name;
	this->pos = pos;
	this->star = star;
	this->level = 0;

	this->mainAttrId = this->randMainAttr(pos);
	this->mainAttrValue = this->getMainAttrBaseValue(this->mainAttrId, star);

	if (star >= 2)
	{
		subAttrSize = star - 2;
		if (randEngine.randSucceed(fullSubAttrP) == true)
		{
			subAttrSize++;
		}
	}

	for (i = 0; i < subAttrSize; i++)
	{
		int tempI = this->randSubAttr(this->mainAttrId, this->subAttrId);
		vector<double> tempD = this->getSubAttrValueList(tempI, star);
		this->subAttrId.push_back(tempI);
		this->subAttrValue.push_back(tempD[randEngine.random(0, (int)tempD.size() - 1)]);
	}
}

void Artifact::levelUp()
{
	RandEngine randEngine;

	if (this->level < (unsigned int)this->star * 4)
	{
		this->level++;
		this->mainAttrValue += this->getMainAttrLvUpValue(this->mainAttrId, this->star);
		if (this->level % 4 == 0)
		{
			if (this->subAttrId.size() < 4)
			{
				int tempI = this->randSubAttr(this->mainAttrId, this->subAttrId);
				vector<double> tempD = this->getSubAttrValueList(tempI, star);
				this->subAttrId.push_back(tempI);
				this->subAttrValue.push_back(tempD[randEngine.random(0, (int)tempD.size() - 1)]);
			}
			else
			{
				int chooseAttrPos = randEngine.random(0, 3);
				vector<double> upLevelList = this->getSubAttrValueList(this->subAttrId[chooseAttrPos], this->star);
				double upLevel = upLevelList[randEngine.random(0, (int)upLevelList.size() - 1)];
				this->subAttrValue[chooseAttrPos] += upLevel;
			}
		}
	}
}

string Artifact::getName()
{
	return this->name;
}

unsigned int Artifact::getLevel()
{
	return this->level;
}

int Artifact::getPos()
{
	return this->pos;
}

short Artifact::getStar()
{
	return this->star;
}

int Artifact::getMainAttrId()
{
	return this->mainAttrId;
}

double Artifact::getMainAttrValue()
{
	return this->mainAttrValue;
}

int Artifact::getSubAttrId(unsigned int num)
{
	if (num < this->subAttrId.size())
	{
		return this->subAttrId[num];
	}
	else
	{
		return 0;
	}
}

double Artifact::getSubAttrValue(unsigned int num)
{
	if(num < this->subAttrValue.size())
	{
		return this->subAttrValue[num];
	}
	else
	{
		return 0.0;
	}
}

bool Artifact::operator<(Artifact object)
{
	if (this->star < object.star)
	{
		return true;
	}
	else if (this->level < object.level)
	{
		return true;
	}
	else if (this->pos < object.pos)
	{
		return true;
	}

	return false;
}

bool Artifact::operator>(Artifact object)
{
	if (this->star > object.star)
	{
		return true;
	}
	else if (this->level > object.level)
	{
		return true;
	}
	else if (this->pos > object.pos)
	{
		return true;
	}

	return false;
}
