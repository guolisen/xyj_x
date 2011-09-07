
inherit ROOM;

void create()
{
	set ("short", "高间");
	set ("long", @LONG

一群人围着紫檀木大桌而坐，首席座着一位精瘦的签客，正在一本
正经地从镶金黑盒里慢悠悠一根一根往外抽出乾坤签，码在桌面上。

LONG);

	set("exits", ([
		"south"		: __DIR__"room20"
	]));

	setup();
}
