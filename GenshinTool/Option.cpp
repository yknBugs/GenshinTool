#include "Option.h"

vector<string> Option::optionList =
{
	"��Ը���ذ汾",
	"��Ը����",
	"��Ը�����ٶ�",
	"��Ը������ɫλ��",
	"ԭʯ����Ԥ����",
	"��Ը��ʷ��¼��ʾ��ʽ",
	"�¼�ʱ��Ԥ����ʾ��ʽ",
	"������Ϣ"
};

vector<bool> Option::isShow =
{
	true,	//��Ը���ذ汾
	true,	//��Ը����
	false,	//��Ը�����ٶ�
	false,	//��Ը������ɫλ��
	true,	//ԭʯ����Ԥ����	
	true,	//��Ը��ʷ��¼��ʾ��ʽ
	true,	//�¼�ʱ��Ԥ����ʾ��ʽ
	true	//������Ϣ
};

vector<string> Option::currentSet = 
{
	"V2.7 �ϰ�",		//��Ը���ذ汾
	"�ر�",			//��Ը����
	"2.0s + 0.4s",	//��Ը�����ٶ�
	"40%��",			//��Ը������ɫλ��
	"�Զ�����",		//ԭʯ����Ԥ����	
	"�Զ�����",		//��Ը��ʷ��¼��ʾ��ʽ
	"����˵��",		//�¼�ʱ��Ԥ����ʾ��ʽ
	"�ر�"			//������Ϣ
};

vector<double> Option::currentChoose =
{
	2.71,	//��Ը���ذ汾
	0.0,	//��Ը����
	20.0,	//��Ը�����ٶ�
	0.4,	//��Ը������ɫλ��
	2.0,	//ԭʯ����Ԥ����	
	2.0,	//��Ը��ʷ��¼��ʾ��ʽ
	2.0,	//�¼�ʱ��Ԥ����ʾ��ʽ
	0.0		//������Ϣ
};

vector<int> Option::optionType =
{
	0,	//��Ը���ذ汾
	0,	//��Ը����
	3,	//��Ը�����ٶ�
	1,	//��Ը������ɫλ��
	0,	//ԭʯ����Ԥ����	
	0,	//��Ը��ʷ��¼��ʾ��ʽ
	0,	//�¼�ʱ��Ԥ����ʾ��ʽ
	0	//������Ϣ
};

vector<string> Option::tipList =
{
	"&CV2.7 �°�Ŀ�������ΪԤ�����ݣ������ο��������Թٷ�����Ϊ׼��",//��Ը���ذ汾
	"&A��������Ը��ʾ���ǰ����ʾһ���򵥵Ķ�����",//��Ը����
	"&A�޸���ʾ��Ը����Ķ����ٶȡ�",	//��Ը�����ٶ�
	"&A�޸���ʾ��Ը���ǰ��������ɫʱ�����������İٷֱȡ�",	//��Ը������ɫλ��
	"&A��ԭʯ����Ԥ������Ա�����ʽ��ʾÿ�տɻ�ȡ�ľ���������",	//ԭʯ����Ԥ����	
	"&A���б����ʽ��ʾ��������Ļ��ͬʱ��ʾ��������ʷ��¼��",	//��Ը��ʷ��¼��ʾ��ʽ
	"&A��С��Ļ���Ա�����ʽչʾ�¼�������ʱ�����ֲ��ֿ��ܳ������⡣",	//�¼�ʱ��Ԥ����ʾ��ʽ
	"&E�����ܽ���������������Ƿ�����������ʱʹ�á�"	//������Ϣ
};

unsigned int Option::getLength()
{
	return (unsigned int)optionList.size();
}

unsigned int Option::getVisibleLength()
{
	unsigned int i = 0;
	unsigned int result = 0;
	for (i = 0; i < optionList.size(); i++)
	{
		if (isShow[i] == true)
		{
			result++;
		}
	}

	return result;
}

vector<string> Option::getChooseList(string name)
{
	if (name == "��Ը���ذ汾")
	{
		vector<string> temp = { "V2.6 �°�", "V2.7 �ϰ�", "V2.7 �°�" };
		return temp;
	}
	else if (name == "��Ը����")
	{
		vector<string> temp = { "�ر�","����" };
		return temp;
	}
	else if (name == "ԭʯ����Ԥ����")
	{
		vector<string> temp = { "�Զ�����","����","�ر�", };
		return temp;
	}
	else if (name == "��Ը��ʷ��¼��ʾ��ʽ")
	{
		vector<string> temp = { "�Զ�����","���","�о�" };
		return temp;
	}
	else if (name == "�¼�ʱ��Ԥ����ʾ��ʽ")
	{
		vector<string> temp = { "����˵��","������","������" };
		return temp;
	}
	else if (name == "������Ϣ")
	{
		vector<string> temp = { "�ر�","����" };
		return temp;
	}
	vector<string> temp;
	return temp;
}

vector<double> Option::getChooseNum(string name)
{
	if (name == "��Ը���ذ汾")
	{
		vector<double> temp = { 2.62, 2.71, 2.72 };
		return temp;
	}
	else if (name == "��Ը����")
	{
		vector<double> temp = { 0.0, 1.0 };
		return temp;
	}
	else if (name == "ԭʯ����Ԥ����")
	{
		vector<double> temp = { 2.0, 1.0, 0.0 };
		return temp;
	}
	else if (name == "��Ը��ʷ��¼��ʾ��ʽ")
	{
		vector<double> temp = { 2.0, 1.0, 0.0 };
		return temp;
	}
	else if (name == "�¼�ʱ��Ԥ����ʾ��ʽ")
	{
		vector<double> temp = { 2.0, 1.0, 0.0 };
		return temp;
	}
	else if (name == "������Ϣ")
	{
		vector<double> temp = { 0.0, 1.0 };
		return temp;
	}
	vector<double> temp;
	return temp;
}

unsigned int Option::getOptionPos(string name)
{
	unsigned int i = 0;
	for (i = 0; i < optionList.size(); i++)
	{
		if (optionList[i] == name)
		{
			return i;
		}
	}

	return 0;
}
