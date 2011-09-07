// by firefox 04/10/2010
// 任务委托人

#include <xyj_x.h>

inherit NPC;

object_f _task;		//该NPC负责的任务，在create中初始化


void init ()
{
	//::init();
	call_out("init_player", 1, _player);

	if(wizardp(_player)) add_action("do_debug", "debug");	
}

//申请任务
mixed apply_task()
{
	return _task->apply(_this, _player);
}

//取消任务
string cancel_task()
{
	return _task->cancel(_this, _player);
}

int init_player(object who)
{
	return _task->init_player(_this, who);
}

int accept_object(object who, object ob)
{
	return _task->accept_object(_this, who, ob);
}

//设置任务，setup之前调用
void set_task(string task, string* words, mapping msg)
{
	seteuid(getuid());
	_task = task;
	
	set("task_msg", msg);

	//安装命令
	foreach(string word in words) {
		set("inquiry/" + word, (: apply_task :));
	}
	//set("inquiry/cancel", (: cancel_task :));

	//其他公共设置
	set("chat_chance", 1);
	set("max_kee", 2000);
	set("max_kee", 2000);
	set("str", 500);
	set("cps", 500);
}

//调试功能
int do_debug(string arg)
{
	return _task->debug(_this, _player, arg);
}

void die ()
{
	set("kee", 200);
	set("eff_kee", 200);
	set("sen", 200);
	set("eff_sen", 200);
}

void unconcious()
{
	die();
}