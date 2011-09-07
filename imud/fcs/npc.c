// by firefox 04/16/2011

inherit NPC;

void create()
{
	set_name("座山雕", ({"zsd"}) );
	set("gender", "男性" );
	set("title", "赌场总管");
	set("age", 40);
	set("per", 1);
	set("long","

北京站的创建者，谨以此纪念他对西游的巨大贡献。

");
	setup();
	carry_object("/d/obj/cloth/choupao")->wear();
}


void init()
{
	if(userp(this_player())) {

		add_action("do_buy", "buy");
		add_action("do_sell", "sell");

	}
}