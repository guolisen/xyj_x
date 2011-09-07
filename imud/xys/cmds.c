// by firefox 10/01/2010
// 西游杀-命令处理

#include "xys.h"

int _top_time;				//top指令
string* _top_text;

mapping _kickout = ([]);	//记录踢出投票(id : 编号)

mapping _e2c = ([
	"busy"		: "自顾不暇",
	"no_cast"	: "不能施法",
	"no_wield"	: "禁用兵器",
	"sleeping"	: "睡眠",
	"no_move"	: "不能移动",
]);

//踢出某人
int do_kickout(string arg)
{
	return 1;
}

//玩家准备就绪后，由主公启动游戏
int do_start(string arg)
{
	//判断是否为主公

	return start();
}


#define HD1 "   名称                  胜利  失败  耗时  伤敌  误伤  错率  称号\n"
#define FM1 "%3d%-12s%6d%6d%6d%6d%6d%6s%s\n"

//在线排名
int do_top(string arg)
{
	//计算排行
	if(!_top_text || time() + _top_time + 1800) {
		_top_text = ({});
		foreach(object who in users()) {
			mapping m = who->query(XYS_PROP);
			if(m) {

			}
		}
	}
	write("西行幻境人物：\n");
	write(LINE1);
	write(TIT02);
	write(LINE1);
	
	foreach(string line in _top_text) {
		write(line);
	}
	write(LINE1);
	return 1;
}

//计算
private int ratio(int a, int b)
{
	b += a;
	return  b ? a *100 / b : 0;
}

#define HD2 "   名称                  身份    伤敌  误伤  错率\n"
#define FM2 "%3d%-22s%8s%6d%6d%s\n"

//当前统计
int do_stat(string arg)
{
	printf("西行幻境战绩(%d分钟)：\n", (time() - _start_time) / 60);
	write(LINE1);
	write(TIT02);
	write(LINE1);
	
	for(int i = 0; i < sizeof(_ori_order); ++i) {
		string id = _order[i];
		mapping m = _chars[id];
		printf(FM2,
			i + 1,
			m["name"] + "(" + id + ")",
			_roles[m["role"]],
			m["injure"],
			m["a_injure"],
			percent(m["a_injure"], m["injure"] + m["a_injure"]) + "%"
		);
	}
	write(LINE1);
	return 1;
}


#define HD3 "   名称                  气血  精神  兵器       穿着       坐骑\n"
#define FM3 "%3d%-22s%6d%6d%11s%11s%s\n"NOR

//大家状态
int do_look(string arg)
{
	string uid = getuid(_player);
	
	write("西行幻境人物：\n");
	write(LINE1);
	write(TIT02);
	write(LINE1);

	for(int i = 0; i < sizeof(_ori_order); ++i) {
		string id = _order[i];
		mapping m = _chars[id];
		if(die(m)) continue;
		printf(
			(uid == id ? HIW : "") + FM2,
			i + 1,
			m["name"] + "(" + id + ")",
			m["kee"],
			m["sen"],
			m["cards"][C_WEAPON],		//todo
			m["cards"][C_CLOTH],		//todo
			m["cards"][C_HORSE],		//todo
		);
	}
	write(LINE1);
	return 1;
}

#define TIT02 "名称            数值        说明\n"
#define FMT02 "%16s%-12d%s\n"

//自身状态
int do_hp(string arg)
{
	int line2 = 0;
	mapping m = _me;
	if(!m) return 0;

	write("人物状态：\n");
	write(LINE1);
	write(TIT02);
	write(LINE1);

	printf(FMT02, "气血", m[kee], "健康状态");
	printf(FMT02, "精神", m[kee], "精神状态");
	printf(FMT02, "内力", m[kee], "内力余量");
	printf(FMT02, "法力", m[kee], "法力余量");
	
	for(int i = 0; i < sizeof(_states); ++i) {
		int time = m["state"][i];
		if(!time) continue;
		if(!line2) {
			write(LINE2);
			line2++;
		}
		printf(FMT02, _states[i][0], time, _states[i][1]);
	}
	                
	write(LINE1);

	return 1;
}

#define TIT02 "   类别        名称          说明\n"
#define FMT02 "%3d%-12s%-14s%s\n"

//显示手牌
int do_inventory(string arg)
{
	write("西行幻境人物特技/装备/物品列表：\n");
	write(LINE1);
	write(TIT02);
	write(LINE1);
	//身份
	print_card(1);
	write(LINE2);
	//技能
	print_card(2);
	print_card(3);
	print_card(4);
	write(LINE2);
	//装备
	print_card(5);
	print_card(6);
	print_card(7);
	write(LINE2);
	//其他
	foreach(int 
	print_card(i++);
	write(LINE1);
	return 1;
}

#define TIT02 "名称                      等级        说明\n"
#define FMT02 "%26s%12s%s\n"

//自身技能
int do_skills(string arg)
{
	if(!_who) return 0;
	write("西行幻人物技能列表：\n");
	write(LINE1);
	write(TIT02);
	write(LINE1);
	foreach(string k, int v in _who["skills"]) {
		printf(
			FMT02,
			to_chinese(k) + "(" + k + ")", 
			100,
			or2(_skill_comments[k], ""),
		);
	}
	write(LINE1);
	
	return 1;
}

//检查编号是否有效，有效返回编号，无效返回-1
private int valid_num(string arg, mixed* arr)
{
	mixed* cards = _char["cards"];
	int n;
	
	if(getuid(_player) != _char["id"]) return notify_ok("还没轮到你。\n") - 2;
	if(arg || sscanf(arg, "%d", n) != 1) return notify_ok("未指定编号。\n") - 2;
	if(n < 1 || n > CARDS_SIZE) return notify_ok("编号超出范围。\n") - 2;
	n--;
	if(!cards[n]) return notify_ok("无效编号。\n") - 2;
	return n;
}

//装备一件装备
int do_equip(string arg)
{
	int n = valid_num(arg, cards);
	if(n == -1) return 1;

	if(!equip(cards[n])) return notify_ok("无法装备。\n");

	return 1;
}

//卸下一件装备
int do_unequip(string arg)
{
	int n = valid_num(arg, );
	if(n == -1) return 1;

	if(!unequip(_char, [n])) return notify_ok("无法卸下。\n");

	return 1;
}

//出牌/使用牌
int do_use(string arg)
{
	string str;
	int n, target;
	
	if(arg && sscanf(arg, "%s on %d", str, target) == 2) {
		arg = str;
	}
	n = valid_num(arg, cards);
	if(n == -1) return 1;

	if(!use(who, n, target)) return notify_ok("无法使用。\n");
	return 1;
}

//弃牌
int do_discard(string arg)
{
	int n = valid_num(arg, cards);
	if(n == -1) return 1;
	if(n < BASIC_CARDS) return notify_ok("不能丢弃。\n");

	cards[n] = 0;

	return 1;
}

