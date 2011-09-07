// by firefox 04/20/2010

#include <xyj_x.h>

inherit EMPLOYER;

void create()
{
	set_name("相婆", ({"xiang po", "xiang", "po"}));
	set("gender", "女性");
	set("title", "御赐");
	set("age", 75);

	set("chat_msg",({
		"相婆高兴地说：相公也说啦，奇货征集了不少，可近期派人将盔甲护具送到京城。\n",
		"相婆说道：皇宫里人说我们相府收集了不少好盔甲护具。\n",
		"相婆又说道：魏大人也说上次送的盔甲护具里不少上乘品。\n",
		"相婆说：有些盔甲护具可以加以改良。\n",
		"相婆说道：相府征集盔甲护具，真是做了好事也。\n",
		"相婆自言道：个别征来的盔甲残缺不全，还需努力征集。\n",	})
	);

	set("inquiry", ([
		"here":   "此乃御赐相府也，妾身在此专门收集盔甲。\n",
		"name":   "相良之妻也。\n",	])
	);

	set("rank_info/self", "妾身");

	set_task(TASK_GET("quest", "armor"), 
		({"armor", "盔甲护具", "盔甲", "护具", "收集", "征集"}),
		([				
			"task"		:
				"$N想想对$n说道：今天$S正准备请人去找%s，\n"
				"这位$r能否帮相府个忙？\n",
			"repeat"	:
				"$N对$n说道：这位$r，$S还盼着您的%s呢！\n",
			"done"		:
				"$N对$n说道：多谢这位$r不辞劳苦寻得%s，$S感激不尽！\n",
			"name_err"	:
				"$N对$n说道：这位$r，$S盼着您的%s，您倒却给$S%s，唉呀呀。\n",
			"id_err"	:
				"$N对$n说道：这位$r，$S盼着您的%s，东西倒挺象，但不是同一个货；\n"
				"$S要的是(%s)，您给的是(%s)！\n",
		])
	);

	setup();
	carry_object("/d/obj/cloth/skirt")->wear();
}

