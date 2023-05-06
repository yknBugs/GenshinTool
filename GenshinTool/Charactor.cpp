#include "Charactor.h"

Charactor::Charactor(unsigned int level, double baseATK, double baseHP, double baseDEF)
{
	int i = 0;
	this->level = level;
	this->baseATK = baseATK;
	this->baseHP = baseHP;
	this->baseDEF = baseDEF;
	for (i = 0; i < 34; i++)
	{
		this->extraAttr.push_back(0.0);
	}
}

double Charactor::translateEM(int id, double EM)
{
	if (id == ELEMENT_DMGBONUS)
	{
		return (2.78 * EM) / (EM + 1400.0);
	}
	else if (id == ELEMENT_EXTRADMG)
	{
		return (16.0 * EM) / (EM + 2000.0);
	}
	else if (id == ELEMENT_SHEILD)
	{
		return (4.44 * EM) / (EM + 1400.0);
	}

	return 0.0;
}

double Charactor::getAttrValue(int attrId)
{
	if (attrId == ATTRIBUTE_HP)
	{
		return this->baseHP * this->getExtraAttr(ATTRIBUTE_HPPER) 
			+ this->getExtraAttr(ATTRIBUTE_HP) + this->baseHP;
	}
	else if (attrId == ATTRIBUTE_ATK)
	{
		return this->baseATK * this->getExtraAttr(ATTRIBUTE_ATKPER) 
			+ this->getExtraAttr(ATTRIBUTE_ATK) + this->baseATK;
	}
	else if (attrId == ATTRIBUTE_DEF)
	{
		return this->baseDEF * this->getExtraAttr(ATTRIBUTE_DEFPER) 
			+ this->getExtraAttr(ATTRIBUTE_DEF) + this->baseDEF;
	}
	else if (attrId == ATTRIBUTE_ER)
	{
		return this->getExtraAttr(ATTRIBUTE_ER) + 1.0;
	}
	else if (attrId == ATTRIBUTE_CRITRATE)
	{
		return this->getExtraAttr(ATTRIBUTE_CRITRATE) + 0.05;
	}
	else if (attrId == ATTRIBUTE_CRITDMG)
	{
		return this->getExtraAttr(ATTRIBUTE_CRITDMG) + 0.5;
	}
	else if (attrId >= 8 && attrId <= 30)
	{
		return this->getExtraAttr(attrId);
	}

	return 0.0;
}

double Charactor::caculateDMG(double skillRate, bool hasCritDMG, int elementId, Charactor enimy, double elementType)
{
	double result = this->getAttrValue(ATTRIBUTE_ATK) * skillRate + this->getExtraAttr(ATTRIBUTE_BUFF_EXTRADMG);
	if (hasCritDMG == true)
	{
		result *= this->getDMGBonusRate(DMGPLUSAREA_CRITDMG, elementId);
	}

	result *= this->getDMGBonusRate(DMGPLUSAREA_DMGBONUS, elementId);

	if (elementType > 1.4)
	{
		result *= elementType;
		result *= this->getDMGBonusRate(DMGPLUSAREA_ELEMENT, elementId);
	}

	result *= this->getDMGBonusRate(DMGPLUSAREA_RES, elementId, enimy);
	result *= this->getDMGBonusRate(DMGPLUSAREA_DEF, elementId, enimy);

	return result;
}

double Charactor::caculateAveDMG(double skillRate, int elementId, Charactor enimy, double elementType)
{
	double critDMG = this->caculateDMG(skillRate, true, elementId, enimy, elementType);
	double noCritDMG = this->caculateDMG(skillRate, false, elementId, enimy, elementType);
	double critRate = this->getAttrValue(ATTRIBUTE_CRITRATE);

	if (critRate > 1.0)
	{
		critRate = 1.0;
	}
	if (critRate < 0.0)
	{
		critRate = 0.0;
	}

	double result = critDMG * critRate + noCritDMG * (1.0 - critRate);

	return result;
}

