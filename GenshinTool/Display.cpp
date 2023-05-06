#include "Display.h"

using namespace std;

COORD Display::current = { 0,0 };
vector<char> Display::buttonOpr = {};
vector<COORD> Display::buttonPos = {};
vector<unsigned int> Display::buttonLength = {};

void Display::changeCursor(char c)
{
	//TODO:字符串中的特殊字符待处理
	if (c == '\n' || c == '\r')
	{
		current.Y++;
		current.X = 0;
	}
	else if (c == '\b')
	{
		current.X--;
	}
	else if (c == '\t')
	{
		current.X++;
		while (current.X % 8 != 0)
		{
			current.X++;
		}
	}
	else
	{
		current.X++;
	}
}

bool Display::hasCharInString(string text, char str)
{
	int i = 0;
	while (text[i] != '\0')
	{
		if (str == text[i])
		{
			return true;
		}
		i++;
	}
	return false;
}

Display::Display()
{
	this->startTime = std::chrono::system_clock::now();
}

void Display::clear()
{
	current.X = 0;
	current.Y = 0;
	system("cls");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), current);
	buttonOpr.clear();
	buttonPos.clear();
	buttonLength.clear();
}

void Display::out(string str)
{
	cout << str;

	int i = 0;
	while (str[i] != '\0')
	{
		this->changeCursor(str[i]);
		i++;
	}
}

void Display::showText(string str, bool toDefault)
{
	int i = 0;
	bool color = false;

	while (str[i] != '\0')
	{
		if (str[i] == '&')
		{
			color = true;
			i++;
			continue;
		}
		if (color == true)
		{
			if (str[i] >= '1' && str[i] <= '9')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)(str[i] - '0'));
			}
			else if (str[i] >= 'A' && str[i] <= 'E')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)(str[i] - 'A' + 10));
			}
			else if (str[i] >= 'a' && str[i] <= 'e')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)(str[i] - 'a' + 10));
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}

			color = false;
			i++;
			continue;
		}

		cout << str[i];
		this->changeCursor(str[i]);

		i++;
	}
	if (toDefault == true)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
}

void Display::createText(string str, int x, int y)
{
	current.X = x;
	current.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), current);
	this->showText(str);
}

void Display::clearText(unsigned int length, int x, int y)
{
	unsigned int i = 0;
	current.X = x;
	current.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), current);
	for (i = 0; i < length; i++)
	{
		cout << ' ';
	}
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), current);
}

void Display::showTextC(char c)
{
	cout << c;
	this->changeCursor(c);
}

void Display::showTextC(char c, int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	this->showTextC(c);
}

void Display::showTextC(string str1, char c, string str2, bool toDefault)
{
	this->showText(str1);
	this->showTextC(c);
	this->showText(str2, toDefault);
}

void Display::showTextC(string str, vector<char> p, bool toDefault)
{
	int i = 0;
	bool color = false;
	unsigned int pPos = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '&')
		{
			color = true;
			i++;
			continue;
		}
		if (str[i] == '#')
		{
			if (pPos < (unsigned int)p.size())
			{
				this->showTextC(p[pPos]);
			}
			else
			{
				this->showTextC('#');
			}
			pPos++;
			i++;
			continue;
		}
		if (color == true)
		{
			if (str[i] >= '1' && str[i] <= '9')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)(str[i] - '0'));
			}
			else if (str[i] >= 'A' && str[i] <= 'E')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)(str[i] - 'A' + 10));
			}
			else if (str[i] >= 'a' && str[i] <= 'e')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)(str[i] - 'a' + 10));
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}

			color = false;
			i++;
			continue;
		}

		cout << str[i];
		this->changeCursor(str[i]);

		i++;
	}
	if (toDefault == true)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
}

void Display::showTextI(int i)
{
	this->showText(this->intToString(i));
}

void Display::showTextI(int i, int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	this->showTextI(i);
}

void Display::showTextI(string str1, int i, string str2, bool toDefault)
{
	this->showText(str1);
	this->showTextI(i);
	this->showText(str2, toDefault);
}

