#include "EventTime.h"

EventTime::EventTime()
{
	this->time.setTime(2020, 9, 30);
	this->primogem = 0;
}

EventTime::EventTime(TimeCaculator time)
{
	this->time = time;
	this->primogem = 0;
}

EventTime::EventTime(int year, int month, int day)
{
	TimeCaculator temp(year, month, day);
	this->time = temp;
	this->primogem = 0;
}

TimeCaculator EventTime::getLastVersionOP()
{
	return this->getCurrentVersionOP() - 42;
}

TimeCaculator EventTime::getLastVersionED()
{
	return this->getCurrentVersionOP() - 1;
}

TimeCaculator EventTime::getCurrentVersionOP()
{
	return this->getNextVersionOP() - 42;
}

TimeCaculator EventTime::getCurrentVersionED()
{
	return this->getNextVersionOP() - 1;
}

TimeCaculator EventTime::getNextVersionOP()
{
	TimeCaculator temp(2020, 9, 30);

	while (temp <= this->time)
	{
		temp = temp + 42;
	}
	
	return temp;
}

TimeCaculator EventTime::getNextVersionED()
{
	return this->getNextVersionOP() + 41;
}

TimeCaculator EventTime::getNextPoolOP()
{
	if (this->time > this->getCurrentVersionOP() + 20)
	{
		return this->getNextVersionOP();
	}
	return this->getCurrentVersionOP() + 20;
}

TimeCaculator EventTime::getNextPoolED()
{
	if (this->time > this->getCurrentVersionOP() + 20)
	{
		return this->getNextVersionOP() + 20;
	}
	return this->getCurrentVersionED();
}

TimeCaculator EventTime::getNextExpEventED()
{
	return this->getNextVersionOP() + 40;
}

TimeCaculator EventTime::getNextReportTime()
{
	TimeCaculator result;
	result = this->getNextVersionOP() - 12;
	if (result < this->time)
	{
		result = result + 42;
	}
	return result;
}

TimeCaculator EventTime::savePrimogemExpect(int count, int ability, bool hasWish, bool hasExp)
{
	int tempCount = this->primogem;
	TimeCaculator result;
	EventTime temp;
	TimeCaculator op;
	result = this->time;

	while (tempCount < count)
	{
		result = result + 1;
		temp.time = result;
		op = temp.getCurrentVersionOP();
		//ÿ������
		tempCount += 60;
		//��Ԩ
		if (result.getDay() == 1 || result.getDay() == 16)
		{
			tempCount += ability;
		}
		//��ɫ����
		if (result == op || result == op + 20)
		{
			tempCount += 20;
		}
		//�汾���²���
		if (result == op)
		{
			tempCount += 600;
		}
		//��
		if (result == op + 1)
		{
			tempCount += 330;
		}
		if (result == op + 4)
		{
			tempCount += 270;
		}
		if (result == op + 7)
		{
			tempCount += 240;
		}
		if (result == op + 10)
		{
			tempCount += 180;
		}
		//С�
		if (result >= op + 15 && result <= op + 21)
		{
			tempCount += 60;
		}
		if (result >= op + 23 && result <= op + 29)
		{
			tempCount += 60;
		}
		if (result >= op + 31 && result <= op + 37)
		{
			tempCount += 60;
		}
		//ǰհֱ��
		if (result == op + 30)
		{
			tempCount += 300;
		}
		//С�¿�
		if (hasWish == true)
		{
			tempCount += 90;
		}
		//���¿�
		if (hasExp == true && result == op + 28)
		{
			tempCount += 680;
		}
	}

	return result;
}

TimeCaculator EventTime::saveWishExpect(int count, int ability, bool hasWish, bool hasExp)
{
	int tempCount = this->primogem;
	TimeCaculator result;
	EventTime temp;
	TimeCaculator op;
	result = this->time;

	while (tempCount < count * 160)
	{
		result = result + 1;
		temp.time = result;
		op = temp.getCurrentVersionOP();
		//ÿ������
		tempCount += 60;
		//��Ԩ
		if (result.getDay() == 1 || result.getDay() == 16)
		{
			tempCount += ability;
		}
		//�³��̵��ǳ��һ�
		if (result.getDay() == 1)
		{
			tempCount += 800;
		}
		//��ɫ����
		if (result == op || result == op + 20)
		{
			tempCount += 20;
		}
		//�汾���²���
		if (result == op)
		{
			tempCount += 600;
		}
		//��
		if (result == op + 1)
		{
			tempCount += 330;
		}
		if (result == op + 4)
		{
			tempCount += 270;
		}
		if (result == op + 7)
		{
			tempCount += 240;
		}
		if (result == op + 10)
		{
			tempCount += 180;
		}
		//С�
		if (result >= op + 15 && result <= op + 21)
		{
			tempCount += 60;
		}
		if (result >= op + 23 && result <= op + 29)
		{
			tempCount += 60;
		}
		if (result >= op + 31 && result <= op + 37)
		{
			tempCount += 60;
		}
		//ǰհֱ��
		if (result == op + 30)
		{
			tempCount += 300;
		}
		//С�¿�
		if (hasWish == true)
		{
			tempCount += 90;
		}
		//���¿�
		if (hasExp == true)
		{
			if (result == op + 28)
			{
				tempCount += 680;
			}
			if (result == op + 4 || result == op + 9 || result == op + 13 || result == op + 20)
			{
				tempCount += 160;
			}
		}
	}

	return result;
}

