// by firefox 11/21/2009

inherit F_CLEAN_UP;

#include <xyj_x.h>
#include <ansi.h>

#define ID			"yixing"
#define NAME		HIY"���λ�Ӱ"NOR
#define DURATION	120
#define CD			(7*60)

int on_timer(mapping buff);
mapping get_buff(object me, object target);

int cast(object me, object target)
{
	string msg;
	mapping buff_ori = BUFF->find(me, ID);

	if(!target && buff_ori) {
		BUFF->remove1(buff_ori);
		return 1;
	}
	if(!objectp(target) || !BTL->get_victim(me, target)) return notify_ok("���˭���λ�Ӱ��\n");
	else if(BUFF->find(target, ID)) return notify_ok("�Է��Ѿ��������ˣ�\n");
	else if(BUFF->find2(target, "������")) return notify_ok("�Է��ڱ����У�\n");
	else {
		mapping req = ([
			"ex_temp"	: ([ "d_mana" : 1 ]),
			"ex_class"	: ([ "������" : 1 ]),
			"skill1"	: ([ "pingtian-dafa" : 120]),
			"prop"		: ([ "mana" : 300 ]),
		]);
		mapping cmp_parm = ([
			"prop"		: ([ "mana" : 1, "daoxing" : 1 ]),
			"skill"		: ([ "spells" : 3]),
			"temp"		: ([ "no_cast" : -1]),
		]);
		if(!BTL->require(me, NAME, req)) return 1;
		if(!cd_start(me, ID, CD)) return notify_fail("����ʱ������ʹ��"NAME"��\n");

		BTL->pay(me, req["prop"]);
		message_vision("$N��ȣ�"NAME"��$N��$n������һ��ת�������ֲ���˴ˡ�\n"
			"Ƭ��֮������ͣ�������Եö����Ǳ���\n", me, target);

		if(BTL->cmp_random20(me, target, cmp_parm) >= 90) {
			mapping b1 = get_buff(me, target);
			mapping b2 = get_buff(target, me);
			BUFF->link_each(b1, b2);
			BUFF->add(me, b1);
			BUFF->add(target, b2);
		}		
		if(!target->is_busy()) target->start_busy(2);
		me->start_busy(2);
	}
	return 1;
}

mapping get_buff(object me, object target)
{
	mapping buff = ([
		"id"		: ID,
		"name"		: NAME,
		"comment"	: "�ͱ��˽�������",
		"class"		: "������",
		"duration"	: DURATION,
		"temp"		: ([	//�����
			"apply/id"		: target->parse_command_id_list(),
			"apply/name"	: ({ target->name() }),			
			"apply/short"	: ({ target->short() }),
			"apply/long"	: ({ target->long() }),
			"no_heal_up/"ID : 1,
		]),
		"add_apply"	: ([	//��������ò
			//"armor"			: target->query_temp("apply/armor") - me->query_temp("apply/armor"),
			"personality"	: target->query_per() - me->query_per(),
		]),
		"add"		: ([	//��Ѫ
			"max_kee"		: target->query("max_kee") - me->query("max_kee"),
			"eff_kee"		: target->query("eff_kee") - me->query("eff_kee"),
			"kee"			: target->query("kee") - me->query("kee"),
		]),
		"stop_msg"	: HIY"��㱼�$N�·�ͻȻ���˹���������Χ��İ����",
		"interval"	: 1,
		//"timer_act"	: (: on_timer :),
		"post_act"	: function(mapping buff) {
			object me = buff["me"];
			me->receive_curing("kee", 1);
			me->receive_heal("kee", 1);
		},
		"data"		: (["target" : target ]),
	]);
	tell_object(me, "��о�������Щ������\n");
	return buff;
}

int on_timer(mapping buff)
{
	object me = buff["me"];
	object target = buff["data"]["target"];
	mapping b2 = BUFF->find(target, ID);

	//TODO:����ʲô��
	return 1;
}
