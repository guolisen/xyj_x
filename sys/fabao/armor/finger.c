
#include <armor.h>

inherit FINGER;

/*

摧决cuī jué
　　扣断扳指。决，骨制品。

  射决shè jué
　　即佩韘。俗称扳指或搬指。

*/

void create()
{
	set_name("金戒指", ({ "jin jiezhi", "jiezhi", "ring" }));
	set("weight", 400);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "个");
		set("value", 2000);
		set("material", "gold");
		set("armor_prop/armor", 1);
	}
	setup();
}	