void Display::showTextI(string str, vector<int> p, bool toDefault)
{
	int i = 0;
	bool color = false;
	unsigned int pPos = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '&')
		{
			color = true;
			i++;
			continue;
		}
		if (str[i] == '#')
		{
			if (pPos < (unsigned int)p.size())
			{
				this->showTextI(p[pPos]);
			}
			else
			{
				this->showTextC('#');
			}
			pPos++;
			i++;
			continue;
		}
		if (color == true)
		{
			if (str[i] >= '1' && str[i] <= '9')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)(str[i] - '0'));
			}
			else if (str[i] >= 'A' && str[i] <= 'E')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)(str[i] - 'A' + 10));
			}
			else if (str[i] >= 'a' && str[i] <= 'e')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)(str[i] - 'a' + 10));
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}

			color = false;
			i++;
			continue;
		}

		cout << str[i];
		this->changeCursor(str[i]);

		i++;
	}
	if (toDefault == true)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
}

void Display::showTextD(double d)
{
	this->showText(this->doubleToString(d));
}

void Display::showTextD(double d, int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	this->showTextD(d);
}

void Display::showTextD(string str1, double d, string str2, bool toDefault, unsigned int numLength)
{
	this->showText(str1);
	this->showText(this->doubleToString(d, numLength));
	this->showText(str2, toDefault);
}

void Display::showTextD(string str, vector<double> p, bool toDefault, unsigned int numLength)
{
	int i = 0;
	bool color = false;
	unsigned int pPos = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '&')
		{
			color = true;
			i++;
			continue;
		}
		if (str[i] == '#')
		{
			if (pPos < (unsigned int)p.size())
			{
				this->showText(this->doubleToString(p[pPos], numLength));
			}
			else
			{
				this->showTextC('#');
			}
			pPos++;
			i++;
			continue;
		}
		if (color == true)
		{
			if (str[i] >= '1' && str[i] <= '9')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)(str[i] - '0'));
			}
			else if (str[i] >= 'A' && str[i] <= 'E')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)(str[i] - 'A' + 10));
			}
			else if (str[i] >= 'a' && str[i] <= 'e')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)(str[i] - 'a' + 10));
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}

			color = false;
			i++;
			continue;
		}

		cout << str[i];
		this->changeCursor(str[i]);

		i++;
	}
	if (toDefault == true)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
}

