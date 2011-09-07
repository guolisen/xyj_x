// by firefox 11/21/2009

inherit ROOM;

void create()
{
	set("short", "海底莽林");
	set("long", @LONG

这里水色变的浑浊起来，周围已看不大清楚了。偶有暗流袭来，卷
起阵阵的泥流。四处长着些高高的海草，密密麻麻把头上遮的一丝
光芒也没有了。

LONG);

	set("exits", ([
		"east" : __DIR__"maze1",
		"north" : __DIR__"maze2",
		"south" : __DIR__"maze4",
		"west" : __DIR__"maze5",
	]));

	set("water", 1);

	setup();
}

