// purge.c

#include <ansi.h>
#define SYNTAX	"指令格式：purge [<未上线天数>] | <使用者姓名> because <原因>\n"

inherit F_CLEAN_UP;

#define INTERVAL			10

string* _dirs = ({"login", "user", "mail"});
int _total = 0;
int purge_players(int day);

string file(string dir, string id)
{
	return DATA_DIR + dir + "/" + id[0..0] + "/" + id + __SAVE_EXTENSION__;
}

void purge_id(string id)
{
	foreach(string dir in _dirs)
		rm(file(dir, id));
}

int main(object me, string arg)
{
	string name, reason;
	string status = wizhood(me);
	int day;
	
	if(me != this_player(1) || wiz_level(me) < wiz_level(status))
		return notify_fail("你没有权力使用这个指令。\n");

	if(!arg) return notify_fail(SYNTAX);

	if(sscanf(arg, "%d", day) && day >= 0) return purge_players(day);

	if(sscanf(arg, "%s because %s", name, reason) != 2) return notify_fail(SYNTAX);

	seteuid(getuid());

	if( file_size(file("login", name)) < 0) return notify_fail("没有这位使用者。\n");
	if((string)SECURITY_D->get_status(name)!="(player)")
		return notify_fail("非玩家档案不能被删除。\n"); 

	purge_id(name);
	write("删除用户：" + name + "。\n");
	log_file("static/PURGE", sprintf("[%s] %s purged %s because %s.\n",
		ctime(time())[0..15], geteuid(this_player(1)), name, reason));

	return 1;
}


int purge_dir(string dir, int last_day)
{
	object who;
	string* ids = get_dir(dir);
	
	foreach(string id in ids) {
		string file = dir + id;
		if(sscanf(id, "%s.o", id) != 1) continue;

		who = new(LOGIN_OB);
		who->set("id", id);

		if(who->restore()) {
			int t = who->query("last_on");
			int c = who->query("count_come");
			if(t < last_day && c < 5) {
				printf("\t%s(%s) %d %d\n", who->query("name"), id, (time() - t) / 86400, c);
				purge_id(id);
				_total++;
			}
		}
		destruct(who);
		reset_eval_cost();
	}
	printf("目录:%s 累计删除:%d。\n", dir, _total);
	
}

int purge_players(int day)
{
	string path = DATA_DIR + "login/";
	mixed* dirs = get_dir(path, -1);
	int last_day = time() - day * 86400;
	int delay = 0;
	
	seteuid(getuid());
	_total = 0;
	foreach(mixed* info in dirs) {
		if(info[1] == -2) {
			delay += INTERVAL;
			call_out("purge_dir", delay, path + info[0] + "/", last_day);
		}
	}

	return 1;
}


int help(object me)
{
	write(@HELP
指令格式：purge [<未上线天数>] | <使用者姓名> because <原因>

清除一个使用者或清除超过一定天数不曾上线地使用者。
HELP
		);
	return 1;
}
