
// cracked by vikee 2/09/2002   vikee@263.net
// bank.c

#include <ansi.h>

inherit ROOM;

string money_str(int amount);
int pay_player(object who, int amount);
void reset_balance(object me);

private string mid(string id)
{
	return (id == "cash") ? "thousand-cash" : id;
}

void init()
{
	add_action("do_convert", "convert");
	add_action("do_deposit", "deposit");
	add_action("do_check", "account");
	add_action("do_withdraw", "withdraw");
	
	reset_balance(this_player());
}

int do_convert(string arg)
{
	string from, to;
	int amount, bv1, bv2;
	object from_ob, to_ob;

	if( !arg || sscanf(arg, "%d %s to %s", amount, from, to)!=3 )
		return notify_fail("指令格式：convert <数量> <货币种类> to <货币种类>\n");

	from = mid(from);
	to = mid(to);

	if( this_player()->is_busy() )
		return notify_fail("你现在正忙着呢...。\n");

	from_ob = present(from + "_money", this_player());
	to_ob = present(to + "_money", this_player());
	if( !to_ob && file_size("/obj/money/" + to + ".c") < 0 )
		return notify_fail("你想兑换哪一种钱？\n");

	if( !from_ob )		return notify_fail("你身上没有这种货币。\n");
	if( amount < 1 )	return notify_fail("兑换货币一次至少要兑换一个。\n");

	if( (int)from_ob->query_amount() < amount )
		return notify_fail("你身上没有那么多" + from_ob->query("name") + "。\n");

	bv1 = from_ob->query("base_value");
	if( !bv1 ) return notify_fail("这种东西不值钱。\n");

	bv2 = to_ob ? to_ob->query("base_value") : call_other("/obj/money/" + to, "query", "base_value" );

	if( bv1 < bv2 ) amount -= amount % (bv2 / bv1);
	if( amount==0 )	return notify_fail("这些" + from_ob->query("name") + "的价值太低了，换不起。\n");
	this_player()->start_busy(1);

	if( !to_ob ) {
		to_ob = new("/obj/money/" + to);
		if(!(to_ob->move(this_player())))
			return 0;
		to_ob->set_amount(amount * bv1 / bv2);
	} else
		to_ob->add_amount(amount * bv1 / bv2);

	message_vision( sprintf("$N从身上取出%s%s%s，换成%s%s%s。\n",
		chinese_number(amount), from_ob->query("base_unit"), from_ob->query("name"),
		chinese_number(amount * bv1 / bv2), to_ob->query("base_unit"), to_ob->query("name")),
		this_player() );
	if( (int)from_ob->query_amount() == amount )
		destruct(from_ob);
	else
		from_ob->add_amount(-amount);

	this_player()->save();

	return 1;
}

static string* _ids = ({"coin_money", "silver_money", "gold_money", "thousand-cash_money"});

int do_deposit(string arg)
{
	int amount = 0;
	object me = this_player();

	if (arg=="all") {
		
		foreach(string id in _ids) {
			object ob = present(id, me);
			if(ob && ob->value() > 0) {
				amount += ob->value();
				destruct(ob);
			}
		}
		me->add("balance", amount);
		message_vision("$N把身上所有的钱都存进了钱庄。\n", me);

	} else {
		string what;
		object what_ob;

		if(!arg || sscanf(arg, "%d %s", amount, what) != 2)
			return notify_fail("命令格式：deposit <数量> <货币单位>\n");

		what = mid(what);

		if( me->is_busy() )
			return notify_fail("你现在正忙着呢...。\n");

		what_ob = present(what + "_money", me);

		if(!what_ob)
			return notify_fail("你身上没有带这种钱。\n");
		if(amount < 1)
			return notify_fail("你想存多少" + what_ob->query("name") + "？\n");
		if(what_ob->query_amount() < amount)
			return notify_fail("你带的" + what_ob->query("name") + "不够。\n");

		me->start_busy(1);
		message_vision(
			sprintf("$N拿出%s%s%s，存进了钱庄。\n", 
				chinese_number(amount), 
				what_ob->query("base_unit"),
				what_ob->query("name")
			),
			me
		);
		me->add("balance", what_ob->query("base_value") * amount);
		if(what_ob->query_amount() == amount)
			destruct(what_ob);
		else
			what_ob->add_amount(-amount);
	}
	me->save();

	return 1;
}


