// firefox 03/01/2012

#include <xyj_x.h>
#include <ansi.h>

inherit F_CLEAN_UP;

//查询天赋
int query_attr(string prop, object who)
{
	if(prop == "int") return who->query_int();
	if(prop == "spi") return who->query_spi();
	return 0;
}
//查询两属性比率
int query_ratio(string prop0, string prop1, object who)
{
	int i0 = who->query(prop0);
	int i1 = who->query(prop1);
	if(intp(i0) && intp(i1) && i1 != 0) return 100 * i0 / i1;
	return 0;
}
//查询两属性之差
int query_diff(string prop0, string prop1, object who)
{
	int i0 = who->query(prop0);
	int i1 = who->query(prop1);
	if(intp(i0) && intp(i1)) return i0 - i1;
	return 0;
}
//身上物品数量
int inv_count(object who, string id)
{
	int s = 0;
	foreach(object ob in all_inventory(who)) {
		if(ob->query("id") == id) {
			int n = ob->query_amount();
			s += n ? n : 1;
		}
	}
	return s;
}
//房间属性
mixed room_prop(object who, string prop)
{
	object room = environment(who);
	string* props = ({"short", "outdoors", "no_fight", "no_magic", "water"});

	if(member_array(prop, props) != -1) 
		return room->query(prop);
	if(prop == "exits") {
		mixed exits = room->query(prop);
		if(mapp(exits)) return implode(keys(exits), "|");
	}
	return 0;
}
//房间属性
string here_obj(object who, string id)
{
	object room = environment(who);
	object ob = id ? present(id, room) : 0;
	return ob ? ob->name() : 0;
}
//查询技能
string skill(object who, string skill)
{
	mapping m = who->query_learned();
	return who->query_skill(skill, 1) + "|" +
		and2(m, m[skill]) + "|" + 
		who->query_skill_mapped(skill);
}

//查询任务
string task(object who, string id)
{
	mapping m =  who->query(TASK_PROP"/list/" + id);
	if(!m) return "0|0|0|0|0|0";

	return m["ename"] + "|" + m["tname"] + "|" + m["tid"] + "|" +
		m["state"] + "|" + m["level"] + "|" 
		+ (m["remark"] != "" ? m["remark"] : "0");
}

//属性对应表
mapping _props = ([

	//hp
	"kee"			: "kee",
	"sen"			: "sen",		
	"eff_kee"		: "eff_kee",
	"eff_sen"		: "eff_sen",
	"kee_ratio"		: (: query_ratio, "eff_kee", "max_kee" :),
	"sen_ratio"		: (: query_ratio, "eff_sen", "max_sen" :),
	
	"force"			: "force",
	"mana"			: "mana",
	"max_force"		: "max_force",
	"max_mana"		: "max_mana",
	"force_ratio"	: (: query_ratio, "max_force", "maximum_force" :),
	"mana_ratio"	: (: query_ratio, "max_mana", "maximum_mana" :),

	"food"			: "food",
	"water"			: "water",
	"bellicosity"	: "bellicosity",

	"combat_exp"	: "combat_exp",
	"daoxing"		: "daoxing",

	"potential"		: (: query_diff, "potential", "learned_points" :),

	//score
	"title"			: "title",
	"name"			: "name",
	"id"			: "id",
	"age"			: "age",
	"int"			: (: query_attr, "int" :),
	"spi"			: (: query_attr, "spi" :),
	"damage"		: "damage",
	"armor"			: "armor",
	"family"		: "family/family_name",
	"master"		: "family/master_name",
	"balance"		: "balance",

	//i
	"count"			: (: inv_count :),

	//look
	"room"			: (: room_prop :),
	"here"			: (: here_obj :),

	//skills	
	"skill"			: (: skill :),

	//tasks	
	"task_norm"		: TASK_PROP"/norm",
	"task"			: (: task :),

	"stl_zg"		: (: query_diff, "sys_alx/exp", "sys_alx/exp_used" :),
]);


int main(object me, string arg)
{
	string title = "属性值";
	mixed result = 0;
	string* arr;
		
	if(!arg) return notify_fail("指令格式 ： query [标题:]<属性>|<属性列表>\n");
	sscanf(arg, "%s:%s", title, arg);

	arr = explode(arg, ",");
	
	write("\n" + title + ":");
	foreach(string str in arr) {
		string fun, args;
		
		result = 0;
		if(sscanf(str, "%s(%s)", fun, args) == 2) {
			function f = _props[fun];
			if(functionp(f)) result = evaluate(f, me, args);
		} else {
			mixed v = _props[str];
			if(functionp(v)) result = evaluate(v, me);
			if(stringp(v)) result = me->query(v);
		}
		write(result + ",");
	}
	write("\n");

	return 1;
}

int help(object me)
{
	write(@HELP

指令格式 ： query [标题:]<属性>|<属性列表>

查询自身/环境的属性/属性列表(以逗号分隔)，显示被查询属性的值，该指令旨在减少带宽
占用，思想源自北大侠客行。

hp相关
- 气血/精神：kee sen eff_kee eff_sen kee_ratio sen_ratio 
- 内力/法力：force mana max_force max_mana force_ratio mana_ratio
- 饮食/杀气：water food bellicosity
- 经验/潜能：combat_exp daoxing potential

score相关
- 名称/头衔：title name id
- 攻击/防护：damage armor
- 门派/师承：family master
- 悟性/灵性：int spi
- 其他：     balance age

i相关
- 物品数量：count(物品ID)，计算身上该物品总数

look相关
- 房间属性：room(属性)，属性：short exits outdoors no_fight no_magic water
- 目标存在：here(目标ID)，查看该目标的名字

skills相关
- 技能信息：skill(技能ID)

tasks相关
- 任务额度：task_norm
- 任务信息：task(任务)
任务格式为：<任务类别>/<任务>，类别和任务如下：
- 灭妖(mieyao)：mieyao
- 解谜(quest)：food weapon armor cloth ask give kill
- 势力(forces)：cien
比如李靖任务为：mieyao/mieyao，猪八戒任务为：quest/food。

其他
* 狮驼岭战功：stl_zg，随着相关指令的上线，该参数会移去

用法举例
- 气血比例：query 气血:kee,eff_kee,kee_ratio
- 查看技能：query 技能:skill(force),skill(spells)
- 任务信息：query task(mieyao/mieyao),task(quest/food)
- 几个枕头：query count(huangliang zhen)
- 房间出口：query room(exits)
- NPC在否：query here(li jing)

HELP
	);
	return 1;
}
