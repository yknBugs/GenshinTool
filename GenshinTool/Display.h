#pragma once

//本文件控制屏幕上的文字显示

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>
#include <ShlObj.h>
#include <conio.h>

#include "RandEngine.h"

using namespace std;

class Display
{
private:
	static COORD current;
	static vector<char> buttonOpr;
	static vector<COORD> buttonPos;
	static vector<unsigned int> buttonLength;
	std::chrono::system_clock::time_point startTime;

	void changeCursor(char c);
	bool hasCharInString(string text, char str);

public:
	Display();

	void clear();

	void out(string str);
	//显示文字，使用"&+数字"改变文字颜色，使用"#"替代参数
	void showText(string str, bool toDefault = false);
	void createText(string str, int x, int y);
	void clearText(unsigned int length, int x, int y);

	void showTextC(char c);
	void showTextC(char c, int color);
	void showTextC(string str1, char c, string str2, bool toDefault = false);
	void showTextC(string str, vector<char> p, bool toDefault = false);
	void showTextI(int i);
	void showTextI(int i, int color);
	void showTextI(string str1, int i, string str2, bool toDefault = false);
	void showTextI(string str, vector<int> p, bool toDefault = false);
	void showTextD(double d);
	void showTextD(double d, int color);
	void showTextD(string str1, double d, string str2, bool toDefault = false, unsigned int numLength = 4);
	void showTextD(string str, vector<double> p, bool toDefault = false, unsigned int numLength = 4);

	void showCodeText(string str);

	void showButton(char opr, string text, bool changeLine = true, int color = 7);
	void createButton(char opr, string text, int x, int y, bool changeLine = true, int color = 7);
	void clearButton(char opr, bool remainCursor = true);
	void clearAllButton();

	string selectString(vector<string> str, int firstPos = 0);

	void showFakeLoading(unsigned int length, int speed, char begin, char end,
		int startColor, int endColor, double changePercent, int x, int y);
	void showLoading(unsigned int length, char begin, char end, double percent, int x, int y, int color = 7);
	void showStringIfBetween(double num, vector<double> range, vector<string> text);

	int getInputInt(int max = 2147483647, bool canBelowZero = true);
	double getInputDouble(bool canBelowZero = true, int maxLength = 15);
	string getInputString();
	string getInputString(int maxLength);
	char selectButton();

	string charToString(char c);
	string intToString(int i);
	string doubleToString(double d, unsigned int numLength = 4);
	string boolToString(bool b);
	string vectorIntToString(vector<int> v);
	string vectorUIntToString(vector<unsigned int> v);
	string vectorBoolToString(vector<bool> v);

	void setCursorPos(int x, int y);
	int getCursorPosX();
	int getCursorPosY();

	void clockStart();
	double getLastSec();
	string getStringLastSec();
	string getStringLastTime();
	string secondsToTime(int sec);
	string microsecToTime(double sec);

	string getSystemUserName();
};