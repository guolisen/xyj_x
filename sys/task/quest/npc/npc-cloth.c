// by firefox 04/20/2010

#include <xyj_x.h>

inherit EMPLOYER;

void create()
{
	set_name("香兰", ({"xiang lan", "xiang", "lan"}));
	set("gender", "女性");
	set("age", 28);
	set("per", 28);

	set("chat_msg",({
		"香兰咯咯一笑：各类异宝可不少。\n",
		"香兰宛尔一笑说道：天下善人多也。\n",
		"香兰说：大开眼界，乐也乐也。\n",
	}));

	set("inquiry", ([
		"here":   "此乃高姓兰亭府也，姑娘在此收集奇珍异宝。\n",
		"name":   "高家小姐香兰也。\n",
	]));

	set("rank_info/self", "姑娘");

	set_task(TASK_GET("quest", "cloth"),
		({"cloth", "异宝", "募捐", "捐"}),
		([				
			"task"		:
				"$N对$n一笑：$S想起有人想要%s，\n"
				"这位$r能否替$S想个办法？\n",
			"repeat"	:
				"$N对$n说道：这位$r，$S还盼着您的%s呢！\n",
			"done"		:
				"$N对$n说道：多谢这位$r替香兰寻得%s，$S好个开心！\n",
			"name_err"	:
				"$N对$n说道：这位$r，$S说过需要%s，您倒给$S%s，好玩好玩。\n",
			"id_err"	:
				"$N对$n说道：这位$r，$S是想要%s，东西倒挺象，但不是同一个货；\n"
				"$S要的是(%s)，您给的是(%s)！\n",
		])
	);

	setup();

	carry_object("/d/obj/cloth/pinkskirt")->wear();
	carry_object("/d/obj/cloth/shoes")->wear();
}

