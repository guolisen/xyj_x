// by firefox 02/21/2010

inherit ITEM;

void create()
{
	set_name("丹炉", ({ "dan lu", "lu" }) );
	//set("short", "丹炉");
	set_weight(300000);
	set_max_encumbrance(300000);

	set("unit", "鼎");
	set("long", @LONG

这是一鼎一人多高的紫色丹炉。上面铭刻着风火雷电，五行八卦各
种图案。

LONG);
}

int is_container()
{
	return 1;
}

void init ()
{
	add_action ("do_enter", "jump");
	add_action ("do_enter", "plunge");
}

int do_enter (string arg)
{
	object who = this_player();
	if (arg != "tong danlu" && arg != "danlu")
		return 0;

	message_vision ("$N潜身往丹炉里一跃，袅袅青烟中$N呼地一声不见了。\n",who);
	who->move(this_object());
	who->start_busy(1);
	return 1;
}

void smoking (object me)
{
	object where = environment (me);
	tell_room (where,"铜丹炉冒出袅袅的青烟。\n");
}
