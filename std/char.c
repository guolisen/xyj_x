// char.c

#pragma save_binary

#include <action.h>
#include <ansi.h>
#include <command.h>
#include <condition.h>
#include <dbase.h>
#include <move.h>
#include <name.h>
#include <skill.h>
#include <team.h>
#include <user.h>
#include <combat.h>

inherit F_ACTION;
inherit F_ALIAS;
inherit F_APPRENTICE;
inherit F_ATTACK;
inherit F_ATTRIBUTE;
inherit F_COMMAND;
inherit F_CONDITION;
inherit F_DAMAGE;
inherit F_DBASE;
inherit F_EDIT;
inherit F_FINANCE;
inherit F_MESSAGE;
inherit F_MORE;
inherit F_MOVE;
inherit F_NAME;
inherit F_SKILL;
inherit F_TEAM;

// Use a tick with longer period than heart beat to save cpu's work
static int tick;

void create()
{
	seteuid(0); // so LOGIN_D can export uid to us
}

// Use this function to identify if an object is a character.
int is_character() { return 1; }

// setup: used to configure attributes that aren't known by this_object()
// at create() time such as living_name (and so can't be done in create()).
void setup()
{
	seteuid(getuid(this_object()));

	set_heart_beat(1);
	tick = 5 + random(10);
	enable_player();
	set_max_items(30);

	this_object()->update_age(); // mon 7/3/99
	CHAR_D->setup_char( this_object() );
}

void heart_beat()
{
	object me = this_object();
	int wimpy_ratio, cnd_flag;
	mapping my = query_entire_dbase();
	object ob;

	// If we are dying because of mortal wounds?
	if( my["eff_kee"] < 0 || my["eff_sen"] < 0) {
		QUEST->quest_kill(me);
		remove_all_enemy();
		die();
		return;
	}

	// If we're dying or falling unconcious?
	if( my["kee"] < 0 || my["sen"] < 0) {
		QUEST->quest_kill(me);
		remove_all_enemy();
		if( !living(me) ) die();
		else unconcious();
		return;
	}

	// Do attack if we are fighting.
	if( is_busy() ) {
		continue_action();
		// We don't want heart beat be halt eventually, so return here.
		return;
	}
	// added by snowcat, pickle's implementation 
	if ( query_temp("no_move") ) {
		continue_action();
		return;
	} else {
		// Is it time to flee?
		if( is_fighting()
			&&	intp(wimpy_ratio = (int)query("env/wimpy"))
			&&	wimpy_ratio > 0
			&&	(	my["kee"] * 100 / my["max_kee"] <= wimpy_ratio
			||	my["sen"] * 100 / my["max_sen"] <= wimpy_ratio) )
			GO_CMD->do_flee(me);
		// Do attack or clean up enemy if we have fleed.
		attack();
	}

	// mon add check living. 8/3/98
	if( !userp(me) && living(me) ) {
		me->chat();		// chat() may do anything -- include destruct(me)
		if( !me ) return;	
	}

	if( tick--  ) return;
	else tick = 5 + random(10);

	cnd_flag = update_condition();

	// If we are compeletely in peace, turn off heart beat.
	// heal_up() must be called prior to other two to make sure it is called
	// because the && operator is lazy :P
	if( ((cnd_flag & CND_NO_HEAL_UP) || !heal_up())
		&&	!is_fighting() 
		&&	!interactive(me)) {
			if( environment() ) {
				ob = first_inventory(environment());
				while(ob && !interactive(ob))
					ob = next_inventory(ob);
			}
			if(!ob) set_heart_beat(0);
	}

	// Make us a bit older. Only player's update_age is defined.
	// Note: update_age() is no need to be called every heart_beat, it
	//       remember how much time has passed since last call.
	me->update_age();

	if( !interactive(me) ) return;

	if(query_idle(me) > IDLE_TIMEOUT)
		me->user_dump(DUMP_IDLE);
}

// added by snowcat 6/27/1997
int command_function (string arg)
{
	command (arg);
	return 1;
}

// mon optimize this function 4/20/98
// this function is extensively referenced, for example from id(),
// present(), ... so must be fast.
int visible(object ob)
{
	int n0, n1;

	if(wizardp(this_object())) return 1;

	n1 = ob->query("env/invisibility");

	if(n1) {
		if(wizardp(ob) || !ob->is_character()) return 0;

		n0 = query("env/invisibility")  + query("max_mana")/400 + query("spi")/10;
		n1 += ob->query("max_mana")/400 + ob->query("spi")/10;
		return n0 >= n1;	// firefox 2011.9
	}

	if(ob->is_ghost() && !is_ghost()) return 0;
	return 1;
}

varargs int eff_skill_level(int level, int usage)
{
	return level;
}

// mon 5/19/98
// for characters reset_eval_cost, so that total eval_cost
// won't be too high.
int command( string str )
{
	reset_eval_cost();
	return efun::command(str);
}
