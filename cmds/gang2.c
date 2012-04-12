// by firefox 04/10/2010
// �������

#include <ansi.h>
#include <xyj_x.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object g = GANG->of(me);
	string str;

	seteuid(getuid());

	if(!arg || arg == "list") return GANG->list();

	//���������
	if(sscanf(arg, "join %s", str) == 1) {
		if(g) return notify_fail("���Ѿ������ᡣ\n");
		g = GANG_GET(str);
		if(!g) return notify_fail("��᲻���ڡ�\n");
		return g->join(me);
	}

	//���ð������
	if(wizardp(me) && sscanf(arg, "leader %s %s", str, arg) == 2) {
		g = GANG_GET(str);
		if(!g) return notify_fail("��᲻���ڡ�\n");
		return g->leader(find_player(arg));
	}

	if(!g) return notify_fail("�㻹�������κΰ�ᡣ\n");

	if(arg == "who") return g->who();

	if(arg == "quit") return g->quit(me);
	
	if(sscanf(arg, "accept %s", arg) == 1)
		return g->accept(me, find_player(arg));

	if(sscanf(arg, "promote %s", arg) == 1)
		return g->promote(me, find_player(arg));

	if(sscanf(arg, "demote %s", arg) == 1)
		return g->demote(me, find_player(arg));

	if(sscanf(arg, "title %s %s", arg, str) == 2)
		return g->title(me, find_player(arg), str);

	return notify_fail("��Ч�����������\n");
}

int help(object me)
{
	write("
ָ���ʽ : gang | bang [<������>] [<����>] [<����>]

������ͨ��������鿴��������ᣬ���������£�

list                  ����б�
who                   ������Ա�б�
quit                  �˳����
join gid              ���������
accept sb.            ���ܼ���������
promote sb.           ��γ�Ա
demote sb.            ������Ա
title sb. title       ���ó�Աͷ��
leader gid sb.        ���ð�����(wizר��)

");
        return 1;
}
