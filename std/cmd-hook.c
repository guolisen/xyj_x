// by firefox 11/21/2009

inherit ITEM;
inherit F_MOVE_TO;

#include <xyj_x.h>

mixed _listener;
mixed _verbs;

void create()
{
	set_name("�����", ({"hook"}));

	set("long", "����ӣ����������û����������������������ˡ�\n");
	set("env/invisibility", 1);
	set("no_put", 1);
	set("no_get", 1);
	set("no_give", 1);
	set("no_drop", 1);
	
	seteuid(getuid());
	setup();
}

void init()
{
	if(_listener) {
		if(_verbs) add_action("block", _verbs);
		else add_action("block", "", 1);
	}
}

int block(string arg)
{
	if(_listener) return _listener->do_verb(arg);
	return 0;
}

//��������ļ�����
varargs void set_listener(mixed listener, mixed verbs)
{
	_listener = listener;
	_verbs = verbs;
}
