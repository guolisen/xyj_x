// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

mapping _family_tab = ([
	0			: ({ 0,			0,		0}),
	"南海普陀山"	: ({ "普陀山",	"pt",	HIY }),
	"方寸山三星洞"	: ({ "方寸山",	"fc",	HIY }),
	"五庄观"		: ({ "五庄观",	"wzg",	HIY }),
	"月宫"		: ({ "月宫",		"moon", HIY }),

	"将军府"		: ({ "将军府",	"jjf",	HIY }),
	"阎罗地府"	: ({ "地府",		"hell", HIY }),
	"东海龙宫"	: ({ "龙宫",		"lg",	HIY }),

	"大雪山"		: ({ "大雪山",	"xs",	HIY }),
	"陷空山无底洞"	: ({ "无底洞",	"wdd",	HIY }),	
	"火云洞"		: ({ "火云洞",	"hyd",	HIY }),
	"盘丝洞"		: ({ "盘丝洞",	"psd",	HIY }),
]);

//门派简称
string short(object who)
{
	return _family_tab[who->query("family/family_name")][0];
}

//门派id
string id(object who)
{
	return _family_tab[who->query("family/family_name")][1];
}

//门派id转名称
string id_to_name(string id)
{
	foreach(string name, mixed* arr in _family_tab) {
		if(arr[1] == id) return name;
	}
	return 0;
}

//门派颜色
string color(object who)
{
	return _family_tab[who->query("family/family_name")][2];
}

mapping _skills = ([
	"南海普陀山"	: ({
		({ "literate" }),
			
		({ "jienan-zhi",		"unarmed" }), 	
		({ "lotusmove",			"dodge" }),
			
		({ "lotusforce",		"force" }),
		({ "buddhism",			"spells" }),

		({ "lunhui-zhang",		"staff",		"parry" }),		
	}),
	"方寸山三星洞"	: ({
		({ "literate" }),
			
		({ "puti-zhi",			"unarmed" }), 	
		({ "jindouyun",			"dodge" }),
			
		({ "wuxiangforce",		"force" }),
		({ "dao",				"spells" }),

		({ "qianjun-bang",		"stick",		"parry" }),
		({ "liangyi-sword",		"sword" }),
	}),
	"五庄观"		: ({
		({ "literate" }),
			
		({ "wuxing-quan",		"unarmed" }),
		({ "baguazhen",			"dodge" }),
			
		({ "zhenyuan-force",	"force" }),
		({ "taiyi",				"spells" }),

		({ "kaishan-chui",		"hammer",	"parry" }),
		({ "sanqing-jian",		"sword" }),
		({ "yange-blade",		"blade" }),
	}),
	"月宫"		: ({
		({ "literate" }),
			
		({ "baihua-zhang",		"unarmed" }), 	
		({ "moondance",			"dodge" }),
			
		({ "moonforce",			"force" }),
		({ "moonshentong",		"spells" }),

		({ "jueqingbian",		"whip",		"parry" }),
		({ "snowsword",			"sword" }),			
	}),

	"将军府"		: ({
		({ "literate" }),
			
		({ "changquan",			"unarmed" }), 	
		({ "yanxing-steps",		"dodge" }),
			
		({ "lengquan-force",	"force" }),
		({ "baguazhou",			"spells" }),

		({ "bawang-qiang",		"spear",		"parry" }),
		({ "sanban-axe",		"axe" }),
		({ "wusi-mace",			"mace" }),
	}),
	"阎罗地府"	: ({
		({ "literate" }),
			
		({ "jinghun-zhang",		"unarmed" }), 	
		({ "ghost-steps",		"dodge" }),
			
		({ "tonsillit",			"force" }),
		({ "gouhunshu",			"spells" }),

		({ "kusang-bang",		"stick",		"parry" }),
		({ "hellfire-whip",		"whip" }),
		({ "zhuihun-sword",		"sword" }),
	}),
	"东海龙宫"	: ({
		({ "literate" }),
			
		({ "dragonfight",		"unarmed" }), 	
		({ "dragonstep",		"dodge" }),
			
		({ "dragonforce",		"force" }),
		({ "seashentong",		"spells" }),

		({ "huntian-hammer",	"hammer",		"parry" }),
		({ "fengbo-cha",		"fork" }),
	}),

	"大雪山"		: ({
		({ "literate" }),
			
		({ "cuixin-zhang",		"unarmed" }), 	
		({ "xiaoyaoyou",		"dodge" }),
			
		({ "ningxie-force",		"force" }),
		({ "dengxian-dafa",		"spells" }),

		({ "bingpo-blade",		"blade",	"parry" }),
		({ "bainiao-jian",		"sword" }),			
	}),
	"陷空山无底洞"	: ({
		({ "literate" }),
			
		({ "yinfeng-zhua",		"unarmed" }), 	
		({ "lingfu-steps",		"dodge" }),
			
		({ "huntian-qigong",	"force" }),
		({ "yaofa",				"spells" }),

		({ "kugu-blade",		"blade",	"parry" }),
		({ "qixiu-jian",		"sword" }),
	}),
	"火云洞"		: ({
		({ "literate" }),
			
		({ "moyun-shou",		"unarmed" }), 	
		({ "moshenbu",			"dodge" }),
			
		({ "huomoforce",		"force" }),
		({ "pingtian-dafa",		"spells" }),

		({ "huoyun-qiang",		"spear",		"parry" }),
		({ "dali-bang",			"stick" }),
	}),
	"盘丝洞"		: ({
		({ "literate" }),
			
		({ "yinfeng-zhua",		"unarmed" }), 	
		({ "lotusmove",			"dodge" }),
			
		({ "lotusforce",		"force" }),
		({ "pansi-dafa",		"spells" }),

		({ "ziqing-sword",		"sword",		"parry" }),
		({ "baigu-whip",		"whip" }),
	}),
]);

//获取门派技能
mixed* skills_of(string name)
{
	return _skills[name];
}

//快速设置技能/状态，用户npc或测试
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

