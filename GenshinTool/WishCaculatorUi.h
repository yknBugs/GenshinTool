#pragma once

#define RUNTIME_CHANGERESULT 0.5
#define RUNTIME_INTERRUPT 0.5
#define RUNTIME_MAXEXPECT 10e9

#include "Display.h"
#include "WishPool.h"
#include "Data.h"

class WishCaculatorUi
{
private:
	void createTemplatePool(WishPool* wishpool, int templateId);
	bool hasSameElement(vector<string> list, string ele);
	void connectVector(vector<string>* subject, vector<string>* object);

	string showCaculatingUi(WishPool wishpool, string text, vector<string> wantItem,
		int wantCount, int hasCount, int simTime);

public:
	void showUi();

	void showTemplateSimUi();
};
