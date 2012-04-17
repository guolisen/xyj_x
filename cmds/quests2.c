
inherit F_CLEAN_UP;

#include <xyj_x.h>


int main(object me, string arg)
{
	TASK->child("quest")->show_clouds(me);
	return 1;
}

int help()
{
        write(@TEXT

显示解密的彩云数，其他信息请查看tasks -r quest。

TEXT
        );
        return 1;
}
