// purge.c

#include <ansi.h>
#define SYNTAX	"ָ���ʽ��purge [<δ��������>] | <ʹ��������> because <ԭ��>\n"

inherit F_CLEAN_UP;


string* _dirs = ({"login", "user", "mail"});

int purge_dir(string dir, int day);

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
		return notify_fail("��û��Ȩ��ʹ�����ָ�\n");

	if(!arg) return notify_fail(SYNTAX);

	if(sscanf(arg, "%d", day) && day >= 0) return purge_dir(day);

	if(sscanf(arg, "%s because %s", name, reason) != 2) return notify_fail(SYNTAX);

	seteuid(getuid());

	if( file_size(file("login", name)) < 0) return notify_fail("û����λʹ���ߡ�\n");
	if((string)SECURITY_D->get_status(name)!="(player)")
		return notify_fail("����ҵ������ܱ�ɾ����\n"); 

	purge_id(name);
	write( "ʹ���� " + capitalize(name) + " ��ɾ�����ˡ�\n");
	log_file("static/PURGE", sprintf("[%s] %s purged %s because %s.\n",
		ctime(time())[0..15], geteuid(this_player(1)), name, reason));

	return 1;
}


int purge_dir(string dir, int day)
{
	object who;
	string* ids = get_dir(dir);
	reset_eval_cost();
	foreach(string id in ids) {
		string file = dir + id;
		if(sscanf(id, "%s.o", id) != 1) continue;

		who = new(LOGIN_OB);
		who->set("id", id);

		if(who->restore()) {
			int d = (time() - who->query("last_on"))/86400;
			int c = who->query("count_come");
			if(d > day && c >-1)
				printf("\t%s %d %d\n", who->query("name"), day, come);
		}
		destruct(who);
	}
}
//DATA_DIR + "login/"
int purge_players(int day)
{
	mixed* dirs = get_dir((DATA_DIR + "login/", -1);

	seteuid(getuid());

	foreach(mixed* info in dirs) {
		if(info[1] == -2) {
			call_out("purge_dir", 10, path + info[0] + "/", day);
		}
	}
}


int help(object me)
{
	write(@HELP
ָ���ʽ��purge [<δ��������>] | <ʹ��������> because <ԭ��>

���һ��ʹ���߻��������һ�������������ߵ�ʹ���ߡ�
HELP
		);
	return 1;
}
