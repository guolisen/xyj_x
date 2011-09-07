// by firefox 11/21/2009

#include <ansi.h>


#define SEC_PER_HB				2		//每心跳秒数


/********************************数学函数***********************************/

//较大值
mixed max2(mixed a, mixed b) 
{
	return a >= b ? a : b;
}

//较小值
mixed min2(mixed a, mixed b)
{
	return a <= b ? a : b;
}

//最大值
mixed max3(mixed a, mixed b, mixed c)
{
	return max2(max2(a, b), c);
}

//最小值
mixed min3(mixed a, mixed b, mixed c)
{
	return min2(min2(a, b), c);
}

//如果a非空则a，否则b。
mixed or2(mixed a, mixed b)
{
	return a ? a : b;
}

//如果a空则a，否则b
mixed and2(mixed a, mixed b)
{
	return !a ? a : b;
}

//从数组中随机选择一个元素
mixed random1(mixed* arr)
{
	return arr[random(sizeof(arr))];
}


/********************************字符串函数***********************************/

//反向搜索指定字符位置
int rfind(string str, int ch)
{
	int i;
	for(i = sizeof(str) - 1; i >= 0; --i) {
		if(str[i] == ch) break;
	}
	return i;
}

//全路径中的文件名
string path_file(string path)
{
	int i = rfind(path, '/');
	return path[i+1..];
}

//全路径中的路径名
string path_dir(string path)
{
	int i = rfind(path, '/');
	return path[0..i-1];
}

/********************************对象函数***********************************/

//建立对象并放置于目标环境（失败则销毁对象）
object new_to(string file, object env)
{
	object ob = new(file);

	if(!ob || !env) return 0;
	if(ob->is_character() && env->is_character()) env = environment(env);
	if(env && ob->move(env)) return ob;
	destruct(ob);
	return 0;
}

//判断id是否为指定对象
int id_match_ob(string id, object ob)
{
	object ob1;

	if(!id || !ob) return 0;
	ob1 = present(id, environment(ob));

	return ob == ob1;
}

/********************************消息函数***********************************/

//显示信息，并返回1，某些时候用于代替notify_fail
int notify_ok(string msg)
{
	write(msg);
	return 1;
}

//向wiz报告测试数据
varargs int trace(string msg, object who)
{
	if(!who) who = this_player();
	if(who && wizardp(who)) {
		tell_object(who, HIW"TRACE:"HIY + msg + NOR"\n");
	}
	return 1;
}

//替换字符串中的称谓，称谓习惯沿袭message_vision，与emote不同
private string _vision_rep(string msg, object who, int low)
{
	object weapon = who->query_temp("weapon");
	mapping m = ([
		"$R"	: RANK_D->query_respect(who),		//敬称
		"$U"	: RANK_D->query_rude(who),			//蔑称
		"$S"	: RANK_D->query_self(who),			//谦称
		"$A"	: RANK_D->query_self_rude(who),		//狂称，Arrogant
		"$W"	: weapon ? weapon->name() : "拳头",	//武器
	]);
	foreach(string k, string v in m) {
		if(low) k = lower_case(k);
		if(v) msg = replace_string(msg, k, v);
	}
	return msg;
}

//message_vision加强版
varargs int msvx(string msg, object me, object you, mixed a1, mixed a2, mixed a3, mixed a4)
{
	if(!msg || !me) return 1;
	msg = sprintf(msg, a1, a2, a3, a4);
	if(me) msg = _vision_rep(msg, me, 0);
	if(you) msg = _vision_rep(msg, you, 1);
	message_vision(msg, me, you);
	return 1;
}

/********************************其他工具函数***********************************/

//技能开始冷却，返回：0-技能正处于冷却期；非0-技能已经冷却，开始进入新的冷却期。
int cd_start(object who, string prop, int duration)
{
	string str = "sys_cd/" + prop;
	int t = time();

	if(t < who->query(str)) return 0;
	return who->set(str, t + duration * SEC_PER_HB);
}

//技能是否冷却结束
int cd_end(object who, string prop)
{
	string str = "sys_cd/" + prop;
	return time() >= who->query(str);
}

//检查技能是否冷却，未冷却则返回错误信息
varargs int cd_check(object who, string prop, string fail_msg)
{
	if(cd_end(who, prop)) return 1;

	fail_msg = fail_msg ? fail_msg : "技能暂时不能使用。\n";
	tell_object(who, fail_msg);
	return 0;
}

