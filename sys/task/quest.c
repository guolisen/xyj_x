// by firefox 04/10/2010
// 解密任务

#include <xyj_x.h>
#include <ansi.h>

inherit TT_GROUP;

void create()
{
	push_backs( ({"food", "ask", "kill", "armor", "weapon", "cloth", "give"}) );

	init_prop();
}

/********************************花色函数***********************************/

//本任务的彩云属性
mapping color_data(object who)
{
	return DB->query_map(who, _stat_prop + "/colors");
}

//查询几色
int color_num(object who)
{
	mapping m = color_data(who);
	int n = 0;

	foreach(string k, int v in m) {
		if(v > 0) n++;
	}
	return n;
}

//任务取消，减一色
int color_remove(object who)
{
	mapping m = color_data(who);
	string* arr = ({});

	foreach(string k, int v in m) {
		if(v > 0) arr += ({k});
	}
	if(sizeof(arr)) m[random1(arr)] = 0;
}

//奖励消耗掉花色
void color_consume(object who)
{
	mapping m = color_data(who);

	foreach(string k, int v in m) {
		if(v > 0) m[k]--;
	}
}

mapping _color_code = ([
	"food"			: HIR"红",
	"ask"			: HIG"绿",
	"kill"			: HIY"黄",
	"weapon"		: HIB"蓝",
	"armor"			: HIM"粉",
	"give"			: HIC"青",
	"cloth"			: HIW"白",
]);

void show_clouds(object who)
{
	mapping m = color_data(who);

	string colors = "";
	int i = 0;

	foreach(string k, int v in m) {
		if(v > 0) {
			colors += _color_code[k];
			i++;
		}
	}
	colors += NOR;

    if(i < 1) return;

	if(i == 1)
		colors += "色";
	else if(i == 2)
		colors += "两色";
	else
		colors += chinese_number(i) + "彩";

	tell_object(who, "你的身上徐徐飘浮起一小团" + colors + "祥云。\n");
}

/********************************其他函数***********************************/

//取消全部任务
void cancel_all(object who)
{
	mapping m = data_of(who);
	if(!sizeof(m)) return;
	set_data(who, ([]));
	color_remove(who);
}

/********************************兑换函数***********************************/

string* _gifts = ({
	"strength", "courage", "intelligence", "spirituality", 
	"composure", "personality", "constitution", "karma"
});

//奖励天赋
string reward_gift(object who, int point)
{
	string gift = random1(_gifts);
	point = 2;

	add_gain(who, "gifts/" + gift, point);
	who->add_temp("apply/" + gift, point);

	return chinese_number(point) + "点" + e2c(gift);
}

private void _improve(object who, string name, int point, int level)
{	
	while(1) {
		int pot = level*level*2;
		if(point <= pot) break;
		who->improve_skill(name, pot, (level > 50));
		level++;
		point -= pot;
	}
	who->improve_skill(name, point, (level > 50));
}

//奖励技能
string reward_skill(object who, int point)
{
	mapping skills = who->query_skills();
	string skill = sizeof(skills) ? random1(keys(skills)) : "force";
	int level = (skills ? skills[skill] : 0) + 1;

	point = point / 4 * 20;	//换算成qn，并按40 int学习

	_improve(who, skill, point, level);
	add_gain(who, "skills/" + skill, point);

	return chinese_number(point) + "点" + to_chinese(skill);
}

//奖励潜能
string reward_pot(object who, int point)
{
	point /= 4;
	who->add("potential", point);	
	add_gain(who, "potential", point);

	return chinese_number(point) + "点潜能";
}

//奖励道行
string reward_dx(object who, int point)
{
	who->add("daoxing", point);
	add_gain(who, "daoxing", point);

	return COMBAT_D->chinese_daoxing(point) + "道行";
}

//奖励白银
string reward_silver(object who, int point)
{
	who->add("balance", point * 100);
	add_gain(who, "silver", point);
	return chinese_number(point) + "两白银";
}

/********************************皇宫兑奖***********************************/

//选择奖励种类
mapping _funs = ([
	"张士衡"		: (: reward_gift :),
	"孟子如"		: (: reward_silver :),
	"杜如晦"		: (: reward_skill :),
	"段志贤"		: (: reward_pot :),
	"徐茂功"		: (: reward_dx :),
]);

//兑现奖励
void pay(object me, object who)
{
	int balance = who->query(_stat_prop + "/balance");
	if(balance > 0) {
		//根据色彩数计算奖励系数
		int color = color_num(who);
		int* tab = ({1, 2, 4, 6, 10, 11, 12, 15});		//高端奖励该削弱？
		int reward = tab[color];
		string color_str = color > 2 ? (chinese_number(color) + "彩") : "";

		mapping m1 = ([ "张士衡" : 1, "孟子如" : 2, "杜如晦" : 3, "段志贤" : 47, "徐茂功" : 47]);
		string dachen = roulette(m1);

		//计算奖励
		if(total_exp(who) < 40*K) reward = max2(reward, 10);
		reward = reward * balance / 10;
		who->set(_stat_prop + "/balance", 0);

		msv("\n一进大殿，$N身上涌起淡淡的" + color_str + "祥云。\n", who);
		msvx("$N对$n赞赏道：$r祥云缭绕，面生瑞气，朕果然有赏御赐与你！\n\n", me, who);
		msv("$n走上前，赶紧在$N的殿前俯身跪下。\n", me, who);

		who->start_busy (3, 3);
		call_out("reward_player", 2, me, who, reward, dachen);
	}
}

void reward_player(object me, object who, int reward, string dachen)
{
	string gain = evaluate(_funs[dachen], who, reward);
	color_consume(who);

	msvx("\n旁边闪过大臣%s低声向$N说了几句，$N点了点头。\n", me, 0, dachen);
	msvx("%s对$N一拜：陛下有旨，赐$R%s！\n\n", who, 0, dachen, gain);
	msv("$N连忙俯身一拜，小心翼翼地站起来。\n", who);

	MONITOR_D->report_system_object_msg (who, "得到" + gain);
	who->interrupt_me();
}

