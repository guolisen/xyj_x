// by firefox 04/16/2011

inherit NPC;

void create()
{
	set_name("��ɽ��", ({"zsd"}) );
	set("gender", "����" );
	set("title", "�ĳ��ܹ�");
	set("age", 40);
	set("per", 1);
	set("long","

����վ�Ĵ����ߣ����Դ˼����������εľ޴��ס�

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