// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIY"������ë"NOR, ({ "hair" }) );
	set_weight(10);

	set("long", "һ��������ë��Σ��ʱ������(use)������\n");
	set("unit", "��");

	set("no_get", 1);
	set("no_put", 1);
	set("no_give", 1);

	setup();
}

int init ()  
{   
	object who = _player;
	add_action ("do_use", "use");

	if(environment() == who) {
		msv(CYN"\nһƬ����Ҷ������Ʈ��$N���У�����һ����ë��\n"NOR, who);
		tell_object(who, CYN
			"ڤڤ�д���һ��������\n\n"HIY
			"    ���������޼�������ʱ�ڣ��������Ӧ�䣬�ȵ��㼱��֮�֡���\n\n"NOR);
		trace(getuid(who) + "�õ�������ë��", D_WIZ);
	}
	return 1;
}

int do_use (string arg)
{
	if(arg != "hair") return 0;	
	ALX->help_me(_player);
	destruct(_this);
	return 1;
}
