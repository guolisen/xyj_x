
inherit ROOM;

void create ()
{
	set ("short", "三楼");
	set ("long", @LONG

乐坊楼上显得格外热闹，走廊里人来人往，几间屋子里人声嘈杂，牌
签骨骰钱币落盘的声音不绝。看样子，客人们赌得正欢呢。
LONG);

	set("exits", ([
		"east"		: __DIR__"room31",
		"south"		: __DIR__"room32",
		"west"		: __DIR__"room33",
		"north"		: __DIR__"room34",
		"down"		: __DIR__"room20",
	]));


	setup();

}

