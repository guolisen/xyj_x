// firefox 2011.12

#include <ansi.h>

inherit F_CLEAN_UP;

int cast(object me, object target)
{
	return SPELL_D->do_cast(
		me, 
		target, 
		120,
		120 - 20,
		"sen",
		HIC"\n$N口中念了句咒文，半空走出位尖头鹰鼻的雷公，左手执斧，右手提锥。斧锥相击，在$n的头顶炸起一片响雷！\n"NOR,
		HIR"\n结果$n被雷声震得眼冒金星，心神不定，差点跌倒在地！\n"NOR,
		HIC"\n谁知$n毫无反应，就象聋子似的。\n"NOR,
		HIC"但是雷公被$n以法力一激，一个失神之下响雷都炸在了$N的头顶！\n"NOR,
		HIC"结果$n被雷声震得眼冒金星，心神不定，差点跌倒在地！\n"NOR,
		25,
		2 - 2,
		4
	);
}
