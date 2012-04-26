// firefox 11/21/2009

inherit SSERVER;

#include <xyj_x.h>
#include <ansi.h>

#define ID				"qimen"
#define NAME			HIW"���Ŷݼ���"NOR
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
	mapping buff_ori = BUFF->find(me, ID);

	if(buff_ori) {
		BUFF->remove1(buff_ori);
	} else {
		int skill = me->query_skill("taiyi", 1);
		mapping env_req = ([
			"ex_value"	: ([ "no_change"	: "���ﲻ��ʩ��"NAME"��" ]),
			"ex_class"	: ([ "װ��"			: "�����Ѿ����˸����ˡ�"]),
		]);
  		mapping req = ([
			"skill1"	: ([ "taiyi"		: 60]),
			"prop"		: ([ "mana"			: 400,	"sen"	: 100 ]),
		]);
		object barrier;

		if(!BTL->require(env, NAME, env_req)) return 1;
		if(!BTL->require(me, NAME, req)) return 1;
		if(!cd_start(me, ID, CD)) return notify_fail("����ʱ������ʹ��"NAME"��\n");

		seteuid(getuid());
		barrier = new(X_DIR"obj/fabao/barrier");
		barrier->set("host", me);

		msv(HIW"$Nߴ����������˼������ͻȻ����հ׹�һ��!\n"NOR, me);
		if(barrier->move_to(env)) {
			mapping env_buff = ([
				"id"		: ID,
				"name"		: NAME,
				"class"		: "װ��",
				"comment"	: BUFF_DESC,
				"replace"	: ([
					"short"		: NAME,
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
				"id"		: ID,
				"name"		: NAME,
				"comment"	: BUFF_DESC,
				"_env"		: env,
			]);
			BTL->pay(me, req["prop"]);
			BUFF->link_each(env_buff, buff);
			BUFF->add(env, env_buff);
			BUFF->add(me, buff);
			me->start_busy(2);
		}
	}
	return 3;
}

int post_act(mapping buff)
{
	destruct(buff["_barrier"]);
	tell_room(buff["me"], "���һ����"NAME"��ʧ�ˡ�\n"); 
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
