// by firefox 02/21/2010

inherit BULLETIN_BOARD;

#include "_config.h"

void create()
{
	set_name("留言板", ({ "board" }) );
	set("location", __DIR__"bedroom");
	set("board_id", "g_" + GANG_ID);
	set("long",	"这是一个供人留言记事的留言板。\n" );
	setup();
	set("capacity", 100);
	replace_program(BULLETIN_BOARD);
}
