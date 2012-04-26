// by firefox 11/21/2009

inherit F_CLEAN_UP;

#include <xyj_x.h>
#include <ansi.h>

#define ID				"yihun"
#define NAME			HIW"�ƻ��"NOR
#define DESC			"ʩ��/���������ƻ�󷨡�"
#define CD				40
#define DURATION		30

#define MY_HOST			"yhdf_my_host"
#define MY_SERVANT		"yhdf_my_servant"
#define MY_COMMAND		"yhdf_my_command"
#define SOUL			X_DIR"obj/fabao/soul"

int buff_sb(object me, string relation, object target);

int cast(object me, object target)
{
	mapping req = ([
		"skill1"	: ([ "spells"		: 100 ]),
		"prop"		: ([ "mana"			: 400 ]),
	]);
	mapping cmp_parm = ([
		"prop"		: ([ "cps" : 3, DEXP : 1, "sen" : 1, "max_sen" : -1, "max_mana" : 3 ]),
		"skill"		: ([ "spells" : 3 ]),
		"temp"		: ([ "no_cast" : -1 ]),
	]);
	
	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("��Ҫ����˭��\n");

	if(BUFF->find(target, ID)) return notify_ok("�Է��޷������ƣ�\n");
	if(!BTL->require(me, NAME, req)) return 1;
	if(!cd_start(me, ID, CD)) return notify_fail("����ʱ������ʹ��"NAME"��\n");

	BTL->pay(me, req["prop"]);

	msv(HIC"\n$N���һ�����ƻ�󷨡���ֻ��$NĿ����磬ֱ����$n���С�\n", me, target);
	
	if(BTL->cmp_random20(me, target, cmp_parm) > 150) {
		buff_sb(me, MY_SERVANT, target);
		buff_sb(target, MY_HOST, me);
		target->receive_damage("sen", 1, me);

		msv("$n���������㱣���ʧ�����ǡ�ĬĬվ��$N���\n\n"NOR, me, target);
		BUFF->link_each(BUFF->find(me, ID), BUFF->find(target, ID));

		SKILL_D("pansi-dafa")->random_level_up(me);
	} else {
		msv("$n����������Ŀ�����⡣\n\n"NOR, me, target);
		BTL->fight_enemy(target, me);
	}
	me->start_busy(1);
	return 3;
}

int post_act(mapping buff)
{
	if(buff["_invoker"])	{
		object me = buff["me"];
		me->set_leader(0);
		me->remove_all_killer();
		msv(HIW"$N�ַ���ͷ��ҡҡ�λΣ������˹�����\n\n"NOR, me);
	}
	return 1;
}

int on_timer(mapping buff)
{
	object me = buff["me"];
	object host = buff["_invoker"];
	if(!host) return 0;
	me->set_temp(MY_COMMAND, 1);
	if(same_env(me, host)) {
		if(host->is_fighting(me)) return 0;	//����ɱ�Լ������������
		if(host->is_fighting()) {
			string* cmds = buff["_cmds"];
			me->remove_all_killer();
			BTL->copy_enemy(host, me);
			if(sizeof(cmds)) me->command(random1(cmds));		
		} else {
			string id = getuid(host);
			string* cmds = ({"fool", "idle", "sweat " + id, "lick " + id, "say ���ˡ�" });
			if(!random(10)) me->command(random1(cmds));
		}		
	} else {
		if(!random(20)) me->command("say ���ˣ������Ķ���");
	}
	me->set_temp(MY_COMMAND, 0);
	return 1;
}

int buff_sb(object me, string relation, object target)
{
	object soul = new(SOUL);
	mapping buff = ([
		"id"		: ID,
		"name"		: NAME,
		"class"		: "�������",
		"comment"	: DESC,
		"duration"	: DURATION,
		"temp"		: ([ relation : target ]),
		"object"	: ([ "soul" : soul ]),
		"interval"	: 1,
		"post_act"	: (: post_act :),
	]);
	me->remove_killer(target);
	if(relation == MY_HOST) {
		buff["_cmds"] = ({ "exert recover", "exert refresh" });
		buff["_invoker"] = target;
		buff["timer_act"] = (: on_timer :);
		me->set_leader(target);
	}
	BUFF->add(me, buff);
	return soul->move_to(me);
}

