// by firefox 04/10/2010
// ����

#include <ansi.h>
#include <xyj_x.h>

inherit F_CLEAN_UP;

#define FAME_D		"/adm/daemons/schemed"

int main(object me, string arg)
{
	object who = me;
	if(arg) {
		who = find_player(arg);
		
		if(!wizardp(me)) return notify_fail("����Ȩ�鿴����������\n");

		if(!who)	return notify_fail("û�������ҡ�\n");
	}

	return FAME_D->show(who);
}



int help (object me)
{
	write(@HELP
ָ���ʽ : fame [<���>]

�г���Ҹ�����Ӫ��������

HELP );
        return 1;
}
