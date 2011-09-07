// by firefox 04/10/2010
// ȫ���������������������

#include <xyj_x.h>
#include <ansi.h>

inherit F_DATA_OF;
inherit F_FOT;
inherit F_VECTOR;

#define MAX_NORM					3000*K			//ÿ�����
#define RESET_TIME					(7*24*3600)

void create()
{
	seteuid(getuid());
	push_backs( ({"mieyao", "quest", "forces", "misc"}) );
	
	set_data_prop(TASK_PROP);
}

//�����б�
mapping list_data(object who)
{
	return DB->query_map(who, TASK_PROP + "/list");
}

//ͳ���б�
mapping stat_data(object who)
{
	return DB->query_map(who, TASK_PROP + "/stat");
}

//��ѯ���
int query_norm(object who)
{	
	mapping m = data_of(who);
	int t = time();

	if(t > m["start_time"] + RESET_TIME) {
		m["start_time"] += m["start_time"] ? RESET_TIME : t;
		m["norm"] = MAX_NORM;
	}
	return m["norm"];
}


//��������������м�ȥ�����������ʧ��
int apply_norm(object who, int norm)
{
	mapping m = data_of(who);

	query_norm(who);

	if(m["norm"] >= norm) {
		m["norm"] -= norm;
		return 1;
	}
	return 0;
}

//��ʾƣ����Ϣ
void tell_tired(object employer, object who)
{
	string* msg = ({
		"$N��$n˵�����������Ͷ٣������в�֧���ֽ��˶�ЪϢ��\n",
		HIG"�װ�����ң�������������Ѿ��þ�����ע����Ϣ�Լ����ܣ�ף����졣\n"NOR,
	});
	msvx(msg[0], employer, who);
	tell_object(who, msg[1]);
}

//�����Ƿ�ƥ��
varargs int info_match(mapping info, object target, mixed sth, string type)
{
	return info["state"] == "����"
		&& info["type"] == type
		&& name_id_is(target, info["tname"], info["tid"])
		&& (!stringp(sth) || sth == info["sth"])
		&& (!objectp(sth) || name_id_is(sth, info["oname"], info["oid"]));
}


//���������б�����ָ����ָ������������
varargs object_f find_task(object who, string type, object target, mixed sth)
{
	mapping list = list_data(who);
	foreach(string gid, mapping group in list) {
		
		reset_eval_cost();
		foreach(string tid, mapping task in group) {
			if(info_match(task, target, sth, type)) return TASK_GET(gid, tid);
		}
	}
	return 0;
}

//�������ָ������������
varargs mixed done_task(object who, string type, object target, mixed sth)
{
	object_f task = find_task(who, type, target, sth);
	return task ? task->done(who) : 0;
}

//ѯ��
string do_ask(object me, object who, string topic)
{
	/* ʦ��������ʱ�ر�
	if(topic == "task") {
		if(me->is_apprentice_of(who)) {
			return TASK_GET("forces", "family")->apply(who, me);		//���뷵�ش�
		}
	}*/

	return TASK->done_task(me, "ask", who, topic);;
}


//������������ת��
void clear_list(object who)
{
	who->set(TASK_PROP + "/list", ([]));
}


/*
��ǰ�����(ʣ���ȣ�1000)��[1]
��������������������������������������������������������������������
ί����    ����Ŀ��    ״̬    �Ѷ�  ����  ��ע
��������������������������������������������������������������������
�      ̡צʨ      ����    9     81    ��������
Ԭ���    ���ù�      ���    8     14    ����ɽ
--------------------------------------------------------------------
��˽�    �����      ���    5     22            
���½�    ���        ����    4     33    ˮ������
�¹���    ����        ����    5     21    ����
������    ������      ����    6     66          
�๫      ţ����      ���    4     4            
����      �����ȹ    ����    1     33
����      �λõ�      ����    3     9
--------------------------------------------------------------------
����    ����        ���    6     11
����      ������      ����    -     8
--------------------------------------------------------------------
���      ħ��Ⱥ��    ����    -     19			[2]
����⨺�  �ɽ�����    ����    -     44
--------------------------------------------------------------------
�ȶ���ʦ  ������Ƭ    ����    -     15			[3]
��������������������������������������������������������������������
*/

