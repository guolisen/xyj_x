
inherit NPC;

#include <imud-efun.h>

object_f _localizer = __DIR__"localizer";

void create()
{
	mapping m = _localizer->get("cashier");

	set_name(m["name"], ({ m["id"] }));
	set("title", m["title"]);
	set("gender", m["gender"]);

	setup();
	
	carry_object("/obj/cloth");

}

void init()
{
	object who = this_player();

	if(userp(who)) {
		add_action ("do_buy", "buy");
		add_action ("do_sell", "sell");
	}
	remove_call_out("greeting");
	call_out("greeting", 1, who);
}

void greeting(object who)
{
	if(!userp(who)) {
		foreach(string k, string v in _localizer->get("exits")) {
			who->move(v);
			return;
		}
	}
	if(!who || !visible(who) || environment(who) != environment() ) return;
	command("say 这位客官，是否需要买(buy)或退(sell)筹码？");
}


int do_buy(string arg)
{

}

int do_sell(string arg)
{

}