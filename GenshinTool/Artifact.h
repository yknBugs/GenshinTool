#pragma once

//���ļ�����ʥ����ϵͳ
//Ϊ���㣬���еİٷֱȴ���ȫ����ʾΪ��ʾ����ֵ����52%��д��52������0.52

#include <string>
#include <vector>

#include "RandEngine.h"

using namespace std;

#define ARTIFACTPOS_FLOWER 1 //����λ
#define ARTIFACTPOS_WING 2 //��ë��λ
#define ARTIFACTPOS_SAND 3 //ɳ©��λ
#define ARTIFACTPOS_CUP 4 //���Ӳ�λ
#define ARTIFACTPOS_HEAD 5 //ͷ��λ

#define ATTRIBUTE_HP 1 //����ֵ
#define ATTRIBUTE_ATK 2 //������
#define ATTRIBUTE_DEF 3 //������
#define ATTRIBUTE_HPPER 4 //�ٷֱ�����ֵ
#define ATTRIBUTE_ATKPER 5 //�ٷֱȹ�����
#define ATTRIBUTE_DEFPER 6 //�ٷֱȷ�����
#define ATTRIBUTE_ER 7 //Ԫ�س���Ч��
#define ATTRIBUTE_EM 8 //Ԫ�ؾ�ͨ
#define ATTRIBUTE_CRITRATE 9 //������
#define ATTRIBUTE_CRITDMG 10 //�����˺�
#define ATTRIBUTE_HB 11 //���Ƽӳ�
#define ATTRIBUTE_IHB 12 //�����Ƽӳ�
#define ATTRIBUTE_CDRE 13 //��ȴ����
#define ATTRIBUTE_SS 14 //����ǿЧ
#define ATTRIBUTE_DMGPYRO 15 //��Ԫ���˺��ӳ�
#define ATTRIBUTE_DMGHYDRO 16 //ˮԪ���˺��ӳ�
#define ATTRIBUTE_DMGDENDRO 17 //��Ԫ���˺��ӳ�
#define ATTRIBUTE_DMGELEC 18 //��Ԫ���˺��ӳ�
#define ATTRIBUTE_DMGANEMO 19 //��Ԫ���˺��ӳ�
#define ATTRIBUTE_DMGCRYO 20 //��Ԫ���˺��ӳ�
#define ATTRIBUTE_DMGGEO 21 //��Ԫ���˺��ӳ�
#define ATTRIBUTE_DMGPHY 22 //�����˺��ӳ�
#define ATTRIBUTE_RESPYRO 23 //��Ԫ�ؿ���
#define ATTRIBUTE_RESHYDRO 24 //ˮԪ�ؿ���
#define ATTRIBUTE_RESDENDRO 25 //��Ԫ�ؿ���
#define ATTRIBUTE_RESELEC 26 //��Ԫ�ؿ���
#define ATTRIBUTE_RESANEMO 27 //��Ԫ�ؿ���
#define ATTRIBUTE_RESCRYO 28 //��Ԫ�ؿ���
#define ATTRIBUTE_RESGEO 29 //��Ԫ�ؿ���
#define ATTRIBUTE_RESPHY 30 //������

#define ATTRIBUTE_BUFF_EXTRADMG 31 //���ܱ��ʳ���buff
#define ATTRIBUTE_BUFF_DMGBONUS 32 //���˳���buff
#define ATTRIBUTE_BUFF_EXTRAEM 33  //Ԫ�ط�Ӧϵ�����
#define ATTRIBUTE_BUFF_CHANGEDMG 34//��������buff

class Artifact
{
private:
	short star;
	unsigned int level;
	string name;
	int pos; //��λ[������ë��ɳ©�����ӣ�ͷ]

	int mainAttrId;
	double mainAttrValue;

	vector<int> subAttrId;
	vector<double> subAttrValue;

	int randMainAttr(int pos);
	int randSubAttr(int mainAttr, vector<int> subAttr);

public:
	Artifact(string name = "��ֵ�ʥ����", int pos = ARTIFACTPOS_FLOWER, short star = 5, double fullSubAttrP = 0.25);

	void levelUp();

	string getName();
	unsigned int getLevel();
	int getPos();
	short getStar();
	int getMainAttrId();
	double getMainAttrValue();
	int getSubAttrId(unsigned int num);
	double getSubAttrValue(unsigned int num);

	bool operator < (Artifact object);
	bool operator > (Artifact object);

	bool getAttrIsPercent(int attrId);
	string attrIdToString(int attrId);
	double getMainAttrBaseValue(int mainAttr, short star);
	double getMainAttrLvUpValue(int mainAttr, short star);
	vector<double> getSubAttrValueList(int subAttr, short star);
};