
#include <imud-efun.h>

inherit ROOM;
inherit F_iEFUN;

object_f _game;
object_f _localizer = __DIR__"localizer";

void create()
{
	_game = __DIR__"c" + path_file(__FILE__)[5..];
	_localizer->set_safety(_this);
	trace(_game);	
	_game->refresh_look();

	setup();
}


void init()
{
	if(userp(this_player())) {
		add_action("do_join", "join");
	}
}

//请求加入游戏
int do_join(string arg)
{
	if(arg != "game")
		return notify_fail("这里只可加入游戏(game)。\n");
	return _game->do_join(0);
}
