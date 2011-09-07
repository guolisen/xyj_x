//Cracked by Roath
//changan city

inherit ROOM;

void create ()
{
        set ("short", "十字街头");
        set ("long", @LONG

这里便是长安城的中心，四条大街交汇于此。一座巍峨高大的钟楼耸
立于前，很是有些气势。每到清晨，响亮的钟声便会伴着淡淡雾气传
向长安城的大街小巷。路口车水马龙，来往人潮不断。
LONG);

        //set("item_desc", ([" *** " : " *** ", ]));

        set("exits", 
        ([ //sizeof() == 4
		"south" : __DIR__"zhuque-s1",
        "down": __DIR__"recycle",
                "west" : __DIR__"baihu-w1",
                "east" : __DIR__"qinglong-e1",
                "north" : __DIR__"xuanwu-n0",
//		"northwest" : "/d/jjf/qilin",
//		"southeast" : "/d/jjf/zuixing",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/libai" : 1,
                __DIR__"obj/treasure_box" : 1,
		"/d/qujing/wuzhuang/npc/zhangguolao": 1,
		"/d/xyj_x/wiz/mp": 5,
		"/d/xyj_x/wiz/armor": 5,
        ]));

        set("outdoors", "changan");
	set("no_clean_up", 0);
        setup();
	replace_program(ROOM);
}

