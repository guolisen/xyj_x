

inherit NPC;

void create()
{
	object ob;

	set_name("���ݹ���Ա", ({ "npc", }));

	set("gender", "����" );

	set("long","

�������û����ݵ�NPC��Ҳ������ָ�

    literate �ȼ�                �趨literate���µȼ���ֻ����һ�Σ�

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