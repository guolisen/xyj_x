// by firefox 02/04/2010

inherit ITEM;

#include <ansi.h>

#define EXP		10000

string _g;
mapping _m;

void create()
{
	set_name("Ö²Îï", ({"plant"}));
	set("env/invisibility",1);
	set("no_get",1);
	set("no_give",1);

	setup();
}

void init()
{
	object env = environment();

	if((_g = env->query_guild())
		&& (_m = G->query("plant")))
	{
		if(1) {
			set_name(_m["name"], _m["ids"]);
			set("long", _m["long"]);
			set("env/invisibility", 0);
		}
		add_action("do_spread", _m["spread_verb"]);	
		add_action("do_work", _m["work_verb"]);
		add_action("do_gather", _m["gather_verb"]);
		add_action("do_kill", _m["kill_verb"]);
	}
	
}

int do_spread(string arg)
{
	object who = this_player();

	message_vision(HIC + _m["gather_msg"] + NOR, who);
	who->start_busy(3);
	return 1;
}



int do_work(string arg)
{
	object who = this_player();
	
	_m["exp"] += _g->add_score(who, EXP);
	
	who->add(_m["cost"], -EXP);

	message_vision(HIC + _m["work_msg"] + NOR, who);
	
	who->start_busy(3);
	return 1;
}

int do_gather(string arg)
{
	object who = this_player();

	if(_m["goods_amount"]) {
		_m["goods_amount"] -= 1;
		message_vision(HIC + _m["gather_msg1"] + NOR, who);
	} else {
		message_vision(HIC + _m["gather_msg0"] + NOR, who);
	}
	who->start_busy(3);
	return 1;
}

int do_kill(string arg)
{
	object who = this_player();

	message_vision(HIC + _m["kill_msg0"] + NOR, who);
	message_vision(HIC + _m["kill_msg1"] + NOR, who);
	who->start_busy(3);
	return 1;
}