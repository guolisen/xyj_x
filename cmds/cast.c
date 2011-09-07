// by firefox 11/21/2009

#include <xyj_x.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	int no_cast = SKI->do_act("cast", arg, "%s on %s", "spells", "no_magic");
	
	if(no_cast > 1) BUFF->start_no_cast(me, no_cast);
	return no_cast;
}

