// by firefox 11/21/2009

inherit ROOM;

void create ()
{
  set ("short", "小路");
  set ("long", @LONG

两边飞楼插空，雕甍绣槛，皆隐於山坳树杪之间。俯而视之，则青溪泻雪
，石磴穿云，白石为栏，环抱池沼。
LONG);

  set("outdoors", 1);
  set("exits", ([ /* sizeof() == 4 */
  "east" : __DIR__"snow.c",
  "north" : __DIR__"road3.c",
  "south" : __DIR__"road3.c",
  "west" : __DIR__"rain.c",
]));

  set("objects",(["/d/obj/flower/yehua.c":1,]));
  setup();
}






