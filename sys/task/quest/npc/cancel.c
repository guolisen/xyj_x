// by firefox 04/10/2010

#include <xyj_x.h>

inherit ITEM;

#define PROP		TASK_PROP"/quest/cancel"

void create()
{
	set_name("����ȡ��", ({ "cancel" }) );

	set("env/invisibility", 1);
	set("no_get", 1);

	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("value", 1);
	}
}

void init ()
{
	add_action ("do_sth", ({"qing", "ning", "jing"}));

	if(file_id(_env) == "sanxin" && _player->query_temp(PROP)) {
		_player->set_temp(PROP, 0);
		call_out("feeling", 1, _player);
	}
}

int do_sth(string arg)
{
	_player->set_temp(PROP, 1);
	msv("$N������³�һ����������վ��������\n", _player);

	TASK->child("quest")->cancel_all(_player);
	return 1;
}

void feeling(object who)
{
	msv("$N�߳����Ĺ�������һ��������ʱ�ľ������羵��\n", who);
}