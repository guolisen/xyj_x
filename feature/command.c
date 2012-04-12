

#include <command.h>
#include <dbase.h>
#include <origin.h>

// Let command path be static, thus we can make sure no one can get command
// path directly from restore_object().
static string *path;

// Leave this to allow other objects can search your commands such as
// help, which...
string find_command(string verb)
{
	return (string)COMMAND_D->find_command(verb, path);
}

//command filter
private int do_filter(function* funs, object me, string verb, string arg)
{
	for(int i = sizeof(funs) - 1; i >= 0; --i) {
		if(functionp(funs[i]) && evaluate(funs[i], me, verb, arg)) return 1;
	}
	return 0;
}

// This is the add_action hook handling movement, commands, emotes and
// channels. Optimization is needed.
// private nomask int command_hook(string arg)
nomask int command_hook(string arg)
{
	int start = eval_cost();
	int ret = 1;
	string file;
	object me = this_object();
	string verb = query_verb();
	mapping filters = me->query_temp("cmd_filter");

	if(sizeof(filters) && (filters["*"] && do_filter(filters["*"], me, verb, arg)
		|| filters[verb] && do_filter(filters[verb], me, verb, arg)));
	else if(!arg 
		&& (environment() && environment()->query("exits/" + verb))
		&& stringp(file = find_command("go"))
		&& call_other(file, "main", this_object(), verb));
	else if(stringp(file = find_command(verb))
		&& call_other(file, "main", this_object(), arg));
	else if(EMOTE_D->do_emote(me, verb, arg));
	else if(CHANNEL_D->do_channel(me, verb, arg));
	else ret = 0;

	COMMAND_D->verb_cost(verb, start - eval_cost());

	return ret;
}

// private nomask void set_path(string *p)
nomask void set_path(string *p)
{
	//	if( origin() != ORIGIN_LOCAL
	//	&&	geteuid(previous_object()) != ROOT_UID )
	//		return;
	path = p;
}

string *query_path() { return path; }
mixed *query_commands() { return commands(); }

int force_me(string cmd)
{
	if( geteuid(previous_object()) != ROOT_UID )
		return 0;

	return command( this_object()->process_input(cmd) );
}

nomask void enable_player()
{
	if( stringp(query("id")) ) set_living_name(query("id"));
	else set_living_name(query("name"));

	delete_temp("disabled");
	enable_commands();
	add_action("command_hook", "", 1);

	if( !userp(this_object()) )
		set_path(NPC_PATH);
	else
		switch( wizhood(this_object()) ) {
		case "(admin)":
			set_path(ADM_PATH);
			enable_wizard();
			break;
		case "(arch)":
			set_path(ARC_PATH);
			enable_wizard();
			break;
		case "(wizard)":
			set_path(WIZ_PATH);
			enable_wizard();
			break;
		case "(apprentice)":
			set_path(APR_PATH);
			enable_wizard();
			break;
		case "(immortal)":
			set_path(IMM_PATH);
			enable_wizard();
			break;
		case "(elder)":
			set_path(ELD_PATH);
			enable_wizard();
			break;
		default:
			set_path(PLR_PATH);
	}
}

nomask void disable_player(string type)
{
	if( geteuid(previous_object())!=ROOT_UID
		&&	previous_object()!=this_object()) return;

	set("disable_type", type);
	set_temp("disabled", 1);
	disable_commands();
	enable_commands();  // enable command again so this object would be
	// marked living again. block command in alias.c
	// instead of here.
}


