// by firefox 04/10/2010
// 基础任务模板

#include <xyj_x.h>
#include <ansi.h>

inherit F_DATA_OF;
inherit F_FOT;

string _stat_prop;				//任务统计信息属性名
int	_norm;						//任务配额
int _show_id;

//初始化属性
void init_prop(int norm)
{
	seteuid(getuid());

	set_data_prop(TASK_PROP + "/list/" + parent_id() + "/" + id());
	_stat_prop = TASK_PROP + "/stat/" + parent_id();
	_norm = norm;
	
}


/********************************虚函数***********************************/

//检查任务的前提条件
int pre_check(object employer, object who) { return 1; }

//兑现奖励
void give_reward(object who, int reward);

//布置新任务
void new_task(object who, mapping task)
{
	task["tid"]		= "ID";
	task["tname"]	= "目标名称";
	task["level"]	= 9;
	task["remark"]	= 0;			//补充信息"
	task["reward"]	= 100;			//确定任务奖励
}

//获取提示信息集
mapping get_msg(object employer)
{
	return employer->query("task_msg");
}

/********************************标准接口***********************************/

//向雇主申请任务
mixed apply(object employer, object who)
{
	mapping msg = get_msg(employer);
	mapping m = data_of(who);
	string str, target;

	//检查CD(注意带say的信息是为/std/quest拦截ask准备的)
	if(m["cd"] && time() < m["cd"]) {
		msvx(msg["cd"], employer, who);
		return or2(msg["cd_say"], 1);
	}

	//检查前置条件
	if(!pre_check(employer, who)) return or2(msg["check_say"], 1);

	//检查配额
	if(!TASK->apply_norm(who, _norm)) {
		TASK->tell_tired(employer, who);
		return or2(msg["no_norm"], 1);
	}

	//新任务
	m["num"]++;
	m["ename"] = employer->query("name");
	new_task(who, m);
	m["state"] = "进行";
	
	who->add(_stat_prop + "/num", 1);
	
	//不同type的任务，提示信息可能不同
	str = mapp(msg["task"]) ? msg["task"][m["type"]] : msg["task"];
	target = _show_id ? name_id2(m["tname"], m["tid"]) : m["tname"];

	msvx(str, employer, who, target, or2(m["sth"], m["oname"]));

	return or2(msg["apply_say"], 1);
}

//完成任务
varargs mixed done(object who, int ratio)
{
	mapping m = data_of(who);
	int reward;
	
	if(!ratio) ratio = 100;
	ratio = truncate(ratio, 20, 100);
	reward = m["reward"] * ratio / 100;

	give_reward(who, reward);
	
	who->add(_stat_prop + "/reward", reward);
	who->add(_stat_prop + "/done", 1);

	m["state"] = "完成";
	//MONITOR_D->report_system_object_msg(who, " got " + reward + "\n");

	return or2(m["return"], 1);
}

//调试功能
int debug(object employer, object who, string arg)
{
	tell_object(who, HIR"暂无调试功能。\n");
	return 1;
}

//取消任务
mixed cancel(object employer, object who);

//遇见玩家
int init_player(object employer, object who);



