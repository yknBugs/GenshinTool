#pragma once

#include "Charactor.h"

//计算时未知元素类型默认为雷元素

class CharactorUi
{
private:
	Charactor inputCharaBaseAttr(string* text, bool hasATK = true, bool hasHP = false, bool hasDEF = false);
	void inputCharaEM(string* text, Charactor* charactor, bool hasTranslate = false);
	void inputCharaCrit(string* text, Charactor *charactor);
	void inputElementDMGBonus(string* text, Charactor* charactor, int elementId = 0);
	double inputSkillRate(string* text);

	//具体角色相关的函数
	bool inputWeaponPurify(string* text, double* weaponPurify);
	void inputExtraATK(string* text, Charactor* charactor, double baseATK);
	void inputExtraHP(string* text, Charactor* charactor, double baseHP);
	bool selectWeapon(string* text, int *weaponId, vector<string> weaponList);
	void showUsefulAttr(double hasUsefulAttr, int maxUsefulAttr);
	void showErrorInfo(double hasUsefulAttr, int maxUsefulAttr);

	void listAttr(Charactor charactor, Charactor emily, double skillRate,
		bool hasEM = true, bool hasTranEM = false, int elementId = 0);
	void listExpectDMG(Charactor charactor, Charactor emily, double skillRate, int elementId);

public:
	void showUi();

	void showAddBuffUi(Charactor* charactor, Charactor* emily, int elementId = 0);
	void showDeleteBuffUi(Charactor* charactor, Charactor* emily, bool showElement = true);

	void showDMGCaculatorUi();
	void showCPlaceTemplateUi();

	void showGanYuUi();
	void showHuTaoUi();
};
