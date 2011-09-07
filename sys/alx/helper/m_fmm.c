// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";


void on_init(object me, object who)
{
	if(!random(2)) me->command("snicker");
}

void create()
{
	set_name("机器螃蟹", ({"jiqi pangxie", "pangxie", "crab"}));
	set("gender", "女性" );
	set("age", 23);
	set("long", "\n"
		"一只精密的全自动螃蟹。不锈钢外壳上点点凸凹，看似平底\n"
		"锅的痕迹。上面歪歪扭扭的字迹，像是用酱油写下的：\n\n"RED
		"    无才可去补苍天，横行西游若许年。\n"
		"    本非居家琐碎事，被谁拉去一通扁？\n\n"NOR
	);
	set("title", HIC"卿本"HIM"夹人"NOR);

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
			"born"		: HIW"一阵轰鸣由远而近，$N屁股后冒着黑烟风驰电掣般驶来。",
			"leave"		: HIW"天空中伸出一只平底锅把$N舀了起来，然后不见了。\n"NOR
				"隐约传来『臣妾再也不偷玩MUD了...』。",
			"init"		: (: on_init :),
			"kill"		: "！",
	
			"cmds"		: ({ "cast suliao" }),
		])
	);

	setup();

}

