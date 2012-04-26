
#define TEXT_SIZE					2000
#define SCHEME_CMD					"/cmds/usr/scheme"

#include <ansi.h>
#include <xyj_x.h>

#define SPC							20		//每n秒执行一条命令

#define WHO							0
#define CMDS						1
#define START_TIME					2


void done_input(object me, string text);
int init(object me);
int execute_schedule(object me, mapping tdb);

mapping _users = ([]);


//计划是否在执行
int is_doing(object who)
{
	return who->query_temp("scheme") != 0;
}

//注册玩家
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

	//更新时，登记已经在执行scheme的玩家
	foreach(object who in children("/obj/user")) {
		if(is_doing(who)) add(who);
	}
}

//查看计划
int show(object who)
{
	string schedule = who->query("schedule");
	if(!schedule)
		return notify_fail("计划不存在。\n");

	write(who->name() + "现在制订的计划如下：\n" + schedule);

	if(is_doing(who))
		write("该计划目前正在执行中。\n");

	return 1;
}

//列出执行计划的ID
int list()
{
	string* tab = ({ "# ", "  "});
	int n = 0;
	int now = time();

	write("下列玩家在执行计划：\n");
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
	write("共有" + n + "个玩家在执行计划。\n");
	return 1;
}

//清除计划
int clear(object who)
{
	if(is_doing(who))
		return notify_fail("你现在正在执行计划，请先停下来。\n");
	
	who->delete("schedule");
	write("Ok.\n");
	return 1;
}

//编辑计划
int edit(object who)
{
	if(is_doing(who))
		return notify_fail("你现在正在执行计划，请先停下来。\n");

	write("请输入你将要执行的计划：\n");
	who->edit((: done_input, who :));
	return 1;
}

//开始计划
int start(object who)
{
	string schedule = who->query("schedule");
	
	if(!schedule)
		return notify_fail("计划不存在。\n");
	if(is_doing(who))
		return notify_fail("你现在正在执行计划，请先停下来。\n");

	write("计划开始执行。\n");

	add(who);
	
	return init(who);

}

//停止计划
int stop(object user)
{
	map_delete(_users, user->query("id"));

	user->delete_temp("scheme");
	write("计划停止执行。\n");
	return 1;
}

//异常中止计划，玩家退出
int abort(object me)
{
	stop(me);
	trace("scheme abort:" + interactive(me) + getuid(me), D_WIZ);
	if(!interactive(me))
		call_out("user_quit", 1, me);
	return 1;
}

//不良状态
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
			//条指过多/忙/晕倒，本轮被跳过
			int thr = arr[CMDS] * (interactive(user) ? 2 : SPC);		//离线计划执行慢

			if((thr < now - arr[START_TIME]) && !user->is_busy() && living(user)) {
				if(bad_state(user))
					abort(user);
				else {
					mapping tdb = user->query_temp("scheme");
					if(tdb) arr[CMDS] += execute_schedule(user, tdb);	//执行指令，并累计指令数
				}
			}
		} else {
			map_delete(_users, id);
		}
	}
}

//玩家退出
int user_quit(object me)
{
	if(!me) return 1;
	me->command("quit");
	if(objectp(me) && !interactive(me))
		call_out("user_quit", 1, me);
	return 1;
}

//初始化计划
int init(object me)
{
	string schedule = me->query("schedule");
	mapping db = ([ ]);
	string* lines = explode(schedule, "\n");

	lines = filter_array(lines, (: replace_string($1, " ", "\n") != "" :));
	if (sizeof(lines) < 1) {
		write("这是一份空计划，你没什么好做的。\n");
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

//编辑结束
void done_input(object me, string text)
{
	string* lines;

	if (!stringp(text)) {
		tell_object(me, "你没有输入任何新的计划。\n");
		return;
	}

	if (strlen(text) > TEXT_SIZE) {
		tell_object(me, "你这份计划太长了，请重新设置一个短一些的。\n");
		return;
	}

	lines = explode(text, "\n");
	lines = filter_array(lines, (: replace_string($1, " ", "") != "" :));
	text = implode(lines, "\n") + "\n";

	me->set("schedule", text);
	tell_object(me, "你设置了一份新的计划。\n");
}

int _cmds_count = 0;						//某玩家某一次执行的命令数

//执行一组命令
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
				return ret;	//输入太多命令
			}
			ret = who->command(c);
		}
		_cmds_count += times;
	}
	return ret;
}

// 执行计划中
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

	// 取第 n 步骤
	if(sscanf(cmd, "%s~:%s", cmd, cmd_case) == 2)
		cmd_ok = 0;
	else if(sscanf(cmd, "%s:%s", cmd, cmd_case) == 2)
		cmd_ok = 1;
	else
		cmd_case = "IGNORE";

	tell_object(me, "> " + HIY + cmd + NOR "\n");

	switch (cmd) {
	case "REPEAT":			// 开始循环
		
		//寻找匹配的LOOP
		count = 1;
		for(i = step + 1; i < sizeof(lines); i++) {
			if(lines[i] == "LOOP") {
				if(--count < 1)	break;
			}
			if(lines[i] == "REPEAT")	count++;
		}

		if (count > 0) {
			tell_object(me, "计划中 repeat 没有找到与之匹配的 loop 命令，无法继续执行。\n");
			abort(me);
			break;
		}
		tdb["loops"] += ({ ({ step, i }) });		//循环起/止行
		break;

	case "LOOP":		// 循环执行
		if(sizeof(loops) < 1) {
			tell_object(me, "没有找到计划中与之匹配的 repeat 命令。\n");
			abort(me);
			return 0;
		}
		step = loops[sizeof(loops) - 1][0];
		break;

	case "BREAK":		// 跳出该循环
		if(sizeof(loops) < 1) {
			tell_object(me, "没有找到计划中与之匹配的 repeat-loop 命令。\n");
			abort(me);
			return 0;
		}

		step = loops[sizeof(loops) - 1][1];
		tdb["loops"] = loops[0..<2];
		break;

	default:
		// 执行第 n 步，并视情况看下一步是否执行第二操作

		//command( this_object()->process_input(cmd) );
		cmd_res = exec_cmds(me, cmd) != 0;
		
		if(cmd_case != "IGNORE" && cmd_res == cmd_ok) {	//后继命令
			
			tell_object(me, "> " + HIY + cmd_case + NOR "\n");

			switch(cmd_case)
			{
			case "RETRY":
				tdb["scheme_last_fail"] = time();
				return _cmds_count;

			case "CONTINUE":	// 循环执行
				if(sizeof(loops) < 1) {
					tell_object(me, "没有找到计划中与之匹配的 repeat 命令。\n");
					abort(me);
					break;
				}
				step = loops[sizeof(loops) - 1][0];
				break;

			case "BREAK":		// 跳出该循环
				if (sizeof(loops) < 1) {
					tell_object(me, "没有找到计划中与之匹配的 repeat-loop 命令。\n");
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
			// 命令失败时执行 cmd_case 完毕。
		}
		// 执行玩家命令完毕
	}

	if(++step >= sizeof(lines)) {
		tell_object(me, "计划执行完毕。\n");
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