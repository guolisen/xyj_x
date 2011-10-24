// firefox  10/24/2011
// 新人系统判定系统

#include <ansi.h>


void make_all()
{
	mapping groups = ([]);

	foreach(object who in users()) {
		string ip = query_ip_number(who);
		string uid = getuid(who);
		if(ip && uid != "MudOS") {
			if(!groups[ip]) groups[ip] = ({});
			groups[ip] += ({ who });
		}
	}

	foreach(string ip, object* arr in groups) {

	}



void create()
{

}

