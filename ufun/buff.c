// by firefox 11/21/2009
// buff函数，目标必须派生自dbase

#include <xyj_x.h>
#include <ansi.h>

inherit F_NO_CLEAN_UP;

#define PROP			"buff"
#define ID(id)			(PROP"/" + id)

//buff的完整id
string id(string id1)
{
	return ID(id1);
}

//在目标上查找指定id的buff
mixed find(object me, string id)
{
	return me->query_temp(ID(id));
}

//在目标上查找指定类别的buff
mapping find2(object me, string class_name)
{
	mixed buffs = me->query_temp(PROP);
	if(!mapp(buffs)) return 0;

	foreach(string id, mapping buff in buffs) {
		if(buff["class"] == class_name) return buff;
	}
	return 0;
}

//为目标buff
mapping add(object me, mapping buff)
{
	string id = ID(buff["id"]);
	if(!me) return 0;
	if(me->query_temp(id)) {
		if(buff["done_msg"]) printf(buff["done_msg"]);
		return 0;
	}
	me->set_temp(id, buff);
	buff["me"] = me;

	if(buff["temp"]) {		//设置临时标志
		foreach(string k, mixed v in buff["temp"]) {
			me->set_temp(k, v);
		}
	}
	if(buff["add_temp"]) {	//累加临时标志
		foreach(string k, int v in buff["add_temp"]) {
			me->add_temp(k, v);
		}
	}
	if(buff["add_apply"]) {		//增加apply
		foreach(string k, int v in buff["add_apply"]) {
			me->add_temp("apply/" + k, v);
		}
	}
	if(buff["replace"]) {	//替换状态
		mapping m = ([]);
		foreach(string k, mixed v in buff["replace"]) {
			m[k] = me->query(k);
			me->set(k, v);
		}
		if(!me->query(id)) me->set(id, m);	//备份原始状态
	}
	if(buff["add"]) {		//状态增加值，不撤销的
		foreach(string k, mixed v in buff["add"]) {
			me->add(k, v);
		}
	}
	if(buff["interval"] && buff["timer_act"]) {	//周期触发的行为，返回0则buff被移除！
		call_out("on_timer", buff["interval"] * SEC_PER_HB, buff);
	}
	if(buff["duration"] > 0) {	//还原
		call_out("remove1", buff["duration"] * SEC_PER_HB, buff);
	}
	if(buff["start_msg"]) msv(buff["start_msg"] + "\n"NOR, me);
	return buff;
}

//buff是否有效存在于目标之上
int valid(mapping buff)
{
	object me;
	if(!mapp(buff) || !(me = buff["me"])) return 0;
	return buff == find(me, buff["id"]);
}

varargs void remove1(mapping buff, int silent);

//周期触发buff的行为
void on_timer(mapping buff)
{
	if(!valid(buff)) return;

	if(evaluate(buff["timer_act"], buff)) {
		call_out("on_timer", buff["interval"] * SEC_PER_HB, buff);
	} else {
		remove1(buff);
	}
}

//移除被替换的状态
private void reset_replace(object me, string id)
{
	mapping m = me->query(id);
	foreach(string k, mixed v in m) {
		me->set(k, v);
	}
	me->delete(id);
}

//减去临时属性(包括数组)
void sub_temp(object me, string prop, mixed value)
{
	if(arrayp(value)) {
		mixed* arr = me->query_temp(prop);		//for temp array
		trace(sizeof(arr));
		arr -= value;
		trace(sizeof(arr));
		me->set_temp(prop, arr);
	}			
	else me->add_temp(prop, -value);
}

//从目标上的移除buff
varargs void remove1(mapping buff, int silent)
{
	object me;
	string id;
	if(!valid(buff) || buff["removed"]) return;	//防止递归重复删除
	buff["removed"] = 1;

	me = buff["me"];
	id = ID(buff["id"]);

	if(buff["temp"]) {
		foreach(string k, mixed v in buff["temp"]) {
			me->delete_temp(k);
		}
	}
	if(buff["add_temp"]) {
		foreach(string k, mixed v in buff["add_temp"]) {
			sub_temp(me, k, v);
		}
	}
	if(buff["add_apply"]) {
		foreach(string k, int v in buff["add_apply"]) {
			me->add_temp("apply/" + k, -v);
		}
	}
	if(buff["replace"]) {
		reset_replace(me, id);
	}
	if(buff["add"]) {
		foreach(string k, mixed v in buff["add"]) {
			me->add(k, -v);
		}
	}
	if(buff["object"]) {	//销毁和buff密切相关的对象
		foreach(string k, object v in buff["object"]) {
			if(v) destruct(v);
		}
	}
	if(buff["link"]) {
		foreach(mapping k, mixed v in buff["link"]) {
			remove1(k, silent);
		}
		buff["link"] = 0;	//防止循环引用影响GC
	}
	if(buff["post_act"]) evaluate(buff["post_act"], buff);

	if(objectp(me)) {	//me可能被post_act销毁
		if(buff["stop_msg"]) msv(buff["stop_msg"] + "\n"NOR, me);
		me->delete_temp(id);
	}
}

