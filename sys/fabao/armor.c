// by firefox 11/21/2009
// 法宝——盔甲

#include <armor.h>
#include <ansi.h>
inherit ARMOR;

//护甲，物甲，魔甲，偏物魔甲

/*

混铁棍
头上戴一顶水磨银亮熟铁盔
身上贯一副绒穿锦绣黄金甲
足下踏一双卷尖粉底麂皮靴
腰间束一条攒丝三股狮蛮带

金鱼精

头戴金盔晃且辉，	晃辉金盔
身披金甲掣虹霓。	虹霓金甲
腰围宝带团珠翠，	团珠带
足踏烟黄靴样奇。	烟黄靴


秦琼

龙鳞黄金细甲
描金箭壶
麂皮靴


如意真仙：

头戴星冠飞彩艳，身穿金缕法衣红。
足下云鞋堆锦绣，腰间宝带绕玲珑。
一双纳锦凌波袜，半露裙襕闪绣绒。
手拿如意金钩子，鐏利杆长若蟒龙。
*/

void create()
{
	set_name(HIY"龙鳞黄金细甲"NOR, ({ "dragon armor", "armor"}));
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

