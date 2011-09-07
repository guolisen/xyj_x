
#include <ansi.h>

//inherit ROOM;
inherit "/d/city/misc/scoresheet.c";

#include <banned.h>
void finish(int);
void fullup(object);
void pre_status(object);


void setup()
{
	set("broadcast", 1);
	set("alternative_die", 1);

	::setup();
}


void init()
{
	add_action("do_block", ({"quit", "accept", "fly", "surrender"}));
	add_action("do_cast",({"cast"}));
}

int do_block(string arg)
{
	return notify_ok("你不能在这里用这条命令。\n");
}

int do_cast(string arg) 
{
	string* casts=({"escape", "chuqiao", "tudun", "shuidun"});

    if(!arg) return 0;
    while(sscanf(arg, "%s %*s", arg) == 2);
    trace(arg);
    if(member_array(arg,banned_cast)==-1) return 0;
    return notify_ok("请勿使用" + arg + ",多谢合作。\n");
}

void alternative_die(object who)
{
	object p1=query("player1");
	object p2=query("player2");
	int winner=0;

	if (!userp(who)) {
		message_vision("$N死了。\n",who);
		destruct(who);
		return;
	}

	who->delete_temp("last_fainted_from");

	if (!p1 || !p2) {
		message_vision(HIW"BEEP!BUG!\n"NOR,who);
		fullup(who);
		who->move(__DIR__"kantai");
		return;
	}
	if (p1==who) winner=2;
	else winner=1;
	finish(winner);
}

void finish(int r) {
	object winner,loser;
	remove_call_out("finish");

	set("no_fight",1);
	if (r==1) {
		winner=query("player1");
		loser=query("player2");
	} else {
		winner=query("player2");
		loser=query("player1");
	}

	fullup(loser);
	fullup(winner);
	winner->remove_killer(loser);
	loser->remove_killer(winner);
	winner->remove_enemy(loser);
	loser->remove_enemy(winner);

	if (!r) {     
		message_vision(HIG"$N$n大战三百回合，不分胜败，各自离场，改日再战！\n"NOR,winner,loser);
		loser->move(__DIR__"kantai");
	} else {
		message_vision(HIG"$N把$n打翻在地，飞起一脚，将$n踢下了擂台。\n"NOR,winner,loser);
		loser->move(__DIR__"kantai");
		message_vision(HIG"$N在观众的欢呼声中，高高兴兴地下场休息了。\n"NOR,winner);
		//     update_score(winner,loser);
	} 
	winner->move(__DIR__"kantai");
	delete("player1");
	delete("player2");
	delete("busy");
}


void start() {
	object p1=query("player1");
	object p2=query("player2");
	if ((!p1) || (!p2)) return;
	message_vision(HIW"$N和$n比武开始！限时五分钟！\n"NOR,p1,p2);  
	delete("no_fight");
	p1->kill_ob(p2);
	p2->kill_ob(p1);
	call_out("finish",300,0);
}


void broadcast(string msg) 
{
	object room = load_object(__DIR__"stand");
	string prefix = HIY"【擂台】"NOR;
	string s1 = str, s2 = "", s3;
	int i;

	reset_eval_cost();

	// remove extra trailing NOR. mon 7/13/99
	s1=replace_string(s1,"\n"NOR,"\n");

	while (strsrch(s1,"\n\n") != -1)
		s1 = replace_string(s1,"\n\n","\n");

	while (sizeof(s1)>1 && s1[sizeof(s1)-1]=='\n')
	{
		s1 = s1[0..(sizeof(s1)-2)];
		s2 = "\n";
	}
	if (sizeof(s1) <= 1)
		return;

	s1 = replace_string(s1,"\n","\n"+prefix);

	tell_room (room, prefix+s1+ NOR+"\n");
}
