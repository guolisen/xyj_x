// by firefox 11/21/2009

#include <xyj_x.h>

int main(object me, string arg)
{
	object ob = UTIL->search_id(me, arg);
	
	if(!ob) {
		printf("����û��%s��\n", arg);
		return 1;
	}
	BUFF->list(ob, wizardp(me) || ob == me);
	return 1;
}
