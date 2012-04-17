// firefox 04/10/2010

#include <xyj_x.h>

int help(object me)
{
	write(@HELP

指令格式 :
    tasks [id]           列出当前任务
    tasks [id] -s        列出任务统计信息
    tasks [id] -r gid    列出某类任务的奖励信息

注意：
1.只有wizard可以查看其它玩家的任务信息。
2.gid为任务组id，目前有：
  mieyao - 灭妖，  quest  - 解迷
  forces - 势力，  misc   - 其他
 
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