// by firefox  22/04/2009

#include <ansi.h>

inherit ITEM;

private string rep_color(string str)
{
	mapping tab = ([
		"$BLK$" : BLK, "$RED$" : RED, "$GRN$" : GRN, "$YEL$" : YEL, 
		"$BLU$" : BLU, "$MAG$" : MAG, "$CYN$" : CYN, "$WHT$" : WHT,
		"$HIR$" : HIR, "$HIG$" : HIG, "$HIY$" : HIY, "$HIB$" : HIB,
		"$HIM$" : HIM, "$HIC$" : HIC, "$HIW$" : HIW, "$NOR$" : NOR,
	]);

	foreach(string k, string v in tab) {
		str = replace_string(str, k, v);
	}
	return str;
}

mapping _records	= ([]);		//��¼ͶƱ��Ϣ (ͶƱ�� : (��ѡ�� : ԭ��))
mapping _ip2id		= ([]);		//ip => id ��Ӧ��
mapping _id2ip		= ([]);		//id => ip ��Ӧ��
mapping _marks		= ([]);		//���ͶƱid������ͬip��id
mapping _candidates = ([]);		//Ԥ��ĺ�ѡ��

int _max_num		= 10;		//���ͶƱ��
string _title		= "";
string _dest;

string _reward_ob	= "/obj/money/gold";
int _reward_amount	= 5;
mapping _reward_alias	= ([
	"coin"		: "/obj/money/coin",
	"silver"	: "/obj/money/silver",
	"gold"		: "/obj/money/gold",
	"cash"		: "/obj/money/thousand-cash",

	"rsg"		: "/d/obj/drug/renshen-guo",
	"pig"		: "/d/meishan/npc/pigg",
	"blade"		: "/d/obj/weapon/blade/handudao-blue",
]);

int _vote_closed	= 0;
string _line		= "������������������������������������������������������������\n";

//������ͶƱ�ʸ�û���ʸ��򷵻�ʧ��ԭ��
private string fail_msg(object who)
{
	string id = getuid(who);
	string ip = query_ip_number(who);

	int age_limit	= 18;
	int time_limit	= (age_limit - 14) * 3600 * 24;
	int exp_limit	= 50000;

	if(_vote_closed) return "ͶƱ�Ѿ���ֹ\n";

	if(!wizardp(who)) {
		if (who->query("age") < age_limit || time() - who->query("birthday") < time_limit)
			return "�����䲻��" + chinese_number(age_limit)+ "��û��ͶƱȨ\n";
		if(_marks[id])
			return "ͬIP�û���" + capitalize(_marks[id]) + "���Ѿ�Ͷ��Ʊ.\n";
		if(_ip2id[ip] && _ip2id[ip] != id)
			return "ͬIP�û���" + capitalize(_ip2id[ip]) + "���Ѿ�Ͷ��Ʊ\n";
		//������Ӽ������������
		if (who->query("combat_exp") + who->query("daoxing") < exp_limit)
			return "�㾭�鲻��" + chinese_number(exp_limit)+ "��û��ͶƱȨ\n";
	}
	//���id/ip
	_ip2id[ip] = id;
	_id2ip[id] = ip;
	
	//�Ѻ�ͶƱidͬip������id����ǣ��������ǻ�ipҲ������ͶƱ��
	foreach(object user in users()) {
		string uid = getuid(user);
		if(uid != id && query_ip_number(user) == ip) {
			_marks[uid] = id;
		}
	}
	return 0;
}


void create()
{
	set_name("ͶƱ��", ({ "ballot box", "box" }) );
	set_weight(2500);

	set("unit", "��");
	set("no_get", 1);
	set("long",	_dest);
	set("value", 100);

	setup();
}



string long()
{
	string dest = "����һ��ͶƱ�䣬������("HIC"bbhelp"NOR")����̶ĳ���������ͶƱ����ġ�\n";
	if(_dest) dest += "��������ŤŤ��д�ţ�\n" + _dest;

	if(sizeof(_candidates)) {
		string* k = keys(_candidates);
		dest += "\n";
		dest += _line;
		for(int i = 0; i < sizeof(k); ++i) {
			dest += sprintf("%-2s: %s\n", k[i], _candidates[k[i]]);
		}
		dest += _line;
		dest += "�������г���ѡ����ѡ��ֻ������ѡ��ǰ��Ĵ��ż��ɡ�\n"NOR;
	}
	return dest;
}

int clean_up()
{
	return 0;
} 

void init ()
{
	add_action("do_help", "bbhelp");
	add_action("do_vote", "bbvote");
	add_action("do_clear", "bbclear");
	add_action("do_list", "bblist");
	add_action("do_stat", "bbstat");
	add_action("do_get", "bbget");

	if(wizardp(this_player())) {
		add_action("do_set", "bbset");
		add_action("do_close", "bbclose");
	}
}

