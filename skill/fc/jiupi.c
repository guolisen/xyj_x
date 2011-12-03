// by firefox 11/21/2009

inherit F_CLEAN_UP;

#include <xyj_x.h>
#include <ansi.h>

#define ID				"jiupi"
#define NAME			HIG"��ƨ��"NOR
#define CD				5
#define DURATION		30	//�����۶�ʱ��
#define DEPTH			4	//����room���

int cast(object me)
{
	int skill = me->query_skill("dao", 1);
	mapping req = ([
		"cd"		: ([ ID	: 1 ]),
		"skill1"	: ([ "dao"		: 300 ]),
		"prop"		: ([ "mana"	: skill * 2 ]),
	]);

	BTL->pay(me, req["prop"]);
	BUFF->start_cd(me, ID, NAME, CD);	
	message_vision(YEL"$NͻȻ������������״����Ҽ�æ���ˡ����磡���˰�Ȼ����\n"NOR, me);
	call_out("make_gas", 3, me);
	return 1;
}

void blow(object me, object who)
{
	int odds = BTL->random_cmp(me, who, ([
		"prop"		: ([ "mana" : 4, "daoxing" : 2]),
		"skill"		: ([ "spells" : 4]),
	]));
	if(odds >= 50) {
		object weapon;
		while(weapon = who->query_temp("weapon")) weapon->unequip();
		foreach(object ob in all_inventory(who)) {
			int damage = ob->query("weapon_prop/damage");
			if(damage > 0) BUFF->start_broken(ob, MATH->random_pct(DURATION, 30));
		}
	} else {
		tell_object(who, "��߶���������������\n");
	}
}

void make_gas(object me)
{
	object env = me ? environment(me) : 0;
	mapping rooms = ([]);
	if(!env) return;
	me->command("say �Բ����ô��ʧ���ˡ�");
	message_vision(YEL"$Nת��һ��ƨ�ɣ�", me);

	BTL->find_room(rooms, env, DEPTH);
	foreach(object room in keys(rooms)) {
		tell_room(room, YEL"����������˱��������������������ۡ�\n"NOR);
		foreach(object who in all_inventory(room)) {
			if(!living(who) || who == me ) continue;
			blow(me, who);
		}
	}
	trace("ƨ���ǵķ������:" + sizeof(rooms));
}
