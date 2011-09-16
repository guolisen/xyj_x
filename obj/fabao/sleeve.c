//Cracked by Roath
// magic sleeve for holding stuffs.
// by mon. 1/11/98 

#include <ansi.h>

inherit ITEM;

int do_quit();

int is_sleeve() {return 1;}

void create()
{
	set_name("衣袖中",({"in sleeve","sleeve"}));     
	set("short","衣袖中");
	set("long", "\n这里漆黑一片．．．\n\n");

	set_max_encumbrance(300000);
	set_weight(100);
	seteuid(getuid());
	
	set("no_fight", 1);
	set("no_magic", 1);
	set("alternative_die", 1);
	set("is_fabao", 1);

	setup();

}

void init()
{
	//    add_action("do_quit", "quit");
}

int do_quit() {return 1;}

int clean_up()
{    //clean_up sleeve
	object *inv;

	if( !clonep() && this_object()->query("no_clean_up") ) return 1;

	inv = all_inventory();
	if(sizeof(inv)>0) return 1;
	//if not empty, no clean up.

	destruct(this_object());
	return 0;
}

void alternative_die(object who)
{
	who->set("kee", max2(1, who->query("kee")));
	who->set("eff_kee", max2(1, who->query("eff_kee")));
	who->set("sen", max2(1, who->query("sen")));
	who->set("sen_kee", max2(1, who->query("eff_sen")));
}
