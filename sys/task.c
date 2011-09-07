// by firefox 04/10/2010
// 全局任务对象，任务操作的入口

#include <xyj_x.h>
#include <ansi.h>

inherit F_DATA_OF;
inherit F_FOT;
inherit F_VECTOR;

#define MAX_NORM					3000*K			//每周配额
#define RESET_TIME					(7*24*3600)

void create()
{
	seteuid(getuid());
	push_backs( ({"mieyao", "quest", "forces", "misc"}) );
	
	set_data_prop(TASK_PROP);
}

//任务列表
mapping list_data(object who)
{
	return DB->query_map(who, TASK_PROP + "/list");
}

//统计列表
mapping stat_data(object who)
{
	return DB->query_map(who, TASK_PROP + "/stat");
}

//查询配额
int query_norm(object who)
{	
	mapping m = data_of(who);
	int t = time();

	if(t > m["start_time"] + RESET_TIME) {
		m["start_time"] += m["start_time"] ? RESET_TIME : t;
		m["norm"] = MAX_NORM;
	}
	return m["norm"];
}


//申请配额，从总配合中减去，如果不足则失败
int apply_norm(object who, int norm)
{
	mapping m = data_of(who);

	query_norm(who);

	if(m["norm"] >= norm) {
		m["norm"] -= norm;
		return 1;
	}
	return 0;
}

//显示疲惫信息
void tell_tired(object employer, object who)
{
	string* msg = ({
		"$N对$n说道：你连日劳顿，恐体有不支，现今宜多歇息。\n",
		HIG"亲爱的玩家，您的任务配额已经用尽。请注意休息以及节能，祝您愉快。\n"NOR,
	});
	msvx(msg[0], employer, who);
	tell_object(who, msg[1]);
}

//任务是否匹配
varargs int info_match(mapping info, object target, mixed sth, string type)
{
	return info["state"] == "进行"
		&& info["type"] == type
		&& name_id_is(target, info["tname"], info["tid"])
		&& (!stringp(sth) || sth == info["sth"])
		&& (!objectp(sth) || name_id_is(sth, info["oname"], info["oid"]));
}


//遍历任务列表，查找指满足指定条件的任务
varargs object_f find_task(object who, string type, object target, mixed sth)
{
	mapping list = list_data(who);
	foreach(string gid, mapping group in list) {
		
		reset_eval_cost();
		foreach(string tid, mapping task in group) {
			if(info_match(task, target, sth, type)) return TASK_GET(gid, tid);
		}
	}
	return 0;
}

//完成满足指定条件的任务
varargs mixed done_task(object who, string type, object target, mixed sth)
{
	object_f task = find_task(who, type, target, sth);
	return task ? task->done(who) : 0;
}

//询问
string do_ask(object me, object who, string topic)
{
	/* 师门任务，暂时关闭
	if(topic == "task") {
		if(me->is_apprentice_of(who)) {
			return TASK_GET("forces", "family")->apply(who, me);		//必须返回答复
		}
	}*/

	return TASK->done_task(me, "ask", who, topic);;
}


//清空任务表，用于转世
void clear_list(object who)
{
	who->set(TASK_PROP + "/list", ([]));
}


