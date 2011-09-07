
#include <ansi.h>
inherit ROOM;

#define DNTG11			"dntg11"	//dtng 11关标记
#define DNTG12			"dntg12"	//dtng 12关标记

#define IN_PRISON		(5*3600/100)	//坐牢时间
#define SEND_LETTER		600/10			//送信间隔

#define TERM			"prison_term"



//限制太多未必有意义，可以通过大米喊
//那么长时间太折磨人了，不如允许打打内力

string* _verbs = ({			//可用指令
	"chat", "tell", 
	"look", "inventory", "hp",
	"exert", "exercise", "meditate", "eat",
	"quit",
	"call", "update",
});

void check_time(object who);
int do_break(string arg);
int do_say(string arg);
void send_letter(object who);
string name_id(object who);
void show_pusa(object who);

void create ()
{
	set ("short", "莲花五行山底");
	set ("long", @LONG

太行山，又名五行山、王母山、女娲山。传说中五百年前
如来佛祖将五指化作金、木、水、火、土五座联山，唤名
“五行山”将大闹天宫的美猴王压于五指山下，只见五峰矗
起，怪石嶙峋，这里芳草萋萋，灌木丛生。 


LONG);

	set("exits", ([
		"east"		: __DIR__"shandi",
		"west"		: __DIR__"shandi",
		"northup"	: __DIR__"shanding",
	]));

	set("outdoors", __DIR__);
	set("valid_startroom", 1);

	setup();
}

void init()
{
	object who = this_player();

	add_action("exec_cmd", "", 1);

	if((who->query(DNTG11) == "done") && (who->query(DNTG12) != "done")) {
		who->set("startroom", base_name(this_object()));
		who->set(TERM"/start", time());

		who->set_temp("apply/short", ({ name_id(who) + HIR" <被压在山石中>"NOR }));

		who->set_temp("apply/long", ({ @LONG

被压在山石中，露着头，伸着手。头上堆苔藓，耳中生薜
萝。鬓边少发多青草，颔下无须有绿莎。眉间土，鼻凹泥
十分狼狈，指头粗，手掌厚，尘垢余多。

LONG }));
		check_time(who);
	}
}

//屏蔽大多数命令
int exec_cmd(string arg)
{
	object who = this_player();
	string verb = query_verb();

	if(!who->query(TERM)) return 0;

	check_time(who);
	if(member_array(verb, _verbs) >= 0) return 0;

	if(verb == "break") return do_break(arg);
	if(verb == "say") return do_say(arg);
	write("五行山紧紧压住，你身不由己。\n");
	return 1;
}

//检查坐牢时间
void check_time(object who)
{
	//累计坐牢时间
	int elapse = time() - who->query(TERM"/start");
	who->add(TERM"/elapse", elapse);
	who->set(TERM"/start", time());

	if(wizardp(who))
		printf("[bebug]:时间流逝: %d秒\n", who->query(TERM"/elapse"));

	//刑满释放
	if(who->query(TERM"/elapse") > IN_PRISON
		&& !who->query_temp(TERM"/sending"))
	{
		who->set_temp(TERM"/sending", 1);
		show_pusa(who);
	}
}

//发送求救信
void send_letter(object who)
{
	object letter = new(__DIR__"letter");
	object* players = users();
	object savior;

	if(!who || !who->query(TERM)) return 0;

	while(1) {
		savior = players[random(sizeof(players))];
		if (savior && savior != who					//给wiz便于测试，也没什么大不了的
			&& savior->query("combat_exp") > 500) break;
	}
	if(letter->move(savior)) {
		letter->set("savior_id", getuid(savior));
		letter->set("prisoner_id", getuid(who));		

		tell_object(who, HIG"你现在压在五行山底动弹不得。\n",);
		tell_object(who, HIG"只有" + name_id(savior) + "才能解除五行山的符咒。\n"NOR);

		tell_object(savior,  HIG + name_id(who) + "现在被困五行山下，只有你才能到五行山解除符咒。\n"NOR);
		tell_object(savior,  HIY"一条黄绢慢慢的飘到了你的身上。\n"NOR);
	}
	call_out("send_letter", SEND_LETTER, who);
}

