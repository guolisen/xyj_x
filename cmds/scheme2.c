// scheme.c

#include <ansi.h>
#include <xyj_x.h>

inherit F_CLEAN_UP;

#define SCHEME_D		"/adm/daemons/schemed"

int main(object me, string arg)
{
	string schedule = me->query("schedule");

	seteuid(getuid());

	if(!arg) return SCHEME_D->show(me);

	if(sscanf(arg, "show %s", arg) == 1) {
		object ob = find_player(arg);
		
		if(!wizardp(me))
			return notify_fail("����Ȩ�鿴�����ƶ��ļƻ���\n");

		if(!ob)
			return notify_fail("û�������ҡ�\n");

		return SCHEME_D->show(ob);
	}

	if(arg == "clear") return SCHEME_D->clear(me);

	if(arg == "edit") return SCHEME_D->edit(me);

	if(arg == "start") return SCHEME_D->start(me);

	if(arg == "stop") return SCHEME_D->stop(me);

	if(wizardp(me) && arg == "list") return SCHEME_D->list();

	return notify_fail("�Ƿ������������\n");
}



int help (object me)
{
	write(@HELP
ָ���ʽ : scheme [<edit> | <start> | <clear> | <show> <���>]
 
�趨��ʼ��ļƻ����������Ҫ��ʱ��Ķ��������ϰ���ܣ�����
ʹ�üƻ�����ɣ�������μ� help schedule��

edit  : �趨�ƻ�
start : ��ʼִ�мƻ�
stop  : ִֹͣ�мƻ�
clear : ���Ŀǰ�ļƻ�
show  : ��ʾĳ����ҵļƻ���ֻ����ʦ����ʹ��������

HELP );
        return 1;
}
