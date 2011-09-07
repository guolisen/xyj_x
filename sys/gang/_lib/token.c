// by firefox 02/21/2010

#include <xyj_x.h>
#include <ansi.h>
#include <armor.h>

inherit FINGER;
//inherit F_LOADABLE;	//auto load��Ʒ�������ܸ�������

void create()
{
	set_name("��������", ({ "gang token", "token" }) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("material", "gold");
		set("armor_prop/armor", 10);

		set("no_give", 1);
		set("no_put", 1);
		set("no_get", 1);
	}
	setup();
}

string long()
{
	string str = "\n����һ��������ơ���Ϊ�������һ����";
	string gname = GANG->name(environment());

	str += gname ? "��" + gname : "�����Ѿ����ϲ�����";
	str += "��\n"NOR;
	return str;
}

void init()
{
	object who = this_player();

	add_action("do_fly", "fly");
	add_action("do_enter", ({"enter", "jump", "climb", "swim"}));
}

int do_fly(string arg)
{
	if(arg == "gang" || arg == "bang") return GANG->home(this_player());
	return 0;
}

//���Դӵ�ǰλ�ý���һ���������ڵ�
int do_enter(string arg)
{
	if(arg) return 0;
	return GANG->try_enter(this_player(), query_verb());
}
