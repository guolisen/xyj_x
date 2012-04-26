// by firefox 11/21/2009

inherit SSERVER;

#include <xyj_x.h>
#include <ansi.h>

#define ID				"gouhun2"
#define NAME			HIB"勾魂"NOR
#define DURATION		30
#define CD				20

#define BUFF_ID			"shlp"
#define BUFF_NAME		"失魂落魄"

mapping po_tab = ([
	"dodge"			: ({ "和魄", HIW, "平衡之力/轻功",}),
	"karma"			: ({ "义魄", HIG, "生死之义/福缘",}),
	"intelligence"	: ({ "智魄", HIM, "智慧/智力",}),
	"attack"		: ({ "德魄", HIY, "品行/命中",}),
	"strength"		: ({ "力魄", HIC, "力量",}),
	"composure"		: ({ "气魄", HIB, "正义/定力",}),
	"courage"		: ({ "恶魄", HIR, "邪恶/胆识",}),
]);

void po_lost(object target, int n);

int cast(object me, object target)
{
	int success = 0;
	int skill = me->query_skill("gouhunshu", 1);
	int mana = 25 + 2*(int)me->query("mana_factor");
	mapping req = ([
		"skill1"	: ([ "gouhunshu"	: 250]),
		"prop"		: ([ "mana"			: mana,		"sen"			: 50]),
	]);
	mapping cmp_parm = ([
		"prop"		: ([ "mana" : 2, "daoxing" : 2, "mana_factor" : 2 ]),
		"skill"		: ([ "spells" : 4]),
	]);

	target = BTL->get_victim(me, target);
	if(!objectp(target)) return notify_ok("你要勾谁的魂魄？\n");

	if(!BTL->require(me, NAME, req)) return 1;
	if(!cd_start(me, ID, CD)) return notify_fail("你暂时还不能使用"NAME"。\n");
	BTL->pay(me, req["prop"]);

	message_vision(HIC"$N对$n阴阴地笑着：阎王叫你三更死，不敢留你到五更。。。\n"NOR, me, target);

	success = BTL->cmp_parm(me, target, cmp_parm);
	trace("gouhun2 success = " + success);
	success = MATH->random_pct(success, 30);	//加入30%的随机性
	success = (success - 50)/20;		//平均2.5个魂魄
	success = min2(success, 7);			//最多7
	if(success > 0) {
		int damage = target->query("max_sen") * success / 10;
		target->receive_damage("sen", damage, me);
		target->receive_wound("sen", damage, me);
		po_lost(target, success);
		COMBAT_D->report_sen_status(target);
	} else {		
		message_vision(HIC"但是$n神情专注，对$N理都不理。\n"NOR, me, target);
	}
	BTL->fight_enemy(target, me);
	me->start_busy(2);
	return 1;
}

//目标失去n个魂魄
void po_lost(object target, int n)
{	
	mapping flags = target->query_temp(BUFF_ID);	//已经散去的“魄”的标记集合
	string* remains = keys(po_tab) - (mapp(flags) ? keys(flags) : ({}));	//剩下的“魄”的集合
	int size = sizeof(remains);
	n = min2(n, size);
	
	if(size) {
		string colors = "";
		foreach(string key in MATH->random_elem(remains, n)) {
			string color = po_tab[key][1];
			string name = color + po_tab[key][0] + NOR;
			mapping buff = ([
				"id"		: BUFF_ID + key,
				"name"		: BUFF_NAME + "-" + name,
				"comment"	: name + "被勾走了，失去了" + po_tab[key][2] + "。",
				"duration"	: 1 + random(DURATION * 2),
				"temp"		: ([ BUFF_ID + "/" + key : 1 ]),
				"add_apply" : ([ key : -BTL->query_attr(target, key) ]),
				"stop_msg"	: "一股" + color + "灵气"NOR"缓缓飘向$N，渐渐隐没在$N的头顶。\n\n",
			]);
			if(size < 3 && !target->query_temp("no_move")) {
				buff["temp"]["no_move"] = 1;
				//message_vision("$N失魂落魄，呆若木鸡。\n", target);
			}
			BUFF->add(target, buff);
			colors += color + COLOR->ch(color);
		}
		//message_vision(colors + NOR + chinese_number(n) + "股灵气"NOR"从$N脑门上钻出，飞散开去。\n"NOR, target);
		message_vision(chinese_number(n) + "股灵气"NOR"从$N脑门上钻出，飞散开去。\n"NOR, target);
	} else {	//七魄光了，现在失去命魂就要挂了		
		message_vision(YEL"灵气从$N头顶散尽，$N已经三魂尽失，七魄皆散......\n"NOR, target);
	}
}
