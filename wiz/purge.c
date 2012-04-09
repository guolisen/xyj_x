// purge.c

#include <ansi.h>
#define SYNTAX	"指令格式：purge [<未上线天数>] | <使用者姓名> because <原因>\n"

inherit F_CLEAN_UP;

private int do_purge_players(int day);


string* _dirs = ({"login", "user", ""});

string file(string dir, string id)
{
	return DATA_DIR + dir + "/" + id[0..0] + "/" + id + __SAVE_EXTENSION__;
}

void purge_id(string id)
{
	foreach(string dir in _dirs)
		rm(file(dir, id));
	write("删除" + id + "。\n");
}

int main(object me, string arg)
{
	string name, reason;
	string status = wizhood(me);
	int day;
	
	if(me != this_player(1) || wiz_level(me) < wiz_level(status))
		return notify_fail("你没有权力使用这个指令。\n");

	if(!arg) return notify_fail(SYNTAX);

	if(sscanf(arg, "%d", day) && day >= 0) return do_purge_players(day);

	if(sscanf(arg, "%s because %s", name, reason) != 2) return notify_fail(SYNTAX);

	seteuid(getuid());

	if( file_size(file("login", name) < 0) return notify_fail("没有这位使用者。\n");
	if((string)SECURITY_D->get_status(name)!="(player)")
		return notify_fail("非玩家档案不能被删除。\n"); 

	rm(DATA_DIR + "login/" + name[0..0] + "/" + name + __SAVE_EXTENSION__);
	rm(DATA_DIR + "user/" + name[0..0] + "/" + name + __SAVE_EXTENSION__);
	rm(DATA_DIR + "qingdan/" + name[0..0] + "/" + name + __SAVE_EXTENSION__); //added gslxz 删除仓库清单记录
	write( "使用者 " + capitalize(name) + " 被删除掉了。\n");
	log_file("static/PURGE", sprintf("[%s] %s purged %s because %s.\n",
		ctime(time())[0..15], geteuid(this_player(1)), name, reason));

	return 1;
}

private int do_purge_players(int day)
{
	int i, j, ppl_cnt, count;
	string *dir, *ppls, name;
	mixed info;
	object who;

	if(day<31) return notify_fail("天数应该大于31。\n");
	seteuid(getuid());
	//	message("system", "\n*** 整理玩家储存档中，请稍候.... ***\n", users());
	write("处理中：\n");
	count = 0;
	ppl_cnt = 0;
	dir = get_dir(DATA_DIR + "login/");
	for(i=0; i<sizeof(dir); i++) {
		reset_eval_cost();
		write("目录"+dir[i]+": 玩家");
		ppls = get_dir(DATA_DIR + "login/" + dir[i] + "/");
		ppl_cnt += sizeof(ppls);
		for(j=0; j<sizeof(ppls); j++) {
			if( sscanf(ppls[j], "%s.o", name)==1 )
				if( (string)SECURITY_D->get_status(name)!="(player)" )
					continue;

			// Modified by dream on June 26, 1997 to avoid incorrect touching  
			// from outer sources like shell modification 
			//			info = stat(DATA_DIR + "login/" + dir[i] + "/" + ppls[j]);
			who = new(LOGIN_OB);
			who->set("id", name);
			if (! who->restore())
				continue;
			if( (time()-who->query("last_on"))/86400 >= day ) {
				rm(DATA_DIR + "login/" + dir[i] + "/" + ppls[j]);
				rm(DATA_DIR + "user/" + dir[i] + "/" + ppls[j]);
				rm(DATA_DIR + "qingdan/" + dir[i] + "/" + ppls[j]); //added gslxz 删除仓库清单记录
				write(" "+name);
				count ++;
			}
			destruct(who);
		}
		write(" 被清除掉了。\n");
	}
	write("\n\n原来总共有 " + ppl_cnt + " 位使用者。\n");
	write( count + " 个超过 " + day + " 天未上线的使用者被清除掉了。\n");
	write("现在总共有 " + (ppl_cnt - count) + " 位使用者。\n");
	log_file("static/PURGE", sprintf("[%s] %s cleaned up %d characters who didn't login for more than %d days\n"
		"\t\tResulting statistics: %d characters remaining.\n",
		ctime(time())[0..15], geteuid(this_player(1)), count, day, ppl_cnt - count));


	return 1;
}



//DATA_DIR + "login/"
void retrve(string path)
{
	object who;

	string* dirs = get_dir(path);
	foreach(string dir in dirs) {
		string* ids = get_dir(path + dir + "/");
		reset_eval_cost();
		write("目录" + dir + "\n");
		foreach(string id in ids) {
			string file = path + dir + "/" + id;			
			if(sscanf(id, "%s.o", id) != 1) continue;
			printf("id:%s\n", id);
			who = new(LOGIN_OB);
			who->set("id", id);
			if(who->restore()) {
				int day = (time() - who->query("last_on"))/86400;
				printf("\t%s %d\n", who->query("name"), day);

			}
			destruct(who);
		}
	}
	/*
	who = new(LOGIN_OB);
	who->set("id", name);
	if (! who->restore())
	continue;
	if( ( >= day ) {
	rm(DATA_DIR + "login/" + dir[i] + "/" + ppls[j]);
	rm(DATA_DIR + "user/" + dir[i] + "/" + ppls[j]);
	rm(DATA_DIR + "qingdan/" + dir[i] + "/" + ppls[j]); //added gslxz 删除仓库清单记录
	write(" "+name);
	count ++;
	}
	
	*/
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
