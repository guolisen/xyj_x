// by firefox 11/21/2009

#include <xyj_x.h>


int main(object me, string arg)
{
	object who = arg ? find_player(arg) : me;
	if(!who) write("Ë­£¿\n");
	if(!wizardp(me)) return 0;

	HP->full(who);

	write("OK.\n");
	return 1;
}
