// firefox 04/10/2010

#include <xyj_x.h>

int help(object me)
{
	write(@HELP

ָ���ʽ :
    tasks [id]           �г���ǰ����
    tasks [id] -s        �г�����ͳ����Ϣ
    tasks [id] -r gid    �г�ĳ������Ľ�����Ϣ

ע�⣺
1.ֻ��wizard���Բ鿴������ҵ�������Ϣ��
2.gidΪ������id��Ŀǰ�У�
  mieyao - ������  quest  - ����
  forces - ������  misc   - ����
 
HELP
	);
    return 1;
}

int main(object me, string arg)
{
	string id, gid;
	object target;

	if(!arg) return TASK->list(me);

	else if(arg == "-s") return TASK->stat(me);

	else if(sscanf(arg, "%s -s", id) == 1) {
		if(target = UTIL->find_player2(id)) return TASK->stat(target);
	}
	else if(sscanf(arg, "-r %s", gid) == 1) return TASK->gain(me, gid);

	else if(sscanf(arg, "%s -r %s", id, gid) == 2) {
		if(target = UTIL->find_player2(id)) return TASK->gain(target, gid);
	}
	else if(target = UTIL->find_player2(arg)) return TASK->list(target);
	
	return help(me);
}