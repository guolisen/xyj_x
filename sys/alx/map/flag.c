// by firefox 11/21/2009

#include <xyj_x.h>

inherit ITEM;

void create()
{
	set_name("����", ({"flag", "qi"}));
	set_weight(1);

	set("unit", "��" );
	set("long", "һ�˴���ӭ��Ʈ�");
	
	set("no_get", 1);
	set("value", 1);
}

void init()
{
	add_action("do_climb", "climb");
}

int do_climb(string arg)
{
	object who = this_player();
	string msg = BTL->bad_state(who, ({ "busy", "no_move", "invisible" }));
	
	if(arg != "flag") return 0;	
	
	if(msg) return notify_ok("��" + msg + "��\n");	
	
	ALX->room_climb_flag(who, _this);

	return 1;
}
