// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit ITEM;
inherit F_MOVE_TO;




void create()
{
	set_name("���ʯ",({"banjiao shi"}));

	set("env/invisibility", 1);
	set("no_get", 1);
	set("no_give", 1);
	set("no_drop", 1);
	
	seteuid(getuid());
	setup();
}

int success();

void init()
{
	add_action("block", ({"exert", "cast", "perform"}));
	add_action("do_go", ({"go"}));
}

int block(string arg)
{
	if(success()) return 0;
	write("���������Ŷݼ��������޴롣\n");
	return 1;
}

int do_go(string arg)
{
	object me = this_player();
	if(success()) return 0;
	message_vision(HIC"$N��ֻûͷ��Ӭ��ײ��ײȥ���ɾ����Ҳ��ŷ���\n"NOR, me);
	return 1;
}

//�Ƚϵ���ʵ�����ж������ܷ�ɹ�
int success()
{
	object me = this_player();
	object host = query("host");
	mapping cmp_parm = ([
		"prop"		: ([ "mana" : 3, "daoxing" : 1]),
		"skill"		: ([ "spells" : 3]),
	]);
	int odds;
	if(me->is_busy()) return 1;
	if(!objectp(host) || !host->is_fighting(this_player())) return 1;	
	//����ɹ���
	odds = BTL->cmp_parm(me, host, cmp_parm);
	if(me->query_skill_mapped("spells") == "taiyi") odds *= 2;
	
	if(random(odds) >= 50) return 1;

	me->start_busy(2);
	return 0;
}
