// by firefox 02/21/2010

inherit ROOM;

void create()
{
	set ("short", "经阁");
	set ("long", @LONG
		
这里是一间小室，为弟子们研读经书提供了一个安静个地方。墙
上挂着一个条幅，写着『潜思入定』四个的大字。

LONG);

	set("exits", ([
		"west": __DIR__"yard" 
	]));

	setup();

}