int EventTime::keepPrimogemExpect(TimeCaculator t, int ability, bool hasWish, bool hasExp)
{
	int result = this->primogem;
	TimeCaculator tempTime;
	EventTime temp;
	TimeCaculator op;
	tempTime = this->time;

	while (tempTime < t)
	{
		tempTime = tempTime + 1;
		temp.time = tempTime;
		op = temp.getCurrentVersionOP();
		//ÿ������
		result += 60;
		//��Ԩ
		if (tempTime.getDay() == 1 || tempTime.getDay() == 16)
		{
			result += ability;
		}
		//��ɫ����
		if (tempTime == op || tempTime == op + 20)
		{
			result += 20;
		}
		//�汾���²���
		if (tempTime == op)
		{
			result += 600;
		}
		//��
		if (tempTime == op + 1)
		{
			result += 330;
		}
		if (tempTime == op + 4)
		{
			result += 270;
		}
		if (tempTime == op + 7)
		{
			result += 240;
		}
		if (tempTime == op + 10)
		{
			result += 180;
		}
		//С�
		if (tempTime >= op + 15 && tempTime <= op + 21)
		{
			result += 60;
		}
		if (tempTime >= op + 23 && tempTime <= op + 29)
		{
			result += 60;
		}
		if (tempTime >= op + 31 && tempTime <= op + 37)
		{
			result += 60;
		}
		//ǰհֱ��
		if (tempTime == op + 30)
		{
			result += 300;
		}
		//С�¿�
		if (hasWish == true)
		{
			result += 90;
		}
		//���¿�
		if (hasExp == true && tempTime == op + 28)
		{
			result += 680;
		}
	}

	return result;
}

int EventTime::keepWishExpect(TimeCaculator t, int ability, bool hasWish, bool hasExp)
{
	int result = this->primogem;
	TimeCaculator tempTime;
	EventTime temp;
	TimeCaculator op;
	tempTime = this->time;

	while (tempTime < t)
	{
		tempTime = tempTime + 1;
		temp.time = tempTime;
		op = temp.getCurrentVersionOP();
		//ÿ������
		result += 60;
		//��Ԩ
		if (tempTime.getDay() == 1 || tempTime.getDay() == 16)
		{
			result += ability;
		}
		//�³��̵��ǳ��һ�
		if (tempTime.getDay() == 1)
		{
			result += 800;
		}
		//��ɫ����
		if (tempTime == op || tempTime == op + 20)
		{
			result += 20;
		}
		//�汾���²���
		if (tempTime == op)
		{
			result += 600;
		}
		//��
		if (tempTime == op + 1)
		{
			result += 330;
		}
		if (tempTime == op + 4)
		{
			result += 270;
		}
		if (tempTime == op + 7)
		{
			result += 240;
		}
		if (tempTime == op + 10)
		{
			result += 180;
		}
		//С�
		if (tempTime >= op + 15 && tempTime <= op + 21)
		{
			result += 60;
		}
		if (tempTime >= op + 23 && tempTime <= op + 29)
		{
			result += 60;
		}
		if (tempTime >= op + 31 && tempTime <= op + 37)
		{
			result += 60;
		}
		//ǰհֱ��
		if (tempTime == op + 30)
		{
			result += 300;
		}
		//С�¿�
		if (hasWish == true)
		{
			result += 90;
		}
		//���¿�
		if (hasExp == true)
		{
			if (tempTime == op + 28)
			{
				result += 680;
			}
			if (tempTime == op + 4 || tempTime == op + 9 || tempTime == op + 13 || tempTime == op + 20)
			{
				result += 160;
			}
		}
	}

	return result / 160;
}

