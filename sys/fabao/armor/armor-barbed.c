// by firefox 11/21/2009
// 法宝——刺甲，受到攻击返伤

#include <armor.h>
#include <ansi.h>
inherit ARMOR;

//五彩仙衣
void create()
{
	set_name(HIY"五彩仙衣"NOR, ({ "dragon armor", "armor"}));
	set_weight(1);

	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "件");
		set("long", "一件金灿灿的盔甲．\n");

		set("material", "iron");
		set("armor_prop/armor", 1);
		set("armor_prop/dodge", 1);

		//set("no_get", 1);
	}
	setup();
}

