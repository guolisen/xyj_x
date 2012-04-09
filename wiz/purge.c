// purge.c

#include <ansi.h>
#define SYNTAX	"ָ���ʽ��purge [<δ��������>] | <ʹ��������> because <ԭ��>\n"

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
	write("ɾ��" + id + "��\n");
}

int main(object me, string arg)
{
	string name, reason;
	string status = wizhood(me);
	int day;
	
	if(me != this_player(1) || wiz_level(me) < wiz_level(status))
		return notify_fail("��û��Ȩ��ʹ�����ָ�\n");

	if(!arg) return notify_fail(SYNTAX);

	if(sscanf(arg, "%d", day) && day >= 0) return do_purge_players(day);

	if(sscanf(arg, "%s because %s", name, reason) != 2) return notify_fail(SYNTAX);

	seteuid(getuid());

	if( file_size(file("login", name) < 0) return notify_fail("û����λʹ���ߡ�\n");
	if((string)SECURITY_D->get_status(name)!="(player)")
		return notify_fail("����ҵ������ܱ�ɾ����\n"); 

	rm(DATA_DIR + "login/" + name[0..0] + "/" + name + __SAVE_EXTENSION__);
	rm(DATA_DIR + "user/" + name[0..0] + "/" + name + __SAVE_EXTENSION__);
	rm(DATA_DIR + "qingdan/" + name[0..0] + "/" + name + __SAVE_EXTENSION__); //added gslxz ɾ���ֿ��嵥��¼
	write( "ʹ���� " + capitalize(name) + " ��ɾ�����ˡ�\n");
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

	if(day<31) return notify_fail("����Ӧ�ô���31��\n");
	seteuid(getuid());
	//	message("system", "\n*** ������Ҵ��浵�У����Ժ�.... ***\n", users());
	write("�����У�\n");
	count = 0;
	ppl_cnt = 0;
	dir = get_dir(DATA_DIR + "login/");
	for(i=0; i<sizeof(dir); i++) {
		reset_eval_cost();
		write("Ŀ¼"+dir[i]+": ���");
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
				rm(DATA_DIR + "qingdan/" + dir[i] + "/" + ppls[j]); //added gslxz ɾ���ֿ��嵥��¼
				write(" "+name);
				count ++;
			}
			destruct(who);
		}
		write(" ��������ˡ�\n");
	}
	write("\n\nԭ���ܹ��� " + ppl_cnt + " λʹ���ߡ�\n");
	write( count + " ������ " + day + " ��δ���ߵ�ʹ���߱�������ˡ�\n");
	write("�����ܹ��� " + (ppl_cnt - count) + " λʹ���ߡ�\n");
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
		write("Ŀ¼" + dir + "\n");
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
	rm(DATA_DIR + "qingdan/" + dir[i] + "/" + ppls[j]); //added gslxz ɾ���ֿ��嵥��¼
	write(" "+name);
	count ++;
	}
	
	*/
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
