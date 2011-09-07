// by firefox 11/21/2009

inherit ITEM;

#include <xyj_x.h>
#include <ansi.h>

inherit F_MOVE_TO;

#define MY_HOST			"yhdf_my_host"
#define MY_SERVANT		"yhdf_my_servant"
#define MY_COMMAND		"yhdf_my_command"
#define ID				"yihun"

string* commands = ({ "kill", "perform", "cast", "exert", "say", "jump", "climb", "dive" });

void create()
{
	set_name("魂", ({ "soul" }));

	set("long", "可以控制一个人的灵魂。");
	set("env/invisibility", 1);

	set("no_get", 1);
	set("no_put", 1);
	set("no_give", 1);
	set("no_drop", 1);
	setup();
}


void init()
{
	object who = this_player();
	
	if(who->query_temp(MY_SERVANT))	add_action("do_say", "say");
	if(who->query_temp(MY_HOST)) add_action("exec_cmd", "", 1);
	
}

int exec_cmd(string arg)
{
	object who = this_player();
	if(who->query_temp(MY_COMMAND))	return 0;
	else write("你身不由己。\n");
	return 1;
}

int do_say(string arg)
{
	object who = this_player();
	object servant = who->query_temp(MY_SERVANT);
	string verb;
	string arg1;

	if(servant && arg && sscanf(arg, "%s %s", verb, arg1) == 2) 
	{
		mapping buff = BUFF->find(servant, ID);
		if(!buff || !verb || member_array(verb, commands) == -1) return 0;
		buff["_cmds"] += ({ arg });
	}
	return 0;
}
