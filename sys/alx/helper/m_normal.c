// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

void create()
{
	set_name("豁牙", ({"abnormal"}));
	set("gender", "男性" );
	set("age", 10);
	set("long", "\n"
		"一个可爱的小娃娃，光着屁股，肚皮上用胭脂写着：\n\n"HIM
		"    十年一觉西游梦，赢得玩家变态名。\n\n"NOR
	);
	set("title", HIC"我本"HIM"正常"NOR);

	set("per", 120);
	set("str", 150);	
	
	SKI->set_list2(_this,
		({
			({ "literate" }),
			
			({ "yinfeng-zhua",		"unarmed",	"parry" }), 	
			({ "lingfu-steps",		"dodge" }),
			
			({ "huntian-qigong",	"force" }),
			({ "yaofa",				"spells" }),	
		}),
		1
	);

	set_events(
		([
			"born"		: HIW"『一二一，一二一』$N迈着正步走来。",
			"leave"		: HIW"$N喊道『我已正常，请西游人民放心』，说罢披头散发，发足狂奔。",
			"kill"		: "！",
	
			"cmds"		: ({ "cast huanying1" }),
		])
	);

	setup();
}

