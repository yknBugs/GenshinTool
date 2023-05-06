#include <fstream>
#include <string>
#include <vector>
#include "Data.h"

Data::Data()
{
	Option option;
	string gameVersion = option.currentSet[option.getOptionPos("��Ը���ذ汾")];

	this->star3Item = { "����","������֮��","ѻ��","������","����Ӣ��̷","ħ������",
					"��ӧǹ","�������","��ԡ��Ѫ�Ľ�","��Ӱ����","��������","������","����" };
	this->star4Weapon = { "����","����","����","�����Թ�","����","�������",
							 "��������","�����ص�","���糤ǹ","ϻ����","���","�����",
							 "�ӽ�","�����","ϻ������","����","�ѽ�","���罣" };
	this->star4Person = { "��ɯ����","����","ɰ��","�ϰ���","����","ŵ����","������","��л��","����",
							 "����","����","����","����","����","����","�Ű���","��ɯ","�̷�","����",
							 "��������","����","����","����" };
	this->star5Person = { "����","Ī��","����","��¬��","��" };
	this->star5Weapon = { "��Ī˹֮��","���֮��","�ķ�ԭ��","���֮��","����",
							 "���֮��","�ǵ�ĩ·","���֮��","���֮��","��ӥ��" };
	this->star4NoPerson = { "����","����","��ɯ" };

	if (gameVersion == "V2.6 �°�")
	{
		this->star4UpWeapon = { "�����Թ�","���糤ǹ","�����ص�","�ӽ�","���罣" };
		this->star5UpWeapon = { "����֮�ع�","�޹�֮��" };
		this->star4UpPerson = { { "����","����","��ɯ����" } };
		this->star5UpPerson = { { "����类�" } };
	}
	else if (gameVersion == "V2.7 �°�")
	{
		this->star4UpWeapon = { "����֮��","���˳���","ϻ������","���","�������" };
		this->star5UpWeapon = { "��ˮ","Ϣ��" };
		this->star4UpPerson = { { "������","����","����" } };
		this->star5UpPerson = { { "����һ��" } };
	}
	else
	{
		this->star4UpWeapon = { "����","ǧ�ҳ�ǹ","����","�����","����" };
		this->star5UpWeapon = { "��ˮ","����" };
		this->star4UpPerson = { { "�Ű���","ŵ����","�̷�" } };
		this->star5UpPerson = { { "ҹ��" }, { "��" } };
	}
}

vector<string> Data::getArtifactHouseList()
{
	vector<string> result = 
	{
		"����֮��[�籾]",
		"����ͥ԰[�ױ�]",
		"��������[���ұ�]",
		"���������ܹ�[��]",
		"��������֮��[�ұ�]",
		"�ҵ����֮��[����]",
		"ɽ������[�԰ױ�]",
		"��Ⱦ֮ͥ[���ܱ�]",
		"����֮ͥ[������]",
		"�����Ĺ�[������]"
	};
	return result;
}

vector<string> Data::getArtifactCraftList()
{
	vector<string> result =
	{
		"�Ƕ�ʿ����Ļ��",
		"���˴�ص�����",
		"��������֮��",
		"ȾѪ����ʿ��"
	};
	return result;
}

vector<vector<string>> Data::getArtifactsList(short star)
{
	if (star == 5)
	{
		vector<vector<string>> result =
		{
			{"����֮Ӱ","����������Ů"},
			{"���׵�ʢŭ","ƽϢ���׵�����"},
			{"��������֮��","ȾѪ����ʿ��"},
			{"���ҵ���֮ħŮ","�ɹ��һ������"},
			{"�ƹŵ�����","��ɵ�����"},
			{"������;����ʿ","����֮��"},
			{"�԰�֮��","ǧ���ι�"},
			{"��Ե֮��ӡ","׷��֮ע��"},
			{"���������κ���","��Ⱦ���"},
			{"�������","��ɰ����¼"}
		};
		return result;
	}
	else if(star == 4)
	{
		vector<vector<string>> result =
		{
			{"����֮Ӱ","����������Ů","�漣"},
			{"���׵�ʢŭ","ƽϢ���׵�����","����֮��"},
			{"��������֮��","ȾѪ����ʿ��","��ͽ","ѧʿ"},
			{"���ҵ���֮ħŮ","�ɹ��һ������","�ػ�֮��","����"},
			{"�ƹŵ�����","��ɵ�����","��ʿ֮��"},
			{"������;����ʿ","����֮��","��ͽ","�ػ�֮��"},
			{"�԰�֮��","ǧ���ι�","��ʿ֮��","����"},
			{"��Ե֮��ӡ","׷��֮ע��","����֮��","�漣"},
			{"���������κ���","��Ⱦ���","�ػ�֮��","��ʿ֮��"},
			{"�������","��ɰ����¼","����","��ͽ"}
		};
		return result;
	}
	else if (star == 3)
	{
		vector<vector<string>> result =
		{
			{"��ҽ","�漣"},
			{"ð�ռ�","����֮��"},
			{"��ͽ","ѧʿ"},
			{"�ػ�֮��","����"},
			{"���˶�","��ʿ֮��"},
			{"��ͽ","�ػ�֮��"},
			{"��ʿ֮��","����"},
			{"����֮��","�漣"},
			{"�ػ�֮��","��ʿ֮��"},
			{"����","��ͽ"}
		};
		return result;
	}
	else
	{
		vector<vector<string>> result = {{}};
		return result;
	}
}

