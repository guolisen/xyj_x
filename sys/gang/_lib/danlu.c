// by firefox 02/21/2010

inherit ITEM;

void create()
{
	set_name("��¯", ({ "dan lu", "lu" }) );
	//set("short", "��¯");
	set_weight(300000);
	set_max_encumbrance(300000);

	set("unit", "��");
	set("long", @LONG

����һ��һ�˶�ߵ���ɫ��¯�����������ŷ���׵磬���а��Ը�
��ͼ����

LONG);
}

int is_container()
{
	return 1;
}

void init ()
{
	add_action ("do_enter", "jump");
	add_action ("do_enter", "plunge");
}

int do_enter (string arg)
{
	object who = this_player();
	if (arg != "tong danlu" && arg != "danlu")
		return 0;

	message_vision ("$NǱ������¯��һԾ������������$N����һ�������ˡ�\n",who);
	who->move(this_object());
	who->start_busy(1);
	return 1;
}

void smoking (object me)
{
	object where = environment (me);
	tell_room (where,"ͭ��¯ð�����������̡�\n");
}
