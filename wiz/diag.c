// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit ITEM;
inherit F_LOADABLE;

void create()
{
	set_name(HIG"Õï¶Ï±¦Öé"NOR, ({ "diag pearl", "pearl" }) );
	set("long", "Ò»¿Å±¦Öé£¬¿É·¢³ödiag/clear_buff/ip_list/same_ipÖ¸Áî¡£\n");
	set("unit", "¿Å" );
	set("changed", 1);
}

void init()
{
	if(wizardp(this_player())) {
		add_action("do_diag", "diag");
		add_action("do_clear_buff", "clear_buff");
		add_action("do_ip_list", "ip_list");
		add_action("do_same_ip", "same_ip");
		add_action("do_getc", "getc");

		add_action("do_accepts", "accepts");
	}
}


int do_diag(string arg)
{
	foreach(object user in users()) {
		mapping buffs = user->query_temp("buff");
		if(mapp(buffs)) {
			foreach(string id in keys(buffs)) {
				if(buffs[id]["removed"]) {
					printf("%s removed buff:%s\n", getuid(user), id);
					map_delete(buffs, id);
				}
			}
		}
	}
	write("OK.\n");
	return 1;

}

int do_clear_buff(string arg)
{
	foreach(object user in users()) {
		BUFF->clear(user);
	}
	write("OK.\n");
	return 1;
}

mapping ip_group()
{
	mapping m = ([]);
	int i = 1;
	foreach(object who in users()) {
		string ip = query_ip_number(who);
		if(!m[ip]) m[ip] = ({});
		m[ip] += ({ who });
	}
	return m;
}

int do_ip_list(string arg)
{
	mapping m = ip_group();
	int i = 1;
	foreach(string ip, object* obs in m) {
		printf("%-4d:%s\n", i++, ip);
		foreach(object who in obs) {
			printf("\t%s(%s)\n", who->query("name"), getuid(who));
		}
	}
	write("OK.\n");
	return 1;
}

int do_same_ip(string arg)
{
	mapping m = ip_group();
	object user;
	object* group;
	
	if(arg && (user = find_player(arg)) && (group = m[query_ip_number(user)])) {
		foreach(object who in group) {
			printf("\t%s(%s)\n", who->query("name"), getuid(who));
		}
		write("OK.\n");
	} else {
		write("What?\n");
	}
	return 1;
}


int do_getc(string arg)
{
	object obj = find_player(arg);
	if(!obj) obj = find_living(arg);

	if(obj) {
		obj->move(environment(this_player()));
		write("OK.\n");
	} else {
		write("What?\n");
	}
	return 1;
}

int do_accepts(string arg)
{
	foreach(object who in children("/obj/user")) {
		string str = who->query_temp("accept");		
		if(str)
			printf("  %-24s    %s\n", name_id(who), str);		
	}
	write("OK.\n");
	return 1;
}

