// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

#define PROP			XYJ_X"/fabao"		//法宝属性
#define ELEMS			"elems"
#define FABAOS			(PROP ELEMS)		//法宝数组

/*

玩家法宝信：
- sn					下一个法宝的序列号
- elems					法宝数组
	- sn					法宝序列号
	- id					法宝类别id
	- name					法宝名称
	- exp					法宝的exp，决定法宝攻/防


有特效，吸血，反馈毒

可祭出，有法术

无特效

组合法宝优点，方便携带，缺点，不灵活。

*/

void create()
{
	seteuid(getuid());
}

//查询目标的法宝信息
varargs mixed query(object who, string prop)
{
	mapping m = DB->query_map(who, PROP);
	if(!m[ELEMS]) m[ELEMS] = ({});
	return prop ? m[prop] : m;
}

//法宝数量
int query_amount(object who)
{
	return sizeof(query(who, ELEMS));
}

//找指定法宝信息
mapping find(object who, int sn)
{
	foreach(mapping m in query(who, ELEMS)) {
		if(m["sn"] == sn) return m;
	}
	return 0;
}

//获取序列号对应的法宝序号
mapping sn_index(object who, int sn)
{
	mapping* arr = query(who, ELEMS);
	for(int i = 0; i < sizeof(arr); ++i) {
		if(arr[i]["sn"] == sn) return i;
	}
	return -1;
}


//给目标增加一个法宝，返回法宝序列号
int add(object who, string id, string name, int exp)
{
	mapping m = query(who);
	m[ELEMS] += (["id" : id, "name" : name, "exp" : exp, "sn" : m["sn"] ]);
	return m["sn"]++;	
}

//去掉一个法宝
void del(object who, int sn)
{
	mapping m = query(who);
	mapping fabao = find(who, sn);
	m[ELEMS]
}

//禁用一个法宝(比如放进熔炉煅烧)
varargs void disable(object who, int sn, string msg)
{
	mapping m = find(who, sn);
	if(m) m["disable"] = "<" + or2(msg, "禁用") + ">";
}

//启用一个法宝
void enable(object who, int sn)
{
	mapping m = find(who, sn);
	if(m) m["disable"] = 0;
}


//列出所有法宝
void list(object who)
{
	mapping* arr = query(who, ELEMS);
	write("所有法宝：\n");
	for(int i = 0; i < sizeof(arr); ++i) {
		printf("%2d:   %s\n", i, arr[i]["name"]);
	}
}

//计算法宝的加权和，
int wei_sum(object who)
{
	mapping* arr = query(who, ELEMS);
	int s = 0;
	foreach(mapping m in arr) {
		s += 0;
	}
	return s;
}

//取出法宝
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

//收起法宝
void put(object who, object fabao)
{
	destruct(fabao);
}

//携带一个法宝，用于NPC
varargs object carry(object who, string id, string name, int exp)
{
	int index = query_amount(who);
	add(who, id, name, or2(exp, 3*M));
	return get(who, index);
}

