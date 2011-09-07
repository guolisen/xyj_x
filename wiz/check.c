
#include <ansi.h>

void check()
{
	printf("------------------------------------------------------------------\n");
	printf("姓名            ID        武学    道行    潜能    灭妖    武潜比\n");
	printf("------------------------------------------------------------------\n");
	foreach(object user in users()) {
		if(user && user->query("combat_exp") > 100000) {
			int ratio = user->query("combat_exp")/(user->query("potential") + 100);
			printf("%-16s%-10s%-8d%-8d%-8d%-8d%-8s\n",
				user->query("name"),
				user->query("id"),			
				user->query("combat_exp")/1000,
				user->query("daoxing")/1000,
				user->query("potential")/1000,
				user->query("mieyao/number1"),
				(ratio > 4 ? HIR : "") + ratio + NOR,
				);
		}
	}
	printf("------------------------------------------------------------------\n");
 }
