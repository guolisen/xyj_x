// firefox 11/10/2011
// 假身

inherit NPC;

#include <xyj_x.h>
#include <ansi.h>

void create()
{
	if(!GUARD->init_jiashen(_this)) {
		set_name("假身",({"jia shen"}));
		setup();		
	}
}

void die()
{
	string msg = HIB"$N身子一晃，变成一股青烟散去了。\n"NOR;

	message_vision(or2(query("leave_msg"), msg), _this);
	destruct(_this);
}


varargs int set_life(int delay, string leave_msg)
{
	remove_call_out("die");
	call_out("die", delay);
	set("leave_msg", leave_msg);
}

/*无门派前不需要
int prevent_learn(object me, string skill)
{
	return 1;
}*/
