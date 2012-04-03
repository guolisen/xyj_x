
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
		return notify_fail("ָ���ʽ��convert <����> <��������> to <��������>\n");

	from = mid(from);
	to = mid(to);

	if( this_player()->is_busy() )
		return notify_fail("��������æ����...��\n");

	from_ob = present(from + "_money", this_player());
	to_ob = present(to + "_money", this_player());
	if( !to_ob && file_size("/obj/money/" + to + ".c") < 0 )
		return notify_fail("����һ���һ��Ǯ��\n");

	if( !from_ob )		return notify_fail("������û�����ֻ��ҡ�\n");
	if( amount < 1 )	return notify_fail("�һ�����һ������Ҫ�һ�һ����\n");

	if( (int)from_ob->query_amount() < amount )
		return notify_fail("������û����ô��" + from_ob->query("name") + "��\n");

	bv1 = from_ob->query("base_value");
	if( !bv1 ) return notify_fail("���ֶ�����ֵǮ��\n");

	bv2 = to_ob ? to_ob->query("base_value") : call_other("/obj/money/" + to, "query", "base_value" );

	if( bv1 < bv2 ) amount -= amount % (bv2 / bv1);
	if( amount==0 )	return notify_fail("��Щ" + from_ob->query("name") + "�ļ�ֵ̫���ˣ�������\n");
	this_player()->start_busy(1);

	if( !to_ob ) {
		to_ob = new("/obj/money/" + to);
		if(!(to_ob->move(this_player())))
			return 0;
		to_ob->set_amount(amount * bv1 / bv2);
	} else
		to_ob->add_amount(amount * bv1 / bv2);

	message_vision( sprintf("$N������ȡ��%s%s%s������%s%s%s��\n",
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
		message_vision("$N���������е�Ǯ�������Ǯׯ��\n", me);

	} else {
		string what;
		object what_ob;

		if(!arg || sscanf(arg, "%d %s", amount, what) != 2)
			return notify_fail("�����ʽ��deposit <����> <���ҵ�λ>\n");

		what = mid(what);

		if( me->is_busy() )
			return notify_fail("��������æ����...��\n");

		what_ob = present(what + "_money", me);

		if(!what_ob)
			return notify_fail("������û�д�����Ǯ��\n");
		if(amount < 1)
			return notify_fail("��������" + what_ob->query("name") + "��\n");
		if(what_ob->query_amount() < amount)
			return notify_fail("�����" + what_ob->query("name") + "������\n");

		me->start_busy(1);
		message_vision(
			sprintf("$N�ó�%s%s%s�������Ǯׯ��\n", 
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
		return notify_fail("���ڱ���ׯû�д�Ǯ��\n");
	}
	write("���ڱ���ׯ������" +
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
		return notify_fail("�����ʽ��withdraw <����> <���ҵ�λ>\n");

	what = mid(what);

	if(me->is_busy() )
		return notify_fail("��������æ����...��\n");
	if(amount < 1)
		return notify_fail("����ȡ������Ǯ��\n");
	if (file_size("/obj/money/" + what + ".c") < 0)
		return notify_fail("����ȡ��ʲôǮ��\n");

	what = "/obj/money/" + what;
	v = amount * what->query("base_value");

	if(v > me->query("balance"))
		return notify_fail("����Ǯ����ȡ��\n");
	if(v < what->query("base_value")) 
		return notify_fail("������Ч��\n");

	me->start_busy(1);

	ob = new(what);
	ob->set_amount(amount);
	what = ob_str(ob);
	if(!ob->move(me))
		return notify_fail("�����ϵĶ���̫���ˡ�\n");

	me->add("balance",  -v);
	me->save();

	message_vision("$N��������ȡ��" + what + "��\n", me);
	return 1;
}


string money_str(int amount)
{        
	// returns a chinese string of `amount` of money
	string output;

	if (amount / 10000) {
		output = chinese_number(amount / 10000) + "���ƽ�";
		amount %= 10000;
	}
	else
		output = "";
	if (amount / 100) {
		output = output + chinese_number(amount / 100) + "������";
		amount %= 100;
	}
	if (amount || sizeof(output)<2)
		return output + chinese_number(amount) + "��ͭ��";
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
	string NPCNAME="�Թ���";

	if(myexp<1) myexp=1;
	if(myexp>1000) myexp=2000;
	allowed=myexp*1000000;//each year can have 100 gold, range 100-200k. 
	
	if (me->query("balance") > allowed)	{
		me->set("balance_old", me->query("balance"));
		me->set("balance", allowed);
		removed_gold = (me->query("balance_old") - me->query("balance"))/10000;
		log_file("MONEY_RESET", ctime( time() )+"��κ�����ս���"+me->query("name")+"("+me->query("id")+")"+removed_gold+"���ƽ�\n");
		tell_object(me, GRN+NPCNAME+"����Ķ�������˵����"+RANK_D->query_respect(me)+
			"���⡢���治֪��ô˵�Ǻã�����\n"NOR);
		tell_object(me, GRN+NPCNAME+"����Ķ�������˵����"+
			"����κ��������ǰ���참���������ϵĻƽ���·������\n"NOR);
		tell_object(me, GRN+NPCNAME+"����Ķ�������˵����"+
			"���������°����ϱ�⣬���ϵ�Ǯ��ȫ���乫�ˣ�����\n"NOR);
	}
}