double Charactor::caSingleAttrAdv(int attrId, int elementId, bool considerBurst, double elementType)
{
	Artifact artifact;
	Charactor emily(this->level, 10, 1000, (double)this->level * 5.0 + 500.0);
	vector<double> tempDList = artifact.getSubAttrValueList(attrId, 5);
	double singleAttrValue = tempDList[tempDList.size() - 1];
	if (artifact.getAttrIsPercent(attrId) == true)
	{
		singleAttrValue /= 100.0;
	}
	if (considerBurst == true)
	{
		double withoutBuff = this->caculateAveDMG(1.0, elementId, emily, elementType);
		this->addBuff("qpeofhoubjvs", attrId, singleAttrValue);
		double withBuff = this->caculateAveDMG(1.0, elementId, emily, elementType);
		this->clearBuff("qpeofhoubjvs");

		return withBuff / withoutBuff - 1.0;
	}
	else
	{
		double withoutBuff = this->caculateDMG(1.0, true, elementId, emily, elementType);
		this->addBuff("eiqobkqbwjkf", attrId, singleAttrValue);
		double withBuff = this->caculateDMG(1.0, true, elementId, emily, elementType);
		this->clearBuff("eiqobkqbwjkf");

		return withBuff / withoutBuff - 1.0;
	}
}

double Charactor::caculateEMDMG(int elementId, Charactor enimy)
{
	double DMGBonus = this->translateEM(ELEMENT_EXTRADMG, this->getAttrValue(ATTRIBUTE_EM))
		+ this->getExtraAttr(ATTRIBUTE_BUFF_EXTRAEM) + 1.0;
	double baseDMG = this->getEMBaseDMG(this->level);

	if (elementId == ELEMENT_SUPERCON)
	{
		double emilyRES = this->getDMGBonusRate(DMGPLUSAREA_RES, ELEMENTAL_CRYO, enimy);
		return baseDMG * DMGBonus * emilyRES;
	}
	if (elementId == ELEMENT_SWIRL_PYRO)
	{
		double emilyRES = this->getDMGBonusRate(DMGPLUSAREA_RES, ELEMENTAL_PYRO, enimy);
		return baseDMG * DMGBonus * emilyRES * 1.2;
	}
	if (elementId == ELEMENT_SWIRL_HYDRO)
	{
		double emilyRES = this->getDMGBonusRate(DMGPLUSAREA_RES, ELEMENTAL_HYDRO, enimy);
		return baseDMG * DMGBonus * emilyRES * 1.2;
	}
	if (elementId == ELEMENT_SWIRL_ELECTRO)
	{
		double emilyRES = this->getDMGBonusRate(DMGPLUSAREA_RES, ELEMENTAL_ELECTRO, enimy);
		return baseDMG * DMGBonus * emilyRES * 1.2;
	}
	if (elementId == ELEMENT_SWIRL_CRYO)
	{
		double emilyRES = this->getDMGBonusRate(DMGPLUSAREA_RES, ELEMENTAL_CRYO, enimy);
		return baseDMG * DMGBonus * emilyRES * 1.2;
	}
	if (elementId == ELEMENT_ELECHAR)
	{
		double emilyRES = this->getDMGBonusRate(DMGPLUSAREA_RES, ELEMENTAL_ELECTRO, enimy);
		return baseDMG * DMGBonus * emilyRES * 2.4;
	}
	if (elementId == ELEMENT_OVERLOAD)
	{
		double emilyRES = this->getDMGBonusRate(DMGPLUSAREA_RES, ELEMENTAL_PYRO, enimy);
		return baseDMG * DMGBonus * emilyRES * 4.0;
	}
	if (elementId == ELEMENT_SHUTTER)
	{
		double emilyRES = this->getDMGBonusRate(DMGPLUSAREA_RES, ELEMENTAL_PHYSICAL, enimy);
		return baseDMG * DMGBonus * emilyRES * 3.0;
	}

	return baseDMG * DMGBonus;
}

double Charactor::caculateEMDMG(int elementId, Charactor enimy, int elementType)
{
	double DMGBonus = this->translateEM(ELEMENT_EXTRADMG, this->getAttrValue(ATTRIBUTE_EM))
		+ this->getExtraAttr(ATTRIBUTE_BUFF_EXTRAEM) + 1.0;
	double emilyRES = this->getDMGBonusRate(DMGPLUSAREA_RES, elementType, enimy);
	double baseDMG = this->getEMBaseDMG(this->level);

	if (elementId == ELEMENT_SUPERCON)
	{
		return baseDMG * DMGBonus * emilyRES;
	}
	if (elementId == ELEMENT_SWIRL)
	{
		return baseDMG * DMGBonus * emilyRES * 1.2;
	}
	if (elementId == ELEMENT_ELECHAR)
	{
		return baseDMG * DMGBonus * emilyRES * 2.4;
	}
	if (elementId == ELEMENT_OVERLOAD)
	{
		return baseDMG * DMGBonus * emilyRES * 4.0;
	}
	if (elementId == ELEMENT_SHUTTER)
	{
		return baseDMG * DMGBonus * emilyRES * 3.0;
	}

	return baseDMG * DMGBonus;
}

