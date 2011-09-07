// by firefox 03/21/2009

#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
	set_name("双股剑", ({ "xiong sword", "sword" }) );
	set_weight(780);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("material", "steel");
		set("long", "双股雄剑，东汉先秦制式，柄饰祥瑞黄龙，长三尺七寸，重七斤八两。\n");
		set("wield_msg", "$N抽出$n握在手中，仿佛游龙出海。\n");
		//set("unwield_msg", "$N把$n插入剑鞘，光华顿收。\n");
	}
	init_sword(70);
	setup();
}

/*



if(who->query("food") < who->query("max_food")) {

	

	众僧道；“老爷，不知是那山里来的妖邪在这寺里。我们晚夜间着两个小和尚去撞钟打鼓，只听得钟鼓响罢，再不见人回。
	至次日找寻，只见僧帽、僧鞋，丢在后边园里，骸骨尚存，将人吃了。你们住了三日，我寺里不见了六个和尚。故此，我
	兄弟们不由的不怕，不由的不伤。因见你老师父贵恙，不敢传说，忍不住泪珠偷垂也。”

	$N对着$n馋的直流口水。

	$N扑向$n，大口小口的啃起来，一会功夫$n已经被啃得残缺不全了。\n"
	
	$N打了一个嗝。

	$N轻轻的舔着嘴角的血迹。

	set("name", "残缺的尸体");
	set("long", "一具残缺不全的尸体，上面都是啃咬过的痕迹。\n\n");
}


*/