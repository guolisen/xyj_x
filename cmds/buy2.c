// buy.c

inherit F_CLEAN_UP;

//根据id或货物寻找货主
object find_vender(object env, string id, string item)
{
	if(id) return present(id, env);
	foreach(object who in all_inventory(env)) {
		if(who->buy_object(0, item) > 0) return who;
	}
	return 0;
}

int main(object me, string arg)
{
	string item, vid;
	int n = 0;
	object vender;
	int price = 0, afford = 0;

	if(me->is_busy()) return notify_fail("你现在正忙着呢。\n");

	if(arg) {
		if(sscanf(arg, "%s from %s", item, vid) != 2) item = arg;
		if(sscanf(item, "%d %s", n, item) != 2) n = 1;
		vender = find_vender(environment(me), vid, item);
		if(!objectp(vender)) return notify_fail("你要跟谁买东西？\n");		
		price = vender->buy_object(me, item) * n;
	}
	
	if(price < 1) return notify_fail("指令格式: buy [数量] <某物> [from <某人>]\n");

	if(afford = me->can_afford(price)) {
		if(afford == 2) return notify_fail("你没有足够的零钱，而银票又没人找得开。\n");

		if(vender->complete_trade(me, item, n)) {
			me->pay_money(price);
			return 1;
		}
	} 
	else return notify_fail("你的钱不够。\n");

	return 0;
}

int help(object me)
{
	write( @HELP
指令格式: buy [数量] <某物> [from <某人>]

这一指令让你可以从某些人身上买到物品。可输入数量，也可省略货商。
HELP
	  );
	return 1;
}
