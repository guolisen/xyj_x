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

mapping _records	= ([]);		//记录投票信息 (投票者 : (被选者 : 原因))
mapping _ip2id		= ([]);		//ip => id 对应表
mapping _id2ip		= ([]);		//id => ip 对应表
mapping _marks		= ([]);		//标记投票id的所有同ip的id
mapping _candidates = ([]);		//预设的候选项

int _max_num		= 10;		//最大投票数
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
string _line		= "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";

//检查玩家投票资格，没有资格则返回失败原因
private string fail_msg(object who)
{
	string id = getuid(who);
	string ip = query_ip_number(who);

	int age_limit	= 18;
	int time_limit	= (age_limit - 14) * 3600 * 24;
	int exp_limit	= 50000;

	if(_vote_closed) return "投票已经截止\n";

	if(!wizardp(who)) {
		if (who->query("age") < age_limit || time() - who->query("birthday") < time_limit)
			return "你年龄不满" + chinese_number(age_limit)+ "，没有投票权\n";
		if(_marks[id])
			return "同IP用户『" + capitalize(_marks[id]) + "』已经投过票.\n";
		if(_ip2id[ip] && _ip2id[ip] != id)
			return "同IP用户『" + capitalize(_ip2id[ip]) + "』已经投过票\n";
		//继续添加检查条件，比如
		if (who->query("combat_exp") + who->query("daoxing") < exp_limit)
			return "你经验不足" + chinese_number(exp_limit)+ "，没有投票权\n";
	}
	//标记id/ip
	_ip2id[ip] = id;
	_id2ip[id] = ip;
	
	//把和投票id同ip的所有id做标记，就算他们换ip也不能在投票了
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
	set_name("投票箱", ({ "ballot box", "box" }) );
	set_weight(2500);

	set("unit", "个");
	set("no_get", 1);
	set("long",	_dest);
	set("value", 100);

	setup();
}



string long()
{
	string dest = "这是一个投票箱，可用来("HIC"bbhelp"NOR")对泥潭某个议题进行投票表决的。\n";
	if(_dest) dest += "上面歪歪扭扭的写着：\n" + _dest;

	if(sizeof(_candidates)) {
		string* k = keys(_candidates);
		dest += "\n";
		dest += _line;
		for(int i = 0; i < sizeof(k); ++i) {
			dest += sprintf("%-2s: %s\n", k[i], _candidates[k[i]]);
		}
		dest += _line;
		dest += "请大家在列出的选项中选择，只需输入选项前面的代号即可。\n"NOR;
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
		"投票箱可以使用下列命令：\n"
		"    bbvote sb.|sth. [for reason]    为某人或某事投票及理由\n"
		"    bbclear                         擦去自己的投票信息\n"
		"    bblist [sb.]                    列出某人的投票信息\n"
		"    bblist -t sb.|sth.              列出针对某人或某事的投票\n"
		"    bbstat                          列出此次投票的统计信息\n"
		"    bbget                           领取投票奖励\n"
		"巫师专用命令:\n"
		"    bbclear [sb.|all]               擦去某人或所有投票信息\n"
		"    bbset -t title                  设置投票议题\n"
		"    bbset -m max_num                设置投票上限(默认10)\n"
		"    bbset -d dest                   设置议题的说明，投票要求\n"
		"    bbset -r account obj            设置投票奖励，投票截止\n"
		"    bbset -c code candidate         设置预设候选人/项\n"
		"    bbset -c code                   删除候选人/项\n"
		"    bbclose                         投票截止\n"
		"注意事项：\n"
		"    1.必须用自己" HIC "最活跃ID" NOR "投票，否则可能无效\n"
		"    2.每活人仅限用一ID投票，违者" HIR "重罚\n" NOR
		"    3.如果是指定候选人/候选项的投票，请不要乱发挥\n"
		"    4.投票时注明缘由，可能得到更多人认同甚至额外奖励\n"
		"    5.如果wiz设定候选人/项，则玩家只能从中选择\n"
		"    6.领取投票奖励时，注意身上空位和负重，丢失不赔，过期不候\n"
		);
	return 1;
}


//投票
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
	if(sizeof(list) >= _max_num) return notify_fail("你投的票数太多了\n");

	if(!arg) return notify_fail("指令格式：bbvote <某人> [for <原因>]\n");
	if(sscanf(arg, "%s for %s", candidate, reason)!=2 ) {
		candidate = arg;
		reason = "";
	}

	if(sizeof(_candidates)) {
		candidate = _candidates[candidate];
		if(!candidate) return notify_fail("你只能从预设选项中选择\n");
	}

	list[candidate] = reason;

	printf("你投了『%s』一票", candidate);
	if(reason == "") {
		printf("\n");
	} else {
		printf("，因为：%s\n", _records[id][candidate]);
	}
	return 1;
}

