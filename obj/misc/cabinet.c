// by firefox 02/21/2010

inherit "/d/sldh2/feature/container";

void create()
{
	set_name("紫檀柜", ({ "zitan gui", "gui", "cabinet" }) );
	set_weight(500000);
	set_max_encumbrance(500000);
	set_max_items(20);

	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "个");
		set("long", "这是一个古色古香的紫檀柜，看来可以容纳很多东西。\n");
		set("value", 50);
		set("no_get", 1);
	}
	load_data();
}
