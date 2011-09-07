// by firefox 04/10/2010
// q4����ģ�壬������������find��give��ask��kill

#include <xyj_x.h>
#include "tdb.h"

inherit TT_BASE;


#define AUTO_TAKE		"$N��$n��������%s����Ͻ����ֽӹ�ȥ��\n"
#define INDEX_DELTA		20			//��������

int _base_reward = 200;				//��������
int _index_reward = 400;			//������صĽ����������exp����
int _level_reward = 400;			//�ȼ���ؽ�����������level����


/********************************��׼�ӿ�***********************************/

//�������
int init_player(object employer, object who)
{
	if (!same_env(employer, who) || !employer->visible(who)) return 0;
	else {
		mapping msg = get_msg(employer);
		mapping m = data_of(who);

		if(m["state"] != "����") return 0;

		if(m["type"] == "find") {
			object ob = UTIL->present2(m["tname"], m["tid"], who);
		
			if(!ob || !ob->query("no_give")) 
				return 0;

			msvx(AUTO_TAKE, employer, who, m["tname"]);
			done(who);
			msvx(msg["done"], employer, who, m["tname"], or2(m["sth"], m["oname"]));
			destruct1(ob);
		}
	}
}

//������Ʒ
int accept_object(object employer, object who, object ob)
{
	mapping msg = get_msg(employer);
	mapping m = data_of(who);

	if(m["state"] != "����") return 0;
	
	if(m["tname"] != ob->query("name")) {
		msvx(msg["name_err"], employer, who, m["tname"], ob->query("name"));
		return 0;
	}
	if(m["tid"] != ob->query("id")) {
		msvx(msg["id_err"], employer, who, m["tname"], m["tid"], ob->query("id"));
		return 0;
	}
	
	done(who);
	msvx(msg["done"], employer, who, m["tname"], or2(m["sth"], m["oname"]));

	destruct1(ob);
	return 1;
}

/********************************ģ���麯��***********************************/

//������
void new_task(object who, mapping task)
{
	//���ݾ���ѡ��һ������
	
	mapping data = tdb_data(who);						//�������ݿ�
	int* keys = tdb_keys(who);
	int total = sizeof(keys);

	int exp = max2(1, eff_dx(who));
	int index = MATH->find_rang(keys, exp);
	
	index = total > 20 ? (index + INDEX_DELTA) : total;
	index = random(index);
	index = truncate(index, 0, total - 1);

	//��������
	{
		mixed* arr = data[keys[index]];

		task["type"]	= arr[0];
		task["tname"]	= arr[1];
		task["tid"]		= arr[2];
		task["remark"]	= "";
	
		if(task["type"] == "ask") {
			task["sth"]		= arr[3];
			task["remark"]	= arr[3];
			task["return"]	= "�ã������Ͼ�ȥ׼����\n";
		}
		else if(task["type"] == "give") {
			string id, name;
			if(sscanf(arr[3], "%s(%s)", name, id) == 2) {
				task["oid"]		= id;
				task["oname"]	= name;
				task["remark"]	= name;
			} else {
				task["remark"]	= "��������";
			}
		}
	}
	//�����Ѷ�
	{
		int lvl = 9 * keys[index] * 10 / exp / 12;	//120%ʱ�Ѷ���9
		task["level"]	= truncate(lvl, 1, 9);
	}
	//���㽱��������+����+�Ѷ�
	{
		int reward = _base_reward 
			+ _index_reward * (1 + index) / sizeof(keys)
			+ _level_reward * task["level"] / 9;
		task["reward"]	= reward;
	}
}

/********************************Q4����***********************************/

//��������Լ�����ϵ��
int init_param(int norm, int base_reward, int index_reward, int level_reward)
{
	init_prop(norm);
	_base_reward = base_reward;
	_index_reward = index_reward;
	_level_reward = level_reward;
}

/********************************���Ժ���***********************************/
object _npc, _obj;

//���Ժ���
int debug(object employer, object who, string arg)
{
	mapping m = data_of(who);
	string t = m["type"];
	
	if(!t) return 1;
	if(!_npc) _npc = new_to("/d/city/npc/girl", who);
	if(!_obj) _obj = new_to("/d/city/obj/jitui", who);

	if(t == "find") _obj->set_name(m["tname"], ({ m["tid"] }));
	else  _npc->set_name(m["tname"], ({ m["tid"] }));

	if(t == "give") _obj->set_name(m["oname"], ({ m["oid"] }));
	tell_object(who, "\nOK.\n");
	return 1;
}
