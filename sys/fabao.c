// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

#define PROP			XYJ_X"/fabao"		//��������
#define ELEMS			"elems"
#define FABAOS			(PROP ELEMS)		//��������

/*

��ҷ����ţ�
- sn					��һ�����������к�
- elems					��������
	- sn					�������к�
	- id					�������id
	- name					��������
	- exp					������exp������������/��


����Ч����Ѫ��������

�ɼ������з���

����Ч

��Ϸ����ŵ㣬����Я����ȱ�㣬����

*/

void create()
{
	seteuid(getuid());
}

//��ѯĿ��ķ�����Ϣ
varargs mixed query(object who, string prop)
{
	mapping m = DB->query_map(who, PROP);
	if(!m[ELEMS]) m[ELEMS] = ({});
	return prop ? m[prop] : m;
}

//��������
int query_amount(object who)
{
	return sizeof(query(who, ELEMS));
}

//��ָ��������Ϣ
mapping find(object who, int sn)
{
	foreach(mapping m in query(who, ELEMS)) {
		if(m["sn"] == sn) return m;
	}
	return 0;
}

//��ȡ���кŶ�Ӧ�ķ������
mapping sn_index(object who, int sn)
{
	mapping* arr = query(who, ELEMS);
	for(int i = 0; i < sizeof(arr); ++i) {
		if(arr[i]["sn"] == sn) return i;
	}
	return -1;
}


//��Ŀ������һ�����������ط������к�
int add(object who, string id, string name, int exp)
{
	mapping m = query(who);
	m[ELEMS] += (["id" : id, "name" : name, "exp" : exp, "sn" : m["sn"] ]);
	return m["sn"]++;	
}

//ȥ��һ������
void del(object who, int sn)
{
	mapping m = query(who);
	mapping fabao = find(who, sn);
	m[ELEMS]
}

//����һ������(����Ž���¯����)
varargs void disable(object who, int sn, string msg)
{
	mapping m = find(who, sn);
	if(m) m["disable"] = "<" + or2(msg, "����") + ">";
}

//����һ������
void enable(object who, int sn)
{
	mapping m = find(who, sn);
	if(m) m["disable"] = 0;
}


//�г����з���
void list(object who)
{
	mapping* arr = query(who, ELEMS);
	write("���з�����\n");
	for(int i = 0; i < sizeof(arr); ++i) {
		printf("%2d:   %s\n", i, arr[i]["name"]);
	}
}

//���㷨���ļ�Ȩ�ͣ�
int wei_sum(object who)
{
	mapping* arr = query(who, ELEMS);
	int s = 0;
	foreach(mapping m in arr) {
		s += 0;
	}
	return s;
}

//ȡ������
object get(object who, int index)
{
	mapping* arr = query(who, FABAOS);
	object ob;	
	if(index < sizeof(arr)) {
		mapping m = arr[index];
		ob = who->query_temp(PROP + m["sn"]);
		if(!ob) {	
			ob = new(__DIR__ + "fabao/" + m["id"]);
			ob->to_owner(who, m);
		}
	}
	return ob;
}

//���𷨱�
void put(object who, object fabao)
{
	destruct(fabao);
}

//Я��һ������������NPC
varargs object carry(object who, string id, string name, int exp)
{
	int index = query_amount(who);
	add(who, id, name, or2(exp, 3*M));
	return get(who, index);
}