int do_help (string arg)
{
	tell_object(this_player(), 
		"ͶƱ�����ʹ���������\n"
		"    bbvote sb.|sth. [for reason]    Ϊĳ�˻�ĳ��ͶƱ������\n"
		"    bbclear                         ��ȥ�Լ���ͶƱ��Ϣ\n"
		"    bblist [sb.]                    �г�ĳ�˵�ͶƱ��Ϣ\n"
		"    bblist -t sb.|sth.              �г����ĳ�˻�ĳ�µ�ͶƱ\n"
		"    bbstat                          �г��˴�ͶƱ��ͳ����Ϣ\n"
		"    bbget                           ��ȡͶƱ����\n"
		"��ʦר������:\n"
		"    bbclear [sb.|all]               ��ȥĳ�˻�����ͶƱ��Ϣ\n"
		"    bbset -t title                  ����ͶƱ����\n"
		"    bbset -m max_num                ����ͶƱ����(Ĭ��10)\n"
		"    bbset -d dest                   ���������˵����ͶƱҪ��\n"
		"    bbset -r account obj            ����ͶƱ������ͶƱ��ֹ\n"
		"    bbset -c code candidate         ����Ԥ���ѡ��/��\n"
		"    bbset -c code                   ɾ����ѡ��/��\n"
		"    bbclose                         ͶƱ��ֹ\n"
		"ע�����\n"
		"    1.�������Լ�" HIC "���ԾID" NOR "ͶƱ�����������Ч\n"
		"    2.ÿ���˽�����һIDͶƱ��Υ��" HIR "�ط�\n" NOR
		"    3.�����ָ����ѡ��/��ѡ���ͶƱ���벻Ҫ�ҷ���\n"
		"    4.ͶƱʱע��Ե�ɣ����ܵõ���������ͬ�������⽱��\n"
		"    5.���wiz�趨��ѡ��/������ֻ�ܴ���ѡ��\n"
		"    6.��ȡͶƱ����ʱ��ע�����Ͽ�λ�͸��أ���ʧ���⣬���ڲ���\n"
		);
	return 1;
}


//ͶƱ
int do_vote (string arg)
{
	object who = this_player();
	
	string id = getuid(who);
	string ip = query_ip_number(who);
	mapping list;
	string candidate;
	string reason;
	
	string msg = fail_msg(who);
	if(msg) return notify_fail(msg);

	
	if(!_records[id]) _records[id] = ([]);

	list = _records[id];
	if(sizeof(list) >= _max_num) return notify_fail("��Ͷ��Ʊ��̫����\n");

	if(!arg) return notify_fail("ָ���ʽ��bbvote <ĳ��> [for <ԭ��>]\n");
	if(sscanf(arg, "%s for %s", candidate, reason)!=2 ) {
		candidate = arg;
		reason = "";
	}

	if(sizeof(_candidates)) {
		candidate = _candidates[candidate];
		if(!candidate) return notify_fail("��ֻ�ܴ�Ԥ��ѡ����ѡ��\n");
	}

	list[candidate] = reason;

	printf("��Ͷ�ˡ�%s��һƱ", candidate);
	if(reason == "") {
		printf("\n");
	} else {
		printf("����Ϊ��%s\n", _records[id][candidate]);
	}
	return 1;
}

int do_clear (string arg)
{
	string id = getuid(this_player ());

	if(_vote_closed) return notify_fail("ͶƱ�Ѿ���ֹ\n");

	if(arg) {
		if(wizardp(this_player())) {
			id = arg;
		} else {
			return notify_fail("ֻ��wiz�ܲ������˵�ͶƱ��Ϣ\n");
		}
	}
	if(id == "all") {
		_records	= ([]);
		_id2ip = ([]);
		_ip2id = ([]);
		_marks = ([]);
		printf("�������ȫ��ͶƱ��Ϣ\n");
	} else {
		map_delete(_records, id);
		map_delete(_ip2id, _id2ip[id]);
		map_delete(_id2ip, id);
		_marks = filter(_marks, (: $2 != $3 :), id);
		printf("������ˡ�%s����ͶƱ��Ϣ\n", capitalize(id));
	}
	return 1;
}

