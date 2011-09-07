

inherit NPC;

void create()
{
	object ob;

	set_name("数据管理员", ({ "npc", }));

	set("gender", "男性" );

	set("long","

负责处理用户数据的NPC，也用下列指令：

    literate 等级                设定literate的新等级（只可用一次）

");


	setup();
	
	carry_object("/obj/cloth");

}

void init()
{
	add_action ("do_literate", "literate");

}


int do_literate(string arg)
{
	return __DIR__"cvt"->set_literate(to_int(arg));
}