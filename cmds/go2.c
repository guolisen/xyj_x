
inherit F_CLEAN_UP;
#include "/cmds/std/valid_move.h";

mapping default_dirs = ([
	"north":                "北",
	"south":                "南",
	"east":                 "东",
	"west":                 "西",
	"northup":              "北边",
	"southup":              "南边",
	"eastup":               "东边",
	"westup":               "西边",
	"northdown":			"北边",
	"southdown":			"南边",
	"eastdown":             "东边",
	"westdown":             "西边",
	"northeast":			"东北",
	"northwest":			"西北",
	"southeast":			"东南",
	"southwest":			"西南",
	"up":                   "上",
	"down":                 "下",
	"out":                  "外",
	"enter":                "里",
	"left":                 "左",
	"right":                "右",
]);

void create() { seteuid(getuid()); }

// follow will have silent=2, so as to reduce the CPU load.
int main(object me, string arg, int silent)
{
	mixed dest;
	string ridemsg, mout, min, dir;
	object env, obj, ridee;
	mapping exit;
	int valid;

	if( !arg ) return notify_fail("你要往哪个方向走？\n");

	if(!valid_move(me)) return 0;

	env = environment(me);
	if(!env) return notify_fail("你哪里也去不了。\n");

	if( !mapp(exit = env->query("exits")) || !exit[arg] ||  undefinedp(exit[arg]) ) {
		if( query_verb()=="go")	return notify_fail("这个方向没有出路。\n");
		else return 0;
	}

	dest = exit[arg];

	if (dest && objectp(dest)) obj = dest;
	else if( !(obj = load_object(dest)) ) return notify_fail("你要去的区域还没有连通。\n");
	else if( !(obj = find_object(dest)) ) return notify_fail("无法移动。\n");

	valid=(int)env->valid_leave(me, arg);
	if( !valid ) return 0;
	// valid>1 also indicates fail, but return 1 here, not 0.
	if(valid>1) return 1;

	if( !undefinedp(default_dirs[arg]) ) dir = default_dirs[arg];
	else dir = arg;

	// snowcat 12/20/97
	if (ridee = me->ride()) ridemsg = ridee->ridee_msg(1);
	else ridemsg = "";

	if(ridee && !valid_move(ridee)) return notify_fail("你的座骑走动不了。\n");

	if( me->is_fighting() ) {
		mout = ridemsg + "往" + dir + "落荒而逃了。\n";
		min = ridemsg + "跌跌撞撞地跑了过来，模样有些狼狈。\n";
	} else {
		//Jiz. 02/11
		if( ridee && ridee->query_temp("bird") ) {
			mout = ridemsg + "往" + dir + "飞去。\n";
			min = ridemsg + "飞了过来。\n";
		} else {
			mout = ridemsg + "往" + dir + "离开。\n";
			min = ridemsg + "走了过来。\n";
		}
	}

	if( !wizardp(me) || !me->query("env/invisibility") ) {
		if (environment(me) && environment(me)->query("no_look"))
			tell_room(environment(me),"一个模糊的影子" +  mout, ({me}) );
		else
			tell_room(environment(me), me->name() + mout, ({me}) );
	}
	if( (! ridee || ridee->move(obj)) && me->move(obj, silent) ) {
		me->remove_all_enemy();
		if( !wizardp(me) || !me->query("env/invisibility") ) {
			if (environment(me) && environment(me)->query("no_look"))
				tell_room(environment(me), "一个模糊的影子" + min,({me}) );
			else
				tell_room(environment(me), me->name() + min, ({me}) );
		}
		me->set_temp("pending", 0);
		// added by snowcat, to fix the bug of recursive move of mutual follow + move to same room 
		if (env != obj)
			all_inventory(env)->follow_me(me, arg);
		if (ridee)
			tell_object (me,"你" + min);
		return 1;
	}

	return 0;
}

void do_flee(object me)
{
	mapping exits;
	string *directions;
	object e = environment(me);

	if(!e || !living(me)) return;
	exits = e->query("exits");
	if( !mapp(exits) || !sizeof(exits) ) return;
	directions = keys(exits);
	if (e && e->query("no_flee")) return;
	tell_object(me, "看来该找机会逃跑了．．．\n");
	if( me->query_temp("no_move") ) {
		tell_object (me, "可你被定住了，逃不掉！\n");
		return;
	}

	if( random(me->query_skill("dodge")/10 + me->query("kar")) < 10 ) {
		tell_object(me, "你逃跑失败。\n");
		return;
	}

	main(me, directions[random(sizeof(directions))], 0);
}

int help(object me)
{
	write(@HELP
指令格式 : go <方向>

让你往指定的方向移动。

HELP
	   );
	return 1;
}