int do_list(string arg)
{
	string id;
	mapping list;
	string *k;

	if(arg && sscanf(arg, "-t %s", id) == 1) {
		int j = 0;
		k = keys(_records);
		if(sizeof(_candidates)) {
			id = _candidates[id];
			if(!id) return notify_fail("��ֻ�ܴ�Ԥ��ѡ����ѡ��\n");
		}
		printf("��%s�����������ͶƱ֧��:\n", capitalize(id));
		printf(_line);
		for(int i = 0; i < sizeof(k); i++) {
			string reason = _records[k[i]][id];
			if(reason) {
				++j;
				printf("%2d: %-10s %s\n", j, capitalize(k[i]), reason);
			}
		}
		printf(_line);
	} else {
		id = arg;
		if(!id) id = getuid(this_player ());

		list = _records[id];
		if(!list) return notify_fail("����ص�ͶƱ��Ϣ\n");

		k = keys(list);

		printf("��%s��ͶƱѡ������:\n", capitalize(id));
		printf(_line);
		for(int i = 0; i< sizeof(k); i++) {
			printf("%2d: %-20s %s\n", i + 1, capitalize(k[i]), list[k[i]]);
		}
		printf(_line);
	}
	return 1;
}


	
mapping _votes_tab = ([]);	//idƱ���б�
//�Ƚ�����idƱ��
private int cmp_votes(string id1, string id2)
{
	return _votes_tab[id1] < _votes_tab[id2] ? 0 : -1;
}

int do_stat (string arg)
{
	string* candidates;
	int total = 0;

	//��Ʊ
	_votes_tab = ([]);
	foreach(mapping list in values(_records)) {
		foreach(string id1 in keys(list)) {
			_votes_tab[id1] += 1;
			total++;
		}
	}
	//����Ʊ����ѡ������
	candidates = sort_array(keys(_votes_tab), "cmp_votes");

	printf(HIW + _title + NOR + "ͶƱ�������:\n");
	printf(_line);

	for(int i = 0; i < sizeof(candidates); ++i) {
		string id = candidates[i];
		int votes = _votes_tab[id];
		printf("%2d: %-20s %4d (%3d%%)\n", i + 1, capitalize(id), votes, votes * 100 / total);
	}
	printf(_line);
	return 1;
}

int do_get (string arg)
{
	object who = this_player();
	object ob;

	if(!_vote_closed) return notify_fail("ͶƱ��δ��ֹ��������ȡ��Ʒ\n");
	if(!_id2ip[getuid(who)]) return notify_fail("û����Ľ�Ʒ\n");

	ob = new(_reward_ob);
	if(ob && ob->move(who)) {
		if(_reward_amount > 1) ob->set_amount(_reward_amount);
		map_delete(_id2ip, getuid(who));
		printf("����ͶƱ��Ʒ:%s\n", ob->query("name"));
	}
	return 1;
}

int do_close (string arg)
{
	string msg = HIW + _title + NOR "ͶƱ��ֹ��ͶƱ��ҿ���ͶƱ����ȡͶƱ��Ʒ\n";
	_vote_closed = 1;
	shout(msg);
	printf(msg);
	set_name(HIR + _title + "ͶƱ��" + NOR, ({ "ballot box", "box" }) );	
	_candidates = ([]);
	return 1;
}

int do_set (string arg)
{
	int num;
	string str, str1;
	
	if(!arg) return notify_fail("ָ��ȱ�ٲ���\n");

	if(sscanf(arg, "-t %s", str) == 1) {
		_title = rep_color(str) + NOR;
		set_name(HIW + _title + "ͶƱ��" + NOR, ({ "ballot box", "box" }) );
		printf("����ͶƱ�������ǣ�%s����֪ͨ���ͶƱ\n", _title);
		shout(HIW + _title + NOR "ͶƱ��ʼ�����ͶƱ�н�\n");
	} 
	else if(sscanf(arg, "-m %d", num) == 1) {
		_max_num = num;		
		printf("����ͶƱ�����ͶƱ��Ϊ:%d\n", _max_num);
	}
	else if(sscanf(arg, "-d %s", str) == 1) {
		_dest = rep_color(str) + NOR;
		printf("�����������˵����Ϣ\n");
	}
	else if(sscanf(arg, "-r %d %s", num, str) == 2) {
		object ob;
		_reward_amount = num;
		_reward_ob = _reward_alias[str] ? _reward_alias[str] : str;
		ob = new(_reward_ob);
		if(ob) {
			printf("���ý�ƷΪ:%s\n", ob->query("name"));
			destruct(ob);
		}
	}
	else if(sscanf(arg, "-c %s %s", str, str1) == 2) {
		_candidates[str] = rep_color(str1) + NOR;
		printf("Ԥ���ѡ��:%sΪ%s\n", str, _candidates[str]);
	} 
	else if(sscanf(arg, "-c %s", str) == 1) {	//ȥ����ѡ��
		map_delete(_candidates, str);
		printf("���Ԥ���ѡ��:%s\n", str);
	} else {
		return notify_fail("ָ��ȱ�ٲ���\n");
	}

	return 1;
}
