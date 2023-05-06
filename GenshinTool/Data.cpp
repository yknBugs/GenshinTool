#include <fstream>
#include <string>
#include <vector>
#include "Data.h"

Data::Data()
{
	Option option;
	string gameVersion = option.currentSet[option.getOptionPos("祈愿卡池版本")];

	this->star3Item = { "弹弓","神射手之誓","鸦羽弓","翡玉法球","讨龙英杰谭","魔导绪论",
					"黑缨枪","以理服人","沐浴龙血的剑","铁影阔剑","飞天御剑","黎明神剑","冷刃" };
	this->star4Weapon = { "弓藏","祭礼弓","绝弦","西风猎弓","昭心","祭礼残章",
							 "流浪乐章","西风秘典","西风长枪","匣里灭辰","雨裁","祭礼大剑",
							 "钟剑","西风大剑","匣里龙吟","祭礼剑","笛剑","西风剑" };
	this->star4Person = { "罗莎莉亚","辛焱","砂糖","迪奥娜","重云","诺艾尔","班尼特","菲谢尔","凝光",
							 "行秋","北斗","香菱","安柏","雷泽","凯亚","芭芭拉","丽莎","烟菲","早柚",
							 "九条裟罗","托马","五郎","云堇" };
	this->star5Person = { "刻晴","莫娜","七七","迪卢克","琴" };
	this->star5Weapon = { "阿莫斯之弓","天空之翼","四风原典","天空之卷","和璞鸢",
							 "天空之脊","狼的末路","天空之傲","天空之刃","风鹰剑" };
	this->star4NoPerson = { "安柏","凯亚","丽莎" };

	if (gameVersion == "V2.6 下半")
	{
		this->star4UpWeapon = { "西风猎弓","西风长枪","西风秘典","钟剑","西风剑" };
		this->star5UpWeapon = { "雾切之回光","无工之剑" };
		this->star4UpPerson = { { "雷泽","早柚","罗莎莉亚" } };
		this->star5UpPerson = { { "神里绫华" } };
	}
	else if (gameVersion == "V2.7 下半")
	{
		this->star4UpWeapon = { "曚云之月","断浪长鳍","匣里龙吟","雨裁","祭礼残章" };
		this->star5UpWeapon = { "若水","息灾" };
		this->star4UpPerson = { { "久歧忍","行秋","五郎" } };
		this->star5UpPerson = { { "荒泷一斗" } };
	}
	else
	{
		this->star4UpWeapon = { "祭礼弓","千岩长枪","昭心","西风大剑","祭礼剑" };
		this->star5UpWeapon = { "若水","和璞鸢" };
		this->star4UpPerson = { { "芭芭拉","诺艾尔","烟菲" } };
		this->star5UpPerson = { { "夜兰" }, { "魈" } };
	}
}

vector<string> Data::getArtifactHouseList()
{
	vector<string> result = 
	{
		"铭记之谷[风本]",
		"仲夏庭园[雷本]",
		"华池岩柚[宗室本]",
		"无妄引咎密宫[火本]",
		"孤云凌霄之处[岩本]",
		"芬德尼尔之顶[冰本]",
		"山脊守望[苍白本]",
		"椛染之庭[充能本]",
		"沉眠之庭[防御本]",
		"岩中幽谷[攻击本]"
	};
	return result;
}

vector<string> Data::getArtifactCraftList()
{
	vector<string> result =
	{
		"角斗士的终幕礼",
		"流浪大地的乐团",
		"昔日宗室之仪",
		"染血的骑士道"
	};
	return result;
}