vector<string> Data::getArtifactList(string listName)
{
	if (listName == "�Ƕ�ʿ����Ļ��")
	{
		vector<string> result = { "�Ƕ�ʿ������","�Ƕ�ʿ�Ĺ���","�Ƕ�ʿ��ϣ��","�Ƕ�ʿ�ĺ���","�Ƕ�ʿ�Ŀ���" };
		return result;
	}
	else if (listName == "���˴�ص�����")
	{
		vector<string> result = { "���ŵĳ���","��ʦ�ļ���","��Ļ��ʱ��","������֮��","ָ�ӵ���ñ" };
		return result;
	}
	else if (listName == "����֮Ӱ")
	{
		vector<string> result = { "Ұ���������Ұ","�������ļ���","�������˵��ƶ�","�������˵�����","���̵�����֮��" };
		return result;
	}
	else if (listName == "����������Ů")
	{
		vector<string> result = { "Զ������Ů֮��","��ŮƮҡ��˼��","��Ů��̵�����","��ŮƬ�̵���Ͼ","��Ů���ŵķ���" };
		return result;
	}
	else if (listName == "���׵�ʢŭ")
	{
		vector<string> result = { "���������","���������","������ʱ��","���׵�����","�����ߵ�ͷ��" };
		return result;
	}
	else if (listName == "ƽϢ���׵�����")
	{
		vector<string> result = { "ƽ��֮��","ƽ��֮��","ƽ��֮��","ƽ��֮��","ƽ��֮��" };
		return result;
	}
	else if (listName == "��������֮��")
	{
		vector<string> result = { "����֮��","����֮��","����ʱ��","��������","�������" };
		return result;
	}
	else if (listName == "ȾѪ����ʿ��")
	{
		vector<string> result = { "ȾѪ����֮��","ȾѪ�ĺ�֮��","��ʿȾѪ֮ʱ","ȾѪ����ʿ֮��","ȾѪ��������" };
		return result;
	}
	else if (listName == "���ҵ���֮ħŮ")
	{
		vector<string> result = { "ħŮ����֮��","ħŮ��ȼ֮��","ħŮ����֮ʱ","ħŮ����֮��","���Ƶ�ħŮñ" };
		return result;
	}
	else if (listName == "�ɹ��һ������")
	{
		vector<string> result = { "�ɻ��ߵľ���","�ɻ��ߵĽ���","�ɻ��ߵļ尾","�ɻ��ߵ�����","�ɻ��ߵ��ǻ�" };
		return result;
	}
	else if (listName == "�ƹŵ�����")
	{
		vector<string> result = { "��������֮��","�϶�Ⱥ��֮��","���޹��֮��","�f������֮��","������ʯ֮��" };
		return result;
	}
	else if (listName == "��ɵ�����")
	{
		vector<string> result = { "�ļ�֮��","�ļ���ĩ","�ļ�֮��","�ļ�ˮ��","�ļ�֮��" };
		return result;
	}
	else if (listName == "������;����ʿ")
	{
		vector<string> result = { "������ѩ��˼��","�ݱ����е�ִ��","��ѩ��԰������","��Ắ˪�İ���","�Ʊ�̤ѩ�Ļ���" };
		return result;
	}
	else if (listName == "����֮��")
	{
		vector<string> result = { "�ν��ػ�","׷��֮��","��ͭ����","����֮յ","���մ�ñ" };
		return result;
	}
	else if (listName == "�԰�֮��")
	{
		vector<string> result = { "�޹�֮��","��ҽ֮��","ͣ��֮��","��Խ֮յ","��Ц֮��" };
		return result;
	}
	else if (listName == "ǧ���ι�")
	{
		vector<string> result = { "ѫ��֮��","��������","��ͭʱ��","���Ľ��","��˧����" };
		return result;
	}
	else if (listName == "��Ե֮��ӡ")
	{
		vector<string> result = { "����֮��","����֮��","����֮��","系�֮��","����֮��" };
		return result;
	}
	else if (listName == "׷��֮ע��")
	{
		vector<string> result = { "�֮��","˼��֮ʸ","��¶֮ʱ","����֮��","�޳�֮��" };
		return result;
	}
	else if (listName == "���������κ���")
	{
		vector<string> result = { "�ٻ�֮��","����֮��","����֮ҥ","����֮ư","�κ�֮��" };
		return result;
	}
	else if (listName == "��Ⱦ���")
	{
		vector<string> result = { "��Ⱦ֮��","Ԩ��֮��","���֮��","����֮��","����֮��" };
		return result;
	}
	else if (listName == "�������")
	{
		vector<string> result = { "����֮��","����֮Ҷ","ף��֮ƾ","ӿȪ֮յ","����֮��" };
		return result;
	}
	else if (listName == "��ɰ����¼")
	{
		vector<string> result = { "����֮��","Ǳ��Ƭ��","����֮��","����֮��","���֮��" };
		return result;
	}
	else if (listName == "��ʿ֮��")
	{
		vector<string> result = { "��ʿ��ѫ��","��ʿ������","��ʿ�ļ���","��ʿ��׳��","��ʿ�Ĺ���" };
		return result;
	}
	else if (listName == "�̹�")
	{
		vector<string> result = { "�̹ٵ��ػ�","�̹ٵ�����","�̹ٵĻ���","�̹ٵĲ豭","�̹ٵ�ñ��" };
		return result;
	}
	else if (listName == "������")
	{
		vector<string> result = { "������֮��","������֮��","�����߻���","������֮��","������ͷ��" };
		return result;
	}
	else if (listName == "ս��")
	{
		vector<string> result = { "ս���Ǿޱ","ս�������","ս���ʱ��","ս��ĹǱ�","ս��Ĺ���" };
		return result;
	}
	else if (listName == "����")
	{
		vector<string> result = { "���˵ĺ컨","���˵�����","���˵�ˮ©","���˵ľƱ�","���˵�ͷ��" };
		return result;
	}
	else if (listName == "ѧʿ")
	{
		vector<string> result = { "ѧʿ����ǩ","ѧʿ�����","ѧʿ��ʱ��","ѧʿ��ī��","ѧʿ�ľ�Ƭ" };
		return result;
	}
	else if (listName == "��ͽ")
	{
		vector<string> result = { "��ͽ���ػ�","��ͽ������","��ͽ�Ļ���","��ͽ������","��ͽ�Ķ���" };
		return result;
	}
	else if (listName == "�漣")
	{
		vector<string> result = { "�漣֮��","�漣֮��","�漣֮ɳ","�漣֮��","�漣��׹" };
		return result;
	}
	else if (listName == "����֮��")
	{
		vector<string> result = { "����֮��","����֮��","���֮ʯ","���֮յ","�б�֮��" };
		return result;
	}
	else if (listName == "�ػ�֮��")
	{
		vector<string> result = { "�ػ�֮��","�ػ���ӡ","�ػ�����","�ػ�֮��","�ػ�����" };
		return result;
	}
	else if (listName == "���˶�")
	{
		vector<string> result = { "���˶��̻�","���˶�ӥ��","���˶�ɳ©","���˶�֮��","���˶�����" };
		return result;
	}
	else if (listName == "ð�ռ�")
	{
		vector<string> result = { "ð�ռ�֮��","ð�ռ�β��","ð�ռһ���","ð�ռҽ�","ð�ռ�ͷ��" };
		return result;
	}
	else if (listName == "��ҽ")
	{
		vector<string> result = { "��ҽ������","��ҽ������","��ҽ�Ļ���","��ҽ��ҩ��","��ҽ�ķ���" };
		return result;
	}
	else
	{
		vector<string> result;
		return result;
	}
}

