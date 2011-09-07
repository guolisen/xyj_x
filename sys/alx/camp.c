// by firefox 11/21/2009
// ��Ӫ���

#include <xyj_x.h>
#include "alx.h"

#define CAMP_ID					"alx_camp"


//ȷ��Ŀ����Ӫ
int camp_id(object ob)
{
	return objectp(ob) ? ob->query_temp(CAMP_ID) : 0;
}

//�ж���Ŀ���Ƿ�ͬ��Ӫ
int camp_same(object ob1, object ob2)
{
	return ob1 && ob2 && (camp_id(ob1) == camp_id(ob2));
}

//ȷ��Ŀ����Ӫ
int set_camp(object ob, int c)
{
	ob->set_temp(CAMP_ID, c);
	return 1;
}

//������Ӫ
int camp_opp(int camp)
{
	return camp ^ 3;
}

//��Ӫbuff
mapping camp_buff(object who)
{
	return BUFF->find(who, CAMP_ID);
}

//ĳ��Ӫռ�챾��
void camp_occupy(object flag, int camp, string color)
{	
	mapping flag_buff = ([
		"id"		: CAMP_ID,
		"name"		: color + "ռ��"NOR,
		"comment"	: "�����ҵĵ��̡�",
		"temp"		: ([ CAMP_ID	: camp ]),
		"replace"	: ([ "name"		: color + "����"NOR ]),
	]);
	BUFF->remove2(flag, CAMP_ID);
	BUFF->add(flag, flag_buff);
}

//��ʼ��
void camp_init()
{
	_camps[XIAN]["users"] = ({});
	_camps[MO]["users"] = ({});
}

//��Ӫ��
string camp_name(mapping camp)
{
	return camp["color"] + camp["name"] + NOR;
}


//����Ӫ����
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

//��Ŀ��������Ӫbuff
mapping camp_add_buff(object who, mapping camp)
{
	string title = camp["color"] + filter_color(who->query("title")) + NOR;		
	return BUFF->add(who, ([
		"id"		: CAMP_ID,
		"name"		: camp_name(camp),
		"attr"		: 2,					//����buff
		"comment"	: "��Ŀ�������" + camp["name"] + "��",
		"temp"		: ([ CAMP_ID	: camp["index"] ]),
		"replace"	: ([ "title"	: title ]),
		"camp"		: camp["index"],
		"color"		: camp["color"],])
	);
}


mapping _ip2camp;				//ip����Ӫ
mapping _ip2ids;				//ip��id��

private void camp_check_(mapping camp)
{
	object* users = ({}) + camp["users"];

	foreach(object who in users) {
		if(who) {// && !wizardp(who)) {
			string ip = query_ip_number(who);
			int ip_camp = _ip2camp[ip];

			if(!ip) continue;

			if(ip_camp && ip_camp != camp["index"]) {
				tell_object(who, HIR"\n���Ѿ��ӱ�IP�����˲�ͬ��Ӫ���㱻���顣\n"NOR);
				camp_leave(who);
				continue;
			}
			if(_ip2ids[ip] >= ID_PER_IP) {
				tell_object(who, HIR"\n��IP����ս����ID�Ѿ��ﵽ���ޣ��㱻���顣\n"NOR);
				camp_leave(who);
				continue;
			}
			//��¼ip����Ӫ
			_ip2camp[ip] = camp["index"];
			_ip2ids[ip]++;
		}
	}
	reset_eval_cost();
}

//���ͬip��¼����id�����¼��ͬ��Ӫ
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


//��Ҽ�����Ӫ
void camp_join(object who, mapping camp)
{
	camp["users"] += ({ who });

	help_record_top(who);

	//״̬
	HP->full(who);
	BUFF->clear(who);
	HP->full(who);

	score_clear(who);
	score_add(who, "mp", PULSE);
		
	camp_add_buff(who, camp);
	tell_object(who, HIW"һ��ǿ����ҫ���㣬���������۾���ʱ�򣬷����Լ��Ѿ�����ʨ���롣\n"NOR);
	who->move(MAP->random_room1());

	reset_eval_cost();
}

//�뿪��Ӫ
void camp_leave(object who)
{
	int c;
	if(who && (c = camp_id(who))) {

		_camps[c]["users"] -= ({ who });

		room_get_out(who);
		reset_eval_cost();
	}
}

//֪ͨ
void camp_msg(mapping camp, string msg)
{
	foreach(object who in camp["users"]) {
		if(who) tell_object(who, msg + "\n");
	}
}


//������Ҽ�����Ӫ
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



