// by firefox 11/21/2009
// 命令拦截器

#include <xyj_x.h>

#define CMD_PATH				X_DIR"cmds/"

string* bian_cmds = ({ "bian", "buff", "tell" });	//变身成物品时可用命令

int exec_cmd_(string arg)
{
	object who = this_player();
	string verb = query_verb();

	if((who->query_temp("d_mana") > 0) && (who->query_temp("is_living") != 1)) {
		if(member_array(verb, bian_cmds) == -1) return 0;
	}

	if(file_size(CMD_PATH + verb + ".c") > 0) {
		string cmd = CMD_PATH + verb;
		return cmd->main(who, arg);
	}
	return 0;
}

int filter_cmd()
{
	add_action("exec_cmd_", "", 1);
	return 1;
}