vector<string> Data::getLimitWishList(short star, bool isLocal, int style, int poolId)
{
	vector<string> list;
	int temp = poolId - 1;
	if (star == 3)
	{
		return this->star3Item;
	}
	else if (star == 4 && isLocal == true)
	{
		return this->star4UpPerson[temp];
	}
	else if (star == 4 && isLocal == false && style == 0)
	{
		unsigned int i = 0;
		unsigned int j = 0;
		unsigned int temp = 0;
		for (i = 0; i < this->star4Person.size(); i++)
		{
			temp = 0;
			for (j = 0; j < this->star4UpPerson[temp].size(); j++)
			{
				if (this->star4Person[i] == this->star4UpPerson[temp][j])
				{
					temp++;
					break;
				}
			}
			for (j = 0; j < this->star4NoPerson.size(); j++)
			{
				if (this->star4Person[i] == this->star4NoPerson[j])
				{
					temp++;
					break;
				}
			}
			if (temp == 0)
			{
				list.push_back(this->star4Person[i]);
			}
		}
		return list;
	}
	else if (star == 4 && isLocal == false && style == 1)
	{
		return this->star4Weapon;
	}
	else if (star == 5 && isLocal == false)
	{
		unsigned int i = 0;
		unsigned int j = 0;
		unsigned int temp = 0;
		for (i = 0; i < this->star5Person.size(); i++)
		{
			temp = 0;
			for (j = 0; j < this->star5UpPerson[temp].size(); j++)
			{
				if (this->star5Person[i] == this->star5UpPerson[temp][j])
				{
					temp++;
					break;
				}
			}
			if (temp == 0)
			{
				list.push_back(this->star5Person[i]);
			}
		}
		return list;
	}
	else if (star == 5 && isLocal == true)
	{
		return this->star5UpPerson[temp];
	}
	return list;
}

