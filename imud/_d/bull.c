// by firefox 04/16/2011

inherit ROOM;

#include <imud.h>
#include <ansi.h>

void create()
{
	set ("short", "��������");
	set ("long", @LONG

�����������᱾�������������̨��

LONG);

	set("outdoors", "/u/hkgroup");
	set("exits", ([
		"frontyard" : __DIR__"yard3",
	]));
	set("no_clean_up", 1);
	setup();
}

void init()
{
	if(userp(this_player())) {
		add_action("do_enter", "enter");
	}
}

int do_enter(string arg)
{
	object who = this_player();
	
	message_vision(CYN"$N����ǰ���޾�����գ�������û����...\n\n"NOR, who);
	who->move(iFCS_MAP_DIR "r0");
	return 1;
}

