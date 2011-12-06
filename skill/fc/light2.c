// firefox 2011.12

#include <ansi.h>

inherit F_CLEAN_UP;

int cast(object me, object target)
{
	return SPELL_D->do_cast(
		me, 
		target,
		100 + 40,
		100,
		"kee",
		HIC"\n$N口中念了句咒文，半空走出一位电母，双手铜镜相转，忽的闪出一道金光射向$n！\n"NOR,
		HIR"\n结果「嗤」地一声，金光从$n身上透体而过，\n拖出一条长长的血箭，直射到两三丈外的地下！\n"NOR,
		HIC"结果嗤！地一声$n闻到了一股焦味。还好只烧掉了几根头发。\n"NOR,
		HIC"但是金光被$n以法力反激，反向$N射去！\n"NOR,
		HIR"结果金光从$n身上透体而过，拖出一条长长的血箭，直射到两三丈外的地下！\n"NOR,
		25,
		2 + 1,
		5
	);
}
