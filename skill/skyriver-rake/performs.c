// by firefox 02/09/2010

inherit SSERVER;

#include <xyj_x.h>
#include <ansi.h>

//���ѡ��ͬ������һ��������
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

//��ʼ���ģ���Ż��
varargs mapping start_sick(object me, int duration, string msg)
{
	mapping buff = ([
		"id"		: "sick",
		"name"		: HIY"����"NOR,
		"comment"	: "θ�﷭����������Ż�¡�",
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
#define NAME			HIW"�������"NOR
#define CD				10

//����ħ��˫��master��˽䡣�񰡣�������������ػ�����ˡ����������¡�
int attack(object me, object target);

int perform(object me, object target)
{
	mapping req = ([
		"cd"		: ([ ID					: 1 ]),
		"skill1"	: ([ "skyriver-rake"	: 250 ]),
		"prop"		: ([ "force"			: 10 ]),
	]);
	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("��˭��\n");
	
	if(me->query_per() > 10) return notify_ok("�㲻����û��ȥ���ˡ�\n");	
	if(!BTL->require(me, NAME, req)) return 1;
	BTL->pay(me, req["prop"]);
	
	BUFF->start_cd(me, ID, NAME, CD);
	attack(me, target);


	return 1;
}

mapping performs = ([
	"zhuyan"	: ([
		"name"		: "���հ׷�",
		"begin"		: HIM
			"$N��̤�۷����貽�ݣ��İ��۲�ȫ���ɣݣ������裬ʹ������Ӱҷ��ݵľ���\n"
			"             ��������"HIR" ���� "HIW" �׷� "HIM"��������\n"
			"ֻ��$N��ëƮƮ���������ǣ���Ŀ�����Ҳ��̶ã�\n"
			"ʹ�����龡�⴦��˫�����ߣ��ޱ���ζ�뵰����$n��\n",
		"prefix"	: HIY"ֻ��һ��ɱ���ĺ��У�",
		"names"		: ({
			HIG"�����䣬ʳΪ���� "NOR"��",
			HIC"̾���������ںη� "NOR"��",
			HIB"�త��������Կ� "NOR"��",
			HIR"�����棬��ɷ���� "NOR"��",
			HIW"Ц��ʳ����˰׷� "NOR"��",
		}),
		"post_msg"	: HIW"$n��Ѭ���޷�����������һ�Σ���ǰһ�ڡ�����",
		"post_act"	: function(object me, object target) {
			target->receive_damage("sen", 500, me);
			target->receive_wound("sen", 500, me);
			COMBAT_D->report_sen_status(target);
			return 1;
		},
	]),

	"fcbd"	: ([
		"name"		: "�ʳ�����",
		"begin"		: HIW"\n$N�����䶯,�·������������赸,����Ʈ������$nʹ���ˣ۳��ʱ��ǣݣ�\n",
		"prefix"	: "",
		"names"		: ({
            MAG"����",
            HIC"        �±�",
            HIB"                ����",
            YEL"                        ����",
            HIW"                                ����",
		}),
		"post_msg"	: "$n����������$N��ͻȻ��"HIR"һ����Ѫ�籡����"NOR"��ֱ���������⡣",
		"post_act"	: function(object me, object target) {
			target->receive_damage("kee", 500, me);
			target->receive_wound("kee", 500, me);
			COMBAT_D->report_status(target);
			return 1;
		},
	]),

	"szkw"	: ([
		"name"		: "�������",
		"begin"		: HIW"\n"
			"$N���μӿ�,�������,������Ӱҷ����ռ�������������ݣ�\n\n"
			"��$NѤ������ʽ֮��$n�����ܵ���Ӱ��,�������д��ͣ�\n",
		"prefix"	: "",
		"names"		: ({
			HIC"����������֮[Ǭ��һ��]",
			HIW"����������֮[��������]",
			"",
			"",
			HIW"����������֮[�������]",
		}),
		"post_msg"	: HIW"�����˶���ס����һ��������������$N���·��������綼ֹͣ�ˡ�",
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

#define FINISHED HIY"\n$N�����ñ�.ͣ����Ť��������\n"NOR

int attack(object me, object target)
{
	mapping pfm = random1(values(performs));
	mapping act = ([
		"damage"		: 1,
		"dodge"			: 90,
		"parry"			: 90,
		"damage_type"	: "����",
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
