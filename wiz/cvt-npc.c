

inherit NPC;

#include <xyj_x.h>

void create()
{
	object ob;

	set_name("数据员", ({ "npc", }));

	set("gender", "男性" );

	set("long","

负责处理用户数据的NPC，也用下列指令：

    literate 等级                设定literate的新等级（只可用一次）
    exchange                     用80K配额兑换潜能25K潜能

");
	setup();
	
	carry_object("/obj/cloth");

}

void init()
{
	add_action ("do_literate", "literate");
	add_action ("do_exchange", "exchange");
}


int do_literate(string arg)
{
	return __DIR__"cvt"->set_literate(to_int(arg));
}


#define	NORM_RATIO			80

int do_exchange(string arg)
{
	mapping rewards = ([PEXP : 25000]);

	if(total_exp(_player) < 35*K) return notify_fail("你的武学道行太低！\n");

	if(TASK_EXC->do_reward(_player, name(), "兑换", rewards, NORM_RATIO)) {
		_player->add(PEXP, rewards[PEXP]);
		tell_object(_player, "你兑换了潜能。\n");		
	}
	return 1;
}
