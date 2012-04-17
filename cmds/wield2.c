
inherit F_CLEAN_UP;

int do_wield(object me, object ob);

int main(object me, string arg)
{
	object ob;

	if(!arg) return notify_fail("你要装备什么武器？\n");

	if(arg == "all") {
		foreach(ob in all_inventory(me)) {		
			if(ob->query("equipped")) continue;
			do_wield(me, ob);
		}
		write("Ok.\n");
		return 1;
	}

	if(!objectp(ob = present(arg, me)))
		return notify_fail("你身上没有这样东西。\n");

	if(ob->query("equipped"))
		return notify_fail("你已经装备着了。\n");

	return do_wield(me, ob);
}

int do_wield(object me, object ob)
{	
	if(me->query_temp("no_wield"))
		return notify_fail("你现在不能持有兵器！\n");

	if(ob->wield()) {
		string str = or2(ob->query("wield_msg"), "$N装备$n作武器。\n");
		message_vision(str, me, ob);
		return 1;
	} else
		return 0;
}

int help(object me)
{
	write(@HELP
指令格式：wield|zhuangbei <装备名称>
 
这个指令让你装备某件物品作武器, 你必需要拥有这样物品.
 
HELP
    );
    return 1;
}
