//Cracked by Roath

inherit COMBINED_ITEM;

void setup()
{}

void init()
{
	add_action("do_eat", "eat");
}

void create()
{
	set_name("��Ƿ�", ({"jingu fen", "fen"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("base_unit", "��");
		set("unit", "Щ");
		set("long", "һ������ɫ��ҩ�ۡ�\n");
		set("value", 3000);
		set("drug_type", "��ҩ");
	}
	set_amount(1);
	setup();
}

int do_eat(string arg)
{
	if (arg != "jingu fen" && arg != "fen")
		return 0;

	//  if ((int)this_player()->query("eff_kee") == 
	//    (int)this_player()->query("max_kee"))
	//    return notify_fail("�����ڲ���Ҫ�ý�Ƿۡ�\n")
	else {
		this_player()->receive_curing("kee", 40+random(10));
		message_vision("$N����һ����Ƿۣ���ʱ����һ���Ⱥ���\n",this_player());
		add_amount(-1);
		return 1;
	}
}

string query_autoload() 
{
	return this_object()->query_amount() + ""; 
}

void autoload(string param)
{
	int n;
	if( sscanf(param, "%d", n) == 1 && n > 0) this_object()->set_amount(n);
}

