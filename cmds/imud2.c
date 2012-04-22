// firefox 04/20/2012

#include <xyj_x.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	if(!arg || arg == "list") return IMUD->list();

	if(arg == "go") return IMUD->go();
	if(arg == "back") return IMUD->back();

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
ָ���ʽ : gang | bang [<����>]

������̶����������£�

list                  �г�������̶ս��
go                    ǰ��������̶
back                  �ص�ԭ����MUDλ��

");
        return 1;
}