void Display::showCodeText(string str)
{
	int i = 0;
	string tempS = "";
	vector<string> subStr;
	bool isString = false;
	bool isSpace = false;

	//拆分子句
	while (str[i] != '\0')
	{
		if (str[i] == '\\')
		{
			i++;
			tempS.push_back('\\');
			tempS.push_back(str[i]);
			isSpace = false;
		}
		else if (str[i] == '\"')
		{
			if (isString == false)
			{
				isString = true;
			}
			else
			{
				isString = false;
			}

			if (tempS != "")
			{
				subStr.push_back(tempS);
				tempS = "";
			}

			subStr.push_back("\"");
			tempS = "";
			isSpace = false;
		}
		else if (str[i] == '\'')
		{
			if (isString == false)
			{
				isString = true;
			}
			else
			{
				isString = false;
			}

			if (tempS != "")
			{
				subStr.push_back(tempS);
				tempS = "";
			}

			subStr.push_back("\'");
			tempS = "";
			isSpace = false;
		}
		else if (this->hasCharInString("!%^&*()-+={}|[]:<>,./?", str[i]) == true && isString == false)
		{
			if (tempS != "")
			{
				subStr.push_back(tempS);
				tempS = "";
			}

			tempS.push_back(str[i]);
			subStr.push_back(tempS);
			tempS = "";
			isSpace = false;
		}
		else if (this->hasCharInString(" \n\r\b", str[i]) == true && isString == false)
		{
			if (isSpace == false)
			{
				subStr.push_back(tempS);
				tempS = "";
			}

			isSpace = true;
			tempS.push_back(str[i]);
		}
		else
		{
			if (isSpace == true)
			{
				subStr.push_back(tempS);
				tempS = "";
			}

			tempS.push_back(str[i]);
			isSpace = false;
		}

		i++;
	}
	if (tempS != "")
	{
		subStr.push_back(tempS);
		tempS = "";
	}

	//分析结构
	for (i = 0; i < (int)subStr.size(); i++)
	{
		if (subStr[i] == "\"" || subStr[i] == "\'")
		{
			subStr[i] = "&6" + subStr[i];
			i++;
			subStr[i] = "&6" + subStr[i];
			i++;
			subStr[i] = "&6" + subStr[i];
		}
		else if (this->hasCharInString("!%^&*()-+={}|[]:<>,./?", subStr[i][0]) == true)
		{
			subStr[i] = "&8" + subStr[i];
		}
		else if (subStr[i] == "int" || subStr[i] == "double" || subStr[i] == "bool" || subStr[i] == "char"
			|| subStr[i] == "unsigned" || subStr[i] == "true" || subStr[i] == "false" || subStr[i] == "void"
			|| subStr[i] == "short" || subStr[i] == "const" || subStr[i] == "this" || subStr[i] == "long")
		{
			subStr[i] = "&3" + subStr[i];
		}
		else if (subStr[i][0] >= '0' && subStr[i][0] <= '9')
		{
			subStr[i] = "&A" + subStr[i];
		}
		else
		{
			if ((int)subStr.size() == 1)
			{
				subStr[i] = "&B" + subStr[i];
			}
			else if (i == (int)subStr.size() - 1)
			{
				subStr[i] = "&B" + subStr[i];
			}
			else if (subStr[i + 1] == "(")
			{
				subStr[i] = "&E" + subStr[i];
			}
			else if (subStr[i + 1][0] == ' ' || subStr[i + 1][0] == '\n')
			{
				if (i + 2 >= (int)subStr.size())
				{
					subStr[i] = "&B" + subStr[i];
				}
				else if (this->hasCharInString("!%^&*()-+={}|[]:<>,./?", subStr[i + 2][0]) == true)
				{
					subStr[i] = "&B" + subStr[i];
				}
				else
				{
					subStr[i] = "&2" + subStr[i];
				}
			}
			else if (subStr[i + 1][0] == ':')
			{
				if (i + 2 >= (int)subStr.size())
				{
					subStr[i] = "&7" + subStr[i];
				}
				else if (subStr[i + 2][0] == ':')
				{
					subStr[i] = "&2" + subStr[i];
				}
				else
				{
					subStr[i] = "&7" + subStr[i];
				}
			}
			else if (i == 0)
			{
				subStr[i] = "&B" + subStr[i];
			}
			else if (subStr[i - 1][2] == '(' && this->hasCharInString(")*<[", subStr[i + 1][0]))
			{
				subStr[i] = "&2" + subStr[i];
			}
			else if (subStr[i - 1][2] == '<' && subStr[i + 1][0] == '>')
			{
				subStr[i] = "&2" + subStr[i];
			}
			else
			{
				subStr[i] = "&B" + subStr[i];
			}
		}
	}

	//显示出来
	int j = 0;
	for (i = 0; i < (int)subStr.size(); i++)
	{
		if (subStr[i][0] == '&')
		{
			if (subStr[i][1] >= '1' && subStr[i][1] <= '9')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)(subStr[i][1] - '0'));
			}
			else if (subStr[i][1] >= 'A' && subStr[i][1] <= 'E')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)(subStr[i][1] - 'A' + 10));
			}
			else if (subStr[i][1] >= 'a' && subStr[i][1] <= 'e')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)(subStr[i][1] - 'a' + 10));
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			j = 2;
		}
		while (subStr[i][j] != '\0')
		{
			cout << subStr[i][j];
			this->changeCursor(subStr[i][j]);
			j++;
		}
		j = 0;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void Display::showButton(char opr, string text, bool changeLine, int color)
{
	int temp = current.X;

	buttonOpr.push_back(opr);
	buttonPos.push_back(current);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	cout << "[" << opr << "]";
	current.X += 3;
	this->showText(text, true);

	buttonLength.push_back(current.X - temp);

	if (changeLine == true)
	{
		cout << endl;
		current.X = 0;
		current.Y++;
	}
}

void Display::createButton(char opr, string text, int x, int y, bool changeLine, int color)
{
	current.X = x;
	current.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), current);
	this->showButton(opr, text, changeLine, color);
}

void Display::clearButton(char opr, bool remainCursor)
{
	unsigned int i = 0;
	unsigned int size = (unsigned int)buttonOpr.size();
	COORD temp = current;

	for (i = 0; i < size; i++)
	{
		if (buttonOpr[i] == opr)
		{
			current = buttonPos[i];
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), current);
			this->clearText(buttonLength[i], current.X, current.Y);
			buttonPos.erase(buttonPos.begin() + i, buttonPos.begin() + i + 1);
			buttonLength.erase(buttonLength.begin() + i, buttonLength.begin() + i + 1);
			buttonOpr.erase(buttonOpr.begin() + i, buttonOpr.begin() + i + 1);

			if (remainCursor == true)
			{
				current = temp;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), current);
			}

			return;
		}
	}
}

