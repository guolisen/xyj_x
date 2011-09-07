// by firefox 02/09/2010

inherit SSERVER;

#include <xyj_x.h>
#include <ansi.h>

//随机选择同场景内一个其他人
string another(object me)
{
	object env = environment(me);
	object* arr = ({});
	foreach(object who in all_inventory(env)) {
		if(!living(who) || who == me ) continue;
		arr += ({ who });
	}
	return sizeof(arr) ? random1(arr) : 0;
}

//开始恶心，想呕吐
varargs mapping start_sick(object me, int duration, string msg)
{
	mapping buff = ([
		"id"		: "sick",
		"name"		: HIY"恶心"NOR,
		"comment"	: "胃里翻江倒海，想呕吐。",
		"duration"	: duration,
		"interval"	: 1,
		"timer_act"	: function(mapping buff) {
			object me = buff["me"];
			if(!me->is_busy() && !random(4)) {
				string ob = another(me);
				string id = ob ? (" " + ob->query("id")) : "";
				me->command("puke" + id);
				me->start_busy(2);
				me->add("water", -100);
				me->add("food", -100);
			}
			return 1;
		},
		"stop_msg"	: msg,
	]);
	return BUFF->add(me, buff);
}


#define ID				"pig_skill"
#define NAME			HIW"神猪绝技"NOR
#define CD				10

//增加魔武双修master猪八戒。神啊，请以你大海碗般的胸怀，宽恕我无意的亵渎。
int attack(object me, object target);

int perform(object me, object target)
{
	mapping req = ([
		"cd"		: ([ ID					: 1 ]),
		"skill1"	: ([ "skyriver-rake"	: 250 ]),
		"prop"		: ([ "force"			: 10 ]),
	]);
	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("打谁？\n");
	
	if(me->query_per() > 10) return notify_ok("你不够丑，没法去吓人。\n");	
	if(!BTL->require(me, NAME, req)) return 1;
	BTL->pay(me, req["prop"]);
	
	BUFF->start_cd(me, ID, NAME, CD);
	attack(me, target);


	return 1;
}

mapping performs = ([
	"zhuyan"	: ([
		"name"		: "猪颜白饭",
		"begin"		: HIM
			"$N脚踏［肥猪舞步］，心暗［不全琴律］，狂嚎乱舞，使出［天河耙法］的精髓\n"
			"             －－－『"HIR" 猪颜 "HIW" 白饭 "HIM"』－－－\n"
			"只见$N短毛飘飘，汗衫袂袂，面目狰狞惨不忍睹！\n"
			"使到动情尽意处，双脚轮踢，无边气味氤氲般卷向$n！\n",
		"prefix"	: HIY"只听一声杀猪般的嚎叫：",
		"names"		: ({
			HIG"问世间，食为何物 "NOR"？",
			HIC"叹人生，饭在何方 "NOR"？",
			HIB"苦挨饿，猪何以堪 "NOR"？",
			HIR"爱交梨，愁煞猪颜 "NOR"！",
			HIW"笑吃食，青菜白饭 "NOR"！",
		}),
		"post_msg"	: HIW"$n被熏的无法呼吸，身形一晃，眼前一黑。。。",
		"post_act"	: function(object me, object target) {
			target->receive_damage("sen", 500, me);
			target->receive_wound("sen", 500, me);
			COMBAT_D->report_sen_status(target);
			return 1;
		},
	]),

	"fcbd"	: ([
		"name"		: "肥肠爆肚",
		"begin"		: HIW"\n$N身形蠕动,仿佛跳着优美的舞蹈,身形飘忽间向$n使出了［肠肥爆肚］！\n",
		"prefix"	: "",
		"names"		: ({
            MAG"肉香",
            HIC"        月饼",
            HIB"                海鲜",
            YEL"                        肠肥",
            HIW"                                爆肚",
		}),
		"post_msg"	: "$n呆呆的望着$N，突然间"HIR"一口鲜血喷薄而出"NOR"，直溅到三丈外。",
		"post_act"	: function(object me, object target) {
			target->receive_damage("kee", 500, me);
			target->receive_wound("kee", 500, me);
			COMBAT_D->report_status(target);
			return 1;
		},
	]),

	"szkw"	: ([
		"name"		: "神猪狂舞",
		"begin"		: HIW"\n"
			"$N身形加快,耙舞如风,正是天河耙法的终极奥义［神猪狂舞］！\n\n"
			"在$N绚丽的招式之下$n心神受到到影响,身形略有呆滞！\n",
		"prefix"	: "",
		"names"		: ({
			HIC"［神猪狂舞］之[乾坤一耙]",
			HIW"［神猪狂舞］之[霹雳三挠]",
			"",
			"",
			HIW"［神猪狂舞］之[肚里澄清]",
		}),
		"post_msg"	: HIW"所有人都摒住呼吸一动不动，凝视着$N，仿佛整个世界都停止了。",
		"post_act"	: function(object me, object target) {
			object env = environment(me);
			foreach(object who in all_inventory(env)) {
				if(!living(who) || who == me ) continue;
				start_sick(who, 20);
			}
			return 1;
		},
	]),
]);

#define FINISHED HIY"\n$N绝招用毕.停下了扭动的身形\n"NOR

int attack(object me, object target)
{
	mapping pfm = random1(values(performs));
	mapping act = ([
		"damage"		: 1,
		"dodge"			: 90,
		"parry"			: 90,
		"damage_type"	: "刺伤",
	]);

	message_vision(pfm["begin"], me, target);
	foreach(string name in pfm["names"])
	{
		act["action"] = pfm["prefix"] + name + NOR;
		me->set("actions", act);
		COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
	}
	me->reset_action();
	if(target) {
		message_vision(FINISHED, me, target);
		message_vision("\n" + pfm["post_msg"] + NOR"\n", me, target);
		if(functionp(pfm["post_act"])) evaluate(pfm["post_act"], me, target);

		BTL->fight_enemy(target, me);
		me->start_busy(3);
		if(!target->is_busy()) target->start_busy(3);
	}
}
