// by firefox 09/14/2010

#include <ansi.h>

//���л�
string* _flower_list = ({
	HIR"��",	HIR"��÷",	HIY"�ջ�",	HIW"����",	HIM"����",	HIB"��ҩ",
	HIG"ˮ��",	HIW"����",	HIR"�ž�",	HIG"����",	HIM"ĵ��",	HIR"Ǿޱ",
	HIW"����",	HIB"����",	MAG"��ޱ",	HIR"ɽ��",	HIM"����",	HIR"õ��",
	MAG"����",	HIM"�ӻ�",	HIR"ʯ��",	HIW"������",	HIM"�¼�",	HIY"�滨",
	HIR"�",	HIW"ľ��",	HIM"ܽ��",	HIB"����",	HIR"��ڻ�",	HIB"�ﺣ��",
	HIB"ҹ����",	HIY"꼻�",	HIY"����",	HIG"ƻ��",	HIG"�⻨",	HIG"�ɻ�",
	HIG"��֥",	HIG"������",	HIG"���һ�",
});

/*

�������ֶ�ɱ



���磺
	�ϵ�ʿ(Laodao)
	����(Chen yue)



*/

//�����б�
string* _xian_list = ({

});

//�����б�
string* _mo_list = ({
});

//��Ʒ�б�
string* item_list = ({

	"����",			"yangshen dan",	

	// /d/qujing/kusong/obj
	HIW"������"NOR,	"he shou wu",	"������",		"jinyin hua",
	"���ǲ�",			"qixing cao",	"���ƹ�",		"xuanhuang guo",
	"̫�״�",			"taibai ci",	"���ڻ�",		"chique huan",
	"���и�",			"iron axe",		"������",		"iron sword",
	"��ͷ��",			"iron fork",	"���嵶",		"iron blade",
	"������",			"iron whip",	"��ͭ��",		"bronze armor"

});

string* npc_list = ({

	///d/dntg/hgs/npc/ add by huadao.2010.08.22
	"����",			"hu jing",		"����",		"bao jing",
	"ʨ��",			"shi jing",		"�Ǿ�",		"lang jing",
	"����",			"bei jing",		"�ܾ�",		"xiong jing",
	"����",			"hu jing",		"¹��",		"lu jing",
	"����",			"gou jing",		"�ﾫ",		"hou jing",
	"¿��",			"lv jing",
});


//��������
mapping _common = ([
	
]);

//��������
mapping _task_xian = ([


]);

//��ħ����
mapping _task_mo = ([

	
]);



mapping data()
{
	return ([

		//��������
		"common"	: _common,

		"�Ϻ�����ɽ"		: ([
		   20101 : ({ "kill", "ɽ��",         "shan yao",           "", "1" }),
		]),
		"����ɽ���Ƕ�"		: ([
		   20101 : ({ "kill", "ɽ��",         "shan yao",           "", "1" }),
		]),
		"��ׯ��"			: ([
		   20101 : ({ "kill", "ɽ��",         "shan yao",           "", "1" }),
		]),
		"�¹�"			: ([
		   20101 : ({ "kill", "ɽ��",         "shan yao",           "", "1" }),
		]),

		"��������"		: ([
		   20101 : ({ "kill", "ɽ��",         "shan yao",           "", "1" }),
		]),
		"���޵ظ�"		: ([
		   20101 : ({ "kill", "ɽ��",         "shan yao",           "", "1" }),
		]),
		"������"			: ([
		   20101 : ({ "kill", "ɽ��",         "shan yao",           "", "1" }),
		]),
			
		"��ѩɽ"			: ([
			���飬��ɫ����
		80025 : ({ "give", "��ū",       "yue nu",       ""HIR"��"NOR"(flower)", "1" }),
		   20101 : ({ "kill", "ɽ��",         "shan yao",           "", "1" }),
		]),
		"�ݿ�ɽ�޵׶�"		: ([
		   20101 : ({ "kill", "ɽ��",         "shan yao",           "", "1" }),
		]),
		"���ƶ�"			: ([
		   20101 : ({ "kill", "ɽ��",         "shan yao",           "", "1" }),
		]),
		"��˿��"			: ([
		   20101 : ({ "kill", "ɽ��",         "shan yao",           "", "1" }),
		]),	
	]);

}

