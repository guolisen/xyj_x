// by firefox 11/21/2009
// 法宝——吸血枪

#include <weapon.h>
#include <ansi.h>
inherit SPEAR;

string* _names = ({ "金攥提龙枪", "吸水提炉枪", "八宝驼龙枪" });

string _long = @LONG

枪长一丈零八寸，八十二斤。精钢黄金混铸而成，端的是金光闪闪，霸气十足。
传闻夏涂山氏所造，第一任主人项羽，顾也称霸王枪，第二任主人为二十八宿
中的井木犴。

LONG;

void create()
{
	set_name(HIY + names[random(3)] + NOR, ({"spear"}));
	set_weight(1000);
	if(clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("long", _long);
		set("material", "iron");
		set("wield_msg","$N拿出一把$n，握在手中．\n");
		set("unwield_msg", "$N放下手中的$n。\n");
	}
	init_spear(60);
	setup();
}

//吸血
mixed hit_ob(object me, object victim, int damage_bonus)
{
	//20%几率吸血
	if(!random(5) && damage_bonus > 0) {
		int damage = damage_bonus;
		victim->receive_damage("kee", damage, me);
		victim->receive_wound("kee", damage, me);

		message_vision("殷红的"HIR"鲜血"NOR"从$N的枪尾流出来。\n", me);
	}
}