/*
当前任务表(剩余额度：1000)：[1]
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
委托人    任务目标    状态    难度  数量  备注
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
李靖      獭爪狮      放弃    9     81    长安城西
袁天罡    白兔怪      完成    8     14    普陀山
--------------------------------------------------------------------
猪八戒    肉夹馍      完成    5     22            
殷温娇    螭吻        进行    4     33    水晶腰牌
陈光蕊    公主        进行    5     21    宫事
胡敬德    看门妖      进行    6     66          
相公      牛角刃      完成    4     4            
相婆      软锦长裙    进行    1     33
香兰      梦幻灯      进行    3     9
--------------------------------------------------------------------
玉鼠精    袈裟        完成    6     11
鼹鼠      包子馅      长期    -     8
--------------------------------------------------------------------
杨戬      魔道群妖    长期    -     19			[2]
六耳猕猴  仙界诸神    长期    -     44
--------------------------------------------------------------------
慈恩法师  经文碎片    长期    -     15			[3]
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/

#define TIT01 "委托人    任务目标        状态    难度  数量  备注\n"
#define FMT01 "%-10s%-16s%-8s%-6s%-6d%s\n"

mapping _state_color = ([
	"进行"		: HIG,
	"完成"		: NOR,
	"放弃"		: RED,
	"长期"		: NOR,
]);

///列出玩家的当前任务
int list(object who)
{	
	mapping data = list_data(who);
	int has_pre = 0;
	int remain_time = data_of(who, "start_time") + RESET_TIME - time();

	printf("任务表(精力：%dK 时间：%dH)：\n", data_of(who, "norm") / 1000, remain_time / 3600);
	write(LINE1);
	write(TIT01);
	write(LINE1);

	foreach(string gid in elems()) {
		mapping group_data = data[gid];	//任务组信息
		if(group_data) {
			object_f group = child(gid);

			if(has_pre && group->size() > 0) {
				write(LINE2);		//前一个存在才显示分割线
				has_pre = 0;
			}
			foreach(string tid in group->elems()) {
				mapping m = group_data[tid];	//具体任务信息
				if(m && m["ename"]) {
					string str = sprintf(FMT01,
						m["ename"],
						filter_color(m["tname"]),
						m["state"],
						m["level"] < 1 ? "-" : (m["level"] + ""),		//难度范围1-9
						m["num"],
						or2(m["remark"], "")
					);
					write(_state_color[m["state"]] + str + NOR);
					has_pre = 1;
				}
			}
		}
	}
	write(LINE1);
	return 1;
}

/*

tasks -s
任务统计表：
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
类别      总计      成功      比例      奖励
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
灭妖      2130      109       94%       234334
解密      1430      309       32%       43334
门派      143       309       36%       43344
仙魔大战  20        -         -         3344
完善真经  434       430       99%       942342
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/


#define TIT02 "类别      总计      成功      比例      奖励\n"
#define FMT02 "%-10s%-10d%-10d%-10s%d\n"

///列出玩家统计信息
int stat(object who)
{
	int reward = 0;
	mapping data = stat_data(who);
	write(LINE1);
	write(TIT02);
	write(LINE1);
	foreach(string gid in elems()) {
		mapping m = data[gid];
		if(m) {
			printf(FMT02, 
				e2c(gid),
				m["num"],
				m["done"],
				(m["num"] ? m["done"]*100/m["num"] : 0) + "%",
				m["reward"],
			);
			reward += m["reward"];
		}
	}
	write(LINE1);
	return 1;
}

/*
解谜奖励统计表：
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
类别                奖励
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
潜能                32423
--------------------------------------------------------------------
道行                23423
--------------------------------------------------------------------
基本轻功            1440
法术                96
晓风残月剑          1699
拆招卸力之法  	    1524
哭丧棒              48
--------------------------------------------------------------------
容貌                7
根骨                8
灵性                12
膂力                5
--------------------------------------------------------------------
银子                6575
--------------------------------------------------------------------
功勋                234
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/

#define TIT03 "类别                奖励\n"
#define FMT03 "%-20s%d\n"

private void _show_item(string item, int value) {
	printf(FMT03, e2c(item), value);
}

//奖励细节
int gain(object who, string gid)
{
	int has_pre = 0;
	mapping data = data_of(who, "stat/" + gid + "/gain");

	if(data) {
		write(e2c(gid) + "任务收益统计：\n");
		write(LINE1);
		write(TIT03);
		write(LINE1);

		foreach(string id, mixed value in data) {
			if(has_pre)	write(LINE2);
			if(mapp(value)) {
				foreach(string k, int v in value) {
					_show_item(k, v);
				}
			} else {
				_show_item(id, value);
			}
			has_pre = 1;
		}
		write(LINE1);
	} else {
		write("指定的类别不存在。\n");
	}
	return 1;
}