int do_break(string arg)
{
	object env = this_object();
	object who = this_player();
	object shanding = load_object(__DIR__"shanding");
	int str = who->query("force_factor")*5 + who->query("str");

	if(!who->query(TERM)) return 0;
	if(shanding->query("short") != "五行山顶")
		return notify_fail("你奋力挣扎，但被山石压得死死的。\n");

	message_vision("$N使出吃奶的力气想从五行山中钻出来。”\n", who);

	if( str > 300)
		tell_room(env, "五行山开始晃动………\n");
	else if( str > 200)
		tell_room(env, "五行山咔咔作响，似乎快要崩塌了。\n");
	else if( str > 100)
		tell_room(env, "五行山好像裂开了一个大口子………\n");
	else
		tell_room(env, "只听五行山有隆隆声，却不见有丝毫摇动…\n");

	env->add("break", str);
	who->receive_damage("kee", 30);
	who->add("force", - who->query("force_factor"));
	if( who->query("force") < 0 )who->set("force", 0);

	if ( env->query("break") > 3000 ){
		tell_room(env,"五行山好像裂开了一个大口子，怕是快要爆塌了。\n");
		env->delete("break");
		set("long", @LONG

这里黄沙漫天，烟雾弥漫，碎石横行，五个犹如折断的手指一样的山脉横七竖八的交纵着。

LONG);
		shanding->set("short", "乱石堆");
		shanding->set("long", @LONG

昔日直冲云霄的五指山已经崩塌，现在只剩一堆乱石。

LONG);
		tell_room(shanding, HIW"一声巨响惊天动地，莲花五指山轰然崩塌。\n"NOR);
		message_vision(HIW"一声巨响惊天动地，莲花五指山轰然崩塌，$N破石而出！\n\n"NOR, who);

		who->delete_temp("apply/short");
		who->delete_temp("apply/long");		
		who->set(DNTG12, "done");
		who->delete(TERM);
		//todo:宣布12关成功
		who->command("chat "HIY"500年刑满，我终出来了！感谢中央气象台...");
		who->command("chat "HIY"俺从此皈依我佛，踏上取经路。");
	}
	return 1;
}

//用户名与ID
string name_id(object who)
{
	return who->query("name") + "(" + capitalize(who->query("id")) + ")";
}

object _pusa;
object _huian;

void show_pusa(object who)
{
	object env = this_object();

	_pusa = new(__DIR__"pusa");
	_huian = new(__DIR__"huian");

	_pusa->move(env);
	_huian->move(env);

	tell_room(env, CYN + @LONG

从山顶隐隐传来一首诗：


          堪叹妖猴不奉公，当年狂妄逞英雄。
          欺心搅乱皤桃会，大胆私行兜率宫。
          十万军中无敌手．九重天上有威风。
          自遭我佛如来困，何日舒伸再显功！


观音菩萨和惠岸行者自山顶翩翩落下。

菩萨道：认得我么？
LONG + NOR);


	who->set_temp("pusa/stage", ({1, ({"认得", "救"})}));
}

private int say(object who, string msg)
{
	message_vision(CYN"$N说道：" + msg + "\n"NOR, who);
}

int do_say(string arg)
{
	object who = this_player();
	mixed* stage = who->query_temp("pusa/stage");
	int answer_ok = 0;

	if(!arg || !stage) return 0;

	//判断时候正确的回答了指定的关键字
	foreach(string word in stage[1]) {
		if(strsrch(arg, word) >= 0) answer_ok = 1;
	}
	if(!answer_ok) return 0;
	if(wizardp(who)) printf("[bebug]:stage[0]:%d\n", stage[0]);

	switch(stage[0]) {
	case 1:		
		say(who, "认得，你是观音菩萨。我压在此山五百余年，已知悔了，万望菩萨救我一救！");
		say(_pusa, "你既有此心，待我寻取经的人来，教他救你，跟他做个徒弟。");
		say(_pusa, "入佛门，修正果，如何？");
		who->set_temp("pusa/stage", ({2, ({"好", "愿"})}));
		break;
	case 2:
		say(who, "好，愿去！愿去！");
		_pusa->command("nod");
		message_vision(HIY"$N手中射出一道金光罩在$n头顶，金光散去，$n头上多了一个金箍。\n"NOR, _pusa, who);
		message_vision(CYN"$N和惠岸行者踩着祥云，缓缓升空。\n"NOR, _pusa);
		send_letter(who);
		destruct(_pusa);
		destruct(_huian);
		who->delete_temp("pusa/stage");
		//todo:给金箍
		break;
	}		
	return 1;
}