void Display::clearAllButton()
{
	unsigned int i = 0;
	unsigned int size = (unsigned int)buttonOpr.size();
	COORD temp = current;

	for (i = 0; i < size; i++)
	{
		current = buttonPos[i];
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), current);
		this->clearText(buttonLength[i], current.X, current.Y);
	}

	buttonOpr.clear();
	buttonPos.clear();
	buttonLength.clear();

	current = temp;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), current);
}

string Display::selectString(vector<string> str, int firstPos)
{
	string tempS;
	int tempCoordY = this->getCursorPosY();
	int position = firstPos;
	int i = 0;
	int length = (int)str.size();
	char opr = '\0';

	while (opr != '0')
	{
		this->clearAllButton();
		this->setCursorPos(0, tempCoordY);
		for (i = 0; i < length; i++)
		{
			if (position == i)
			{
				int j = 0;
				tempS = "&8";
				tempS += str[i];
				for (j = 0; j < (int)tempS.size(); j++)
				{
					if (tempS[j] == '&')
					{
						j++;
						tempS[j] = '8';
					}
				}
				this->showText(tempS);
				this->showText("&7\n");
			}
			else
			{
				this->showText(str[i]);
				this->showText("&7\n");
			}
		}

		this->showText("&7\n");
		if (position > 0)
		{
			this->showButton('w', "上移");
		}
		if (position < length - 1)
		{
			this->showButton('s', "下移");
		}
		this->showButton('e', "选择");
		this->showButton('0', "放弃");
		opr = this->selectButton();
		if (opr == '0')
		{
			position = firstPos;
			break;
		}
		else if (opr == 'e')
		{
			break;
		}
		else if (opr == 'w')
		{
			position--;
		}
		else if (opr == 's')
		{
			position++;
		}
	}

	this->clearAllButton();
	this->setCursorPos(0, tempCoordY);
	for (i = 0; i < length; i++)
	{
		this->clearText((unsigned int)str[i].size(), 0, tempCoordY + i);
	}
	this->setCursorPos(0, tempCoordY);
	return str[position];
}

void Display::showFakeLoading(unsigned int length, int speed, char begin, char end,
	int startColor, int endColor, double changePercent, int x, int y)
{
	unsigned int i = 0;
	for (i = 0; i < 100; i++)
	{
		if (i < changePercent * 100)
		{
			this->showLoading(length, begin, end, (double)i / 100, x, y, startColor);
		}
		else
		{
			this->showLoading(length, begin, end, (double)i / 100, x, y, endColor);
		}

		Sleep(speed);
	}

	this->clearText(length, x, y);
}

void Display::showLoading(unsigned int length, char begin, char end, double percent, int x, int y, int color)
{
	unsigned int i = 0;
	int pos = (int)(percent * 100);
	unsigned int cur = length / 2 - 1;
	vector<char> str;

	for (i = 0; i < length; i++)
	{
		if (i < percent * length)
		{
			str.push_back(end);
		}
		else
		{
			str.push_back(begin);
		}
	}

	str[cur] = pos / 10 + '0';
	cur++;
	str[cur] = pos % 10 + '0';
	cur++;
	str[cur] = '%';

	current.X = x;
	current.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), current);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	for (i = 0; i < length; i++)
	{
		cout << str[i];
		current.X++;
	}
}

void Display::showStringIfBetween(double num, vector<double> range, vector<string> text)
{
	if (range.size() == 0)
	{
		this->showText(text[0]);
		return;
	}

	if (num < range[0])
	{
		this->showText(text[0]);
		return;
	}

	unsigned int i = 0;
	unsigned int size = (unsigned int)range.size();
	for (i = 0; i < size - 1; i++)
	{
		if (num >= range[i] && num < range[i + 1])
		{
			this->showText(text[i + 1]);
			return;
		}
	}

	if (num >= range[size - 1])
	{
		this->showText(text[size]);
		return;
	}
}

