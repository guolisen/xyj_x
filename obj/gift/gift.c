// by firefox 14/06/2009 


#include <xyj_x.h>

inherit ITEM;

void setup()
{
	//set_weight(10);
	if (clonep())
		set_default_object(__FILE__);
	else {
		if(!query("unit")) set("unit", "粒");
		set("no_steal", 1);
		set("no_drop", 1);
		set("no_sell", 1);
	}
	set("is_monitored", 1);
	::setup();
}

void init()
{
	add_action("do_eat", "eat");
	
	if(userp(_env) && !query("owner")) {
		set("owner", getuid(_env));
	}
}

int check(string arg)
{
	if(!id_match_ob(arg, _this)) return 0;
	if(getuid(_player) != query("owner")) return notify_fail("来路不明的东西还是不要往嘴里放。\n");
	return 1;
}

int do_eat(string arg)
{
	mapping rewards = query("rewards");

	if(!check(arg)) return 0;

	if(rewards) {
		foreach(string k, int v in rewards) {
			_player->add(k, v);
		}
	}
	msvx(query("eat_msg"), _player, _this);
  
	destruct(_this);
	return 1;
}

string query_autoload() 
{
	return query("owner"); 
}

void autoload(string param)
{
	set("owner", param);
}
