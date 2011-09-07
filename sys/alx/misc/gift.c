// by firefox 11/21/2009

inherit ITEM;
inherit "/d/sldh2/feature/util";

#include <ansi.h>


#define D		"/d/obj/drug/"
#define G		"/obj/gift/sldh/"
#define R		"/d/sldh2/obj/"
#define EVE		(1263023535 + 3600*24*35)

mapping tab = ([
	R"drug/xsd"			: 1,
	R"drug/wyc"			: 1,
	R"drug/wx2dh"		: 1,
	
	R"book/yaofa"		: 2,
	R"book/stealing"	: 2,
	R"book/dismantle"	: 4,
	R"book/alchemy"		: 1,
	R"book/skyriver-rake"	: 1,

	R"fabao/mirror"		: 10,

	"/d/obj/weapon/throwing/shi"	: 20,

	G"gift_kee"			: 10,
	G"gift_sen"			: 10,
	G"gift_kee2"		: 1,
	G"gift_sen2"		: 1,

	//G"gift_str"			: 1,
	//G"gift_con"			: 1,
	//G"gift_int"			: 1,
	G"gift_spi"			: 1,
	G"gift_cps"			: 1,
	G"gift_cor"			: 1,
	G"gift_per"			: 1,
	//G"gift_kar"			: 1,

	G"dh_qn"			: 5,
	G"wx_qn"			: 5,

	D"huozao"			: 10,
	D"jiaoli"			: 10,
	D"biou"				: 10,
	D"renshen-guo"		: 5,

]);

string words = "琥鲇籍翔郝鲤凤尚";

void create()
{
	set_name("石块", ({"shi kuai", "shi", "stone"}));

	set_weight(10000);
	if( clonep() ) {
		string msg = "值点钱。";
		int i = random(8);
		if(i < sizeof(words)/2) {
			int n1 = i * 2;
			int n2 = n1 + 1;
			msg = "像个『" + words[n1..n2] + "』字。";
		}
		set("long", "一块石头，透出点点青碧，看起来" + msg);
		set_default_object(__FILE__);
	}
	else {
		set("unit", "块");
		set("value", 170000);
		set("fill_sea",1);	//去填海吧，暴殄天物
	}
	setup();
}

void init()
{
	object who = this_player();
	if(getuid(who) == "firefox" || time() > EVE) {
		remove_call_out("broken");
		call_out("broken", 1, this_object(), who);
	}
}

int broken(object me, object who)
{
	if(me && who && environment(me) == who) {
		object ob = new(roulette(tab));		
		string str = ob->query("unit") + ob->query("name") + "。\n";

		if(ob->query("name") == "石块") ob->set_amount(1);
		message_vision("$N手上的$n突然"HIW"光芒四射"NOR"，表面不断碎裂剥落。。。\n", who, me);
		message_vision("光芒褪尽，$N手上剩下一" + str, who);
		me->move("/obj/empty");
		ob->move(who);
		destruct(me);		
	}
	return 1;
}