int do_check()
{
	int total = (int)this_player()->query("balance");

	if(!total || total < 0)  {
		this_player()->set("balance", 0);
		return notify_fail("您在敝银庄没有存钱。\n");
	}
	write("您在敝银庄共存有" +
		money_str(total) + "\n");

	return 1;
}


string ob_str(object ob)
{
	int amount = ob->query_amount();
	return chinese_number(amount) + ob->query("base_unit") + ob->name();
}
	

int do_withdraw(string arg)
{
	int amount, v;
	string what;
	object me = this_player();
	object ob;

	if(!arg || sscanf(arg, "%d %s", amount, what) != 2)
		return notify_fail("命令格式：withdraw <数量> <货币单位>\n");

	what = mid(what);

	if(me->is_busy() )
		return notify_fail("你现在正忙着呢...。\n");
	if(amount < 1)
		return notify_fail("你想取出多少钱？\n");
	if (file_size("/obj/money/" + what + ".c") < 0)
		return notify_fail("你想取出什么钱？\n");

	what = "/obj/money/" + what;
	v = amount * what->query("base_value");

	if(v > me->query("balance"))
		return notify_fail("你存的钱不够取。\n");
	if(v < what->query("base_value")) 
		return notify_fail("数量无效。\n");

	me->start_busy(1);

	ob = new(what);
	ob->set_amount(amount);
	what = ob_str(ob);
	if(!ob->move(me))
		return notify_fail("你身上的东西太多了。\n");

	me->add("balance",  -v);
	me->save();

	message_vision("$N从银号里取出" + what + "。\n", me);
	return 1;
}


string money_str(int amount)
{        
	// returns a chinese string of `amount` of money
	string output;

	if (amount / 10000) {
		output = chinese_number(amount / 10000) + "两黄金";
		amount %= 10000;
	}
	else
		output = "";
	if (amount / 100) {
		output = output + chinese_number(amount / 100) + "两白银";
		amount %= 100;
	}
	if (amount || sizeof(output)<2)
		return output + chinese_number(amount) + "文铜板";
	return output;
}


// return value is the amount which doesnot paid.
// mon 6/13/98
int pay_player(object who, int amount)
{
	int v;
	object ob;

	seteuid(getuid());
	if (amount < 1)
		amount = 0;
	if (v = amount / 10000) {
		ob = new("/obj/money/gold");
		ob->set_amount(amount / 10000);
		if(!(ob->move(who)))
			return amount;
		amount %= 10000;
	}
	if (amount / 100) {
		ob = new("/obj/money/silver");
		ob->set_amount(amount / 100);
		if(!(ob->move(who)))
			return amount;
		amount %= 100;
	}
	if (amount) {
		ob = new("/obj/money/coin");
		ob->set_amount(amount);
		if(!(ob->move(who)))
			return amount;
	}
	return 0;
}

void reset_balance(object me)
{
	int myexp=(me->query("daoxing")+me->query("combat_exp"))/1000;
	int allowed, removed_gold;
	string myid=me->query("id");
	string NPCNAME="赵公明";

	if(myexp<1) myexp=1;
	if(myexp>1000) myexp=2000;
	allowed=myexp*1000000;//each year can have 100 gold, range 100-200k. 
	
	if (me->query("balance") > allowed)	{
		me->set("balance_old", me->query("balance"));
		me->set("balance", allowed);
		removed_gold = (me->query("balance_old") - me->query("balance"))/10000;
		log_file("MONEY_RESET", ctime( time() )+"：魏大人收缴了"+me->query("name")+"("+me->query("id")+")"+removed_gold+"两黄金。\n");
		tell_object(me, GRN+NPCNAME+"在你的耳边悄声说道："+RANK_D->query_respect(me)+
			"，这、这真不知怎么说是好．．．\n"NOR);
		tell_object(me, GRN+NPCNAME+"在你的耳边悄声说道："+
			"昨日魏大人派人前来察案，发觉你老的黄金来路．．．\n"NOR);
		tell_object(me, GRN+NPCNAME+"在你的耳边悄声说道："+
			"若不是在下帮你老辩解，你老的钱就全都充公了．．．\n"NOR);
	}
}
