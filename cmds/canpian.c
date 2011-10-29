// by firefox 04/10/2010

#include <xyj_x.h>

#define CP		X_DIR"sys/task/forces/cien/canpian"

int main(object me, string arg)
{
	object room = load_object(arg ? arg : "/d/xueshan/bingya-up4");
	if(!room) room = find_player(arg);

	if(!room) return notify_fail("where?");

	for(int i = 0; i < 10; ++i) {
		new_to(CP, room);		
	}
	
	return 1;
}


