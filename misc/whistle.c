// by firefox 11/21/2009

inherit ITEM;
inherit "/d/sldh2/feature/util";

#include <ansi.h>

string _file;
object _object;
mapping _prop;


void create()
{
	set_name("����", ({ "whistle" }));
	set("long", "һ�����ӣ��ܴ�(chui)�졣");
	set("unit", "ֻ");
	set("no_chucun", 1);
	setup();
}

int ctor(string file, mapping prop)
{
	_file = file;
	_prop = prop;
	//set("long", query("long") + "�����ٻ�" + prop["name"] + NOR"��");
}

void init()
{
	add_action("do_chui", "chui");	
}

int do_chui(string arg)
{
	object who = this_player();

	if(!_object) {
		_object = new(_file);
		foreach(string k, mixed v in _prop) {
			_object->set(k, v);
		}
	}
	if(!same_env(who, _object)) {
		object env = environment(_object);
		if(env) message_vision(_prop["leave"] + "\n\n", _object);
		_object->move(environment(who));
		message_vision("$N���ᴵ�������ӣ�" + _prop["come"] + "\n\n", who, _object);
	} else {
		printf("���Ҵ��ˣ�%s��������\n", _object->query("name"));
	}
	return 1;
}

//�������������������Ӷ���
int remove()
{
	if(_object) {
		object env = environment(_object);
		if(env) message_vision(_prop["leave"] + "\n\n", _object);
		destruct(_object);
	}
	return 0;
}
