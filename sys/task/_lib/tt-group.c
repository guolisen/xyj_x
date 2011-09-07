// by firefox 04/10/2010
// 任务组模板

#include <xyj_x.h>
#include <ansi.h>

inherit F_DATA_OF;
inherit F_FOT;
inherit F_VECTOR;

string _stat_prop;				//本组任务统计信息属性名


///初始化属性
void init_prop()
{
	seteuid(getuid());

	set_data_prop(TASK_PROP + "/list/" + id());
	_stat_prop = TASK_PROP + "/stat/" + id();
}

///记录玩家某种收益
void add_gain(object who, string prop, int num)
{
	who->add(_stat_prop + "/gain/" + prop, num);
}