int Display::getInputInt(int max, bool canBelowZero)
{
	bool belowZero = false;
	int result = 0;
	int length = 0;
	int maxLength = 0;
	int temp = 0;
	int str = 0;
	str = _getch();

	//获取最大数位数
	temp = max;
	while (temp != 0)
	{
		maxLength++;
		temp /= 10;
	}

	while (str != 13 || length == 0)
	{
		if (str == 8)
		{
			if (length > 0)
			{
				length--;
				result = result / 10;
				cout << '\b';
				cout << " ";
				cout << '\b';
			}
			else if (length == 0 && belowZero == true)
			{
				belowZero = false;
				cout << '\b';
				cout << " ";
				cout << '\b';
			}
		}
		else if (str == '-' && belowZero == false && length == 0 && canBelowZero == true)
		{
			cout << '-';
			belowZero = true;
		}
		else if (str == 224)
		{
			str = _getch();
		}
		else if (str >= '0' && str <= '9')
		{
			if (result > max / 10)
			{
				//数字过大，替换为最大数
				this->clearText(length, current.X, current.Y);
				if (belowZero == true)
				{
					cout << -max;
				}
				else
				{
					cout << max;
				}
				result = max;
				length = maxLength;
			}
			else if (result == max / 10 && str - '0' > max % 10)
			{
				//数字过大，替换为最大数
				this->clearText(length, current.X, current.Y);
				if (belowZero == true)
				{
					cout << -max;
				}
				else
				{
					cout << max;
				}
				result = max;
				length = maxLength;
			}
			else if (length == 1 && result == 0)
			{
				//第一位数输入的是0，然后输入了第二位数
				cout << '\b';
				cout << (char)str;
				result = result * 10 - '0' + str;
			}
			else
			{
				cout << (char)str;
				length++;
				result = result * 10 - '0' + str;
			}
		}
		str = _getch();
	}

	cout << '\n';
	current.X = 0;
	current.Y++;
	if (belowZero == true)
	{
		return -result;
	}
	return result;
}

double Display::getInputDouble(bool canBelowZero, int maxLength)
{
	bool belowZero = false;
	bool hasPoint = false;
	int length = 0;
	int str = 0;
	unsigned int i = 0;
	double result = 0.0;
	double pointResult = 1.0;

	vector<char> temp;

	//获取输入，将输入临时存进字符数组
	str = _getch();
	while (str != 13 || length == 0)
	{
		if (str == 8)
		{
			if (temp.size() > 0)
			{
				if (temp[temp.size() - 1] == '-')
				{
					belowZero = false;
					temp.pop_back();
				}
				else if (temp[temp.size() - 1] == '.')
				{
					hasPoint = false;
					temp.pop_back();
				}
				else if(length > 0)
				{
					length--;
					temp.pop_back();
				}
				cout << '\b';
				cout << " ";
				cout << '\b';
			}
		}
		else if (str == '-' && belowZero == false && length == 0 && canBelowZero == true)
		{
			cout << '-';
			temp.push_back('-');
			belowZero = true;
		}
		else if (str == '.' && hasPoint == false && length < maxLength)
		{
			if (length == 0)
			{
				//如果小数点前没有数字
				cout << '0';
				temp.push_back('0');
				length++;
			}
			cout << '.';
			temp.push_back('.');
			hasPoint = true;
		}
		else if (str == 224)
		{
			str = _getch();
		}
		else if (str >= '0' && str <= '9')
		{
			if (length == 1 && temp[temp.size() - 1] == '0' && hasPoint == false)
			{
				//输入整数位第一位为零
				cout << '\b';
				cout << (char)str;
				temp[temp.size() - 1] = str;
			}
			else if (length < maxLength)
			{
				cout << (char)str;
				temp.push_back(str);
				length++;
			}
		}
		str = _getch();
	}

	//将字符数组转化成数字
	hasPoint = false;
	for (i = 0; i < temp.size(); i++)
	{
		if (temp[i] == '-')
		{
			continue;
		}
		else if (temp[i] == '.')
		{
			hasPoint = true;
		}
		else if (hasPoint == false)
		{
			result = result * 10 - '0' + temp[i];
		}
		else
		{
			pointResult /= 10;
			result = result + pointResult * ((double)temp[i] - '0');
		}
	}

	if (belowZero == true)
	{
		result *= (-1);
	}

	cout << '\n';
	current.X = 0;
	current.Y++;
	return result;
}

