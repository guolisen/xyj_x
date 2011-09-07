// by firefox 04/20/2010

#include <xyj_x.h>

inherit EMPLOYER;

void create()
{
	set_name("相公", ({"xiang gong", "xiang", "gong"}));
	set("gender", "男性");
	set("title", "御赐");
	set("age", 80);
	set("per", 25);

	set("chat_msg",({
		"相公喜形于色地说：近来各类武器征集了不少，找个时间派人送到京城。\n",
		"相公自言自语道：武器精品将不期进贡给皇宫。\n",
		"相公呐呐地说道：军机大臣派人催问可否弄得武器佳品。\n",
		"相公说：什么兵器都要，可以改良或仿制也。\n",
		"相公低声说道：收集的武器该分类处置。\n",
		"相公自言道：好，各路英雄豪杰都纷纷前来献宝。\n",
	}));
	set("inquiry", ([
		"here":   "此乃御赐相府也，老夫被御准在此收集武器。\n",
		"name":   "姓相名良也。\n",
	]));

	set_task(TASK_GET("quest", "weapon"),
		({"weapon", "武器", "兵器", "法宝", "收集", "征集", "宝"}),
		([				
			"task"		:
				"$N略有所思，然后对$n说道：老夫正想请人去找%s，\n"
				"这位$r能否帮老夫个忙？\n",
			"repeat"	:
				"$N对$n说道：这位$r，老夫还盼着您的%s呢！\n",
			"done"		:
				"$N对$n说道：多谢这位$r不辞劳苦寻得%s，老夫感激不尽！\n",
			"name_err"	:
				"$N对$n说道：这位$r，老夫盼着您的%s，您倒却给老夫%s，咳咳。\n",
			"id_err"	:
				"$N对$n说道：这位$r，老夫盼着您的%s，东西倒挺象，但不是同一个货；\n"
				"老夫要的是(%s)，您给的是(%s)！\n",
		])
	);

	setup();
	carry_object("/d/obj/cloth/choupao")->wear();
}