int do_clear (string arg)
{
	string id = getuid(this_player ());

	if(_vote_closed) return notify_fail("投票已经截止\n");

	if(arg) {
		if(wizardp(this_player())) {
			id = arg;
		} else {
			return notify_fail("只有wiz能擦除别人的投票信息\n");
		}
	}
	if(id == "all") {
		_records	= ([]);
		_id2ip = ([]);
		_ip2id = ([]);
		_marks = ([]);
		printf("你擦除了全部投票信息\n");
	} else {
		map_delete(_records, id);
		map_delete(_ip2id, _id2ip[id]);
		map_delete(_id2ip, id);
		_marks = filter(_marks, (: $2 != $3 :), id);
		printf("你擦除了『%s』的投票信息\n", capitalize(id));
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
			if(!id) return notify_fail("你只能从预设选项中选择\n");
		}
		printf("『%s』由以下玩家投票支持:\n", capitalize(id));
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
		if(!list) return notify_fail("无相关的投票信息\n");

		k = keys(list);

		printf("『%s』投票选举如下:\n", capitalize(id));
		printf(_line);
		for(int i = 0; i< sizeof(k); i++) {
			printf("%2d: %-20s %s\n", i + 1, capitalize(k[i]), list[k[i]]);
		}
		printf(_line);
	}
	return 1;
}


	
mapping _votes_tab = ([]);	//id票数列表
//比较两个id票数
private int cmp_votes(string id1, string id2)
{
	return _votes_tab[id1] < _votes_tab[id2] ? 0 : -1;
}

int do_stat (string arg)
{
	string* candidates;
	int total = 0;

	//计票
	_votes_tab = ([]);
	foreach(mapping list in values(_records)) {
		foreach(string id1 in keys(list)) {
			_votes_tab[id1] += 1;
			total++;
		}
	}
	//按照票数候选人排序
	candidates = sort_array(keys(_votes_tab), "cmp_votes");

	printf(HIW + _title + NOR + "投票结果如下:\n");
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

	if(!_vote_closed) return notify_fail("投票尚未截止，不能领取奖品\n");
	if(!_id2ip[getuid(who)]) return notify_fail("没有你的奖品\n");

	ob = new(_reward_ob);
	if(ob && ob->move(who)) {
		if(_reward_amount > 1) ob->set_amount(_reward_amount);
		map_delete(_id2ip, getuid(who));
		printf("你获得投票奖品:%s\n", ob->query("name"));
	}
	return 1;
}

int do_close (string arg)
{
	string msg = HIW + _title + NOR "投票截止，投票玩家可在投票箱领取投票奖品\n";
	_vote_closed = 1;
	shout(msg);
	printf(msg);
	set_name(HIR + _title + "投票箱" + NOR, ({ "ballot box", "box" }) );	
	_candidates = ([]);
	return 1;
}

int do_set (string arg)
{
	int num;
	string str, str1;
	
	if(!arg) return notify_fail("指令缺少参数\n");

	if(sscanf(arg, "-t %s", str) == 1) {
		_title = rep_color(str) + NOR;
		set_name(HIW + _title + "投票箱" + NOR, ({ "ballot box", "box" }) );
		printf("设置投票的议题是：%s，并通知玩家投票\n", _title);
		shout(HIW + _title + NOR "投票开始，玩家投票有奖\n");
	} 
	else if(sscanf(arg, "-m %d", num) == 1) {
		_max_num = num;		
		printf("设置投票的最大投票数为:%d\n", _max_num);
	}
	else if(sscanf(arg, "-d %s", str) == 1) {
		_dest = rep_color(str) + NOR;
		printf("设置了议题的说明信息\n");
	}
	else if(sscanf(arg, "-r %d %s", num, str) == 2) {
		object ob;
		_reward_amount = num;
		_reward_ob = _reward_alias[str] ? _reward_alias[str] : str;
		ob = new(_reward_ob);
		if(ob) {
			printf("设置奖品为:%s\n", ob->query("name"));
			destruct(ob);
		}
	}
	else if(sscanf(arg, "-c %s %s", str, str1) == 2) {
		_candidates[str] = rep_color(str1) + NOR;
		printf("预设候选项:%s为%s\n", str, _candidates[str]);
	} 
	else if(sscanf(arg, "-c %s", str) == 1) {	//去掉候选项
		map_delete(_candidates, str);
		printf("清除预设候选项:%s\n", str);
	} else {
		return notify_fail("指令缺少参数\n");
	}

	return 1;
}
