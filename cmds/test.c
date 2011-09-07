// by firefox 11/21/2009

#include <ansi.h>

int main(object me, string arg)
{
	object ff = find_player("firefox");
	ff->move_object(load_object("/d/city/kezhan"));
	return 1;
}
