
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

��ʾ���ܵĲ�������������Ϣ��鿴tasks -r quest��

TEXT
        );
        return 1;
}
