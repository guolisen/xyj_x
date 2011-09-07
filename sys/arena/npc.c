// by firefox 11/21/2009

inherit NPC;

#include <xyj_x.h>

void create()
{
	set_name("��ɽ��", ({"zsd"}));
	set("long", @LONG

����վ�Ĵ����ߣ����Դ˼����������εľ޴��ס�

LONG);

	set("title", HIY"��������ܹ�"NOR);
	set("gender", "����");
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

//�г�����
int do_list(string arg)
{
	ARENA->list();
}

//��������
int do_join(string arg)
{
	if(!arg) return notify_fail("�����ʽ:join id1 id2 id3\n");
	
	{
		string* arr = str_split(arg, ' ');
		string gid = "";

		ARENA->join(gid, arr);
	}
}

//����ѡ�ֳ���˳��
int set_order(string arg)
{
	if(!arg) return notify_fail("�����ʽ:order id1 id2 id3\n");
	
	{
		string* arr = str_split(arg, ' ');
		string gid = "";

		ARENA->set_order(gid, arr);
	}

}

//�ۿ�ĳ�˵ı���
int do_watch(string arg)
{
}