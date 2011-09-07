// by firefox 11/21/2009

inherit NPC;
#include <ansi.h>

#define M		6

void create()
{
	set_name("Ä¦¶÷", ({ "scanner", "robot" }));
	set("long", "\nÉ¨Ãè»úÆ÷ÈË¡£\n\n");
	set("title", HIY"É¨Ãè»úÆ÷ÈË"NOR);
	set("gender", "ÄÐÐÔ");
	set("age", 18);
	set("per", 120);

	setup();
}

void init()
{
	::init();
	add_action("do_scan", "scan");
	add_action("do_scan1", "scan1");
}

int do_scan(string arg)
{
	foreach(object user in users()) {
		int has_fake = 0;
		foreach(object ob in all_inventory(user)) {			
			if(ob && ob->query("id") == "chuansuo qi") {
				int n = ob->query_amount();
				printf("%s : %d\n", getuid(user), n);
				if(n > M) {
					int r = n - M;
					user->add("balance", r * 100000);
					user->add("ufo_return", r);					
					ob->set_amount(M);
					printf("return %d\n", r);
				}
				if(n == 0) {
					has_fake = 1;
					printf("%s : fake ufo\n", getuid(user));
				}
			}
		}
		if(!has_fake) {
			//object fake = new("/d/sldh2/obj/fabao/ufo");
			//fake->move(user);
		}
	}
	return 1;
}


int do_scan1(string arg)
{
	foreach(object user in users()) {
		foreach(object ob in all_inventory(user)) {			
			if(ob && ob->query("id") == "chuansuo qi") {
				if(file_name(ob)[0..7] == "/d/sldh2") {
					printf("%s : dest\n", getuid(user));
					destruct(ob);
					new("/d/wuming/obj/chuansuo")->move(user);
				}
			}
		}
	}
	return 1;
}
