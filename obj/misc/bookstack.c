// by firefox 02/21/2010

inherit "/d/sldh2/feature/container";

void create()
{
	set_name("书架", ({ "shu jia", "jia", "bookstack" }) );
	set_weight(500000);
	set_max_encumbrance(500000);
	set_max_items(20);

	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "个");
		set("long", "这是一个多层的大书架，除了书，也可放一些杂物。\n");
		set("value", 50);
		set("no_get", 1);
	}
	load_data();
}
