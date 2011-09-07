
#include <ansi.h>
inherit ROOM;

void create ()
{
	set ("short", "�ƺ���ͷ");
	set ("long", @LONG

�ƺ�ãã��������ӿ��״��󺣣����ʱ�𣬿��ϰ��硣
ʱ��Ũ��ӿ�����������У�����Ī�棻ʱ���ƿ���ɢ������
��⣬һ�����꣬��������Լ�������������ӣ�����һ��
�������ò�׳�ۣ���ϸ�����������Ѿ�������ľ�ͷ��
LONG);

	set("exits", ([ /* sizeof() == 4 */
	]));
	set("outdoors", 2);

	setup();
}

void init()
{
	add_action("do_sa",  "sa");
	add_action("do_ba",  "ba");
	add_action("do_zhan",  "zhan");
	add_action("do_xie",  ({"xie", "write"}));
	add_action("do_back",  ({"huiqu", "flyback", "jump"}));	//������jump������jump������
}

int do_sa (string arg)
{
	object who = this_player();

	if( !arg || (arg != "niao" && arg != "��") ) 
		return notify_fail("��Ҫ��ʲô��\n");			
	if( who->query_temp("dadu/saniao") ) 
		return notify_fail("�������˻�����������ô������\n");	

	message_vision("$N�������������������ܵ���һ�����Ӹ�������һ����\n",who);	
	who->set_temp("dadu/saniao", 1);
	return 1;
}

int do_ba (string arg)
{
	object pen = new(__DIR__"pen");
	object who = this_player();

	if( !arg || arg != "haomao" ) 
		return notify_fail("��Ҫ��ʲô��\n");			

	if( who->query_temp("dadu/ba") ) 
		return notify_fail("������Լ����ϵ�ë�ι���\n");	

	if(pen && pen->move(who)) {
		message_vision("$N�����ϰ���һ����ë�������һֻ˫���ʡ�\n", who);
		who->set_temp("dadu/ba",1);
	}
	return 1;
}

int do_zhan (string arg)
{
	object who = this_player();

	if( !who->query_temp("dadu/ba") || !arg || arg != "bi")
		return notify_fail("��Ҫպʲô��\n");

	if( who->query_temp("dadu/zhan") ) 
		return notify_fail("˫�����Ѿ�����д���ˡ�\n");	

	message_vision("$N�����е�˫���ʷŵ�����պ��պ��\n",who);	
	who->set_temp("dadu/zhan",1);
	return 1;
}

int do_xie (string arg)
{
	object who = this_player();

	if( !who->query_temp("dadu/ba") )
		return notify_fail("����ʲôд�֣�\n");	

	if( !who->query_temp("dadu/zhan") )
		return notify_fail("��ɬ�ı�ͷд����������\n");	

	if( !arg || arg != "�����ʥ����һ��" ) 
		return notify_fail("��֪��дʲôҲ������д�һ���\n");

	if( who->query_temp("dadu/xie") ) 
		return notify_fail("�������Ѿ������ˡ�\n");	

	message_vision("$Nһ�������������м�������дһ�д����ƣ��������ʥ����һ�Ρ���\n",who);	

	set ("long", @LONG

����������ŤŤ��д�š������ʥ����һ�Ρ���
LONG);
	who->set_temp("dadu/xie",1);
	return 1;
}

int do_back (string arg)
{
	object who = this_player();

	if( !who->query_temp("dadu/saniao"))
		return notify_fail("��о�С�����ǣ�Ҫ�ﲻס�ˡ�\n");
	
	if( !who->query_temp("dadu/xie"))
		return notify_fail("��ͻȻ�뵽��������Щ�Ǻţ����������˵����\n");

	message_vision(CYN"$N����̤���ƶˣ��ڿն�ȥ��\n"NOR, who);	

	//who->set_temp("dadu","done");
	
	who->move(__DIR__"lingxiao");

	message_vision(CYN"$N������ͷ��������������ǰ��\n"NOR, who);
	return 1;
}