string Display::getInputString()
{
	string temp = "";
	int str = 0;
	int length = 0;
	str = _getch();
	//13换行，8退格，224方向键
	while (str != 13 || length == 0)
	{
		if (str == 8)
		{
			if (length > 0)
			{
				length--;
				temp.pop_back();
				cout << '\b';
				cout << " ";
				cout << '\b';
			}
		}
		else if (str == 224)
		{
			str = _getch();
		}
		else
		{
			cout << (char)str;
			length++;
			temp.push_back(str);
		}
		str = _getch();
	}

	cout << '\n';
	current.X = 0;
	current.Y++;
	return temp;
}

string Display::getInputString(int maxLength)
{
	string temp = "";
	int str = 0;
	int length = 0;
	str = _getch();
	//13换行，8退格，224方向键
	while (str != 13 || length == 0)
	{
		if (str == 8)
		{
			if (length > 0)
			{
				length--;
				temp.pop_back();
				cout << '\b';
				cout << " ";
				cout << '\b';
			}
		}
		else if (str == 224)
		{
			str = _getch();
		}
		else if (length < maxLength)
		{
			cout << (char)str;
			length++;
			temp.push_back(str);
		}
		str = _getch();
	}

	cout << '\n';
	current.X = 0;
	current.Y++;
	return temp;
}

char Display::selectButton()
{
	char c = '\0';
	unsigned int i = 0;
	unsigned int length = (unsigned int)buttonOpr.size();

	if (length == 0)
	{
		return '\0';
	}

	while (true)
	{
		c = (char)_getch();
		for (i = 0; i < length; i++)
		{
			if (buttonOpr[i] == c)
			{
				return c;
			}
		}
	}

	return '\0';
}

string Display::charToString(char c)
{
	string result = "";
	result.push_back(c);
	return result;
}

string Display::intToString(int i)
{
	string result;
	stringstream ss;
	ss << i;
	ss >> result;
	return result;
}

string Display::doubleToString(double d, unsigned int numLength)
{
	string result = "";
	if (d < 0)
	{
		result.push_back('-');
		result += this->doubleToString(-d, numLength);
		return result;
	}
	else if (d == 0)
	{
		unsigned int t = 0;
		result = "0.";
		for (t = 0; t < numLength; t++)
		{
			result.push_back('0');
		}
		return result;
	}
	else
	{
		//四舍五入对齐
		unsigned int t = 0;
		double extraNum = 0.5;
		for (t = 0; t < numLength; t++)
		{
			extraNum /= 10;
		}
		double num = d + extraNum;

		int iPosi = (int)num;
		double iNega = num - iPosi;
		//整数部分
		result += this->intToString(iPosi);
		result.push_back('.');
		//小数部分
		for (t = 0; t < numLength; t++)
		{
			iNega *= 10;
			iPosi = (int)iNega;
			result.push_back((char)iPosi + '0');
			iNega -= iPosi;
		}

		return result;
	}
}

string Display::boolToString(bool b)
{
	if (b == true)
	{
		return "true";
	}
	else
	{
		return "false";
	}
}

string Display::vectorIntToString(vector<int> v)
{
	string result = "{ ";
	int i = 0;
	for (i = 0; i < (int)v.size(); i++)
	{
		if (i > 0)
		{
			result += ", ";
		}
		result += this->intToString(v[i]);
	}
	result += " }";

	return result;
}

string Display::vectorUIntToString(vector<unsigned int> v)
{
	string result = "{ ";
	int i = 0;
	for (i = 0; i < (int)v.size(); i++)
	{
		if (i > 0)
		{
			result += ", ";
		}
		result += this->intToString((int)v[i]);
	}
	result += " }";

	return result;
}

string Display::vectorBoolToString(vector<bool> v)
{
	string result = "{ ";
	int i = 0;
	for (i = 0; i < (int)v.size(); i++)
	{
		if (i > 0)
		{
			result += ", ";
		}
		result += this->boolToString(v[i]);
	}
	result += " }";

	return result;
}

void Display::setCursorPos(int x, int y)
{
	current.X = x;
	current.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), current);
}

int Display::getCursorPosX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.X;
}

int Display::getCursorPosY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.Y;
}

