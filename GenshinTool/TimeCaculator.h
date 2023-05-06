#pragma once

class TimeCaculator
{
private:
	int year;
	int month;
	int day;

public:
	//Ĭ����2020��9��28������һΪ�������
	TimeCaculator(int year = 2020, int month = 9, int day = 28);

	bool isLeapYear();
	bool isLeapYear(int year);

	int getDaysInMonth();
	int getDaysInMonth(int year, int month);

	bool operator > (TimeCaculator time);
	bool operator < (TimeCaculator time);
	bool operator == (TimeCaculator time);
	bool operator != (TimeCaculator time);
	bool operator >= (TimeCaculator time);
	bool operator <= (TimeCaculator time);
	TimeCaculator operator + (int day);
	TimeCaculator operator - (int day);
	int operator - (TimeCaculator time);
	TimeCaculator operator = (TimeCaculator time);

	void setTime(int year, int month, int day);

	int getYear();
	int getMonth();
	int getDay();
	int getWeek();
};