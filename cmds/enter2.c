// firefox 04/12/2012
#include <xyj_x.h>

inherit F_CLEAN_UP;


int main(object me, string arg)
{
	//if(!cd_start(me, "cmd", 5)) return notify_fail("�벻Ҫ����ʹ�ø�ָ�\n");

	return GANG->try_enter(me);

}

int help(object me)
{
	write(@HELP
ָ���ʽ : enter

�������ص���ڡ�

HELP
	   );
	return 1;
}