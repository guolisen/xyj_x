// by firefox 04/20/2010

inherit __DIR__"employer";

#define S			""

void create()
{
	set_name("��������", ({ "fanzi" }));

	set("long", "�ṩ������list�鿴��\n");
	
	setup();
}

void init()
{
	add_action("do_list", "list");
	add_action("do_fetch", "fetch");
}

//�г�ȫ��
int do_list(string arg)
{
	foreach(mapping m in S->query()) {
		//
	}
}

//ȡ��
int do_fetch(string arg)
{


}