void Charactor::addBuff(string buffName, int buffId, double buffValue)
{
	this->buffName.push_back(buffName);
	this->buffId.push_back(buffId);
	this->buffValue.push_back(buffValue);
	this->extraAttr[buffId - 1] += buffValue;
}

void Charactor::clearBuff(string buffName)
{
	int i = 0;
	for (i = 0; i < (int)this->buffName.size(); i++)
	{
		if (this->buffName[i] == buffName)
		{
			this->extraAttr[this->buffId[i] - 1] -= this->buffValue[i];
			this->buffName.erase(this->buffName.begin() + i, this->buffName.begin() + i + 1);
			this->buffId.erase(this->buffId.begin() + i, this->buffId.begin() + i + 1);
			this->buffValue.erase(this->buffValue.begin() + i, this->buffValue.begin() + i + 1);
			i--;
		}
	}
}

int Charactor::getBuffAttrId(string buffName)
{
	int i = 0;
	for (i = 0; i < (int)this->buffName.size(); i++)
	{
		if (this->buffName[i] == buffName)
		{
			return this->buffId[i];
		}
	}
	return 0;
}

double Charactor::getBuffAttrValue(string buffName)
{
	int i = 0;
	double result = 0.0;
	for (i = 0; i < (int)this->buffName.size(); i++)
	{
		if (this->buffName[i] == buffName)
		{
			result += this->buffValue[i];
		}
	}
	return result;
}

unsigned int Charactor::getBuffLength()
{
	return (unsigned int)this->buffName.size();
}

string Charactor::getBuffName(unsigned int pos)
{
	return this->buffName[pos];
}

int Charactor::getBuffId(unsigned int pos)
{
	return this->buffId[pos];
}

double Charactor::getBuffValue(unsigned int pos)
{
	return this->buffValue[pos];
}

void Charactor::deleteBuff(unsigned int pos)
{
	this->extraAttr[this->buffId[pos] - 1] -= this->buffValue[pos];
	this->buffName.erase(this->buffName.begin() + pos, this->buffName.begin() + pos + 1);
	this->buffId.erase(this->buffId.begin() + pos, this->buffId.begin() + pos + 1);
	this->buffValue.erase(this->buffValue.begin() + pos, this->buffValue.begin() + pos + 1);
}

double Charactor::getDMGBonusRate(int areaId, int elementId)
{
	if (areaId == DMGPLUSAREA_ATK)
	{
		return this->getAttrValue(ATTRIBUTE_ATK) / this->baseATK;
	}
	else if (areaId == DMGPLUSAREA_CRITDMG)
	{
		return this->getAttrValue(ATTRIBUTE_CRITDMG) + 1.0;
	}
	else if (areaId == DMGPLUSAREA_DMGBONUS)
	{
		return this->getAttrValue(ATTRIBUTE_DMGPYRO + elementId - 1)
			+ this->getExtraAttr(ATTRIBUTE_BUFF_DMGBONUS) + 1.0;
	}
	else if (areaId == DMGPLUSAREA_ELEMENT)
	{
		return this->translateEM(ELEMENT_DMGBONUS, this->getExtraAttr(ATTRIBUTE_EM))
			+ this->getExtraAttr(ATTRIBUTE_BUFF_EXTRAEM) + 1.0;
	}

	return 0.0;
}

double Charactor::getDMGBonusRate(int areaId, int elementId, double skillRate)
{
	if (areaId == DMGPLUSAREA_ATK || areaId == DMGPLUSAREA_CRITDMG ||
		areaId == DMGPLUSAREA_DMGBONUS || areaId == DMGPLUSAREA_ELEMENT)
	{
		return this->getDMGBonusRate(areaId, elementId);
	}
	else if (areaId == DMGPLUSAREA_SKILLRATE)
	{
		return this->getExtraAttr(ATTRIBUTE_BUFF_EXTRADMG) / this->getAttrValue(ATTRIBUTE_ATK) + skillRate;
	}

	return 0.0;
}

double Charactor::getDMGBonusRate(int areaId, int elementId, Charactor enimy)
{
	if (areaId == DMGPLUSAREA_ATK || areaId == DMGPLUSAREA_CRITDMG ||
		areaId == DMGPLUSAREA_DMGBONUS || areaId == DMGPLUSAREA_ELEMENT)
	{
		return this->getDMGBonusRate(areaId, elementId);
	}
	else if (areaId == DMGPLUSAREA_RES)
	{
		double enimyRES = enimy.getExtraAttr(ATTRIBUTE_RESPYRO + elementId - 1);
		if (enimyRES < 0)
		{
			return 1.0 - enimyRES / 2.0;
		}
		else if (enimyRES >= 0 && enimyRES < 0.75)
		{
			return 1.0 - enimyRES;
		}
		else if (enimyRES >= 0.75)
		{
			return 1.0 / (4.0 * enimyRES + 1.0);
		}
	}
	else if (areaId == DMGPLUSAREA_DEF)
	{
		return (5.0 * this->level + 500.0) / (5.0 * this->level + enimy.getAttrValue(ATTRIBUTE_DEF) + 500.0);
	}

	return 0.0;
}

