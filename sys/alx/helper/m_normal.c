// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

void create()
{
	set_name("����", ({"abnormal"}));
	set("gender", "����" );
	set("age", 10);
	set("long", "\n"
		"һ���ɰ���С���ޣ�����ƨ�ɣ���Ƥ������֬д�ţ�\n\n"HIM
		"    ʮ��һ�������Σ�Ӯ����ұ�̬����\n\n"NOR
	);
	set("title", HIC"�ұ�"HIM"����"NOR);

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
			"born"		: HIW"��һ��һ��һ��һ��$N��������������",
			"leave"		: HIW"$N����������������������������ġ���˵����ͷɢ��������񱼡�",
			"kill"		: "��",
	
			"cmds"		: ({ "cast huanying1" }),
		])
	);

	setup();
}

