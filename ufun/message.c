// by firefox 11/21/2009

#include <ansi.h>



//显示信息，并返回0，某些时候用于代替notify_fail
int fail(string msg)
{
	write(msg);
	return 0;
}

