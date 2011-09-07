// by firefox 02/21/2010

inherit ITEM;
inherit F_LIQUID;

void create()
{
	set_name("茶碗", ({ "cha wan", "wan", "tea" }) );
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "这是一只粗瓷茶碗。\n");
		set("unit", "只");
		set("value", 40);
		set("max_liquid", 80); 
	}

	set("liquid", ([
		"type": "tea",
		"name": "淡茶",
		"remaining": 100,
	]) );
	setup();
}