#define TIT01 "ί����    ����Ŀ��        ״̬    �Ѷ�  ����  ��ע\n"
#define FMT01 "%-10s%-16s%-8s%-6s%-6d%s\n"

mapping _state_color = ([
	"����"		: HIG,
	"���"		: NOR,
	"����"		: RED,
	"����"		: NOR,
]);

///�г���ҵĵ�ǰ����
int list(object who)
{	
	mapping data = list_data(who);
	int has_pre = 0;
	int remain_time = data_of(who, "start_time") + RESET_TIME - time();

	printf("�����(������%dK ʱ�䣺%dH)��\n", data_of(who, "norm") / 1000, remain_time / 3600);
	write(LINE1);
	write(TIT01);
	write(LINE1);

	foreach(string gid in elems()) {
		mapping group_data = data[gid];	//��������Ϣ
		if(group_data) {
			object_f group = child(gid);

			if(has_pre && group->size() > 0) {
				write(LINE2);		//ǰһ�����ڲ���ʾ�ָ���
				has_pre = 0;
			}
			foreach(string tid in group->elems()) {
				mapping m = group_data[tid];	//����������Ϣ
				if(m && m["ename"]) {
					string str = sprintf(FMT01,
						m["ename"],
						filter_color(m["tname"]),
						m["state"],
						m["level"] < 1 ? "-" : (m["level"] + ""),		//�Ѷȷ�Χ1-9
						m["num"],
						or2(m["remark"], "")
					);
					write(_state_color[m["state"]] + str + NOR);
					has_pre = 1;
				}
			}
		}
	}
	write(LINE1);
	return 1;
}

/*

tasks -s
����ͳ�Ʊ�
��������������������������������������������������������������������
���      �ܼ�      �ɹ�      ����      ����
��������������������������������������������������������������������
����      2130      109       94%       234334
����      1430      309       32%       43334
����      143       309       36%       43344
��ħ��ս  20        -         -         3344
�����澭  434       430       99%       942342
��������������������������������������������������������������������
*/


#define TIT02 "���      �ܼ�      �ɹ�      ����      ����\n"
#define FMT02 "%-10s%-10d%-10d%-10s%d\n"

///�г����ͳ����Ϣ
int stat(object who)
{
	int reward = 0;
	mapping data = stat_data(who);
	write(LINE1);
	write(TIT02);
	write(LINE1);
	foreach(string gid in elems()) {
		mapping m = data[gid];
		if(m) {
			printf(FMT02, 
				e2c(gid),
				m["num"],
				m["done"],
				(m["num"] ? m["done"]*100/m["num"] : 0) + "%",
				m["reward"],
			);
			reward += m["reward"];
		}
	}
	write(LINE1);
	return 1;
}

/*
���ս���ͳ�Ʊ�
��������������������������������������������������������������������
���                ����
��������������������������������������������������������������������
Ǳ��                32423
--------------------------------------------------------------------
����                23423
--------------------------------------------------------------------
�����Ṧ            1440
����                96
������½�          1699
����ж��֮��  	    1524
��ɥ��              48
--------------------------------------------------------------------
��ò                7
����                8
����                12
����                5
--------------------------------------------------------------------
����                6575
--------------------------------------------------------------------
��ѫ                234
��������������������������������������������������������������������
*/

#define TIT03 "���                ����\n"
#define FMT03 "%-20s%d\n"

private void _show_item(string item, int value) {
	printf(FMT03, e2c(item), value);
}

//����ϸ��
int gain(object who, string gid)
{
	int has_pre = 0;
	mapping data = data_of(who, "stat/" + gid + "/gain");

	if(data) {
		write(e2c(gid) + "��������ͳ�ƣ�\n");
		write(LINE1);
		write(TIT03);
		write(LINE1);

		foreach(string id, mixed value in data) {
			if(has_pre)	write(LINE2);
			if(mapp(value)) {
				foreach(string k, int v in value) {
					_show_item(k, v);
				}
			} else {
				_show_item(id, value);
			}
			has_pre = 1;
		}
		write(LINE1);
	} else {
		write("ָ������𲻴��ڡ�\n");
	}
	return 1;
}

