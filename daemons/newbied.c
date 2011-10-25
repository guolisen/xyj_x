// firefox  10/24/2011
// 新人系统判定系统

#include <ansi.h>
#include <xyj_x.h>

#define DIAG_PROP			"sys_diag"
#define A					10				//更新系数(%)

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
		int max_exp = 0;
		foreach(object who in arr) {
			int exp = total_exp(who);
			max_exp = max2(max_exp, exp);
		}
		foreach(object who in arr) {
			mapping m = DB->query_map(DIAG_PROP);
			m["exp"] = m["exp"] / 100 * (100 - A) + max_exp / 100 * A;
		}
	}
}

void create()
{

}

