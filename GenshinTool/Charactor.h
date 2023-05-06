#pragma once

//���ļ������ɫ
//Ϊ���㣬���еİٷֱ�ȫ����ʾΪ��ʵ��ֵ����52%��д��0.52������52

#include "Artifact.h"

#define ELEMENT_DMGBONUS 1  //������Ӧ
#define ELEMENT_EXTRADMG 2  //��䷴Ӧ
#define ELEMENT_SHEILD 3    //�ᾧ��Ӧ
#define ELEMENT_SUPERCON 11 //������Ӧ
#define ELEMENT_SWIRL 12	//��ɢ��Ӧ
#define ELEMENT_ELECHAR 13  //�е練Ӧ
#define ELEMENT_OVERLOAD 14 //���ط�Ӧ
#define ELEMENT_SHUTTER 15	//�����Ӧ
#define ELEMENT_SWIRL_PYRO 51		//����ɢ��Ӧ
#define ELEMENT_SWIRL_HYDRO 52		//ˮ��ɢ��Ӧ
#define ELEMENT_SWIRL_ELECTRO 53	//����ɢ��Ӧ
#define ELEMENT_SWIRL_CRYO 54		//����ɢ��Ӧ

#define DMGPLUSAREA_ATK 1 //����������
#define DMGPLUSAREA_SKILLRATE 2 //���ܱ��ʳ���
#define DMGPLUSAREA_CRITDMG 3 //��������
#define DMGPLUSAREA_DMGBONUS 4 //���˳���
#define DMGPLUSAREA_ELEMENT 5 //Ԫ�ط�Ӧ����
#define DMGPLUSAREA_RES 6 //���Գ���
#define DMGPLUSAREA_DEF 7 //����������

#define ELEMENTAL_PYRO 1 //��Ԫ��
#define ELEMENTAL_HYDRO 2 //ˮԪ��
#define ELEMENTAL_DENDRO 3 //��Ԫ��
#define ELEMENTAL_ELECTRO 4 //��Ԫ��
#define ELEMENTAL_ANEMO 5 //��Ԫ��
#define ELEMENTAL_CRYO 6 //��Ԫ��
#define ELEMENTAL_GEO 7 //��Ԫ��
#define ELEMENTAL_PHYSICAL 8 //����

class Charactor
{
private:
	unsigned int level;
	double baseATK;  //����������
	double baseHP;   //��������ֵ
	double baseDEF;  //����������
	vector<double> extraAttr;  //���������

	vector<string> buffName;
	vector<int> buffId;
	vector<double> buffValue;

public:
	Charactor(unsigned int level = 1, double baseATK = 10.0, double baseHP = 1000.0, double baseDEF = 100.0);

	//��Ԫ�ؾ�ͨ����ת��Ϊ������˺���ʾ�ٷֱ�
	double translateEM(int id, double EM);
	//����ָ���������������ʾ�ľ�����ֵ
	double getAttrValue(int attrId);
	//�����˺�������Ϊ:���ܱ��ʣ��Ƿ񱩻����˺���Ԫ�����ͣ����ˣ�Ԫ�ط�Ӧ��������[1.5��2]
	double caculateDMG(double skillRate, bool hasCritDMG, int elementId, Charactor enimy, double elementType = 1.0);
	//����ƽ���˺�������������ΪȨ�أ�������Ϊ:���ܱ��ʣ��˺���Ԫ�����ͣ����ˣ�Ԫ�ط�Ӧ��������[1.5��2]
	double caculateAveDMG(double skillRate, int elementId, Charactor enimy, double elementType = 1.0);
	//����һ��ʥ���︱�����������˺�����������Ϊ:����id���˺���Ԫ�����ͣ��Ƿ��Ǳ����˺�������Ԫ�ط�Ӧ��������[1.5��2]
	double caSingleAttrAdv(int attrId, int elementId, bool considerBurst = false, double elementType = 1.0);
	//����Ԫ�ط�Ӧ��ɵĶ����˺�������ΪԪ�ط�Ӧ���ͣ�����
	double caculateEMDMG(int elementId, Charactor enimy);
	//����Ԫ�ط�Ӧ��ɵĶ����˺�������ΪԪ�ط�Ӧ���ͣ����ˣ��˺���Ԫ������
	double caculateEMDMG(int elementId, Charactor enimy, int elementType);

	void addBuff(string buffName, int buffId, double buffValue);
	void clearBuff(string buffName);
	int getBuffAttrId(string buffName);
	double getBuffAttrValue(string buffName);
	unsigned int getBuffLength();
	string getBuffName(unsigned int pos);
	int getBuffId(unsigned int pos);
	double getBuffValue(unsigned int pos);
	void deleteBuff(unsigned int pos);

	//��ȡ������������ֵ������Ϊ:����id���������˺���Ԫ��id
	double getDMGBonusRate(int areaId, int elementId);
	//��ȡ������������ֵ������Ϊ:����id���������˺���Ԫ��id�����ܱ���
	double getDMGBonusRate(int areaId, int elementId, double skillRate);
	//��ȡ������������ֵ������Ϊ:����id���������˺���Ԫ��id������
	double getDMGBonusRate(int areaId, int elementId, Charactor enimy);
	//��ȡ���Ԫ�ط�Ӧ�Ļ����˺�
	double getEMBaseDMG(unsigned int level = 0);

	//��ȡbuff��ת����ʥ�������Ч�����ĸ���
	double getUsefulAttrCount(vector<int> attrList);
	double getUsefulAttrCount(int attrList);

	//��ȡbuff��װ���ṩ�Ķ�������
	double getExtraAttr(int attrId);
	unsigned int getLevel();
	double getBaseATK();
	double getBaseHP();
	double getBaseDEF();
};