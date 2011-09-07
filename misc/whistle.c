// by firefox 11/21/2009

inherit ITEM;
inherit "/d/sldh2/feature/util";

#include <ansi.h>

string _file;
object _object;
mapping _prop;


void create()
{
	set_name("哨子", ({ "whistle" }));
	set("long", "一个哨子，能吹(chui)响。");
	set("unit", "只");
	set("no_chucun", 1);
	setup();
}

int ctor(string file, mapping prop)
{
	_file = file;
	_prop = prop;
	//set("long", query("long") + "用来召唤" + prop["name"] + NOR"。");
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
		message_vision("$N轻轻吹响了哨子，" + _prop["come"] + "\n\n", who, _object);
	} else {
		printf("别乱吹了，%s不是在吗？\n", _object->query("name"));
	}
	return 1;
}

//对象析构，销毁所有子对象
int remove()
{
	if(_object) {
		object env = environment(_object);
		if(env) message_vision(_prop["leave"] + "\n\n", _object);
		destruct(_object);
	}
	return 0;
}
