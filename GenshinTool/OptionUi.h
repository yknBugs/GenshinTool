#pragma once

#include "Display.h"
#include "Option.h"

using namespace std;

class OptionUi
{
private:
	void listOption(unsigned int chooseItem);
	bool canChooseUp(unsigned int chooseItem);
	bool canChooseDown(unsigned int chooseItem);
	unsigned int getChooseUp(unsigned int chooseItem);
	unsigned int getChooseDown(unsigned int chooseItem);

	void changeSet(unsigned int chooseItem);
	void changePercent(unsigned int chooseItem, bool isLow);
	void setPercent(unsigned int chooseItem);
	void setStringSet(unsigned int chooseItem);

	void changeNum(unsigned int chooseItem, bool isLow);
	void setNum(unsigned int chooseItem);

public:
	void showUi();
};