//从目标上的移除指定id的buff
void remove2(object me, string id)
{
	remove1(find(me, id));
}

//清除目标上的所有状态
void clear(object me)
{
	mixed buffs = me ? me->query_temp(PROP) : 0;
	if(!mapp(buffs)) return;
	foreach(string id in keys(buffs)) {
		remove2(me, id);
	}
}

//连接两个buff，使前者被删除时同时删除后者
void link(mapping buff1, mapping buff2)
{
	if(!mapp(buff1["link"])) buff1["link"] = ([]);
	buff1["link"] += ([buff2 : 1]);
}

//互相连接两个buff
void link_each(mapping buff1, mapping buff2)
{
	link(buff1, buff2);
	link(buff2, buff1);
}

//修复未正常取消的buff
void repair(object me)
{
	mixed replace = me->query(PROP);
	if(!mapp(replace)) return;

	foreach(string id, mapping m in replace) {
		if(!find(me, id)) reset_replace(me, ID(id));
	}
}

//修复未正常取消的buff，由AT_D启动
void start()
{
	foreach(object user in users()) {
		repair(user);
		reset_eval_cost();
	}
}

//列出目标身上所具有的buff
varargs int list(object me, int all)
{
	mixed buffs = me->query_temp(PROP);
	string name = me->name() ? me->name() : me->query("short");

	if(!mapp(buffs) || sizeof(buffs) == 0) {
		printf("%s上没有任何状态。\n\n", name);
	} else {
		printf("%s上的状态：\n\n", name);
		foreach(string id, mapping buff in buffs) {
			if(all || !buff["attr"]) {
				string c = buff["class"] ? "(" + buff["class"] + ")" : "";
				string d = buff["duration"] > 0 ? "持续" + buff["duration"] + "秒。" : "";
				printf("%-40s%s\n", buff["name"] + c, buff["comment"] + d);
			}
		}
	}
	printf("\n");
	return 1;
}

//开始冷却
mapping start_cd(object me, string id, string name, int duration)
{
	mapping buff = ([
		"id"		: id + "_cd",
		"name"		: name + "冷却",
		"comment"	: name + "冷却，此间禁用" + name + "。",
		"duration"	: duration,
	]);	
	return add(me, buff);
}

//buff开始能却
mapping start_cd2(object me, mapping buff, int duration)
{
	return start_cd(me, buff["id"], buff["name"], duration);
}

//开始定时器
varargs mapping start_timer(object me, function f, string id, int interval, int duration)
{
	mapping buff = ([
		"id"		: "timer" + id,
		"name"		: "定时器",
		"comment"	: "定时器定时执行某个任务。",
		"duration"	: duration,
		"interval"	: or2(interval, 2),
		"timer_act"	: f,
	]);
	return add(me, buff);
}

//开始禁止施法
mapping start_no_cast(object me, int duration)
{
	mapping buff = ([
		"id"		: "no_cast",
		"name"		: "法术冷却",
		"comment"	: "法术冷却，此间不能施放任何法术。",
		"duration"	: duration,
		"add_temp"	: (["no_cast" : 1]),
	]);
	return add(me, buff);
}

//开始禁止移动
mapping start_no_move(object me, int duration)
{
	mapping buff = ([
		"id"		: "no_move",
		"name"		: "禁止移动",
		"comment"	: "期间不能移动。",
		"duration"	: duration,
		"add_temp"	: (["no_move" : 1]),
	]);
	return add(me, buff);
}

//开始禁止移动
mapping start_no_attack(object me, int duration)
{
	mapping buff = ([
		"id"		: "no_attack",
		"name"		: "禁止攻击",
		"comment"	: "期间不能攻击。",
		"duration"	: duration,
		"add_temp"	: (["no_attack" : 1]),
	]);
	return add(me, buff);
}

//开始狂暴状态，不受任何控制
mapping start_frenzy(object me, int duration)
{
	mapping buff = ([
		"id"		: "frenzy",
		"name"		: HIR"狂暴状态"NOR,
		"comment"	: "不受任何控制。",
		"duration"	: duration,
		"interval"	: 1,
		"timer_act"	:  function(mapping buff) {
			object me = buff["me"];
			if(me->is_busy()) me->start_busy(1);
			if(me->query_temp("no_cast")) me->delete_temp("no_cast");
			return 1;
		},
	]);
	return add(me, buff);
}

