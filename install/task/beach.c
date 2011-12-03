
#include <xyj_x.h>
#include <ansi.h>

inherit ROOM;

string dest = __DIR__"beach-stone";

void flood();
void _flood(object);

void create ()
{
	set ("short", "������̲");
	set ("long", @LONG

ҹ��Ĵ󺣣���ˮ��ī����ƽ�˾����¹��ں����ϻ���һ�����⣬������
�ĺ���������һ˿������Ȼ�����������ŵı����£���ˮ�������ӿ��
ˮ��¡¡���ƺ�Ҫ��һ���������ɡ������±��ϵ������Ƿ绯����ʯ��

LONG);

	set("outdoors", 1);
	set("exits", ([
		"west" : __DIR__"eastseashore",
		"east" : this_object(),
	]));

	setup();
	call_out("flood", 21 + random(20));
}

void flood()
{
	call_out("flood", 61 + random(60));

	tell_room(this_object(), "�ǳ��ˣ���ˮ������������ľ޺����������ڰ�����������\n");
	foreach(object who in all_inventory())
		if(userp(who)) _flood(who);
}

void _flood(object me)
{
	object corpse;

	if(!me->query("life/live_forever")) {
		message_vision("$N����ˮ�����ˡ�\n\n", me);
		me->set_temp("death_msg","�������������ˡ�\n");

		me->die();
		me->delete_temp("death_msg");
		corpse = present("corpse", this_object());
		if(corpse && corpse->move(dest))
			tell_room(environment(corpse),"��ˮ��"+corpse->name()+"���ϰ�����\n");
		return;
	}
	if(random(me->query_kar()) > 6) {
		message_vision("$Nһ����������һԾ�����ڽ�ʯ�ϣ���ˮ��Х�Ŵ�$N�������������գ�\n\n", me);
		return;
	}
	message_vision("$N����ˮ�����ˡ�\n\n", me);

	me->unconcious();
	if(me->move(dest))
		tell_room(environment(me), "��ˮ��"+me->name() + "���ϰ�����\n");
}

void init()
{
	add_action("do_fill", "fill");
}

int do_fill(string arg) 
{
	object me = this_player();
	int phase = NATURE_D->query_current_day_phase();
	int pot = me->query_skill("spells") / 10;

	if(!arg && arg!="hai" && arg!="sea") return notify_fail("��Ҫ��ʲô��\n");
	if(me->is_fighting() || me->is_busy()) return notify_fail("����æ���ء�\n");	
	if(phase < 6) return notify_fail("��������̫���ˣ����������ɡ���\n");

	message_vision("$N�Ӱ��߰���һ��ʯͷͶ�뺣�У�ʯ��Ѹ�ٳ���ˮ�У���ˮ����û�����㡣\n",me);
	write("���۵����ᱳʹ�����ֱ۶�̧��������\n\n");
	//������
	if(TASK_EXC->do_reward(me, "����", "�", ([ PEXP : pot ]) ))
		me->add("potential", pot);
	me->start_busy(8/4);
	return 1;
}