void Display::clockStart()
{
	this->startTime = std::chrono::system_clock::now();
}

double Display::getLastSec()
{
	std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();
	std::chrono::microseconds spendTime = duration_cast<microseconds>(endTime - this->startTime);
	double result = double(spendTime.count()) *
		std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
	return result;
}

string Display::getStringLastSec()
{
	return this->doubleToString(this->getLastSec(), 3);
}

string Display::getStringLastTime()
{
	string result = "";
	int spendTime = (int)(this->getLastSec() * 1000.0);
	if (spendTime < 1000)
	{
		result += "0.";
		result += this->intToString(spendTime / 100);
		result += this->intToString((spendTime / 10) % 10);
		result += this->intToString(spendTime % 10);
		result += "秒";

		return result;
	}

	if (spendTime >= 86400000)
	{
		result += this->intToString(spendTime / 86400000);
		result += "天";
		spendTime = spendTime - (spendTime / 86400000 * 86400000);
	}
	if (spendTime >= 3600000)
	{
		result += this->intToString(spendTime / 3600000);
		result += "小时";
		spendTime = spendTime - (spendTime / 3600000 * 3600000);
	}
	if (spendTime >= 60000)
	{
		result += this->intToString(spendTime / 60000);
		result += "分";
		spendTime = spendTime - (spendTime / 60000 * 60000);
	}
	if (spendTime >= 1000)
	{
		result += this->intToString(spendTime / 1000);
		spendTime = spendTime - (spendTime / 1000 * 1000);
		if (spendTime >= 1)
		{
			result += ".";
			result += this->intToString(spendTime / 100);
			result += this->intToString((spendTime / 10) % 10);
			result += this->intToString(spendTime % 10);
		}
		result += "秒";
	}

	return result;
}

string Display::secondsToTime(int sec)
{
	string result = "";
	int spendTime = sec;

	if (spendTime >= 86400)
	{
		result += this->intToString(spendTime / 86400);
		result += "天";
		spendTime = spendTime - (spendTime / 86400 * 86400);
	}
	if (spendTime >= 3600)
	{
		result += this->intToString(spendTime / 3600);
		result += "小时";
		spendTime = spendTime - (spendTime / 3600 * 3600);
	}
	if (spendTime >= 60)
	{
		result += this->intToString(spendTime / 60);
		result += "分";
		spendTime = spendTime - (spendTime / 60 * 60);
	}
	if (spendTime >= 1)
	{
		result += this->intToString(spendTime);
		result += "秒";
	}

	return result;
}

string Display::microsecToTime(double sec)
{
	string result = "";
	int spendTime = (int)(sec * 1000.0);
	if (spendTime < 1000)
	{
		result += "0.";
		result += this->intToString(spendTime / 100);
		result += this->intToString((spendTime / 10) % 10);
		result += this->intToString(spendTime % 10);
		result += "秒";

		return result;
	}

	if (spendTime >= 86400000)
	{
		result += this->intToString(spendTime / 86400000);
		result += "天";
		spendTime = spendTime - (spendTime / 86400000 * 86400000);
	}
	if (spendTime >= 3600000)
	{
		result += this->intToString(spendTime / 3600000);
		result += "小时";
		spendTime = spendTime - (spendTime / 3600000 * 3600000);
	}
	if (spendTime >= 60000)
	{
		result += this->intToString(spendTime / 60000);
		result += "分";
		spendTime = spendTime - (spendTime / 60000 * 60000);
	}
	if (spendTime >= 1000)
	{
		result += this->intToString(spendTime / 1000);
		spendTime = spendTime - (spendTime / 1000 * 1000);
		if (spendTime >= 1)
		{
			result += ".";
			result += this->intToString(spendTime / 100);
			result += this->intToString((spendTime / 10) % 10);
			result += this->intToString(spendTime % 10);
		}
		result += "秒";
	}

	return result;
}

string Display::getSystemUserName()
{
	TCHAR path[1024] = { '\0' };
	SHGetSpecialFolderPath(HWND_DESKTOP, path, CSIDL_APPDATA, false);
	int k = 0;
	string user = "";
	for (k = 9; k < 128; k++)
	{
		if ((char)path[k] == '\\')
		{
			break;
		}
		user.push_back((char)path[k]);
	}

	return user;
}
