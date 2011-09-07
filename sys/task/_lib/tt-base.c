// by firefox 04/10/2010
// ��������ģ��

#include <xyj_x.h>
#include <ansi.h>

inherit F_DATA_OF;
inherit F_FOT;

string _stat_prop;				//����ͳ����Ϣ������
int	_norm;						//�������
int _show_id;

//��ʼ������
void init_prop(int norm)
{
	seteuid(getuid());

	set_data_prop(TASK_PROP + "/list/" + parent_id() + "/" + id());
	_stat_prop = TASK_PROP + "/stat/" + parent_id();
	_norm = norm;
	
}


/********************************�麯��***********************************/

//��������ǰ������
int pre_check(object employer, object who) { return 1; }

//���ֽ���
void give_reward(object who, int reward);

//����������
void new_task(object who, mapping task)
{
	task["tid"]		= "ID";
	task["tname"]	= "Ŀ������";
	task["level"]	= 9;
	task["remark"]	= 0;			//������Ϣ"
	task["reward"]	= 100;			//ȷ��������
}

//��ȡ��ʾ��Ϣ��
mapping get_msg(object employer)
{
	return employer->query("task_msg");
}

/********************************��׼�ӿ�***********************************/

//�������������
mixed apply(object employer, object who)
{
	mapping msg = get_msg(employer);
	mapping m = data_of(who);
	string str, target;

	//���CD(ע���say����Ϣ��Ϊ/std/quest����ask׼����)
	if(m["cd"] && time() < m["cd"]) {
		msvx(msg["cd"], employer, who);
		return or2(msg["cd_say"], 1);
	}

	//���ǰ������
	if(!pre_check(employer, who)) return or2(msg["check_say"], 1);

	//������
	if(!TASK->apply_norm(who, _norm)) {
		TASK->tell_tired(employer, who);
		return or2(msg["no_norm"], 1);
	}

	//������
	m["num"]++;
	m["ename"] = employer->query("name");
	new_task(who, m);
	m["state"] = "����";
	
	who->add(_stat_prop + "/num", 1);
	
	//��ͬtype��������ʾ��Ϣ���ܲ�ͬ
	str = mapp(msg["task"]) ? msg["task"][m["type"]] : msg["task"];
	target = _show_id ? name_id2(m["tname"], m["tid"]) : m["tname"];

	msvx(str, employer, who, target, or2(m["sth"], m["oname"]));

	return or2(msg["apply_say"], 1);
}

//�������
varargs mixed done(object who, int ratio)
{
	mapping m = data_of(who);
	int reward;
	
	if(!ratio) ratio = 100;
	ratio = truncate(ratio, 20, 100);
	reward = m["reward"] * ratio / 100;

	give_reward(who, reward);
	
	who->add(_stat_prop + "/reward", reward);
	who->add(_stat_prop + "/done", 1);

	m["state"] = "���";
	//MONITOR_D->report_system_object_msg(who, " got " + reward + "\n");

	return or2(m["return"], 1);
}

//���Թ���
int debug(object employer, object who, string arg)
{
	tell_object(who, HIR"���޵��Թ��ܡ�\n");
	return 1;
}

//ȡ������
mixed cancel(object employer, object who);

//�������
int init_player(object employer, object who);



