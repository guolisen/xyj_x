// firefox 11/10/2011
// ����

inherit NPC;

#include <xyj_x.h>
#include <ansi.h>

void create()
{
	if(!GUARD->init_jiashen(_this)) {
		set_name("����",({"jia shen"}));
		setup();		
	}
}

void die()
{
	string msg = HIB"$N����һ�Σ����һ������ɢȥ�ˡ�\n"NOR;

	message_vision(or2(query("leave_msg"), msg), _this);
	destruct(_this);
}
