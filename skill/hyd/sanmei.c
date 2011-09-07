// by firefox 11/21/2009

#include <ansi.h>
#include <xyj_x.h>

inherit SSERVER;

#define CD			5		//������ȴʱ��
#define DURATION	60		//���ܳ���ʱ��

#define BUFF_ID		"sanmei2"
#define BUFF_NAME	HIR"�������"NOR
#define BUFF_DESC	HIR"Ũ�̹��������淭�ڣ�һƬ�𺣡�"NOR

#define DEBUFF_ID	"burning"
#define DEBUFF_NAME	HIR"�һ����"NOR
#define DEBUFF_DESC	"�����Ż��Ӿ�ģ���������½���"

int burning(mapping buff);

int cast(object me)
{
	object env = environment(me);
	mapping buff_ori = BUFF->find(me, BUFF_ID);

	if(buff_ori) {
		BUFF->remove1(buff_ori);
	} else {
		int skill = me->query_skill("pingtian-dafa", 1);
		mapping env_req = ([
			"ex_value"	: ([ 
				"no_change"	: "���ﲻ��ʩ��"BUFF_NAME"��",
				"water"		: "�޷���ˮ�зŻ�",
			]),
			"ex_class"	: ([ "װ��"		: "�����Ѿ����˸����ˡ�"]),
		]);
		mapping req = ([
			"cd"		: ([ BUFF_ID	: 1 ]),
			"skill1"	: ([ "pingtian-dafa" : 100 ]),
			"prop"		: ([ "mana"	: skill ]),
		]);
		mapping env_buff = ([
			"id"		: BUFF_ID,
			"name"		: BUFF_NAME,
			"class"		: "װ��",
			"comment"	: BUFF_DESC,
			"duration"	: DURATION + 4,				//�ݻ������ߣ�����Ҳ�ܻظ�
			"replace"	: ([ "long" : env->query("long") + "    "BUFF_DESC"\n" ]),
			"post_act"	: function(mapping buff) {
				tell_room(buff["me"], HIY "��𽥽�Ϩ������һƬ������\n" NOR);
			},
		]);
		mapping buff = ([
			"id"		: BUFF_ID,
			"name"		: BUFF_NAME,
			"comment"	: "����ʩ���������",
			"duration"	: DURATION,			
			"interval"	: 6,
			"timer_act"	: (: burning :),
			"_env"		: env,
		]);
		if(!BTL->require(env, BUFF_NAME, env_req)) return 1;
		if(!BTL->require(me, BUFF_NAME, req)) return 1;

		BTL->pay(me, req["prop"]);
		message_vision(
			"\n$N���Լұ����ϴ�����ȭ��������������𣬱���ð�̣���̼䣺\n\n"
			HIR"��������ӯ���ǣ��պ�������غ졣ȴ�ƻ��ַ����£�����̿м��������\n\n"NOR,
			me
		);
		BUFF->link_each(env_buff, buff);
		BUFF->add(env, env_buff);
		BUFF->add(me, buff);
		BUFF->start_cd2(me, buff, CD);
		
		me->start_busy(1);
	}
	return 1;
}

void burn(object me, object target)
{
	int skill1 = me->query_skill("spells");
	int skill2 = target->query_skill("spells");
	string spells = target->query_skill_mapped("spells");
	int diff;
	
	if(spells != "pingtian-dafa") skill2 /= 3;		//TODO:��ϵ��
	diff = skill1 - skill2;

	if(diff > 10) {
		mapping debuff = ([
			"id"		: DEBUFF_ID,
			"name"		: DEBUFF_NAME,
			"comment"	: DEBUFF_DESC,
			"class"		: "����",
			"duration"	: 5,					//�뿪�𺣣�״̬ҲҪһ��ʱ��ָ�
			"add_apply"		: ([
				"attack"	: -diff,				//�յ��Ӿ�ģ���������½�
				"armor"		: -diff / 2,			//�·��ս��ˣ���������������wound����
				"personality"	: -20,			//������
			]),
		]);
		int damage = diff;						//�������úͷ����������
		BUFF->add(target, debuff);

		target->receive_damage("kee", damage, me);
		target->receive_wound("kee", damage);
		
		tell_object(target, "�㱻�յý�ͷ�ö\n");
		COMBAT_D->report_status(target);

		BTL->fight_enemy(target, me);
	}
}

int burning(mapping buff)
{
	object me = buff["me"];
	object env = environment(me);
	
	if(env != buff["_env"]) return 0;

	tell_room(env, "����ȼ�յ�" HIR "���"  NOR "�·�Ҫ����һ�С�\n");

	foreach(object who in all_inventory(env)) {
		if(!living(who) || !who->is_fighting(me)) continue;
		burn(me, who);
	}
	return 1;
}
