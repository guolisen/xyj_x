//全部符合原著中的剧情。pkyou

#include <ansi.h>
inherit ROOM;

int do_reward(object who);


void create ()
{
	set ("short", "莲花五行山顶峰");
	set ("long", @LONG

五行山顶上，紧紧的贴在一块四方石上。那座山即生根合缝
远远望去，上面六个金灿灿的大字耀的人眼都睁不开。

LONG + HIY"            唵、嘛、呢、叭、咪、吽。\n\n"NOR
		);

	set("exits", ([
		"southdown" : __DIR__"shandi",
	]));
	set("outdoors", __DIR__);

	setup();
}

void init()
{
	add_action("do_open", "open");
}

int do_open(string arg)
{
	object env = this_object();
	object who = this_player();
	object letter = present("feng yin", who);
	object guard = present("shan shen", env);
	object shandi = load_object(__DIR__"shandi");
	object prisoner = letter ? find_player(letter->query("prisoner_id")) : 0;

	if( !arg || arg != "zhou" ) 
		return notify_fail("你要打开什么？\n");

	if (!letter || letter->query("savior_id") != getuid(who))
		return notify_fail("你没有得到佛祖的点化，无法五行山下定心猿。\n");

	if (!prisoner || environment(prisoner) != shandi)
		return notify_fail("山下没有压着人！\n");

	if(!guard && !who->query_temp("kill_guard")) {
		guard = new(__DIR__"guard");
		guard->move(env);
		guard->copy_status(who);
		message_vision(CYN"$N正要去揭开咒符，突然面前出现了一个人。\n"NOR, who);
		who->set_temp("kill_guard", 1);
		return 1;
	}
	if(guard) {
		message_vision(CYN"$n拦住$N说道：不可放这妖孽出来，否则天上地下都要遭殃！\n"NOR, who, guard);
		return 1;
	}

	tell_object(prisoner, WHT"你突然感觉如释重负，身上轻快了很多。\n"NOR);

	set ("short", "五行山顶");

	message_vision("$N小心翼翼将封印解了下来。\n", who);
	message_vision(HIY"封印突然发出一道强烈的金光，照得你睁不开眼。\n"NOR, who);
	message_vision("等金光黯去，$N发现" + letter->name() + "消失得无影无踪！\n", who);
	destruct(letter);
	who->delete_temp("kill_guard");
	do_reward(who);
	return 1;
}

//给奖励
int do_reward(object who)
{
	//玩家更缺潜能，道行不用奖励了吧？
	who->add("potential",1000);
	//这里要赠送一个定心真言的技能或者指令，类似我们修改的大闹天宫第10关赠送的火眼金睛术一样。
	//  tell_object(who,"等金光黯去。\n");
	tell_object(who, sprintf("救人一命胜造七级浮屠。恭喜你！你学会了【定心真言紧箍咒】。\n"NOR) );

	
}


