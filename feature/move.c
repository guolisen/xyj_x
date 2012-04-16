// move.c

// 4/24/98 mon adds max_items related stuff.

#pragma optimize

#include <dbase.h>
#include <room.h>
#include <ansi.h>

static int weight = 0;
static int encumb = 0, max_encumb = 0;

varargs int _move(mixed dest, int silently);
void dest_obj(object obj);

// max_items is the maximum number of items an object can hold.
// note this is for non-character items.
// there is no limitations on # of characters. (limited by encumb)
// this is to prevent some rooms that full of items and
// players and npcs can't even enter. :P
static int max_items = 10; // default max_items.
nomask void set_max_items(int e) { max_items=e; }
nomask int query_max_items() { return max_items; }

nomask int query_encumbrance() { return encumb; }
nomask int over_encumbranced() { return encumb > max_encumb; }

nomask int query_max_encumbrance() { return max_encumb; }
nomask void set_max_encumbrance(int e) { max_encumb = e; }
nomask void add_encumbrance(int w)
{
	object me = this_object();
	object e = environment();

	encumb += w;
	if( encumb < 0 )log_file("move.bug", sprintf("%s%s  encumbrance underflow. env:%s w:%d\n",
		file_name(me), me->query("id"), file_name(e), w));
	if( encumb > max_encumb ) me->over_encumbrance();
	if( e ) e->add_encumbrance(w);
}

void over_encumbrance()
{
	if( !userp(this_object()) ) return;
	tell_object(this_object(), "你的负荷过重了！\n");
}

nomask int query_weight() { return weight; }
nomask void set_weight(int w)
{
	if( !environment() ) {
		weight = w;
		return;
	}
	if( w != weight ) environment()->add_encumbrance( w - weight );
	weight = w;
}


// This is the "current" weight of an object, which is used on weight
// checking in move().
nomask int weight() { return weight + encumb; }

string ridee_msg() 
{
	object me = this_object();
	return sprintf("%s在%s上", me->query("ride/msg"), me->name());
}

string ride_suffix(object me)
{
	object ridee = me->ride();
	if(ridee) return ridee->ridee_msg();
	return 0;
}

// silently=1: after move, no look.
// silently=2: when look, only show room name. (for follow command)
// silently=0: full look.
// mon 4/20/98
varargs int move(mixed dest, int silently)
{
	if(_move(dest, silently)) return 1;

	call_out("dest_obj", 2, this_object());
	return 0;
}

// destruct obj if it failed to move and has no environment.
void dest_obj(object obj)
{
	if(obj && !environment(obj)) destruct(obj);
}

private int too_much_inv(object ob)
{
	return sizeof(all_inventory(ob)) >= ob->query_max_items();
}