//开始禁止武器
varargs mapping start_no_wield(object me, int duration, string msg)
{
	mapping buff = ([
		"id"		: "no_wield",
		"name"		: HIY"放下屠刀"NOR,
		"comment"	: "禁止使用武器。",
		"duration"	: duration,
		"add_temp"	: ([ "No_Wield" : 1 ]),
		"stop_msg"	: msg,
		"post_act"	: function(mapping buff) {
			object weapon = buff["_weapon"];
			if(weapon && environment(weapon) == buff["me"]) {
				weapon->wield();
			}
		},
		"_weapon"	: me->query_temp("weapon"),

	]);
	object weapon;
	while(weapon = me->query_temp("weapon")) weapon->unequip();
	return add(me, buff);
}

//开始长出爪子
varargs mapping start_claw(object me, int duration, int damage, string msg)
{
	mapping buff = ([
		"id"		: "claw",
		"name"		: HIY"长出利爪"NOR,
		"comment"	: "长出利爪，伤害增加，不能拿武器。",
		"duration"	: duration,
		"temp"		: ([ "no_wield"		: 1 ]),
		"add_temp"	: ([ "apply/damage"	: damage ]),
		"stop_msg"	: msg,
	]);
	object weapon;
	while(weapon = me->query_temp("weapon")) weapon->unequip();
	return add(me, buff);
}



//武器折断(一段时间)，不能使用
mapping start_broken(object weapon, int duration)
{
	mapping buff = ([
		"id"		: "broken",
		"name"		: "折断",
		"comment"	: "武器断了",
		"duration"	: duration,
		"replace"	: ([
			"name"		: "折断的" + weapon->query("name"),
			"weapon_prop" : 0,
		]),
	]);
	return add(weapon, buff);
}

//开始对象生命倒计时
varargs mapping start_life(object me, int duration, string msg)
{
	mapping buff = ([
		"id"		: "life_countdown",
		"name"		: HIY"生命倒计时"NOR,
		"comment"	: "目标生命倒计时，计时结束目标被销毁。",
		"duration"	: duration,
		"stop_msg"	: msg,
		"post_act"	: function(mapping buff) {
			msv(buff["stop_msg"] + "\n"NOR, buff["me"]);
			destruct(buff["me"]); 
		},
	]);
	return add(me, buff);
}


//增加目标气血/精神等状态
private varargs mapping start_add_hpx(object me, string prop, string name, int gain, int duration, string msg)
{
	string color = gain > 0 ? HIG : HIR;
	string title = (gain > 0 ? "增加" : "减少") + name;
	mapping buff = ([
		"id"		: "add_hp_" + prop,
		"name"		: color + title + NOR,
		"comment"	: "临时" + title + "。",
		"duration"	: duration,
		"add"		: ([ "max_" + prop : gain, "eff_" + prop : gain, prop : gain ]),
		"stop_msg"	: msg,
		"_prop"		: prop,
		"_gain"		: gain,
		"post_act"	: function(mapping buff) {
			object me = buff["me"];			
			string prop = buff["_prop"];
			int gain = buff["_gain"];
			int max_hp = me->query("max_" + prop);
			//计算状态结束前有效状态比率
			int radio = (me->query("eff_" + prop) + gain) * 100	/ (max_hp + gain);
			int hp = max_hp * radio / 100;

			me->set(prop, hp);
			me->set("eff_" + prop, hp);			
		},
	]);
	return add(me, buff);
}

//增加目标气血
varargs mapping start_add_kee(object me, int gain, int duration, string msg)
{
	return start_add_hpx(me, "kee", "气血", gain, duration, msg);
}

//增加目标精神
varargs mapping start_add_sen(object me, int gain, int duration, string msg)
{
	return start_add_hpx(me, "sen", "精神", gain, duration, msg);
}

//定时修复：buff中的replace未被正常还原
mapping start_repair(object me, int interval)
{
	mapping buff = ([
		"id"		: "buff_repair",
		"name"		: HIG"定时修复"NOR,
		"comment"	: "定时修复：buff中的replace未被正常还原。",
		"interval"	: interval,
		"timer_act"	: function(mapping buff) {
			foreach(object user in users()) {
				repair(user);
			}
			return 1;
		},
	]);
	return add(me, buff);
}

//获取冷却信息
mixed query_cd(object me, string id)
{
	return me->query_temp(ID(id + "_cd"));
}

//获取buff的冷却信息
mixed query_cd2(object me, mapping buff)
{
	return query_cd(me, buff["id"]);
}

