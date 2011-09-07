// by firefox 11/21/2009

#include <xyj_x.h>

inherit ROOM;

#include <ansi.h>

void create ()
{
	set ("short", HIW"阴阳界"NOR);
	set ("long", @LONG

隐约北方现出一座黑色城楼，光线太暗，看不大清楚。许多亡魂正
哭哭啼啼地列队前进，因为一进鬼门关就无法再回阳间了。周围尺
高的野草随风摇摆，草中发出呼呼的风声。
LONG);

	set("exits", ([
		"south"		: this_object(),
		"north"		: this_object(),
		"west"		: this_object(),
		"east"		: this_object(),])
	);
	
	set("no_fight", 1);
	set("no_magic",1);
	set("alternative_die", 1);
	
	set("objects", ([ __DIR__"panguan" : 1 ]));
	
	setup();
}

void init()
{
	if(!_player->is_busy()) _player->start_busy(2);
}

void alternative_die(object who)
{
	HP->full(who, 1);
}

int clean_up()
{
	return 0;
}
