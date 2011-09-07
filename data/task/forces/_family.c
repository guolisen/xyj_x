// by firefox 09/14/2010

#include <ansi.h>

//所有花
string* _flower_list = ({
	HIR"桂花",	HIR"腊梅",	HIY"菊花",	HIW"莲花",	HIM"海棠",	HIB"芍药",
	HIG"水仙",	HIW"玉兰",	HIR"杜鹃",	HIG"兰花",	HIM"牡丹",	HIR"蔷薇",
	HIW"茉莉",	HIB"瑞香",	MAG"紫薇",	HIR"山茶",	HIM"碧桃",	HIR"玫瑰",
	MAG"丁香",	HIM"杏花",	HIR"石榴花",	HIW"并蒂莲",	HIM"月季",	HIY"梨花",
	HIR"李花",	HIW"木香",	HIM"芙蓉",	HIB"蓝菊",	HIR"罂粟花",	HIB"秋海棠",
	HIB"夜来香",	HIY"昙花",	HIY"葵花",	HIG"苹花",	HIG"菱花",	HIG"荷花",
	HIG"灵芝",	HIG"铁树花",	HIG"青囊花",
});

/*

神仙妖怪对杀



方寸：
	老道士(Laodao)
	晨月(Chen yue)



*/

//神仙列表
string* _xian_list = ({

});

//妖怪列表
string* _mo_list = ({
});

//物品列表
string* item_list = ({

	"养身丹",			"yangshen dan",	

	// /d/qujing/kusong/obj
	HIW"何首乌"NOR,	"he shou wu",	"金银花",		"jinyin hua",
	"七星草",			"qixing cao",	"玄黄果",		"xuanhuang guo",
	"太白刺",			"taibai ci",	"齿阙环",		"chique huan",
	"铁刃斧",			"iron axe",		"铁柄剑",		"iron sword",
	"钢头叉",			"iron fork",	"铁板刀",		"iron blade",
	"铁索链",			"iron whip",	"青铜甲",		"bronze armor"

});

string* npc_list = ({

	///d/dntg/hgs/npc/ add by huadao.2010.08.22
	"虎精",			"hu jing",		"豹精",		"bao jing",
	"狮精",			"shi jing",		"狼精",		"lang jing",
	"狈精",			"bei jing",		"熊精",		"xiong jing",
	"狐精",			"hu jing",		"鹿精",		"lu jing",
	"狗精",			"gou jing",		"猴精",		"hou jing",
	"驴精",			"lv jing",
});


//公共任务
mapping _common = ([
	
]);

//神仙任务
mapping _task_xian = ([


]);

//妖魔任务
mapping _task_mo = ([

	
]);



mapping data()
{
	return ([

		//公共任务
		"common"	: _common,

		"南海普陀山"		: ([
		   20101 : ({ "kill", "山妖",         "shan yao",           "", "1" }),
		]),
		"方寸山三星洞"		: ([
		   20101 : ({ "kill", "山妖",         "shan yao",           "", "1" }),
		]),
		"五庄观"			: ([
		   20101 : ({ "kill", "山妖",         "shan yao",           "", "1" }),
		]),
		"月宫"			: ([
		   20101 : ({ "kill", "山妖",         "shan yao",           "", "1" }),
		]),

		"东海龙宫"		: ([
		   20101 : ({ "kill", "山妖",         "shan yao",           "", "1" }),
		]),
		"阎罗地府"		: ([
		   20101 : ({ "kill", "山妖",         "shan yao",           "", "1" }),
		]),
		"将军府"			: ([
		   20101 : ({ "kill", "山妖",         "shan yao",           "", "1" }),
		]),
			
		"大雪山"			: ([
			冰块，蓝色冰块
		80025 : ({ "give", "月奴",       "yue nu",       ""HIR"桂花"NOR"(flower)", "1" }),
		   20101 : ({ "kill", "山妖",         "shan yao",           "", "1" }),
		]),
		"陷空山无底洞"		: ([
		   20101 : ({ "kill", "山妖",         "shan yao",           "", "1" }),
		]),
		"火云洞"			: ([
		   20101 : ({ "kill", "山妖",         "shan yao",           "", "1" }),
		]),
		"盘丝洞"			: ([
		   20101 : ({ "kill", "山妖",         "shan yao",           "", "1" }),
		]),	
	]);

}

