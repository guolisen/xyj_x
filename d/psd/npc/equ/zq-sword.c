// by firefox 03/21/2009

#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
	set_name(HIM"紫青剑"NOR, ({ "ziqing sword", "sword" }) );
	set_weight(400);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("value", 700);
		set("material", "steel");
		set("long", "剑上有七采珠、九华玉以为饰，刃上常若霜雪，紫电青霜。\n");
		set("wield_msg", "$N抽出$n握在手中，光采射人。\n");
		set("unwield_msg", "$N把$n插入剑鞘，光华顿收。\n");
	}
	init_sword(175);
	setup();
}


int wield()
{
	object owner = environment();
	
	
	if(owner){
		string id = owner->query("id");
		if(wizardp(owner) || id == "zi xia" || id == "qing xia")
			return ::wield();
		if(owner->is_character())
			message_vision("$N使出吃奶的劲也无法从剑鞘中拔出$n。\n", owner, this_object());
	}
	return 0;
}


	
