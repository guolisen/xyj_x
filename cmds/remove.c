// by firefox 11/21/2009

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	if(arg == "all" && me->is_fighting()) {
		printf("�����ڴ�ܶ�����ϴ�裬һ��һ������");	//��å��ˢƵ
		return 1;
	}
	return 0;
}
