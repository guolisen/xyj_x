// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

void create()
{
	set_name(HIW"��������"NOR, ({"rjdwwwwwmmmmmbtq", "rjd"}));
	set("gender", "����" );
	set("age", 23);
	set("long", "\n"
		"���ˣ�������Ҫ����������ID�ö�ǰû��Ļ�����ʫΪ֤��\n\n"HIW
		"    R�ڳ���ͷ��Q�ڳ���β��\n"
		"    ���������ò��������Ƴ���ˮ��\n\n"NOR
	);
	set("title", HIY"����������ǰ�㶼��׽��������ʿ"NOR);

	set("per", 120);
	set("str", 150);	
		
	SKI->set_list2(_this, 
		({
			({ "literate" }),
			
			({ "yinfeng-zhua",		"unarmed" }), 	
			({ "lotusmove",			"dodge" }),
			
			({ "lotusforce",		"force" }),
			({ "buddhism",			"spells" }),
		}),
		1
	);

	set_events(
		([
			"born"		: HIW"$N̽ͷ̽�ԵĿ��˿�����������ע�⣬��������߹���",
			"leave"		: HIW"$N�����˴��������죬������һ��С�ܣ�ת�۾Ϳ������ˡ�",
	
			"cmds"		: ({ "cast huanying1" }),
		])
	);

	setup();
	carry_object("/obj/loginload/linen")->wear();
}

