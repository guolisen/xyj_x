// by firefox 11/21/2009

inherit SSERVER;

#include <xyj_x.h>
#include <ansi.h>

#define BUFF_ID			"qimen2"
#define BUFF_NAME		HIW"���Ŷݼ���"NOR
#define BUFF_DESC		"ʩ�����Ŷݼס�"
#define CD				20

string room_long = "\n"
	"��ͻȻ����������ת�������ǳ�ȫ����ʧ����Ҳ�ֲ��嶫���ϱ���\n"
	"��ǰ�������һƬ�������������䣬����������˸������һʱ����\n"
	"��ţ�һʱ������죬һ�ɾ�������������ֱ�����飬���ɼ�\n"
	"�ػ���ֱ�����\n\n";


int checking(mapping buff);
int post_act(mapping buff);
mapping new_exits(object env);

int cast(object me, object target)
{
	object env = environment(me);
	mapping buff_ori = BUFF->find(me, BUFF_ID);

	if(buff_ori) {
		BUFF->remove1(buff_ori);
	} else {
		int skill = me->query_skill("taiyi", 1);
		mapping env_req = ([
			"ex_value"	: ([ "no_change"	: "���ﲻ��ʩ��"BUFF_NAME"��" ]),
			"ex_class"	: ([ "װ��"			: "�����Ѿ����˸����ˡ�"]),
		]);
  		mapping req = ([
			"cd"		: ([ BUFF_ID		: 1 ]),
			"skill1"	: ([ "taiyi"		: 60]),
			"prop"		: ([ "mana"			: 400,	"sen"	: 100 ]),
		]);
		object barrier;

		if(!BTL->require(env, BUFF_NAME, env_req)) return 1;
		if(!BTL->require(me, BUFF_NAME, req)) return 1;

		seteuid(getuid());
		barrier = new(X_DIR"obj/fabao/barrier");
		barrier->set("host", me);

		msv(HIW"$Nߴ����������˼������ͻȻ����հ׹�һ��!\n"NOR, me);
		if(barrier->move_to(env)) {
			mapping env_buff = ([
				"id"		: BUFF_ID,
				"name"		: BUFF_NAME,
				"class"		: "װ��",
				"comment"	: BUFF_DESC,
				"replace"	: ([
					"short"		: BUFF_NAME,
					"long"		: room_long,
					"exits"		: new_exits(env),
				]),
				"interval"	: 2,
				"timer_act"	: (: checking :),
				"post_act"	: (: post_act :),
				"_host"		: me,
				"_barrier"	: barrier,
			]);
			mapping buff = ([
				"id"		: BUFF_ID,
				"name"		: BUFF_NAME,
				"comment"	: BUFF_DESC,
				"_env"		: env,
			]);
			BTL->pay(me, req["prop"]);
			BUFF->link_each(env_buff, buff);
			BUFF->add(env, env_buff);
			BUFF->add(me, buff);
			BUFF->start_cd2(me, buff, CD);
			me->start_busy(2);
		}
	}
	return 3;
}

int post_act(mapping buff)
{
	destruct(buff["_barrier"]);
	tell_room(buff["me"], "���һ����"BUFF_NAME"��ʧ�ˡ�\n"NOR); 
	return 1;
}

//���hostλ�ã�����
int checking(mapping buff)
{
	object env = buff["me"];
	object host = buff["_host"];
	if(!host || environment(host) != env) return 0;
	if(host->query_skill_mapped("spells") != "taiyi") return 0;
	return 1;
}

//�����³��ڣ��ϳ��ڲ��䣬�¼ӵĳ���ָ����
mapping new_exits(object env)
{
	mapping ori = env->query("exits");
	mapping rep = ([
		"east"		: env,		"west"		: env,
		"north"		: env,		"south"		: env,
		"northeast"	: env,		"southeast"	: env,
		"southwest"	: env,		"northwest"	: env,
	]);
	if(mapp(ori)) rep += ori;
	return rep;
}
