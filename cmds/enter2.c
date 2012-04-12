// firefox 04/12/2012
#include <xyj_x.h>

inherit F_CLEAN_UP;


int main(object me, string arg)
{
	//if(!cd_start(me, "cmd", 5)) return notify_fail("请不要连续使用该指令。\n");

	return GANG->try_enter(me);

}

int help(object me)
{
	write(@HELP
指令格式 : enter

进入隐藏的入口。

HELP
	   );
	return 1;
}