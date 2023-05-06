#include "TimeCaculator.h"

bool TimeCaculator::isLeapYear()
{
	if ((this->year % 4 == 0 && this->year % 100 != 0) || this->year % 400 == 0) 
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool TimeCaculator::isLeapYear(int year)
{
	if (year > 0)
	{
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

int TimeCaculator::getDaysInMonth()
{
	int leap = 0;
	if (this->isLeapYear() == true)
	{
		leap = 1;
	}

	switch (this->month)
	{
	case 12:return 31; break;
	case 11:return 30; break;
	case 10:return 31; break;
	case 9:return 30; break;
	case 8:return 31; break;
	case 7:return 31; break;
	case 6:return 30; break;
	case 5:return 31; break;
	case 4:return 30; break;
	case 3:return 31; break;
	case 2:return 28 + leap; break;
	case 1:return 31; break;
	default:return -1; break;
	}
}

int TimeCaculator::getDaysInMonth(int year, int month)
{
	int leap = 0;
	if (this->isLeapYear(year) == true)
	{
		leap = 1;
	}

	switch (month)
	{
	case 12:return 31; break;
	case 11:return 30; break;
	case 10:return 31; break;
	case 9:return 30; break;
	case 8:return 31; break;
	case 7:return 31; break;
	case 6:return 30; break;
	case 5:return 31; break;
	case 4:return 30; break;
	case 3:return 31; break;
	case 2:return 28 + leap; break;
	case 1:return 31; break;
	default:return -1; break;
	}
}

TimeCaculator::TimeCaculator(int year, int month, int day)
{
	this->year = 2020;
	this->month = 9;
	this->day = 28;

	if (year >= 2021)
	{
		this->year = year;
	}

	if (month >= 1 && month <= 12)
	{
		this->month = month;
	}

	if (this->day >= 1 && this->day <= this->getDaysInMonth())
	{
		this->day = day;
	}
}

bool TimeCaculator::operator>(TimeCaculator time)
{
	if (this->year > time.year)
	{
		return true;
	}
	else if (this->year == time.year && this->month > time.month)
	{
		return true;
	}
	else if (this->year == time.year && this->month == time.month && this->day > time.day)
	{
		return true;
	}

	return false;
}

bool TimeCaculator::operator<(TimeCaculator time)
{
	if (this->year < time.year)
	{
		return true;
	}
	else if (this->year == time.year && this->month < time.month)
	{
		return true;
	}
	else if (this->year == time.year && this->month == time.month && this->day < time.day)
	{
		return true;
	}

	return false;
}

bool TimeCaculator::operator==(TimeCaculator time)
{
	if (this->year == time.year && this->month == time.month && this->day == time.day)
	{
		return true;
	}

	return false;
}

bool TimeCaculator::operator!=(TimeCaculator time)
{
	if (this->year != time.year || this->month != time.month || this->day != time.day)
	{
		return true;
	}

	return false;
}

bool TimeCaculator::operator>=(TimeCaculator time)
{
	if (*this > time || *this == time)
	{
		return true;
	}

	return false;
}

bool TimeCaculator::operator<=(TimeCaculator time)
{
	if (*this < time || *this == time)
	{
		return true;
	}

	return false;
}

TimeCaculator TimeCaculator::operator+(int day)
{
	TimeCaculator result(this->year, this->month, this->day);
	result.day += day;
	while (result.day > this->getDaysInMonth(result.year, result.month))
	{
		result.day -= this->getDaysInMonth(result.year, result.month);
		result.month++;
		while (result.month > 12)
		{
			result.month -= 12;
			result.year++;
		}
	}
	return result;
}

TimeCaculator TimeCaculator::operator-(int day)
{
	TimeCaculator result(this->year, this->month, this->day);
	result.day -= day;
	while (result.day <= 0)
	{
		result.month--;
		while (result.month <= 0)
		{
			result.year--;
			result.month += 12;
		}
		result.day += this->getDaysInMonth(result.year, result.month);
	}
	return result;
}

int TimeCaculator::operator-(TimeCaculator time)
{
	int result = 0;
	if (*this < time)
	{
		return -(time - *this);
	}

	TimeCaculator temp(time.year, time.month, time.day);
	while (temp < *this)
	{
		temp = temp + 1;
		result++;
	}

	return result;
}

TimeCaculator TimeCaculator::operator=(TimeCaculator time)
{
	this->year = time.year;
	this->month = time.month;
	this->day = time.day;
	return time;
}

void TimeCaculator::setTime(int year, int month, int day)
{
	this->year = 2020;
	this->month = 9;
	this->day = 28;

	if (year >= 2021)
	{
		this->year = year;
	}

	if (month >= 1 && month <= 12)
	{
		this->month = month;
	}

	if (this->day >= 1 && this->day <= this->getDaysInMonth())
	{
		this->day = day;
	}
}

int TimeCaculator::getYear()
{
	return this->year;
}

int TimeCaculator::getMonth()
{
	return this->month;
}

int TimeCaculator::getDay()
{
	return this->day;
}

int TimeCaculator::getWeek()
{
	TimeCaculator temp;
	return (*this - temp) % 7 + 1;
}
