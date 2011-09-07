// by firefox 02/21/2010

inherit ROOM;

void create()
{
	set ("short", "静室");
	set ("long", @LONG

这里是一间布置得相当雅致的厢房，从窗子可以看到院中的海棠。
左边一个用来打坐练功木榻。

LONG);
	set("exits", ([
		"east": __DIR__"yard"
	]));

	setup();

}
