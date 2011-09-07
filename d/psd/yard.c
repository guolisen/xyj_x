// by firefox 02/21/2010

inherit ROOM;

#include "xyj_x.h"
#include <ansi.h>

#define DONKEY			"/d/qujing/wuzhuang/npc/xiaomaolu"
#define MEET_ZIXIA		"meet_zixia"

void meet_zixia(object env, object who);	//��������

void create()
{
	set("short", "��ǰ");
	set("long", @LONG

���Ŀչȣ��������ء���ͷ��بһ�����ʯ��������Լ�ɼ�һ��
ʯ�����Ϸ�ʯ��������׭�֡���˿������

LONG
		);
	set("outdoors", 1);
	set("no_fixup", 1);
	set("exits", ([
		"west"		: "/d/dntg/hgs/shanya",
	]));

	set("objects", ([
		//__DIR__"guard" : 2,
	]));

	setup();
}

void init() 
{
	add_action("do_say", "say");
	
	if(userp(_player) && !_player->query("family")) {
		remove_call_out("meet_zixia");
		call_out("meet_zixia", 3, _this, _player);
	}
}

/*****************************���˵���*****************************/

//�Ұ��ҵĵ�ù��
object find_victim() 
{
	object* arr = ({});
	foreach(object who in all_inventory()) {
		if(userp(who) && who->query_skill("dodge") < 100) arr += ({ who });
	}
	if(sizeof(arr)) return random1(arr);
	return 0;
}

int talk_to_door(object talker, string arg)
{
	object_f outer = base_name(_this);
	object_f inner = __DIR__"gate";
	string in_exit = "exits/east";
	string out_exit = "exits/west";
	object_f next = base_name(environment(talker)) == outer ? inner : outer;

	if(arg != "֥�鿪��" && arg != "֥�����") return 0;
	
	msv(CYN"$N˵����" + arg + "\n\n"NOR, talker);
	tell_room(next, CYN"��Լ��������˵����" + arg + "\n\n"NOR);


	if(arg == "֥�鿪��" && !query(in_exit)) {
		object victim = find_victim();
		set(in_exit, inner);
		inner->set(out_exit, outer);
		tell_room(inner, CYN"����ʯ��Ȼ���£����ų�����\n"NOR);
		tell_room(outer, CYN"����ʯ��Ȼ���£����ų�����\n"NOR);

		if(victim) {
			msv(HIR"$N�����������ҽ��ű�ѹ�����档\n"NOR, victim);
			tell_room(inner, HIR"���洫��һ�������ĲҽС�\n"NOR);
			victim->start_busy(5);
			victim->receive_wound("kee", 50);
			COMBAT_D->report_status(victim, 1);			
		}
	}
	if(arg == "֥�����" && query(in_exit)) {
		delete(in_exit);
		inner->delete(out_exit);
		tell_room(inner, CYN"����ʯ��Ȼ��λ�������ֱ��ڵ÷��겻͸��\n"NOR);
		tell_room(outer, CYN"����ʯ��Ȼ��λ�������ֱ��ڵ÷��겻͸��\n"NOR);
	}
	return 1;
}

int do_say(string arg)
{
	return talk_to_door(this_player(), arg);
}

/*****************************������ϼ*****************************/

#define	SAY			"$N��$n˵����"

string* words = ({
	"$N������$n������֪����Щʲô���⡣",
	SAY"���ɣ�",
	SAY"���֣�",
	SAY"лл��",
	SAY"����ɽ���еĶ������������ҵģ�����Ҳ���������ڣ�\n",
	SAY"�����ҵ�¿��һ��������Ǹ��£�\n"
	HIR"$N��һ��$nЬ�����$n��æ���������Ь�ӣ����ֽŵ׳����߿��롣",
	SAY"�����ҵ����ˣ���������۸��㣬�ͱ��ҵ����֡���˿���ɡ���",
});

void saying(object zixia, object who)
{
	int step;
	if(!same_env(zixia, who) || (zixia->the_id() != "zi xia")) {
		if(who) who->delete_temp(MEET_ZIXIA);
		return;
	}
	step = who->query_temp(MEET_ZIXIA);
	if(step > 6) {
		if(!_this->query("exits/east")) zixia->command("say ֥�鿪��");
		zixia->command("east");
		zixia->command("say ֥�����");
		return;
	}
	msv(CYN + words[step] + NOR"\n", zixia, who);
	who->add_temp(MEET_ZIXIA, 1);

	call_out("saying", 2, zixia, who);
}

void meet_zixia(object env, object who)
{
	object zixia = ACTOR_D->find("xia");
	if(zixia && who && env == environment(who))	{
		if(at_night()) call_out("meet_zixia", 3, env, who);
		else {
			msv("$N��æ�뿪�ˡ�\n", zixia);
			zixia->move(env);
			msv("$Nǣ��Сë¿�����߹�����\n", zixia);

			call_out("saying", 2, zixia, who);
		}
	}
}

