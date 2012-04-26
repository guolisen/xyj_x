
#define TEXT_SIZE					2000
#define SCHEME_CMD					"/cmds/usr/scheme"

#include <ansi.h>
#include <xyj_x.h>

#define SPC							20		//ÿn��ִ��һ������

#define WHO							0
#define CMDS						1
#define START_TIME					2


void done_input(object me, string text);
int init(object me);
int execute_schedule(object me, mapping tdb);

mapping _users = ([]);


//�ƻ��Ƿ���ִ��
int is_doing(object who)
{
	return who->query_temp("scheme") != 0;
}

//ע�����
private int add(object who)
{
	_users[getuid(who)] = ({ who, 0, time() });
}

void check_heart_beat()
{
	if(!query_heart_beat())
		set_heart_beat(1);
	call_out("check_heart_beat", 611);
}

int pause()
{
	set_heart_beat(0);
	return 1;
}

void create()
{
	seteuid(getuid());
	check_heart_beat();	

	//����ʱ���Ǽ��Ѿ���ִ��scheme�����
	foreach(object who in children("/obj/user")) {
		if(is_doing(who)) add(who);
	}
}

//�鿴�ƻ�
int show(object who)
{
	string schedule = who->query("schedule");
	if(!schedule)
		return notify_fail("�ƻ������ڡ�\n");

	write(who->name() + "�����ƶ��ļƻ����£�\n" + schedule);

	if(is_doing(who))
		write("�üƻ�Ŀǰ����ִ���С�\n");

	return 1;
}

//�г�ִ�мƻ���ID
int list()
{
	string* tab = ({ "# ", "  "});
	int n = 0;
	int now = time();

	write("���������ִ�мƻ���\n");
	foreach(string id, mixed* arr in _users) {
		object who = arr[WHO];
		if(who) {
			int t = now - arr[START_TIME];
			if(t < 1) t = 1;
			printf("%s %-20s  %4d  %4d\n",
				tab[interactive(who)],
				name_id(who),
				t / 3600,
				arr[CMDS] * 60 / t,
				);
			n++;
		}
	}
	write("����" + n + "�������ִ�мƻ���\n");
	return 1;
}

//����ƻ�
int clear(object who)
{
	if(is_doing(who))
		return notify_fail("����������ִ�мƻ�������ͣ������\n");
	
	who->delete("schedule");
	write("Ok.\n");
	return 1;
}

//�༭�ƻ�
int edit(object who)
{
	if(is_doing(who))
		return notify_fail("����������ִ�мƻ�������ͣ������\n");

	write("�������㽫Ҫִ�еļƻ���\n");
	who->edit((: done_input, who :));
	return 1;
}

//��ʼ�ƻ�
int start(object who)
{
	string schedule = who->query("schedule");
	
	if(!schedule)
		return notify_fail("�ƻ������ڡ�\n");
	if(is_doing(who))
		return notify_fail("����������ִ�мƻ�������ͣ������\n");

	write("�ƻ���ʼִ�С�\n");

	add(who);
	
	return init(who);

}

//ֹͣ�ƻ�
int stop(object user)
{
	map_delete(_users, user->query("id"));

	user->delete_temp("scheme");
	write("�ƻ�ִֹͣ�С�\n");
	return 1;
}

//�쳣��ֹ�ƻ�������˳�
int abort(object me)
{
	stop(me);
	trace("scheme abort:" + interactive(me) + getuid(me), D_WIZ);
	if(!interactive(me))
		call_out("user_quit", 1, me);
	return 1;
}

//����״̬
int bad_state(object who)
{
	mapping db = who->query_entire_dbase();
	object env = environment(who);

	if(env && env->query("alternative_die")) return 0;

	return db["eff_kee"] < db["max_kee"]/2 || db["eff_sen"] < db["max_sen"]/2;
}

void heart_beat()
{
	int now = time();

	foreach(string id, mixed* arr in _users) {
		object user = arr[WHO];
		if(userp(user)) {
			//��ָ����/æ/�ε������ֱ�����
			int thr = arr[CMDS] * (interactive(user) ? 2 : SPC);		//���߼ƻ�ִ����

			if((thr < now - arr[START_TIME]) && !user->is_busy() && living(user)) {
				if(bad_state(user))
					abort(user);
				else {
					mapping tdb = user->query_temp("scheme");
					if(tdb) arr[CMDS] += execute_schedule(user, tdb);	//ִ��ָ����ۼ�ָ����
				}
			}
		} else {
			map_delete(_users, id);
		}
	}
}

//����˳�
int user_quit(object me)
{
	if(!me) return 1;
	me->command("quit");
	if(objectp(me) && !interactive(me))
		call_out("user_quit", 1, me);
	return 1;
}

//��ʼ���ƻ�
int init(object me)
{
	string schedule = me->query("schedule");
	mapping db = ([ ]);
	string* lines = explode(schedule, "\n");

	lines = filter_array(lines, (: replace_string($1, " ", "\n") != "" :));
	if (sizeof(lines) < 1) {
		write("����һ�ݿռƻ�����ûʲô�����ġ�\n");
		return 0;
	}

	db["lines"] = lines;

	me->set_temp("scheme", ([
		"lines"		: lines,
		"step"		: 0,
		"loops"		: ({}) ])
	);
	return 1;
}