vector<string> Data::getWeaponWishList(short star, bool isLocal, int style, int poolId)
{
	vector<string> list;
	if (star == 3)
	{
		return this->star3Item;
	}
	else if (star == 4 && isLocal == true)
	{
		return this->star4UpWeapon;
	}
	else if (star == 4 && isLocal == false && style == 0)
	{
		unsigned int i = 0;
		unsigned int j = 0;
		unsigned int temp = 0;
		for (i = 0; i < this->star4Person.size(); i++)
		{
			temp = 0;
			for (j = 0; j < this->star4NoPerson.size(); j++)
			{
				if (this->star4Person[i] == this->star4NoPerson[j])
				{
					temp++;
					break;
				}
			}
			if (temp == 0)
			{
				list.push_back(this->star4Person[i]);
			}
		}
		return list;
	}
	else if (star == 4 && isLocal == false && style == 1)
	{
		unsigned int i = 0;
		unsigned int j = 0;
		unsigned int temp = 0;
		for (i = 0; i < this->star4Weapon.size(); i++)
		{
			temp = 0;
			for (j = 0; j < this->star4UpWeapon.size(); j++)
			{
				if (this->star4Weapon[i] == this->star4UpWeapon[j])
				{
					temp++;
					break;
				}
			}
			if (temp == 0)
			{
				list.push_back(this->star4Weapon[i]);
			}
		}
		return list;
	}
	else if (star == 5 && isLocal == false)
	{
		unsigned int i = 0;
		unsigned int j = 0;
		unsigned int temp = 0;
		for (i = 0; i < this->star5Weapon.size(); i++)
		{
			temp = 0;
			for (j = 0; j < this->star5UpWeapon.size(); j++)
			{
				if (this->star5Weapon[i] == this->star5UpWeapon[j])
				{
					temp++;
					break;
				}
			}
			if (temp == 0)
			{
				list.push_back(this->star5Weapon[i]);
			}
		}
		return list;
	}
	else if (star == 5 && isLocal == true)
	{
		return this->star5UpWeapon;
	}
	return list;
}

vector<string> Data::getStayWishList(short star, int style)
{
	if (star == 3)
	{
		return this->star3Item;
	}
	else if (star == 4 && style == 0)
	{
		return this->star4Person;
	}
	else if (star == 4 && style == 1)
	{
		return this->star4Weapon;
	}
	else if (star == 5 && style == 0)
	{
		return this->star5Person;
	}
	else if (star == 5 && style == 1)
	{
		return this->star5Weapon;
	}
	vector<string> list;
	return list;
}

vector<string> Data::getFirstWishList(short star)
{
	vector<string> list;
	if (star == 3)
	{
		return this->star3Item;
	}
	else if (star == 4)
	{
		unsigned int i = 0;
		unsigned int j = 0;
		unsigned int temp = 0;
		for (i = 0; i < this->star4Person.size(); i++)
		{
			temp = 0;
			for (j = 0; j < this->star4NoPerson.size(); j++)
			{
				if (this->star4Person[i] == this->star4NoPerson[j])
				{
					temp++;
					break;
				}
			}
			if (temp == 0)
			{
				list.push_back(this->star4Person[i]);
			}
		}
		return list;
	}
	else if (star == 5)
	{
		return this->star5Person;
	}
	return list;
}

