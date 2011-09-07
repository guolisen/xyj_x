
#include <ansi.h>
inherit ROOM;

void create ()
{
	set ("short", "云海尽头");
	set ("long", @LONG

云海茫茫，云涛汹涌，状如大海；崇风时起，开合磅礴。
时而浓云涌来，人在其中，伸手莫辨；时而云开雾散，上下
天光，一碧万顷，朦胧中隐约看到五根肉红柱子，撑着一股
青气，好不壮观，仔细看来，好像已经到了天的尽头。
LONG);

	set("exits", ([ /* sizeof() == 4 */
	]));
	set("outdoors", 2);

	setup();
}

void init()
{
	add_action("do_sa",  "sa");
	add_action("do_ba",  "ba");
	add_action("do_zhan",  "zhan");
	add_action("do_xie",  ({"xie", "write"}));
	add_action("do_back",  ({"huiqu", "flyback", "jump"}));	//单机上jump被表情jump拦截了
}

int do_sa (string arg)
{
	object who = this_player();

	if( !arg || (arg != "niao" && arg != "尿") ) 
		return notify_fail("你要干什么？\n");			
	if( who->query_temp("dadu/saniao") ) 
		return notify_fail("刚撒过了还撒？你有那么多尿吗？\n");	

	message_vision("$N东张西望，鬼鬼祟祟的跑到第一根柱子根下撒了一泡尿。\n",who);	
	who->set_temp("dadu/saniao", 1);
	return 1;
}

int do_ba (string arg)
{
	object pen = new(__DIR__"pen");
	object who = this_player();

	if( !arg || arg != "haomao" ) 
		return notify_fail("你要拔什么？\n");			

	if( who->query_temp("dadu/ba") ) 
		return notify_fail("你想把自己身上的毛拔光吗？\n");	

	if(pen && pen->move(who)) {
		message_vision("$N从身上拔下一根毫毛来。变出一只双毫笔。\n", who);
		who->set_temp("dadu/ba",1);
	}
	return 1;
}

int do_zhan (string arg)
{
	object who = this_player();

	if( !who->query_temp("dadu/ba") || !arg || arg != "bi")
		return notify_fail("你要蘸什么？\n");

	if( who->query_temp("dadu/zhan") ) 
		return notify_fail("双毫笔已经可以写字了。\n");	

	message_vision("$N把手中的双毫笔放到嘴里蘸了蘸。\n",who);	
	who->set_temp("dadu/zhan",1);
	return 1;
}

int do_xie (string arg)
{
	object who = this_player();

	if( !who->query_temp("dadu/ba") )
		return notify_fail("你拿什么写字？\n");	

	if( !who->query_temp("dadu/zhan") )
		return notify_fail("干涩的笔头写不出字来。\n");	

	if( !arg || arg != "齐天大圣到此一游" ) 
		return notify_fail("不知道写什么也不能乱写乱画！\n");

	if( who->query_temp("dadu/xie") ) 
		return notify_fail("柱子上已经有字了。\n");	

	message_vision("$N一个猴跳，在那中间柱子上写一行大字云：“齐天大圣到此一游”。\n",who);	

	set ("long", @LONG

柱子上歪歪扭扭的写着“齐天大圣到此一游”。
LONG);
	who->set_temp("dadu/xie",1);
	return 1;
}

int do_back (string arg)
{
	object who = this_player();

	if( !who->query_temp("dadu/saniao"))
		return notify_fail("你感觉小腹涨涨，要憋不住了。\n");
	
	if( !who->query_temp("dadu/xie"))
		return notify_fail("你突然想到：不留下些记号，如何与如来说话？\n");

	message_vision(CYN"$N纵身踏上云端，腾空而去。\n"NOR, who);	

	//who->set_temp("dadu","done");
	
	who->move(__DIR__"lingxiao");

	message_vision(CYN"$N跳下云头，出现在众人面前。\n"NOR, who);
	return 1;
}
