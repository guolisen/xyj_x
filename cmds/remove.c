// by firefox 11/21/2009

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	if(arg == "all" && me->is_fighting()) {
		printf("你是在打架而不是洗澡，一件一件来。");	//流氓的刷频
		return 1;
	}
	return 0;
}
