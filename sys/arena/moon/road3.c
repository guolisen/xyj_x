// by firefox 11/21/2009

inherit ROOM;

void create ()
{
  set ("short", "С·");
  set ("long", @LONG

���߷�¥��գ���������������ɽ������֮�䡣������֮������Ϫкѩ
��ʯ�㴩�ƣ���ʯΪ�����������ӡ�
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






