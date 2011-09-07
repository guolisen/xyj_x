// by firefox 04/20/2010

#include <xyj_x.h>

inherit EMPLOYER;

void create()
{
	set_name("陈光蕊", ({"chen guangrui", "chen", "guangrui"}));

	set("long", "陈光蕊乃玄奘之父，当朝大阐都纲御赐状元。\n");
	set("title", "大阐都纲");
	set("gender", "男性");
	set("age", 50);
	set("per", 35);

	set("chat_msg", ({
		"光蕊大师说道：善哉善哉哪。\n",
		"光蕊大师自语道：世上贤人，有求必应哪。\n",
		"光蕊大师说道：祭祖求贤，乃水陆大会前之必需也。\n",
		"光蕊大师叹言道：天下招贤，利国利民之大策也。\n",
		"光蕊大师说道：八方求贤也。\n",
		"光蕊大师说道：焚香祭祖，以招天下招贤士。\n",})
	);
	set("inquiry", ([
		"here":   "此乃禹王台也，水陆大会将不期举行，本状元在此预做法场以祭祖求贤。\n",
		"name":   "玄奘之父陈光蕊也，在此做法祭祖求贤。\n",])
	);

	set("rank_info/self", "老夫");

	set_task(TASK_GET("quest", "ask"), 
		({"ask", "祭祖", "求贤", "招贤", "贤人", "贤士", "善哉", "招", "求"}),
		([				
			"task"		:
				"$N燃起一根香祭祀一番，对$n说道：祖灵在天，请您去拜见%s并询问有关%s一事。\n",
			"repeat"	:
				"$N对$n说道：这位$r，$S不是请您去见%s询问%s一事吗？\n",
			"done"		:
				//"$N对$n说道：多谢这位$r祭祖拜贤，就%s一事拜见了%s，真是品行可嘉也。\n",
				"$N对$n说道：多谢这位$r祭祖拜贤，拜见%s询问%s一事，真是品行可嘉也。\n",
		])
	);

	setup();
	carry_object("/d/obj/cloth/changpao")->wear();
}

