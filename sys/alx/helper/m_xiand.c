// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

void on_init(object me, object who)
{
	if(!me->is_fighting()) {
		me->command("drink jiu hulu");
	}
}

void create()
{
	set_name("���޸�", ({"changhen ge", "pigeon", "ge"}));
	set("gender", "Ů��" );
	set("age", 23);
	set("long", "\n"
		"һֻ�ָ��ӣ���֪��˭����ë������������Ϳ���ּ���û�ɣ�\n\n"HIR
		"    �쳤�ؾ���ʱ�����˺������޾��ڡ�\n\n"NOR
	);
	set("title", HIG"һŵǧ��"NOR);

	set("per", 120);
	set("str", 150);
	
	SKI->set_list2(_this, 
		({
			({ "literate" }),
			
			({ "yinfeng-zhua",		"unarmed" }), 	
			({ "dragonstep",		"dodge" }),
			
			({ "dragonforce",		"force" }),
			({ "yaofa",		"spells" }),

			({ "huntian-hammer",	"hammer",		"parry" }),
		}),
		1
	);

	set_events(
		([
			"born"		: HIW"$Nҡҡ�λε��߹�������������˵�������շŸ����ݾơ�����",
			"leave"		: HIW"$N�������ˣ����ܱߺ��������������ң����Ͼ�����������ɢ����",
			"init"		: (: on_init :),
	
			"cmds"		: ({ "cast huanying1" }),
		])
	);
	
	setup();
	{
		object hulu = carry_object("/d/obj/weapon/hammer/jiuhulu");
		hulu->wield();
		hulu->set("liquid/remaining", 1000);
	}
}

