#pragma once

#include <string>
#include <vector>

#include "WishHistory.h"
#include "RandEngine.h"
#include "PwFunction.h"

using namespace std;

class WishPool
{
private:
	WishHistory history; //��ʷ��¼
	string name; //��������
	unsigned int num; //�ܳ���

	vector<string> star5Choose;  //�����5����Ʒ

	bool hasChoose; //���޶��챣��
	bool hasUp; //���޴󱣵�
	int upItemType; //up��Ʒ����

	//������һ��������ʲ������һ���Ǽ�
	short randStar();
	//���һ��3����Ʒ
	void randStar3Item(string* item, int* style);
	//���һ���������Ʒ
	bool randChooseItem(string* item, int* style);
	//��û��
	bool randIs5UpItem();
	bool randIs4UpItem();
	//��������
	int randStar5Style();
	int randStar4Style();
	//���һ��up��Ʒ
	void randStar5UpItem(string* item, int* style);
	void randStar4UpItem(string* item, int* style);
	//���һ����פ��Ʒ
	void randStar5BasePerson(string* item, int* style);
	void randStar5BaseWeapon(string* item, int* style);
	void randStar4BasePerson(string* item, int* style);
	void randStar4BaseWeapon(string* item, int* style);
	//�ж��Ƿ񶨹����Ʒ
	bool isChooseItem(string item);

public:
	vector<string> star3;
	vector<string> star4Person;
	vector<string> star4Weapon;
	vector<string> star5Person;
	vector<string> star5Weapon;
	vector<string> star4Up;
	vector<string> star5Up;

	vector<unsigned int> star4Guar; //4�Ǳ��׼���[δ����������ɫ���������������������]
	vector<unsigned int> star5Guar; //5�Ǳ��׼���[δ����������ɫ��������������������񡢶���]

	vector<PwFunction> star4Function; //4�ǳ������׼��㺯��[δ����������ɫ���������������������]
	vector<PwFunction> star5Function; //5�ǳ������׼��㺯��[δ����������ɫ��������������������񡢶���]

	WishPool(string name = "��Ը", bool hasUp = false, bool hasChoose = false);

	void setBaseItem(vector<string> star3, vector<string> star4Person, vector<string> star4Weapon);
	void setUpItem(vector<string> star4Up, vector<string> star5Up, int upItemType);
	void setStar5Person(vector<string> star5Person);
	void setStar5Weapon(vector<string> star5Weapon);
	void setTemplatePby(int id);  //��Ԥ��õ�ģ�����ó�������[id:1Ϊ�޶���ɫ��2Ϊ������3Ϊ��פ]
	void clearHistory();  //�����ʷ��¼
	void resetPool();  //���ÿ���

	vector<string> getStar5Choose();
	string getPoolName();
	int getUpItemType();

	WishHistory getHistory();
	WishHistory getLastItem();
	WishHistory getLastNItem(int endPos);
	WishHistory getLast10Item();
	WishHistory getCenterItem(int startPos, int endPos);
	short getLast10MaxStar();
	short getLastNMaxStar(unsigned int n);

	void setStar5Choose(vector<string> item); //����
	WishHistory singleWish(); //����
	WishHistory templeWish(); //ʮ����
	WishHistory nWish(unsigned int n); //n����
};