private void show_sb(object me, object ob)
{
	string ridemsg;

	if(ob == me || !me->visible(ob) ) return;
	tell_object(me, "  " + ob->short());

	if(ridemsg = ride_suffix(ob)) tell_object(me, " <" + ridemsg + ">");
	tell_object(me, "\n");
}
varargs int _move(mixed dest, int silently)
{
	object dst, env;
	object me = this_object();

	// If we are equipped, unequip first.
	if(query("equipped") && !me->unequip())	return notify_fail("你没有办法取下这样东西。\n");

	// Find the destination ob for moving.
	if(dest && objectp(dest)) dst = dest;
	else if(stringp(dest)) {
		dst = load_object(dest);
		if(!dst) return notify_fail("move: destination unavailable.\n");
	} else
		return notify_fail(sprintf("move: invalid destination %O.\n", dest));

	// check for max_items.
	if(!(me->is_character()) &&	too_much_inv(dst)) {
		if(dst == this_player()) return notify_fail("你身上装不下更多东西了。\n");
		else if(userp(dst)) return notify_fail(dst->name() + "身上装不下更多东西了。\n");
		else { // for rooms and container.
			string name = or2(dst->name(), dst->query("short"));
			return notify_fail(or2(name, dst->short()) + "已经太拥挤了。\n");
		}
	}

	// recursive check can't move sth into itself's belonging's
	// mon 9/1/98
	env = dst;
	if(env == me) return notify_fail("你不能把物品放入自身之中。\n");
	while(env = environment(env)) {
		if(env == me) return notify_fail("你不能把物品放入自身之中。\n");
	}

	// Check if the destination ob can hold this object.
	// Beforce checking it, we check if the destination is environment of
	// this_object() (or environment of its environment). If it is, then
	// this could be like get something from a bag carried by the player.
	// Since the player can carry the bag, we assume he can carry the this
	// object in the bag and encumbrance checking is unessessary.
	env = me;
	while(env = environment(env)) if( env == dst ) break;
	if(!env && dst->query_encumbrance() + weight() > dst->query_max_encumbrance()) {
		if(dst == this_player()) return notify_fail( me->name() + "对你而言太重了。\n");
		else return notify_fail( me->name() + "对" + dst->name() + "而言太重了。\n");
	}

	// Move the object and update encumbrance
	// by snowcat 3/10/1998
	if(env = environment()) {
		env->add_encumbrance( - weight());
		if(userp(env) && me->value() >= 10000) env->save();
	}
	dst->add_encumbrance(weight());

	//added by snowcat
	if (userp(dst) && me->value() >= 10000000) {
		object where1 = environment();
		object where2 = environment(dst);
		string place_me = "某";
		string place_ob = "某";

		if(where1) place_me = or2(where1->short(), where1->query("short")) + "[" + file_name(where1) + "]";
		if(where2) place_ob = or2(where2->short(), where2->query("short")) + "[" + file_name(where2) + "]";
		if(where1 != dst) MONITOR_D->report_system_object_msg (dst, "（在" + place_ob + "）自" +
			place_me + "处得到了价值为" + (me->value() / 10000) + "gold的巨款。");
	}

	move_object(dst);
	if(!me) return 0;  //mon 8/24/97

	// If we are players, try look where we are.
	if(interactive(me) && living(me) && silently != 1) {
		object e = environment();
		string short = or2(e->query("short"), "");
		mixed brief_all = me->query("env/brief_all");

		if(silently == 2 || brief_all) {
			tell_object(me, short + " -\n");
			if(stringp(brief_all)) {
				object ob = present(brief_all, e);
				if(ob) show_sb(me, ob);
			}
		} else {
			mixed brief = me ->query("env/brief");
			string long = e->query("long");
			mapping exits  = e->query("exits");

			tell_object(me, sprintf( "%s - %s\n    %s%s",
				short,
				wizardp(me) ? file_name(e) : "",
				!brief && long ? long : "",
				!brief && e->query("outdoors") ? NATURE_D->outdoor_room_description() : "")
			);
			if(!e->query("no_look") && mapp(exits)) {
				string* dirs = keys(exits);
				string str;
				for(int i = 0; i < sizeof(dirs); ++i)
					if((int)e->query_door(dirs[i], "status") & DOOR_CLOSED) dirs[i] = 0;
				dirs -= ({ 0 });

				if(sizeof(dirs) == 0)
					str = "    这里没有任何明显的出路。\n";
				else if( sizeof(dirs)==1 )
					str = "    这里唯一的出口是 " + BOLD + dirs[0] + NOR + "。\n";
				else
					str = sprintf("    这里明显的出口是 " + BOLD + "%s" + NOR + " 和 " + BOLD + "%s" + NOR + "。\n",
					implode(dirs[0..sizeof(dirs)-2], "、"), dirs[sizeof(dirs)-1]);
				tell_object(me, str);
			}
			if(!e->query("no_look")) {
				foreach(object ob in all_inventory(e)) {
					show_sb(me, ob);
				}
			}
		}
	}
	// the following is made by snowcat on 6/20/1997
	// modified by mon 8/29/97
	if ((me->query("is_monitored") || file_name(me)[0..2] == "/u/") && userp(dst))
		MONITOR_D->report_system_object_msg(dst, "得到了" + me->query("name") + "(" + file_name(me) + ")。");
	return 1;
}

void remove(string euid)
{
	object me = this_object();
	object default_ob;


	if( !previous_object() || base_name(previous_object()) != SIMUL_EFUN_OB )
		error("move: remove() can only be called by destruct() simul efun.\n");

	if( userp(me) && euid!=ROOT_UID ) {
		log_file("destruct", sprintf("%s attempt to destruct user object %s (%s)\n", euid, me->query("id"), ctime(time())));
		error("你(" + euid + ")不能摧毁其他的使用者。\n");
	} else if( me->query("equipped")) {
		if( !me->unequip() ) log_file("destruct", sprintf("Failed to unequip %s when destructed.\n",file_name(me)));
	}

	// We only care about our own weight here, since remove() is called once
	// on each destruct(), so our inventory (encumbrance) will be counted as
	// well.
	if( environment() ) environment()->add_encumbrance( - weight );
	if( default_ob = me->query_default_object() ) default_ob->add("no_clean_up", -1);
}

int move_or_destruct(object dest)
{
	object me = this_object();
	if(userp(me)) {
		tell_object(me, "一阵时空的扭曲将你传送到另一个地方．．．\n");
		move(VOID_OB);
	}
}

//me & ob in same environment
int close_to(object ob)
{
	object env = environment();
	return ob && env && env == environment(ob);
}

int dismount()
{
	object me = this_object();
	object ridee = me->query_temp("ridee");
	mapping props;
	int show_msg = 0;

	if(ridee) {
		if(close_to(ridee)) show_msg = 1;
		ridee->set_temp("no_return", 0);
		ridee->set_temp("rider", 0);
	}
	me->set_temp("ridee", 0);
	props = me->query_temp("ride");

	if(mapp(props)) {
		foreach(string k, int v in props)
			me->add_temp("apply/" + k, -v);								//TODO 属性移动
		me->set_temp("ride", 0);
	}
	return show_msg;
}


void mount(object ridee)
{
	object me = this_object();
	object env = environment();
	
	ridee->set_temp("no_return", 1);
	ridee->set_temp("rider", me);
  
	me->set_temp("ridee", ridee);
	ridee->move(env);
	me->set_temp("ride/dodge", ridee->query("ride/dodge"));								//todo:属性处置
	me->add_temp("apply/dodge", ridee->query("ride/dodge"));
}



//valid ridee
object ride()
{
	object me = this_object();
	object ridee = me->query_temp("ridee");

	if(!ridee) return 0;
	
	if(!close_to(ridee) || !living(ridee)) {
		dismount();
		return 0;
	}
	return ridee;
}