double Charactor::getEMBaseDMG(unsigned int level)
{
	double baseDMG[90] = { 8.6, 9.3, 10.0, 10.6, 11.3, 12.3, 13.3, 14.4, 15.7, 17.1,
			18.6, 20.3, 22.2, 24.3, 26.9, 29.5, 32.2, 34.9, 37.6, 40.3,
			43.1, 45.9, 48.6, 51.4, 54.2, 56.6, 59.1, 61.5, 64.9, 68.1,
			71.3, 74.5, 77.7, 80.9, 84.6, 88.3, 92.0, 95.9, 99.8, 103.7,
			107.7, 112.1, 116.8, 121.7, 128.0, 134.3, 140.8, 147.5, 154.5, 161.8,
			168.4, 175.3, 182.2, 189.3, 199.3, 208.2, 217.2, 226.5, 236.3, 246.4,
			256.8, 269.6, 282.8, 296.3, 312.2, 325.7, 339.7, 353.9, 368.3, 382.8,
			397.4, 412.3, 425.6, 438.9, 457.1, 473.4, 489.7, 505.6, 522.4, 538.7,
			555.0, 571.5, 588.2, 605.1, 626.9, 644.5, 662.7, 681.7, 702.5, 723.4 };
	unsigned int lvl = level;

	if (level == 0)
	{
		lvl = this->level;
	}

	if (level > 90)
	{
		return 750.0;
	}

	return baseDMG[lvl - 1];
}

double Charactor::getUsefulAttrCount(vector<int> attrList)
{
	Artifact artifact;
	double result = 0.0;
	int i = 0;

	for (i = 0; i < (int)attrList.size(); i++)
	{
		if (attrList[i] == ATTRIBUTE_ATKPER)
		{
			double extraAttrValue = this->getExtraAttr(ATTRIBUTE_ATK);
			extraAttrValue /= this->baseATK;
			extraAttrValue += this->getExtraAttr(ATTRIBUTE_ATKPER);
			double singleValue = artifact.getSubAttrValueList(ATTRIBUTE_ATKPER, 5)[3] / 100;
			result = extraAttrValue / singleValue + result;
		}
		else if (attrList[i] == ATTRIBUTE_HPPER)
		{
			double extraAttrValue = this->getExtraAttr(ATTRIBUTE_HP);
			extraAttrValue /= this->baseHP;
			extraAttrValue += this->getExtraAttr(ATTRIBUTE_HPPER);
			double singleValue = artifact.getSubAttrValueList(ATTRIBUTE_HPPER, 5)[3] / 100;
			result = extraAttrValue / singleValue + result;
		}
		else if (attrList[i] == ATTRIBUTE_DEFPER)
		{
			double extraAttrValue = this->getExtraAttr(ATTRIBUTE_DEF);
			extraAttrValue /= this->baseDEF;
			extraAttrValue += this->getExtraAttr(ATTRIBUTE_DEFPER);
			double singleValue = artifact.getSubAttrValueList(ATTRIBUTE_DEFPER, 5)[3] / 100;
			result = extraAttrValue / singleValue + result;
		}
		else
		{
			double extraAttrValue = this->getExtraAttr(attrList[i]); //当前角色获得的属性数值
			double singleValue = artifact.getSubAttrValueList(attrList[i], 5)[3]; //圣遗物副属性的最大词条数值
			if (artifact.getAttrIsPercent(attrList[i]) == true)
			{
				singleValue /= 100;
			}

			result = extraAttrValue / singleValue + result;
		}
	}

	return result;
}

double Charactor::getUsefulAttrCount(int attrList)
{
	vector<int> temp = { attrList };
	return this->getUsefulAttrCount(temp);
}

double Charactor::getExtraAttr(int attrId)
{
	return this->extraAttr[attrId - 1];
}

unsigned int Charactor::getLevel()
{
	return this->level;
}

double Charactor::getBaseATK()
{
	return this->baseATK;
}

double Charactor::getBaseHP()
{
	return this->baseHP;
}

double Charactor::getBaseDEF()
{
	return this->baseDEF;
}
