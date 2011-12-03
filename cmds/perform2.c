// by firefox 11/21/2009

#include <xyj_x.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object weapon = me->query_temp("weapon");
	string skill = weapon ? weapon->query("skill_type") : "unarmed";

	return SKI->do_act("perform", arg, "%s on %s", skill, "no_fight");
}
