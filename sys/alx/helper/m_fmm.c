// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";


void on_init(object me, object who)
{
	if(!random(2)) me->command("snicker");
}

void create()
{
	set_name("�����з", ({"jiqi pangxie", "pangxie", "crab"}));
	set("gender", "Ů��" );
	set("age", 23);
	set("long", "\n"
		"һֻ���ܵ�ȫ�Զ��з�����������ϵ��͹��������ƽ��\n"
		"���ĺۼ�����������ŤŤ���ּ��������ý���д�µģ�\n\n"RED
		"    �޲ſ�ȥ�����죬�������������ꡣ\n"
		"    ���ǾӼ������£���˭��ȥһͨ�⣿\n\n"NOR
	);
	set("title", HIC"�䱾"HIM"����"NOR);

	set("per", 120);
	set("str", 150);	
	
	SKI->set_list2(_this,
		({
			({ "literate" }),
			
			({ "yinfeng-zhua",		"unarmed",	"parry" }), 	
			({ "lingfu-steps",		"dodge" }),
			
			({ "huntian-qigong",	"force" }),
			({ "yaofa",				"spells" }),	
		}),
		1
	);

	set_events(
		([
			"born"		: HIW"һ�������Զ������$Nƨ�ɺ�ð�ź��̷�۵糸��ʻ����",
			"leave"		: HIW"��������һֻƽ�׹���$NҨ��������Ȼ�󲻼��ˡ�\n"NOR
				"��Լ�����������Ҳ��͵��MUD��...����",
			"init"		: (: on_init :),
			"kill"		: "��",
	
			"cmds"		: ({ "cast suliao" }),
		])
	);

	setup();

}

