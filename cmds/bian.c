// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

//inherit F_CLEAN_UP;	//������ָ���callout�Ķ���Ҫ�Զ�����

#define BUFF_ID		"bian2"
#define BUFF_NAME	HIG"�仯"NOR
#define DMANA		30		//ԭ�������Ĺ�ʽ = 30 + 400 / (spells - 20)

int on_timer(mapping buff);

int main(object me, string arg)
{
	string msg;
	mapping buff_ori = BUFF->find(me, BUFF_ID);

	if(me->query_temp("d_mana") > 0 && !buff_ori) return 0;	//�׸�ԭ����bian����

	seteuid(getuid());
	msg = BTL->bad_state(me, ({"fighting", "ghost", "busy"}));
	if(msg) return notify_fail("��" + msg + "\n");

	if(buff_ori && (!arg || arg == "me" || arg == me->query("id"))) {
		BUFF->remove1(buff_ori);
		msv(HIY"$N�����������һ�Σ���������\n"NOR, me);
	} else {
		object who = present(arg + "", environment(me));
		if(!objectp(who) || who == me) {
			return notify_fail("������˭��\n");
		} else {
			mapping req = ([
				"skill"		: ([ "spells"	: 25]),
				"prop"		: ([ "mana"		: 150,	"daoxing": 16000, "max_mana" : 640]),
				]);
			mapping buff = BUFF->find(who, BUFF_ID);

			if(wizardp(who) && !wizardp(me)) return notify_fail("��ķ��������Ա����ʦ��\n");
			if(!BTL->require(me, BUFF_NAME, req)) return 1;
			BTL->pay(me, (["mana" : 100]));
			if(buff) {
				buff = buff + ([]);			//����buff
			} else {
				buff = ([					//�����µ�buff
					"id"		: BUFF_ID,
					"name"		: BUFF_NAME,
					"comment"	: "������������˻��",
					"class"		: "������",
					"attr"		: 2,		//����buff
					"temp"		: ([
						"d_mana"		: DMANA,
						"apply/id"		: who->parse_command_id_list(),
						"apply/name"	: ({ who->name() }),
						"apply/short"	: ({ who->short() }),
						"apply/long"	: ({ who->long() }),
						"no_heal_up/bian" : 1,
						"is_living"		: living(who),
						"is_character"	: who->is_character(),
						"unit"			: who->query("unit"),			
						"gender"		: who->query("gender"),
						"age"			: who->query("age"),
						"race"			: who->query("race"),
						"family"		: who->query("family"),
					]),
					"interval"	: 5,
					"timer_act"	: (: on_timer :),
					"post_act"	: function(mapping buff) {
						object me = buff["me"];
						while( environment(me)->is_character())
							me->move(environment(environment(me)));
					},
				]);
			}
			if(buff_ori) BUFF->remove1(buff_ori);
			BUFF->add(me, buff);
		
			msv(HIY"$N����ھ�������ԣ�ҡ��һ�䣬��ú�$nһģһ����\n"NOR, me, who);
		}
	}
	return 1;
}

int on_timer(mapping buff)
{  
	object me = buff["me"];
	if(me->query("mana") > DMANA + 50) {
		me->add("mana", -DMANA);
		return 1;
	}
	msv(HIY"ֻ��$N��ɫ�԰ף�һ�����֮�䣬�Ѿ�����ԭ�Ρ�\n"NOR, me);
	return 0;
}

int help(object me)
{
	write(@HELP

ָ���ʽ �� bian [<����>|<NPC>|<me>]

�����������ָ������仯�����������ģ�����Ƿ��ܱ䣬��Ҫȡ����
��ķ����ͷ�����С��

�������ָ� observe��
HELP
	);
	return 1;
}
