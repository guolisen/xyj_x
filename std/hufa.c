
#include <ansi.h>

inherit NPC;

void create()
{
	set_name("����", ({ "hufa" }) );
	setup();
}


void die()
{
	object me = this_object();
	string msg = HIB"$N����һ�Σ����һ������ɢȥ�ˡ�\n"NOR;
	message_vision(or2(query("leave_msg"), msg), me);
	destruct(me);
}


varargs int set_life(int delay, string leave_msg)
{
	remove_call_out("die");
	call_out("die", delay);
	set("leave_msg", leave_msg);
}