int EventTime::getPrimogemExpect(TimeCaculator t, string name, int ability)
{
	int result = this->primogem;
	TimeCaculator tempTime;
	EventTime temp;
	TimeCaculator op;
	tempTime = this->time;

	while (tempTime < t)
	{
		tempTime = tempTime + 1;
		temp.time = tempTime;
		op = temp.getCurrentVersionOP();
		//ÿ������
		if (name == "ÿ�ջ�Ծ")
		{
			result += 60;
		}
		if (name == "�����")
		{
			//��Ԩ
			if (tempTime.getDay() == 1 || tempTime.getDay() == 16)
			{
				result += ability;
			}
		}
		if (name == "��ɫ����")
		{
			//��ɫ����
			if (tempTime == op || tempTime == op + 20)
			{
				result += 20;
			}
		}
		if (name == "�汾���²���")
		{
			//�汾���²���
			if (tempTime == op)
			{
				result += 600;
			}
		}
		if (name == "�����")
		{
			//��
			if (tempTime == op + 1)
			{
				result += 330;
			}
			if (tempTime == op + 4)
			{
				result += 270;
			}
			if (tempTime == op + 7)
			{
				result += 240;
			}
			if (tempTime == op + 10)
			{
				result += 180;
			}
			//С�
			if (tempTime >= op + 15 && tempTime <= op + 21)
			{
				result += 60;
			}
			if (tempTime >= op + 23 && tempTime <= op + 29)
			{
				result += 60;
			}
			if (tempTime >= op + 31 && tempTime <= op + 37)
			{
				result += 60;
			}
		}
		if (name == "ǰհֱ��")
		{
			//ǰհֱ��
			if (tempTime == op + 30)
			{
				result += 300;
			}
		}
		//С�¿�
		if (name == "����ף��")
		{
			result += 90;
		}
		//���¿�
		if (name == "�������" && tempTime == op + 28)
		{
			result += 680;
		}
	}

	return result;
}

int EventTime::getWishExpect(TimeCaculator t, string name, int ability)
{
	int result = this->primogem;
	TimeCaculator tempTime;
	EventTime temp;
	TimeCaculator op;
	tempTime = this->time;

	while (tempTime < t)
	{
		tempTime = tempTime + 1;
		temp.time = tempTime;
		op = temp.getCurrentVersionOP();
		//ÿ������
		if (name == "ÿ�ջ�Ծ")
		{
			result += 60;
		}
		if (name == "�����")
		{
			//��Ԩ
			if (tempTime.getDay() == 1 || tempTime.getDay() == 16)
			{
				result += ability;
			}
		}
		if (name == "�ǳ��һ�")
		{
			//�³��̵��ǳ��һ�
			if (tempTime.getDay() == 1)
			{
				result += 800;
			}
		}
		if (name == "��ɫ����")
		{
			//��ɫ����
			if (tempTime == op || tempTime == op + 20)
			{
				result += 20;
			}
		}
		if (name == "�汾���²���")
		{
			//�汾���²���
			if (tempTime == op)
			{
				result += 600;
			}
		}
		if (name == "�����")
		{
			//��
			if (tempTime == op + 1)
			{
				result += 330;
			}
			if (tempTime == op + 4)
			{
				result += 270;
			}
			if (tempTime == op + 7)
			{
				result += 240;
			}
			if (tempTime == op + 10)
			{
				result += 180;
			}
			//С�
			if (tempTime >= op + 15 && tempTime <= op + 21)
			{
				result += 60;
			}
			if (tempTime >= op + 23 && tempTime <= op + 29)
			{
				result += 60;
			}
			if (tempTime >= op + 31 && tempTime <= op + 37)
			{
				result += 60;
			}
		}
		if (name == "ǰհֱ��")
		{
			//ǰհֱ��
			if (tempTime == op + 30)
			{
				result += 300;
			}
		}
		//С�¿�
		if (name == "����ף��")
		{
			result += 90;
		}
		//���¿�
		if (name == "�������")
		{
			if (tempTime == op + 28)
			{
				result += 680;
			}
			if (tempTime == op + 4 || tempTime == op + 9 || tempTime == op + 13 || tempTime == op + 20)
			{
				result += 160;
			}
		}
	}

	if (result - (result / 160 * 160) >= 80)
	{
		return result / 160 + 1;
	}
	else
	{
		return result / 160;
	}
}

int EventTime::allEnergy(TimeCaculator t)
{
	return (t - this->time) * 180;
}

int EventTime::allMoney(TimeCaculator t)
{
	return this->allEnergy(t) / 20 * 60000;
}

string EventTime::getVersionId()
{
	TimeCaculator temp(2020, 9, 30);
	string versionId = "1.0";

	temp = temp + 42;
	while (temp <= this->time)
	{
		versionId[2]++;
		if (versionId[2] >= '7' && versionId[0] == '1')
		{
			versionId[2] = '0';
			versionId[0]++;
		}
		else if (versionId[2] >= '9')
		{
			versionId[2] = '0';
			versionId[0]++;
		}
		temp = temp + 42;
	}

	return versionId;
}
