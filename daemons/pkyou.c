

inherit NPC;

void create()
{
	object ob;

	set_name("���С��", ({"pkyou", }));
	set("gender", "����" );
	set("age", 37);

	set("long","һλ�ಲ׳�������ϴ�Ƭ���࣬���������Ұ׻����м����֣������塣\n");

	set("chat_msg", ({
		CYN"���С��˵���������壡�����壡��ɫ�μ��ˣ�ֻҪ������ʮ�����ӣ�\n",
		CYN"���С��˵����������ԥʲô���Ͽ��ó�Ǯ��Ԥ���ɣ�\n",
	}));

	set("chat_chance", 10);



	setup();

	ob = carry_object("/obj/cloth");
	ob->set_name("��̿�", ({ "duan ku", "ku" }));
	ob->wear();

	carry_object("/d/city/obj/necklace")->wear();

}

void init()
{

}