vector<vector<string>> Data::getArtifactsList(short star)
{
	if (star == 5)
	{
		vector<vector<string>> result =
		{
			{"翠绿之影","被怜爱的少女"},
			{"如雷的盛怒","平息鸣雷的尊者"},
			{"昔日宗室之仪","染血的骑士道"},
			{"炽烈的炎之魔女","渡过烈火的贤人"},
			{"悠古的磐岩","逆飞的流星"},
			{"冰风迷途的勇士","沉沦之心"},
			{"苍白之火","千岩牢固"},
			{"绝缘之旗印","追忆之注连"},
			{"华馆梦醒形骸记","海染砗磲"},
			{"来歆余响","辰砂往生录"}
		};
		return result;
	}
	else if(star == 4)
	{
		vector<vector<string>> result =
		{
			{"翠绿之影","被怜爱的少女","奇迹"},
			{"如雷的盛怒","平息鸣雷的尊者","行者之心"},
			{"昔日宗室之仪","染血的骑士道","赌徒","学士"},
			{"炽烈的炎之魔女","渡过烈火的贤人","守护之心","武人"},
			{"悠古的磐岩","逆飞的流星","勇士之心"},
			{"冰风迷途的勇士","沉沦之心","赌徒","守护之心"},
			{"苍白之火","千岩牢固","勇士之心","武人"},
			{"绝缘之旗印","追忆之注连","行者之心","奇迹"},
			{"华馆梦醒形骸记","海染砗磲","守护之心","勇士之心"},
			{"来歆余响","辰砂往生录","武人","赌徒"}
		};
		return result;
	}
	else if (star == 3)
	{
		vector<vector<string>> result =
		{
			{"游医","奇迹"},
			{"冒险家","行者之心"},
			{"赌徒","学士"},
			{"守护之心","武人"},
			{"幸运儿","勇士之心"},
			{"赌徒","守护之心"},
			{"勇士之心","武人"},
			{"行者之心","奇迹"},
			{"守护之心","勇士之心"},
			{"武人","赌徒"}
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
	if (listName == "角斗士的终幕礼")
	{
		vector<string> result = { "角斗士的留恋","角斗士的归宿","角斗士的希冀","角斗士的酣醉","角斗士的凯旋" };
		return result;
	}
	else if (listName == "流浪大地的乐团")
	{
		vector<string> result = { "乐团的晨光","琴师的箭羽","终幕的时计","吟游者之壶","指挥的礼帽" };
		return result;
	}
	else if (listName == "翠绿之影")
	{
		vector<string> result = { "野花记忆的绿野","猎人青翠的箭羽","翠绿猎人的笃定","翠绿猎人的容器","翠绿的猎人之冠" };
		return result;
	}
	else if (listName == "被怜爱的少女")
	{
		vector<string> result = { "远方的少女之心","少女飘摇的思念","少女苦短的良辰","少女片刻的闲暇","少女易逝的芳颜" };
		return result;
	}
	else if (listName == "如雷的盛怒")
	{
		vector<string> result = { "雷鸟的怜悯","雷鸟的孑遗","雷霆的时计","降雷的凶兆","唤雷者的头冠" };
		return result;
	}
	else if (listName == "平息鸣雷的尊者")
	{
		vector<string> result = { "平雷之心","平雷之羽","平雷之刻","平雷之器","平雷之冠" };
		return result;
	}
	else if (listName == "昔日宗室之仪")
	{
		vector<string> result = { "宗室之花","宗室之翎","宗室时计","宗室银瓮","宗室面具" };
		return result;
	}
	else if (listName == "染血的骑士道")
	{
		vector<string> result = { "染血的铁之心","染血的黑之羽","骑士染血之时","染血的骑士之杯","染血的铁假面" };
		return result;
	}
	else if (listName == "炽烈的炎之魔女")
	{
		vector<string> result = { "魔女的炎之花","魔女常燃之羽","魔女破灭之时","魔女的心之火","焦灼的魔女帽" };
		return result;
	}
	else if (listName == "渡过烈火的贤人")
	{
		vector<string> result = { "渡火者的决绝","渡火者的解脱","渡火者的煎熬","渡火者的醒悟","渡火者的智慧" };
		return result;
	}
	else if (listName == "悠古的磐岩")
	{
		vector<string> result = { "磐陀裂生之花","嵯峨群峰之翼","星罗圭璧之晷","巉岩琢塑之樽","不动玄石之相" };
		return result;
	}
	else if (listName == "逆飞的流星")
	{
		vector<string> result = { "夏祭之花","夏祭终末","夏祭之刻","夏祭水玉","夏祭之面" };
		return result;
	}
	else if (listName == "冰风迷途的勇士")
	{
		vector<string> result = { "历经风雪的思念","摧冰而行的执望","冰雪故园的终期","遍结寒霜的傲骨","破冰踏雪的回音" };
		return result;
	}
	else if (listName == "沉沦之心")
	{
		vector<string> result = { "饰金胸花","追忆之风","坚铜罗盘","沉波之盏","酒渍船帽" };
		return result;
	}
	else if (listName == "苍白之火")
	{
		vector<string> result = { "无垢之花","贤医之羽","停摆之刻","超越之盏","嗤笑之面" };
		return result;
	}
	else if (listName == "千岩牢固")
	{
		vector<string> result = { "勋绩之花","昭武翎羽","金铜时晷","盟誓金爵","将帅兜鍪" };
		return result;
	}
	else if (listName == "绝缘之旗印")
	{
		vector<string> result = { "明威之镡","切落之羽","雷云之笼","绯花之壶","华饰之兜" };
		return result;
	}
	else if (listName == "追忆之注连")
	{
		vector<string> result = { "羁缠之花","思忆之矢","朝露之时","祈望之心","无常之面" };
		return result;
	}
	else if (listName == "华馆梦醒形骸记")
	{
		vector<string> result = { "荣花之期","华管之羽","众生之谣","梦醒之瓢","形骸之笠" };
		return result;
	}
	else if (listName == "海染砗磲")
	{
		vector<string> result = { "海染之花","渊宫之羽","离别之贝","真珠之笼","海祈之冠" };
		return result;
	}
	else if (listName == "来歆余响")
	{
		vector<string> result = { "魂香之花","垂玉之叶","祝祀之凭","涌泉之盏","浮溯之珏" };
		return result;
	}
	else if (listName == "辰砂往生录")
	{
		vector<string> result = { "生灵之华","潜光片羽","阳辔之遗","结契之刻","虺雷之姿" };
		return result;
	}
	else if (listName == "勇士之心")
	{
		vector<string> result = { "勇士的勋章","勇士的期许","勇士的坚毅","勇士的壮行","勇士的冠冕" };
		return result;
	}
	else if (listName == "教官")
	{
		vector<string> result = { "教官的胸花","教官的羽饰","教官的怀表","教官的茶杯","教官的帽子" };
		return result;
	}
	else if (listName == "流放者")
	{
		vector<string> result = { "流放者之花","流放者之羽","流放者怀表","流放者之杯","流放者头冠" };
		return result;
	}
	else if (listName == "战狂")
	{
		vector<string> result = { "战狂的蔷薇","战狂的翎羽","战狂的时计","战狂的骨杯","战狂的鬼面" };
		return result;
	}
	else if (listName == "武人")
	{
		vector<string> result = { "武人的红花","武人的羽饰","武人的水漏","武人的酒杯","武人的头巾" };
		return result;
	}
	else if (listName == "学士")
	{
		vector<string> result = { "学士的书签","学士的羽笔","学士的时钟","学士的墨杯","学士的镜片" };
		return result;
	}
	else if (listName == "赌徒")
	{
		vector<string> result = { "赌徒的胸花","赌徒的羽饰","赌徒的怀表","赌徒的骰盅","赌徒的耳环" };
		return result;
	}
	else if (listName == "奇迹")
	{
		vector<string> result = { "奇迹之花","奇迹之羽","奇迹之沙","奇迹之杯","奇迹耳坠" };
		return result;
	}
	else if (listName == "行者之心")
	{
		vector<string> result = { "故人之心","归乡之羽","逐光之石","异国之盏","感别之冠" };
		return result;
	}
	else if (listName == "守护之心")
	{
		vector<string> result = { "守护之花","守护徽印","守护座钟","守护之皿","守护束带" };
		return result;
	}
	else if (listName == "幸运儿")
	{
		vector<string> result = { "幸运儿绿花","幸运儿鹰羽","幸运儿沙漏","幸运儿之杯","幸运儿银冠" };
		return result;
	}
	else if (listName == "冒险家")
	{
		vector<string> result = { "冒险家之花","冒险家尾羽","冒险家怀表","冒险家金杯","冒险家头带" };
		return result;
	}
	else if (listName == "游医")
	{
		vector<string> result = { "游医的银莲","游医的枭羽","游医的怀钟","游医的药壶","游医的方巾" };
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
		string t = "未找到相应文本。\n";
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
		string t = "未找到相应文本。\n";
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
