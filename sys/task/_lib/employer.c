// by firefox 04/10/2010
// ����ί����

#include <xyj_x.h>

inherit NPC;

object_f _task;		//��NPC�����������create�г�ʼ��


void init ()
{
	//::init();
	call_out("init_player", 1, _player);

	if(wizardp(_player)) add_action("do_debug", "debug");	
}

//��������
mixed apply_task()
{
	return _task->apply(_this, _player);
}

//ȡ������
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

//��������setup֮ǰ����
void set_task(string task, string* words, mapping msg)
{
	seteuid(getuid());
	_task = task;
	
	set("task_msg", msg);

	//��װ����
	foreach(string word in words) {
		set("inquiry/" + word, (: apply_task :));
	}
	//set("inquiry/cancel", (: cancel_task :));

	//������������
	set("chat_chance", 1);
	set("max_kee", 2000);
	set("max_kee", 2000);
	set("str", 500);
	set("cps", 500);
}

//���Թ���
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