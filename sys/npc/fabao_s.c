// by firefox 04/20/2010

inherit __DIR__"employer";

#define S			""

void create()
{
	set_name("法宝贩子", ({ "fanzi" }));

	set("long", "提供法宝，list查看。\n");
	
	setup();
}

void init()
{
	add_action("do_list", "list");
	add_action("do_fetch", "fetch");
}

//列出全部
int do_list(string arg)
{
	foreach(mapping m in S->query()) {
		//
	}
}

//取用
int do_fetch(string arg)
{


}


