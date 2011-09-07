// by firefox 02/21/2010

inherit ITEM;

void create()
{
	set_name("蛋壳", ({ "dan ke", "ke", "shell" }) );
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "一只破碎的蛋壳。\n");
		set("unit", "只");
	}

	setup();
}
