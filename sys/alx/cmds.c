// by firefox 11/21/2009

#include "alx.h"

#define BG_NO_CMD		"alx_no_cmd"

int* _cmd_top_time = ({0, 0});						//ͳ�����а��ʱ��
mixed* _cmd_top_text = ({0, 0});					//���а������

private int start_cmd_cd(int duration)
{
	object who = this_player();
	if(who && userp(who) && !cd_start(who, "cmd", duration)) return 0;
	return 1;
}

//�г�ս���ɼ�
string* list_score(object* users, int history)
{
	string* title = ({ 
		"��ħ���" + (history ? "��ʷ" : "��ǰ") + "ս�����а�:\n"
		LINE1
		"   ����   ���                ��ɱ ��ɱ ���� ͻϮ ���� ս��(��)\n"
		LINE1
	});
	int n = min2(MAX_LIST, sizeof(users));
	int m = sizeof(users) - n;
	string* lines = allocate(n);

	for(int i = 0; i < n; ++i) {
		string color = _camps[camp_id(users[i])]["color"];
		string family = FAMILY->short(users[i]);		//���ɼ��
		mapping score = score_entire(users[i], history);
		lines[i] = sprintf(color + "%-3d%-7s%-20s%-5d%-5d%-5d%-5d%-5d%-5d\n"NOR,
			i + 1,
			family ? family : "����",
			name_id(users[i]),
			score["kill"],
			score["m_kill"],
			score["die"],
			score["occupy"],
			score["repel"],
			score["exp"] / 1000
		);
	}
	return title + lines + ({ LINE1, "�˴���ȥ" + m + "�����...\n" });
}

//�г�ս���ɼ�
int bg_camp()
{
	printf("��Ӫս��(ʱ��:%d/%d,��Դ����:%d):\n", time() - _start_time, MAX_TIME, MAX_RES / 100);
	printf(LINE1);
	printf("����  ����                ���  ��Դ  ս��(��)\n");
	printf(LINE1);
	for(int i = 1; i < sizeof(_camps); ++i) {
		//ͳ����Ӫ�ɼ�
		string color = _camps[i]["color"];
		mapping camp = _camps[i];

		printf(color + "%-6d%-20s%-6d%-6d%-6d\n"NOR,
			i,
			camp["name"],
			sizeof(camp["users"]),
			camp["res"] / 100,
			camp["exp"] / 1000,
		);
	}
	printf(LINE1);
	return 1;
}
//�г�ս���ɼ�
int bg_fort()
{
	printf(LINE1);
	printf("�ݵ�����\n");
	printf(LINE1);
	foreach(object flag in MAP->flags()) {
		int c = camp_id(flag);
		printf("  %-24s%-16s\n",
			environment(flag)->query("short"),
			c ? camp_name(_camps[c]) : "������",
		);
	}
	printf(LINE1);
}

private int cmp_kill0(object user1, object user2)
{
	reset_eval_cost();
	return score_query(user1, "kill") < score_query(user2, "kill") ? 0 : -1;
}

private int cmp_kill1(object user1, object user2)
{
	reset_eval_cost();
	return score_query(user1, "kill", 1) < score_query(user2, "kill", 1) ? 0 : -1;
}

//���ɼ�����user
varargs object* sort_user(string cmp, int camp)
{
	object* users = ({});
	for(int i = 1; i < sizeof(_camps); ++i) {
		_camps[i]["users"] -= ({ 0 });
		users += _camps[i]["users"];
	}
	return sort_array(users, cmp);
}

//�г�ս���ɼ�
private int bg_top(int history)
{
	if(!start_cmd_cd(10)) {
		printf(HIR"\n�벻ҪƵ��ʹ��ͳ�����\n"NOR);
		return 1;
	}
	if(time() > _cmd_top_time[history] + 10) {
		_cmd_top_time[history] = time();
		_cmd_top_text[history] = list_score(sort_user("cmp_kill" + history), history);
	}
	foreach(string s in _cmd_top_text[history]) {
		write(s);
	}
	return 1;
}

//������Ϣ
private int bg_talk(object me, string msg)
{
	mapping c = _camps[camp_id(me)];
	if(c) {
		string channel = c["color"] + "��" + c["name"] + "��" + name_id(me) + "��";
		camp_msg(c, channel + (msg ? msg : "...") + NOR);
	}
	else tell_object(me, "�㲢û�м���ս��\n"NOR);
	return 1;
}

//�뿪ս��/����
private int bg_afk(object me)
{
	int camp = camp_id(me);
	if(camp) {
		rumor(name_id(me) + "�������ӣ��뿪" + TITLE + "��\n");
		camp_leave(me);
	}
}

//����
private int bg_help()
{
	write(TITLE + "��bg�����÷���\n"
		"    bg msg                          ���������ѷ�����Ϣ\n"
		"    bg -[t | top]                   �г����ս�����а�\n"
		"    bg -[h | history]               �г���ʷս�����а�\n"
		"    bg -[c | camp]                  �г���Ӫս�����а�\n"
		"    bg -[f | fort]                  �г��ݵ�Ĺ������\n"
		"    bg -afk                         �˳�ս�����뿪ս��\n"
	);
	return 1;
}


//����
int cmd_bg(string arg)
{
	object me = this_player();
	string str;
	if(!arg) return bg_help();
	if(_status != BATTLE) return notify_ok("ս����δ��ʼ��\n");
	if(sscanf(arg, "-%s", str) == 1) {		
		if(str == "t" || str == "top") bg_top(0);
		else if(str == "c" || str == "camp") bg_camp();
		else if(str == "f" || str == "fort") bg_fort();
		else if(str == "h" || str == "history") bg_top(1);
		else if(str == "afk") bg_afk(me);
		else bg_help();
	} else {
		bg_talk(me, arg);
	}
	return 1;
}

//ս����ͼ
int cmd_show_map(string arg)
{
	if(!start_cmd_cd(3)) {
		printf(HIR"\n�벻ҪƵ��ʹ�õ�ͼ���\n"NOR);
		return 1;
	}
	
	printf(TITLE + "��ͼ��\n");
	MAP->show(_player);
	return 1;
}

//�㲥�ɼ�
void broadcast_score(object* users)
{
	int history = 0;
	string* lines = list_score(users, history);
	foreach(object user in users) {
		foreach(string s in lines) {
			tell_object(user, s);
		}
		reset_eval_cost();
	}
}


