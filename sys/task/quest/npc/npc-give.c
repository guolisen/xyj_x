// by firefox 04/20/2010

#include <xyj_x.h>

inherit EMPLOYER;

void create()
{
	set_name("殷温娇", ({"yin wenjiao", "yin", "wenjiao"}));
	set("long", "殷夫人乃是殷开山之女，玄奘之母。\n");
	set("title", "御赐贤夫人");
	set("gender", "女性");
	set("age", 50);
	set("per", 35);

	set("chat_msg", ({
		"殷夫人叹道：唉，多灾多难哪。\n",
		"殷夫人自言自语地说道：近闻他乡受灾，令妾身彻夜难眠也。\n",
		"殷夫人说道：乡下水祸成灾，妾身痛心也。\n",
		"殷夫人叹言道：普天之下，有多少民众仍处于水深火热之中也。\n",
		"殷夫人说道：妾身救人之急也。\n",
		"殷夫人说道：亦恨不能妾身亲自赴汤蹈海，以解八方之难也。\n",})
	);
	
	set("inquiry", ([
		"here":   "此乃禹王台也，水陆大会将不期举行，妾身在此预做法场以事天下灾民难民。\n",
		"name":   "玄奘之母殷夫人也，在此做法以事天下灾民难民。\n",	])
	);
	
	set_task(TASK_GET("quest", "give"),
		({"give", "灾民", "难民", "穷人", "受灾", "解难", "救灾", "救", "给"}),
		([				
			"task"		:
				"$N拿起一根签，对$n说道：近闻他乡受灾，$S正想请人去给%s送%s。\n",
			"repeat"	:
				"$N对$n说道：这位$r，$S不是请您去给%s送%s吗？\n",
			"done"		:
				"$N对$n说道：多谢这位$r救人之急，为%s送去%s，真是品行可嘉也。\n",
		])
	);

	setup();

	carry_object("/d/obj/cloth/skirt")->wear();
	carry_object("/d/obj/cloth/shoes")->wear();
}


