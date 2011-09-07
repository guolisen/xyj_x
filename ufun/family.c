// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

mapping _family_tab = ([
	0			: ({ 0,			0,		0}),
	"�Ϻ�����ɽ"	: ({ "����ɽ",	"pt",	HIY }),
	"����ɽ���Ƕ�"	: ({ "����ɽ",	"fc",	HIY }),
	"��ׯ��"		: ({ "��ׯ��",	"wzg",	HIY }),
	"�¹�"		: ({ "�¹�",		"moon", HIY }),

	"������"		: ({ "������",	"jjf",	HIY }),
	"���޵ظ�"	: ({ "�ظ�",		"hell", HIY }),
	"��������"	: ({ "����",		"lg",	HIY }),

	"��ѩɽ"		: ({ "��ѩɽ",	"xs",	HIY }),
	"�ݿ�ɽ�޵׶�"	: ({ "�޵׶�",	"wdd",	HIY }),	
	"���ƶ�"		: ({ "���ƶ�",	"hyd",	HIY }),
	"��˿��"		: ({ "��˿��",	"psd",	HIY }),
]);

//���ɼ��
string short(object who)
{
	return _family_tab[who->query("family/family_name")][0];
}

//����id
string id(object who)
{
	return _family_tab[who->query("family/family_name")][1];
}

//����idת����
string id_to_name(string id)
{
	foreach(string name, mixed* arr in _family_tab) {
		if(arr[1] == id) return name;
	}
	return 0;
}

//������ɫ
string color(object who)
{
	return _family_tab[who->query("family/family_name")][2];
}

mapping _skills = ([
	"�Ϻ�����ɽ"	: ({
		({ "literate" }),
			
		({ "jienan-zhi",		"unarmed" }), 	
		({ "lotusmove",			"dodge" }),
			
		({ "lotusforce",		"force" }),
		({ "buddhism",			"spells" }),

		({ "lunhui-zhang",		"staff",		"parry" }),		
	}),
	"����ɽ���Ƕ�"	: ({
		({ "literate" }),
			
		({ "puti-zhi",			"unarmed" }), 	
		({ "jindouyun",			"dodge" }),
			
		({ "wuxiangforce",		"force" }),
		({ "dao",				"spells" }),

		({ "qianjun-bang",		"stick",		"parry" }),
		({ "liangyi-sword",		"sword" }),
	}),
	"��ׯ��"		: ({
		({ "literate" }),
			
		({ "wuxing-quan",		"unarmed" }),
		({ "baguazhen",			"dodge" }),
			
		({ "zhenyuan-force",	"force" }),
		({ "taiyi",				"spells" }),

		({ "kaishan-chui",		"hammer",	"parry" }),
		({ "sanqing-jian",		"sword" }),
		({ "yange-blade",		"blade" }),
	}),
	"�¹�"		: ({
		({ "literate" }),
			
		({ "baihua-zhang",		"unarmed" }), 	
		({ "moondance",			"dodge" }),
			
		({ "moonforce",			"force" }),
		({ "moonshentong",		"spells" }),

		({ "jueqingbian",		"whip",		"parry" }),
		({ "snowsword",			"sword" }),			
	}),

	"������"		: ({
		({ "literate" }),
			
		({ "changquan",			"unarmed" }), 	
		({ "yanxing-steps",		"dodge" }),
			
		({ "lengquan-force",	"force" }),
		({ "baguazhou",			"spells" }),

		({ "bawang-qiang",		"spear",		"parry" }),
		({ "sanban-axe",		"axe" }),
		({ "wusi-mace",			"mace" }),
	}),
	"���޵ظ�"	: ({
		({ "literate" }),
			
		({ "jinghun-zhang",		"unarmed" }), 	
		({ "ghost-steps",		"dodge" }),
			
		({ "tonsillit",			"force" }),
		({ "gouhunshu",			"spells" }),

		({ "kusang-bang",		"stick",		"parry" }),
		({ "hellfire-whip",		"whip" }),
		({ "zhuihun-sword",		"sword" }),
	}),
	"��������"	: ({
		({ "literate" }),
			
		({ "dragonfight",		"unarmed" }), 	
		({ "dragonstep",		"dodge" }),
			
		({ "dragonforce",		"force" }),
		({ "seashentong",		"spells" }),

		({ "huntian-hammer",	"hammer",		"parry" }),
		({ "fengbo-cha",		"fork" }),
	}),

	"��ѩɽ"		: ({
		({ "literate" }),
			
		({ "cuixin-zhang",		"unarmed" }), 	
		({ "xiaoyaoyou",		"dodge" }),
			
		({ "ningxie-force",		"force" }),
		({ "dengxian-dafa",		"spells" }),

		({ "bingpo-blade",		"blade",	"parry" }),
		({ "bainiao-jian",		"sword" }),			
	}),
	"�ݿ�ɽ�޵׶�"	: ({
		({ "literate" }),
			
		({ "yinfeng-zhua",		"unarmed" }), 	
		({ "lingfu-steps",		"dodge" }),
			
		({ "huntian-qigong",	"force" }),
		({ "yaofa",				"spells" }),

		({ "kugu-blade",		"blade",	"parry" }),
		({ "qixiu-jian",		"sword" }),
	}),
	"���ƶ�"		: ({
		({ "literate" }),
			
		({ "moyun-shou",		"unarmed" }), 	
		({ "moshenbu",			"dodge" }),
			
		({ "huomoforce",		"force" }),
		({ "pingtian-dafa",		"spells" }),

		({ "huoyun-qiang",		"spear",		"parry" }),
		({ "dali-bang",			"stick" }),
	}),
	"��˿��"		: ({
		({ "literate" }),
			
		({ "yinfeng-zhua",		"unarmed" }), 	
		({ "lotusmove",			"dodge" }),
			
		({ "lotusforce",		"force" }),
		({ "pansi-dafa",		"spells" }),

		({ "ziqing-sword",		"sword",		"parry" }),
		({ "baigu-whip",		"whip" }),
	}),
]);

//��ȡ���ɼ���
mixed* skills_of(string name)
{
	return _skills[name];
}

//�������ü���/״̬���û�npc�����
int quick_setup(object who, string family, int level)
{
	mixed* skills = skills_of(family);
	int exp = level * level / 3 * level;

	if(!skills) return 0;

	who->set(CEXP, exp);
	who->set(DEXP, exp);

	SKI->set_list2(who, skills, level);
	who->set("max_kee", level * 10);
	who->set("max_sen", level * 10);

	HP->to_max(who);
}

