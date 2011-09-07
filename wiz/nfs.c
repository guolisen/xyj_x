// by firefox 11/21/2009

inherit NPC;
inherit "/d/sldh2/feature/stat";
inherit "/d/sldh2/feature/buff";
inherit "/d/sldh2/feature/util";

/*

ƽ������
����ͳ�ƣ��ĸ������پͶ�buff�ĸ����ɡ�


1/10

max_kee�����У��ֵȱ�����
dodge��attack����ֹ��ֵ̫�����
damage ����


���ɸ�����ϵͳ

force	���Ӵ���Ч�ʣ���߼����˺�
armor	���ˣ�ϵ����Ҫʵ��
defance

����������ϵͳ

spells	��Ч���͹ַ������У�������������

�������������븺��������������ƽ����Ȼ��ģ�ս���У�ȡ�������͡�*/


#include <ansi.h>

#define SPELL_POT		20
#define DEFENSE_POT		20
#define BUFF_ID			"nfs"
#define STAT_ID			"sys_stat"
#define MAX_LVL			400

#define MM				"mm_anadem"
#define MM_LVL			200

int mm_anadem(object user)
{
	if(user->query(MM) && !query_buff(user, MM)) {
		add_buff(user,  ([
			"id"		: MM,
			"name"		: HIM"��ü����"NOR,
			"comment"	: "��MM���Ŵ�����߷����������ס�",
			"add_apply"	: ([
				"spells"	: MM_LVL,
				"defense"	: MM_LVL,
				"armor"		: MM_LVL * 2,
				"personality"	: 20,
			]),
		]));
	}
}

int on_nfs(mapping buff)
{
	object me = buff["me"];
	me->do_stat();
	foreach(object user in users()) {
		string spells = user->query_skill_mapped("spells");
		string family = user->query("family/family_name");
		int spells_lvl = 1;
		int defense_lvl = 1;
		if(spells) {
			int pct = me->str_pct("spells", spells) + 1;
			spells_lvl = 100 * SPELL_POT / pct;
		}
		if(family) {
			int pct = me->str_pct("family", family) + 1;
			defense_lvl = 100 * DEFENSE_POT / pct;
		}
		remove_buff2(user, BUFF_ID);
		add_buff(user,  ([
			"id"		: BUFF_ID,
			"name"		: HIG"ʦ�ŵĻ���"NOR,
			"comment"	: "��߷����ͷ�����",
			"add_apply"	: ([
				"spells"	: min2(spells_lvl, MAX_LVL),
				"defense"	: min2(defense_lvl, MAX_LVL),
			]),
		]));
		if(getuid(user) == "firefox")
			trace(BUFF_ID" ��õ���spells:" + spells_lvl + " defense:" + defense_lvl, user);
		//mm_anadem(user);	//˳��Ϊmm�����˻���
	}
	return 1;
}

//������������������buff
int remove()
{
	foreach(object user in users()) {
		remove_buff2(user, BUFF_ID);
	}
	::remove();
	return 0;
}

void create()
{
	set_name("����", ({ "eve", "robot" }));
	set("long", "\nһ��ͳ�ƻ����ˣ�����topָ����������ͳ����Ϣ��\n\n");
	set("title", HIY"ͳ�ƻ�����"NOR);
	set("gender", "Ů��");
	set("age", 18);
	set("per", 120);

	setup();
}

void init()
{
	::init();
	add_action("do_top", "top");
	add_action("do_skill", "skill");

	if(!query_buff(this_object(), STAT_ID)) {
		add_buff(this_object(),  ([
			"id"		: STAT_ID,
			"name"		: HIG"ʵ��ͳ��"NOR,
			"comment"	: "��ʱͳ������/������ʵ����",
			"interval"	: 60,
			"timer_act"	: (: on_nfs :),
		]));
	}
}

int do_skill(string arg)
{
	if(!arg) return 1;
	foreach(object user in users()) {
		int skill = user->query_skill(arg, 1);
		if(skill) printf("%s: %d\n", getuid(user), skill);
	}
	return 1;
}