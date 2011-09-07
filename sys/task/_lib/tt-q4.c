// by firefox 04/10/2010
// q4任务模板，包括四类任务：find，give，ask，kill

#include <xyj_x.h>
#include "tdb.h"

inherit TT_BASE;


#define AUTO_TAKE		"$N见$n手上拿着%s，便赶紧伸手接过去。\n"
#define INDEX_DELTA		20			//索引浮动

int _base_reward = 200;				//基本奖励
int _index_reward = 400;			//索引相关的奖励，随玩家exp提升
int _level_reward = 400;			//等级相关奖励，随任务level提升


/********************************标准接口***********************************/

//遇见玩家
int init_player(object employer, object who)
{
	if (!same_env(employer, who) || !employer->visible(who)) return 0;
	else {
		mapping msg = get_msg(employer);
		mapping m = data_of(who);

		if(m["state"] != "进行") return 0;

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

//接受物品
int accept_object(object employer, object who, object ob)
{
	mapping msg = get_msg(employer);
	mapping m = data_of(who);

	if(m["state"] != "进行") return 0;
	
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

/********************************模板虚函数***********************************/

//新任务
void new_task(object who, mapping task)
{
	//根据经验选择一个任务
	
	mapping data = tdb_data(who);						//任务数据库
	int* keys = tdb_keys(who);
	int total = sizeof(keys);

	int exp = max2(1, eff_dx(who));
	int index = MATH->find_rang(keys, exp);
	
	index = total > 20 ? (index + INDEX_DELTA) : total;
	index = random(index);
	index = truncate(index, 0, total - 1);

	//设置任务
	{
		mixed* arr = data[keys[index]];

		task["type"]	= arr[0];
		task["tname"]	= arr[1];
		task["tid"]		= arr[2];
		task["remark"]	= "";
	
		if(task["type"] == "ask") {
			task["sth"]		= arr[3];
			task["remark"]	= arr[3];
			task["return"]	= "好，我马上就去准备。\n";
		}
		else if(task["type"] == "give") {
			string id, name;
			if(sscanf(arr[3], "%s(%s)", name, id) == 2) {
				task["oid"]		= id;
				task["oname"]	= name;
				task["remark"]	= name;
			} else {
				task["remark"]	= "错误任务";
			}
		}
	}
	//计算难度
	{
		int lvl = 9 * keys[index] * 10 / exp / 12;	//120%时难度是9
		task["level"]	= truncate(lvl, 1, 9);
	}
	//计算奖励：基本+道行+难度
	{
		int reward = _base_reward 
			+ _index_reward * (1 + index) / sizeof(keys)
			+ _level_reward * task["level"] / 9;
		task["reward"]	= reward;
	}
}

/********************************Q4函数***********************************/

//设置配额以及奖励系数
int init_param(int norm, int base_reward, int index_reward, int level_reward)
{
	init_prop(norm);
	_base_reward = base_reward;
	_index_reward = index_reward;
	_level_reward = level_reward;
}

/********************************调试函数***********************************/
object _npc, _obj;

//调试函数
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
