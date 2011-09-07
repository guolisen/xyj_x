

inherit NPC;

void create()
{
	object ob;

	set_name("麦克小狼", ({"pkyou", }));
	set("gender", "男性" );
	set("age", 37);

	set("long","一位赤膊壮汉，身上大片刺青，左青龙，右白虎，中间仨字：二百五。\n");

	set("chat_msg", ({
		CYN"麦克小狼说道：二百五！二百五！角色俏佳人，只要二百五十两银子！\n",
		CYN"麦克小狼说道：您还犹豫什么，赶快拿出钱袋预定吧！\n",
	}));

	set("chat_chance", 10);



	setup();

	ob = carry_object("/obj/cloth");
	ob->set_name("大短裤", ({ "duan ku", "ku" }));
	ob->wear();

	carry_object("/d/city/obj/necklace")->wear();

}

void init()
{

}
