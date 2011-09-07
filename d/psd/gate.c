// by firefox 02/21/2010

inherit ROOM;


void create()
{
	set("short", "洞口");
	set("long", @LONG

一缕缕光亮从西面射进山洞，看来这里就是山洞的出口，一块断
龙石横在门口。

LONG
		);
	set("no_fixup", 1);
	set("exits", ([
		"east"		: __DIR__"cave1",
	]));

	setup();
}

void init() 
{
	add_action("do_say", "say");

}

int do_say(string arg)
{
	object outer = load_object(__DIR__"yard");
	return outer->talk_to_door(this_player(), arg);
}

/*

『盘丝洞』　　　　　　

                仙霞居
                  ｜
           溶洞──碧池──溶洞──秘洞
                  ｜
　　　    白骨洞 洞内 桃花阁
　   　　　 ｜    ｜    ｜ 
     石室──洞内──洞中──洞内
                  ｜
                 洞内
                  ｜
     洞前──洞口──洞内


*/
