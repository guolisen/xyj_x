// by firefox 04/20/2010

#include <xyj_x.h>

inherit EMPLOYER;

void create()
{
	set_name("胡敬德", ({"hu jingde", "hu", "jingde"}));
	set("long", "一位身披战袍，面容庄重严肃的御林都督。\n");
	set("title", "八十万御林都督");
	set("gender", "男性");
	set("age", 60);
	set("per", 35);

	set("chat_msg", ({
		"都督大人怒发冲冠，将惊堂木啪地一拍，喝道：杀！\n",
		"都督大人怒道：杀尽天下妖魔鬼怪！\n",
		"都督大人拍着惊堂木吼道：妖贼！\n",
		"都督大人怒不可遏：斩尽杀绝！\n",
		"都督大人哼了一声：杀！\n",
		"都督大人说道：要扫除一切牛鬼蛇神！\n",})
	);

	set("inquiry", ([
		"here":   "此乃禹王台也，水陆大会将不期举行，本都督在此预做法场，杀尽妖魔鬼怪！\n",
		"name":   "八十万御林都督胡敬德也，在此做法，以杀尽妖魔鬼怪！\n",])
	);

	set_task(TASK_GET("quest", "kill"),
		({"kill", "妖魔", "妖贼", "鬼怪", "牛鬼", "蛇神", "杀尽", "杀", "斩"}),
		([				
			"task"		:
				"$N迅速地一占卦，将惊堂木啪地一拍对$n说道：去将%s降服了！\n",
			"repeat"	:
				"$N对$n说道：这位$r，老夫不是请您去降服%s吗？\n",
			"done"		:
				"$N对$n说道：多谢这位$r除妖灭怪，降服了%s，真是品行可嘉也。\n",
		])
	);

	setup();
	carry_object("/d/obj/cloth/zhanpao")->wear();
}

