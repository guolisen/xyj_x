// by firefox 11/21/2009
// 阵营相关

#include <xyj_x.h>
#include "alx.h"

#define CAMP_ID					"alx_camp"


//确定目标阵营
int camp_id(object ob)
{
	return objectp(ob) ? ob->query_temp(CAMP_ID) : 0;
}

//判断两目标是否同阵营
int camp_same(object ob1, object ob2)
{
	return ob1 && ob2 && (camp_id(ob1) == camp_id(ob2));
}

//确定目标阵营
int set_camp(object ob, int c)
{
	ob->set_temp(CAMP_ID, c);
	return 1;
}

//对立阵营
int camp_opp(int camp)
{
	return camp ^ 3;
}

//阵营buff
mapping camp_buff(object who)
{
	return BUFF->find(who, CAMP_ID);
}

//某阵营占领本旗
void camp_occupy(object flag, int camp, string color)
{	
	mapping flag_buff = ([
		"id"		: CAMP_ID,
		"name"		: color + "占领"NOR,
		"comment"	: "这是我的地盘。",
		"temp"		: ([ CAMP_ID	: camp ]),
		"replace"	: ([ "name"		: color + "大旗"NOR ]),
	]);
	BUFF->remove2(flag, CAMP_ID);
	BUFF->add(flag, flag_buff);
}

//初始化
void camp_init()
{
	_camps[XIAN]["users"] = ({});
	_camps[MO]["users"] = ({});
}

//阵营名
string camp_name(mapping camp)
{
	return camp["color"] + camp["name"] + NOR;
}


//按阵营分组
mapping camp_group(object* users)
{
	mapping groups = ([]);
	foreach(object who in users) {
		int c = camp_id(who);
		if(c && userp(who)) {			
			if(!groups[c]) groups[c] = ({});
			groups[c] += ({ who });
		}
	}
	return groups;
}

//给目标增加阵营buff
mapping camp_add_buff(object who, mapping camp)
{
	string title = camp["color"] + filter_color(who->query("title")) + NOR;		
	return BUFF->add(who, ([
		"id"		: CAMP_ID,
		"name"		: camp_name(camp),
		"attr"		: 2,					//隐藏buff
		"comment"	: "该目标归属于" + camp["name"] + "。",
		"temp"		: ([ CAMP_ID	: camp["index"] ]),
		"replace"	: ([ "title"	: title ]),
		"camp"		: camp["index"],
		"color"		: camp["color"],])
	);
}


mapping _ip2camp;				//ip到阵营
mapping _ip2ids;				//ip到id数

private void camp_check_(mapping camp)
{
	object* users = ({}) + camp["users"];

	foreach(object who in users) {
		if(who) {// && !wizardp(who)) {
			string ip = query_ip_number(who);
			int ip_camp = _ip2camp[ip];

			if(!ip) continue;

			if(ip_camp && ip_camp != camp["index"]) {
				tell_object(who, HIR"\n你已经从本IP加入了不同阵营，你被退组。\n"NOR);
				camp_leave(who);
				continue;
			}
			if(_ip2ids[ip] >= ID_PER_IP) {
				tell_object(who, HIR"\n该IP加入战斗的ID已经达到上限，你被退组。\n"NOR);
				camp_leave(who);
				continue;
			}
			//记录ip和阵营
			_ip2camp[ip] = camp["index"];
			_ip2ids[ip]++;
		}
	}
	reset_eval_cost();
}

//检查同ip登录过多id，或登录不同阵营
void camp_check_ip()
{
	_ip2camp = ([]);
	_ip2ids = ([]);

	if(random(2)) {
		camp_check_(_camps[XIAN]);
		camp_check_(_camps[MO]);
	} else {
		camp_check_(_camps[MO]);
		camp_check_(_camps[XIAN]);
	}
}


//玩家加入阵营
void camp_join(object who, mapping camp)
{
	camp["users"] += ({ who });

	help_record_top(who);

	//状态
	HP->full(who);
	BUFF->clear(who);
	HP->full(who);

	score_clear(who);
	score_add(who, "mp", PULSE);
		
	camp_add_buff(who, camp);
	tell_object(who, HIW"一道强光照耀着你，当你睁开眼睛的时候，发现自己已经来到狮驼岭。\n"NOR);
	who->move(MAP->random_room1());

	reset_eval_cost();
}

//离开阵营
void camp_leave(object who)
{
	int c;
	if(who && (c = camp_id(who))) {

		_camps[c]["users"] -= ({ who });

		room_get_out(who);
		reset_eval_cost();
	}
}

//通知
void camp_msg(mapping camp, string msg)
{
	foreach(object who in camp["users"]) {
		if(who) tell_object(who, msg + "\n");
	}
}


//遍历玩家加入阵营
void camp_accept_all()
{
	mapping _npc2camp = (["wenshu pusa" : XIAN, "qingshi daiwang" : MO]);

	foreach(object who in children("/obj/user")) {
		if(!camp_id(who)) {			
			int id = _npc2camp[who->query_temp("accept")];
			if(id) {
				camp_join(who, _camps[id]);
				who->set_temp("accept", 0);
			}
		}
	}
}