vector<string> Data::getItemList(short star, int style)
{
	vector<string> list;
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int k = 0;
	bool hasFind = false;

	if(star == 5)
	{
		if (style == 0)
		{
			list = this->star5Person;
			for (i = 0; i < (unsigned int)this->star5UpPerson.size(); i++)
			{
				for (j = 0; j < (unsigned int)this->star5UpPerson[i].size(); j++)
				{
					hasFind = false;
					for (k = 0; k < (unsigned int)this->star5Person.size(); k++)
					{
						if (this->star5Person[k] == this->star5UpPerson[i][j])
						{
							hasFind = true;
							break;
						}
					}
					if (hasFind == false)
					{
						list.insert(list.begin(), this->star5UpPerson[i][j]);
					}
				}
			}
			return list;
		}
		else
		{
			list = this->star5Weapon;
			for (i = 0; i < (unsigned int)this->star5UpWeapon.size(); i++)
			{
				hasFind = false;
				for (j = 0; j < (unsigned int)this->star5Weapon.size(); j++)
				{
					if (this->star5Weapon[j] == this->star5UpWeapon[i])
					{
						hasFind = true;
						break;
					}
				}
				if (hasFind == false)
				{
					list.insert(list.begin(), this->star5UpWeapon[i]);
				}
			}
			return list;
		}
	}
	else if (star == 4)
	{
		if (style == 0)
		{
			list = this->star4Person;
			for (i = 0; i < (unsigned int)this->star4UpPerson.size(); i++)
			{
				for (j = 0; j < (unsigned int)this->star4UpPerson[i].size(); j++)
				{
					hasFind = false;
					for (k = 0; k < (unsigned int)this->star4Person.size(); k++)
					{
						if (this->star4Person[k] == this->star4UpPerson[i][j])
						{
							hasFind = true;
							break;
						}
					}
					if (hasFind == false)
					{
						list.insert(list.begin(), this->star4UpPerson[i][j]);
					}
				}
			}
			return list;
		}
		else
		{
			list = this->star4Weapon;
			for (i = 0; i < (unsigned int)this->star4UpWeapon.size(); i++)
			{
				hasFind = false;
				for (j = 0; j < (unsigned int)this->star4Weapon.size(); j++)
				{
					if (this->star4Weapon[j] == this->star4UpWeapon[i])
					{
						hasFind = true;
						break;
					}
				}
				if (hasFind == false)
				{
					list.insert(list.begin(), this->star4UpWeapon[i]);
				}
			}
			return list;
		}
	}
	else
	{
		return this->star3Item;
	}
}

unsigned int Data::getLimitWishCount()
{
	return (unsigned int)this->star5UpPerson.size();
}

string Data::readText(string fileName, string textName)
{
	if (textName == "Null")
	{
		string t = "δ�ҵ���Ӧ�ı���\n";
		return t;
	}

	fstream sourceText(fileName);
	unsigned int i = 0;
	char matcher[20] = { '\0' };
	char temp = '\0';
	bool coo = false;
	string command = "Null";
	string text = "";
	bool hasFind = false;

	while (sourceText.eof() == false)
	{
		temp = (char)sourceText.get();
		if (temp == '\"' && command == "Null")
		{
			if (coo == false)
			{
				i = 0;
				coo = true;
				continue;
			}
			else
			{
				command.assign(matcher);
				coo = false;
				continue;
			}
		}

		if (coo == true && command == "Null")
		{
			if (i < 18)
			{
				matcher[i] = temp;
				matcher[i + 1] = '\0';
				i++;
			}
		}

		if (temp == '{' && command != "Null")
		{
			coo = true;
			continue;
		}
		if (temp == '}' && command != "Null")
		{
			coo = false;
			command = "Null";
			continue;
		}

		if (coo == true && command == textName)
		{
			hasFind = true;
			text.push_back(temp);
			continue;
		}
	}

	sourceText.close();

	if (hasFind == false)
	{
		string t = "δ�ҵ���Ӧ�ı���\n";
		return t;
	}

	return text;
}

string Data::openFile(string path)
{
	if (path == "Null" || path == "")
	{
		string t = "";
		return t;
	}

	fstream sourceText(path);
	char temp = '\0';
	string text = "";
	
	if (!sourceText)
	{
		string t = "";
		return t;
	}

	while (sourceText.eof() == false)
	{
		temp = (char)sourceText.get();
		text.push_back(temp);
	}

	sourceText.close();

	return text;
}
