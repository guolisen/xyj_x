//Cracked by Roath

#include <xyj_x.h>
#include <ansi.h>

inherit ROOM;

string dest = __DIR__"eastseashore";

void create ()
{
	set ("short", "�����ҽ�");
	set ("long", "

��ʯ��ᾣ������İ���ˮ�����ף��ض�ɽҡ����ʵ���˵���������ȥ��
�������ֵĺ����ߡ�

");

	set("outdoors", 1);
	set("exits", ([
	]));

	setup();
}

void init()
{
	call_out("flood", 0, this_player());
}

void flood(object me)
{
	if(me && !me->query("life/live_forever")) {
		tell_room(this_object(), "�ǳ��ˣ���ˮ������������ľ޺����������ڰ�������\n");
		message_vision("$N����ˮ�����ˡ�\n\n", me);

		if(userp(me)) me->unconcious();
		if(me && me->move(dest))
			tell_room(environment(me),"��ˮ��"+me->name()+"���ϰ�����\n");
	}
}
