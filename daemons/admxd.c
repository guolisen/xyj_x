

void create() { seteuid(getuid()); }


//查找玩家，如果玩家不在线，加载玩家档案
object global_find_player(string id)
{
	object player = find_player(id);
	if(player) return player;
	else {
		object login_ob = new(LOGIN_OB);

		login_ob->set("id", id);
		if (!login_ob->restore() || login_ob->query("id") != id) {
			destruct(login_ob);
			return 0;
		}		
		player = LOGIN_D->make_body(login_ob);
		if (!player) {
			destruct(login_ob);
			return 0;
		}
		if (!player->restore()) {
			destruct(login_ob);
			destruct(player);
			return 0;
		}
		player->set_temp("player_offline", 1);
		destruct(login_ob);
	}
	return player;
}

//销毁玩家对象，如果玩家在线，无动作
int global_destruct_player(object player)
{
	if(player->query_temp("player_offline")) {
		destruct(player);
	}
	return 1;
}
