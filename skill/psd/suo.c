// by firefox 11/21/2009

inherit F_CLEAN_UP;

#include <ansi.h>
#include <xyj_x.h>

#define ID				"suoshen"
#define NAME			HIB"缩身法"NOR
#define DURATION		7
#define CD				15

#define MSG0			"$N念动咒语，一瞬间身形缩小如同一只飞虫，飞向$n口中！\n"
#define MSG1			HIC"$n慌乱之中吸了一口气，却再也找不到$N。\n"NOR
#define MSG2			HIC"$n赶忙屏息闭口，$N见无隙可乘只好恢复身形。\n"NOR

/*
龟缩大法/缩身法

春卅娘：龟缩大法。(捐入牛魔王个肚，狂砍牛魔王内脏)我片你啲内脏，问你点挡？同你打
番个结呀。
牛魔王：原神出壳。(灵魂捐入自己肉身)八婆，你唔好再踩(yai)我条肠呀。

至尊宝：我知道其实你心里面重有怀疑，如果我可以攞个心出嚟畀你睇，你就知我冇讲大话
白晶晶：好容易啫！(晶晶用缩身法进入至尊宝体内。)

基本是个两败俱伤的打法，缩身法要和狮子的吞统一考虑：
主要比较法力/法术，如果『食物』有兵器(或damage)的则占一定优势。

*/

//吞下
int swallow(object eater, object food, int duration, int thr);

int cast(object me, object target)
{
	int thr = 100;
	int mana = 100;
	mapping req = ([
		"skill1"	: ([ "pansi-dafa"	: 80 ]),
		"prop"		: ([ "mana"			: mana ]),
	]);
	mapping cmp_parm = ([
		"prop"		: ([ DEXP : 1, "sen" : 1, "max_sen" : -1 ]),
		"skill"		: ([ "spells" : 3]),
		"temp"		: ([ "no_cast" : -1, "no_move" : -1]),
	]);

	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("你要进入谁的腹中？");
	if(!BTL->require(me, NAME, req)) return 1;

	if(!cd_start(me, ID, CD)) return notify_ok("你暂时不能使用「"NAME"」！\n");

	BTL->pay(me, req["prop"]);

	msv(MSG0, me, target);

	if(target->is_busy()) thr -= 20;

	if(BTL->cmp_random20(me, target, cmp_parm) > thr) {
		msvx(MSG1, me, target);
		swallow(target, me, DURATION, 110);

		SKILL_D("pansi-dafa")->random_level_up(me);
	} else {
		msv(MSG2, me, target);
	}
	BTL->fight_enemy(target, me);
	return 2;
}


/*****************************吞咽函数*****************************/

mapping _food_cmp = ([
	"prop"		: ([ DEXP : 1, "sen" : 1, "max_sen" : -1, "max_mana" : 3 ]),
	"skill"		: ([ "spells" : 2]),
	"temp"		: ([ "no_cast" : -1]),
]);


private int food_damage(object food)
{
	return food->query_str() / 2 + food->query_temp("apply/damage") * 2;
}

private int food_timer(mapping buff)
{	
	object food = buff["me"];
	object eater = buff["_eater"];
	object env;
	
	int damage;

	if(environment(food) != buff["_env"]) return 0;
	if(!eater || BTL->in_safy(eater)) return 0;

	if(BTL->cmp_random20(eater, food, _food_cmp) > buff["_thr"]) {
		
		string msg = CYN"$N打了一个嗝。";
		object weapon = food->query_temp("weapon");	
		damage = eater->query("mana_factor") * 2;
		
		eater->add("food", 1 + damage / 10);
		
		if(weapon && random(2)) {
			msv(CYN"一股急流涌来，$N手中兵器把持不住被冲走了。\n"NOR, food);
			weapon->unequip();
			if(weapon->move(environment(eater)))
				msg += "吐出一" + weapon->query("unit") + weapon->name() + CYN"。";
		} else {
			trace("damage:" + damage);
			msv(CYN"$N身上的酸液浸入肌肤，浑身疼痛难忍。\n"NOR, food);
			food->receive_wound("kee", damage, eater);
		}
		msv(msg + "\n"NOR, eater);
				
	} else {
		msv(CYN"黑暗中$N四处乱捅乱打，只听得外面惨叫一声接一声。\n"NOR, food);

		tell_object(eater, HIR"你腹中一阵搅动，痛彻心肺！\n"NOR);
		msv(CYN"$N痛得满地打滚，一声声惨叫。\n"NOR, eater);

		damage = food_damage(food);
		
		trace("damage:" + damage);
		
		if(damage < eater->query("kee"))
			eater->receive_wound("kee", damage, food);
		if(!eater->is_busy()) eater->start_busy(1);
	}
	return 1;
}

//食物离开吞噬者
private int food_out(mapping buff)
{
	object food = buff["me"];
	object eater = buff["_eater"];
	object env = load_object("/d/city/recycle");
	
	if(eater) {
		int damage = food_damage(food) * 2;
		int ratio = BTL->cmp_random20(eater, food, _food_cmp);

		env = environment(eater);
	
		if(!BTL->in_safy(eater) && ratio < buff["_thr"] - 10 
			&& damage < food->query("force")) 
		{
			food->add("force", -damage);

			msv(CYN"$N用尽全力将墙壁撕开一个口子，钻了出去。\n"NOR, food);
			msv(HIR"$N背上鲜血四溅，$n破背而出！\n"NOR, eater, food);
			food->move(env);

			eater->receive_wound("kee", damage, food);
			return 1;
		} else {
			msv(CYN"$N突然觉得胃一阵抽筋，哇啦哇啦地吐了满地。\n"NOR, eater);
		}
	}
	
	msv(CYN"一股浊流如泥沙俱下，$N身不由己被冲走了。\n"NOR, food);
	food->move(env);
	msv(HIC"$N头顶菜叶，面带米糊，从地上一跃而起。\n"NOR, food);
	return 1;
}

object load_stomach(object who)
{
	string sid = who->query("id") + "'s stomach";
	string sname = RED + who->query("name") + "的腹中"NOR;

	object room = load_object("/d/wiz/sleeveroom");		
	object stomach = present(sid, room);

	if(!stomach) {
		stomach = new(X_DIR"obj/fabao/stomach");
			
		stomach->set_name(sname, ({sid, "sleeve"}));
		stomach->set("short", sname);

		stomach->move(room);
	}
	return stomach;
}

//吞咽目标
int swallow(object eater, object food, int duration, int thr)
{
	object stomach = load_stomach(eater);

	mapping buff = ([
		"id"		: "food",
		"name"		: HIY"食物"NOR,
		"comment"	: "被吃掉了。",
		"duration"	: duration,
		"interval"	: 2,
		"timer_act"	: (: food_timer :),
		"post_act"	: (: food_out :),
		"_eater"	: eater,
		"_thr"		: thr,
		"_env"		: stomach,
	]);

	if(BUFF->add(food, buff)) {
		food->move(stomach);
	}
	return 1;
}