//�༭����
void done_input(object me, string text)
{
	string* lines;

	if (!stringp(text)) {
		tell_object(me, "��û�������κ��µļƻ���\n");
		return;
	}

	if (strlen(text) > TEXT_SIZE) {
		tell_object(me, "����ݼƻ�̫���ˣ�����������һ����һЩ�ġ�\n");
		return;
	}

	lines = explode(text, "\n");
	lines = filter_array(lines, (: replace_string($1, " ", "") != "" :));
	text = implode(lines, "\n") + "\n";

	me->set("schedule", text);
	tell_object(me, "��������һ���µļƻ���\n");
}

int _cmds_count = 0;						//ĳ���ĳһ��ִ�е�������

//ִ��һ������
int exec_cmds(object who, string cmds)
{
	string* arr = explode(cmds, ";");
	int ret = 0;
	int times;
	string cmd;

	foreach(string elem in arr) {
		if(sscanf(elem, "%d%s", times, cmd) != 2) {
			times = 1;
			cmd = elem;
		}
		for(int i = 0; i < times; ++i) {
			string c = who->process_input(cmd);
			if(c == "") {
				who->start_busy(20);
				return ret;	//����̫������
			}
			ret = who->command(c);
		}
		_cmds_count += times;
	}
	return ret;
}

// ִ�мƻ���
int execute_schedule(object me, mapping tdb)
{
	string* lines = tdb["lines"];
	int step = tdb["step"];
	string cmd = lines[step];
	string cmd_case;
	int cmd_ok, cmd_res;
	int i, count;
	mixed* loops = tdb["loops"];

	_cmds_count = 0;

	if(time() - tdb["scheme_last_fail"] < 5)
		return 0;

	// ȡ�� n ����
	if(sscanf(cmd, "%s~:%s", cmd, cmd_case) == 2)
		cmd_ok = 0;
	else if(sscanf(cmd, "%s:%s", cmd, cmd_case) == 2)
		cmd_ok = 1;
	else
		cmd_case = "IGNORE";

	tell_object(me, "> " + HIY + cmd + NOR "\n");

	switch (cmd) {
	case "REPEAT":			// ��ʼѭ��
		
		//Ѱ��ƥ���LOOP
		count = 1;
		for(i = step + 1; i < sizeof(lines); i++) {
			if(lines[i] == "LOOP") {
				if(--count < 1)	break;
			}
			if(lines[i] == "REPEAT")	count++;
		}

		if (count > 0) {
			tell_object(me, "�ƻ��� repeat û���ҵ���֮ƥ��� loop ����޷�����ִ�С�\n");
			abort(me);
			break;
		}
		tdb["loops"] += ({ ({ step, i }) });		//ѭ����/ֹ��
		break;

	case "LOOP":		// ѭ��ִ��
		if(sizeof(loops) < 1) {
			tell_object(me, "û���ҵ��ƻ�����֮ƥ��� repeat ���\n");
			abort(me);
			return 0;
		}
		step = loops[sizeof(loops) - 1][0];
		break;

	case "BREAK":		// ������ѭ��
		if(sizeof(loops) < 1) {
			tell_object(me, "û���ҵ��ƻ�����֮ƥ��� repeat-loop ���\n");
			abort(me);
			return 0;
		}

		step = loops[sizeof(loops) - 1][1];
		tdb["loops"] = loops[0..<2];
		break;

	default:
		// ִ�е� n ���������������һ���Ƿ�ִ�еڶ�����

		//command( this_object()->process_input(cmd) );
		cmd_res = exec_cmds(me, cmd) != 0;
		
		if(cmd_case != "IGNORE" && cmd_res == cmd_ok) {	//�������
			
			tell_object(me, "> " + HIY + cmd_case + NOR "\n");

			switch(cmd_case)
			{
			case "RETRY":
				tdb["scheme_last_fail"] = time();
				return _cmds_count;

			case "CONTINUE":	// ѭ��ִ��
				if(sizeof(loops) < 1) {
					tell_object(me, "û���ҵ��ƻ�����֮ƥ��� repeat ���\n");
					abort(me);
					break;
				}
				step = loops[sizeof(loops) - 1][0];
				break;

			case "BREAK":		// ������ѭ��
				if (sizeof(loops) < 1) {
					tell_object(me, "û���ҵ��ƻ�����֮ƥ��� repeat-loop ���\n");
					abort(me);
					break;
				}

				step = loops[sizeof(loops) - 1][1];
				tdb["loops"] = loops[0..<2];
				break;

			default:
				exec_cmds(me, cmd_case);
				break;
			}
			// ����ʧ��ʱִ�� cmd_case ��ϡ�
		}
		// ִ������������
	}

	if(++step >= sizeof(lines)) {
		tell_object(me, "�ƻ�ִ����ϡ�\n");
		abort(me);
		return 0;
	}

	tdb["step"] = step;
	return _cmds_count;
}


mapping debug() 
{
	return _users;
}