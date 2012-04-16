
#include <ansi.h>

inherit NPC;

void create()
{
	set_name("护法", ({ "hufa" }) );
	setup();
}


void die()
{
	object me = this_object();
	string msg = HIB"$N身子一晃，变成一股青烟散去了。\n"NOR;
	message_vision(or2(query("leave_msg"), msg), me);
	destruct(me);
}


varargs int set_life(int delay, string leave_msg)
{
	remove_call_out("die");
	call_out("die", delay);
	set("leave_msg", leave_msg);
}

