//firefox 11/21/2009

#include <armor.h>
#include <ansi.h>

inherit BAG;

void create()
{
	set_name(HIY"Ãè½ð¼ýºø"NOR, ({"jian hu"}));
	set_weight(200);
	set_max_encumbrance(8000);
	set_max_items(2);
	if(clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "Ö»");
		set("material", "metal");
		set("armor_prop/armor", 1);
	}
	setup();
}
