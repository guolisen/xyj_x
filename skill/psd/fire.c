// by firefox 11/21/2009

inherit F_CLEAN_UP;

#include <weapon.h>
#include <ansi.h>
#include <xyj_x.h>

#define ID				"sm-fire"
#define NAME			HIB"三昧白骨火"NOR
#define CD				10
#define DURATION		4

#define MSG0			"$N用手向$n一指，点点不易察觉的"HIB"磷光"NOR"从$n脚下升起...\n"NOR
#define MSG1			HIY"$n的%s突然起火，惊慌失措，拼命扑打。\n"NOR
#define MSG2			"$n一挥手"HIB"磷光"NOR"随风飘散了...\n"NOR
#define MSG3			CYN"$N扑灭了白骨火，但%s已经一片焦黑。\n"

/*
白晶晶：看来我不用三昧白骨火你是不会承认的！(玉手一指，至尊宝的手马上起火)
至尊宝：还用得着吗？又烧！何苦呢－－？何必呢－－？
白晶晶：难道我搞错了？(飞身上前将火扑灭) 
*/

void po_lost(object target, int n);

int cast(object me, object target)
{
	int mana = 10 + me->query("mana_factor");
	mapping req = ([
		"skill1"	: ([ "pansi-dafa"	: 30 ]),
		"prop"		: ([ "mana"			: mana ]),
	]);
	mapping cmp_parm = ([
		"prop"		: ([ DEXP : 1, "mana_factor" : 1, "sen" : 1, "max_sen" : -1 ]),
		"skill"		: ([ "spells" : 3]),
		"temp"		: ([ "no_cast" : -1]),
	]);

	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("你要烧谁？");
	if(!BTL->require(me, NAME, req)) return 1;
	if(!cd_start(me, ID, CD)) return notify_fail("你暂时还不能使用"NAME"。\n");
	
	BTL->pay(me, req["prop"]);

	msv(MSG0, me, target);

	if(BTL->cmp_random20(me, target, cmp_parm) > 80) {
		int damage = 50 + mana * 2;
		string part = (target->query("gender") == "女性") ? "手上" : random1(({"手上", "裆部"}));

		BUFF->start_no_wield(target, DURATION, sprintf(MSG3, part));
		msvx(MSG1, me, target, part);

		target->receive_damage("kee", damage, me);
		target->receive_wound("kee", damage, me);
		COMBAT_D->report_status(target);

		if(!userp(target) && !random(80))
			target->command("say 还用得着吗？又烧！何苦呢－－？何必呢－－？");
		if(part == "裆部" && !random(20))
			call_out("cut", DURATION * SEC_PER_HB + 1, target);
		
		SKILL_D("pansi-dafa")->random_level_up(me);

	} else {
		msv(MSG2, me, target);
	}
	BTL->fight_enemy(target, me);
	return 2;
}

void cut(object who)
{
	object env = who ? environment(who) : 0;
	object weapon;

	if(!env || who->is_fighting()) return;
	foreach(object ob in all_inventory(env)) {
		if(ob == who || !ob->is_character() || userp(ob)) continue;
		weapon = ob->query_temp("weapon");
		if(weapon && (weapon->query("flag") & EDGED) && weapon->query("weapon_prop/damage") < 51) {
			string uid = who->parse_command_id_list()[0];
			string wid = weapon->query("id");

			msv(CYN"$N同情的看着$n。\n", ob, who);
			ob->command("say 都烧焦了，还是割了吧...");
			if(who->query("env/no_accept"))	ob->command("drop " + wid);
			else ob->command("give " + wid + " to " + uid);
			return;
		}
	}

}