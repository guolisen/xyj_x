// cracked by vikee 2/09/2002   vikee@263.net
// unwield.c

inherit F_CLEAN_UP;

int do_unwield(object me, object ob)
{
	string str;
	if( (string)ob->query("equipped") != "wielded")
		return notify_fail("你并没有装备这样东西作为武器。\n");

	if( ob->unequip() ) {
		if( !stringp(str = ob->query("unwield_msg")) )
			str = "$N放下手中的$n。\n";
		message_vision(str, me, ob);
		return 1;
	}
	return 0;
}

int main(object me, string arg)
{
	object ob;
	int i;

	if( !arg ) return notify_fail("你要脱掉什么？\n");

	if(arg=="all") {
		foreach(ob in all_inventory(me)) {
			do_unwield(me, ob);
		}
		write("Ok.\n");
		return 1;
	}

	if( !objectp(ob = present(arg, me)) )
		return notify_fail("你身上没有这样东西。\n");

	return do_unwield(me, ob);
}

int help(object me)
{
  write(@HELP
指令格式 : unwield|fangxia <物品名>|all 
 
这个指令让你放下手中的武器。
 
HELP
    );
    return 1;
}
 
