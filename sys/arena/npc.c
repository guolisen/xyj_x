// by firefox 11/21/2009

inherit NPC;

#include <xyj_x.h>

void create()
{
	set_name("座山雕", ({"zsd"}));
	set("long", @LONG

北京站的创建者，谨以此纪念他对西游的巨大贡献。

LONG);

	set("title", HIY"帮会联赛总管"NOR);
	set("gender", "男性");
	set("age", 42);
	set("per", 10);

	setup();
}

void init()
{	
	add_action("do_list", "list");
	add_action("do_watch", "watch");
	 
	if() {
		add_action("do_join", "join");
		add_action("set_order", "order");
	}
		
	if(wizardp(this_player())) {
		add_action("do_start", "start");
		add_action("do_start", "stop");
		add_action("do_update", "update");
	}
}

//列出赛程
int do_list(string arg)
{
	ARENA->list();
}

//报名参与
int do_join(string arg)
{
	if(!arg) return notify_fail("命令格式:join id1 id2 id3\n");
	
	{
		string* arr = str_split(arg, ' ');
		string gid = "";

		ARENA->join(gid, arr);
	}
}

//设置选手出场顺序
int set_order(string arg)
{
	if(!arg) return notify_fail("命令格式:order id1 id2 id3\n");
	
	{
		string* arr = str_split(arg, ' ');
		string gid = "";

		ARENA->set_order(gid, arr);
	}

}

//观看某人的比赛
int do_watch(string arg)
{
}