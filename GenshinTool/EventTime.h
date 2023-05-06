#pragma once

#include <string>
#include "TimeCaculator.h"

using namespace std;

class EventTime
{
private:
	TimeCaculator time;
	int primogem;

public:
	EventTime();
	EventTime(TimeCaculator time);
	EventTime(int year, int month, int day);

	//����汾ʱ��
	TimeCaculator getLastVersionOP();
	TimeCaculator getLastVersionED();
	TimeCaculator getCurrentVersionOP();
	TimeCaculator getCurrentVersionED();
	TimeCaculator getNextVersionOP();
	TimeCaculator getNextVersionED();
	//���㿨��ʱ��
	TimeCaculator getNextPoolOP();
	TimeCaculator getNextPoolED();
	//�������ʱ��
	TimeCaculator getNextExpEventED();
	//�����´�ֱ��ʱ��
	TimeCaculator getNextReportTime();
	//�����ܵ�ָ������ԭʯ�Ĺ�������(�������)������:Ŀ����������Ԩ������С�¿������¿�
	TimeCaculator savePrimogemExpect(int count, int ability = 600, bool hasWish = false, bool hasExp = false);
	TimeCaculator saveWishExpect(int count, int ability = 600, bool hasWish = false, bool hasExp = false);
	//����ָ������ԭʯ�������Ե������(�������)
	int keepPrimogemExpect(TimeCaculator t, int ability = 600, bool hasWish = false, bool hasExp = false);
	int keepWishExpect(TimeCaculator t, int ability = 600, bool hasWish = false, bool hasExp = false);
	//����ָ������ͨ��ָ����ʽԭʯ�������Ե������(�������)
	int getPrimogemExpect(TimeCaculator t, string name, int ability = 600);
	int getWishExpect(TimeCaculator t, string name, int ability = 600);
	//������֬�������Լ�ȫ������ˢ���
	int allEnergy(TimeCaculator t);
	int allMoney(TimeCaculator t);

	string getVersionId();
};