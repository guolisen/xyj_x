//Cracked by Roath

#include <xyj_x.h>
#include <ansi.h>

inherit ROOM;

string dest = __DIR__"eastseashore";

void create ()
{
	set ("short", "东海乱礁");
	set ("long", "

怪石嶙峋，惊涛拍岸，水声如雷，地动山摇，着实让人胆寒。向北望去是
若隐若现的海岸线。

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
		tell_room(this_object(), "涨潮了，海水发出震耳欲聋的巨吼声，万马奔腾般扑来！\n");
		message_vision("$N被潮水冲走了。\n\n", me);

		if(userp(me)) me->unconcious();
		if(me && me->move(dest))
			tell_room(environment(me),"潮水将"+me->name()+"冲上岸来。\n");
	}
}
