// by firefox 04/10/2010

#include <xyj_x.h>


#define N 3*K*K

int calc(object who)
{
	int n = 0;

	n += who->query("sys_task/list/mieyao/mieyao/num") * 2400;

	n += who->query("sys_task/list/quest/armor/num") * 800;
	n += who->query("sys_task/list/quest/ask/num") * 800;
	n += who->query("sys_task/list/quest/cloth/num") * 800;
	n += who->query("sys_task/list/quest/food/num") * 800;
	n += who->query("sys_task/list/quest/give/num") * 800;
	n += who->query("sys_task/list/quest/kill/num") * 800;
	n += who->query("sys_task/list/quest/weapon/num") * 800;

	n += who->query("sys_task/list/forces/cien/num") * 15000;

	n += who->query("sys_task/stat/misc/reward");

	if(n > 0) {
		n = N - n;		
		write("old:" + who->query("sys_task/norm") + " new:" + n + "\n");
		who->set("sys_task/norm", n);
	}

	write(who->query("id") + " OK!\n");

}

int main(object me, string arg)
{
	object who;

	if(arg == "all") {
		foreach(who in users()) {
			if(!who) continue;
			calc(who);
		}
	} 
	if(arg && (who = find_player(arg))) {
		calc(who);
	}

	
	return 1;
}