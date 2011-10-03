
inherit ROOM;


void create()
{
	set("short", "×ßÀÈ");
	set("exits", ([
		"east"		: __DIR__"stand0",
		"south"		: __DIR__"stand1",
		"west"		: __DIR__"stand2",
		"north"		: __DIR__"stand3",])
	);

	setup();
}
