
#include <ansi.h>

string _block_msg = "$N拦住$n道：" + GANG_NAME + "重地，不得乱闯！\n";

int valid_leave(object me, string dir)
{
	if (dir == "north") {
		object guard = present("guard", this_object());
		if(guard && living(guard) && !GANG->same(me, guard)) {
			string msg = guard->query("block_msg");
			msv(CYN + or2(msg, _block_msg) + NOR, guard, me);
			return notify_fail("\n");
		}
	}

	return ::valid_leave(me, dir);
}
