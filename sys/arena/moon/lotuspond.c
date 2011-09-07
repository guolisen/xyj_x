// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit ROOM;

void create ()
{
	set ("short", "湖边");
	set ("long", @LONG

湖面绿波上飘着一叶小舟，一个绿衫少女手执双桨，缓缓划水而来，口中
唱着小曲，听那曲子是：“采莲人语隔秋烟，波静如横练。入手风光莫流
转，共留连，画船一笑春风面。江山信美，终非吾土，问何日是归年？”
歌声娇柔无邪，更助秋意。

LONG);

	set("item_desc", ([
		"lotus" : "荷花已经谢了，莲梗上孤零零的吊着莲蓬。\n",
	]));
	set("exits", ([
		"north" : __DIR__"rain",
	]));

	setup();
}

void init()
{
  add_action("do_dive", "dive");
}

int do_dive(string arg)
{
	if(cannot_move(_player)) return notify_fail("你现在动不了。\n");

	message_vision(CYN"$N纵身一跃，扑通一声跳进了莲花池．\n"NOR, _player);
	_player->move(__DIR__"hudi");
	return 1;
}
