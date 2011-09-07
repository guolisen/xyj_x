// by firefox 04/20/2010

#include <xyj_x.h>

inherit EMPLOYER;

void create()
{
	set_name("猪八戒", ({ "zhu bajie", "zhu", "bajie" }));
	set("long", "嘿嘿，连老猪都不认识啦？\n");
	
	set("age", 600);
	set("gender", "男性");
	set("per", 10);

	set("combat_exp", 1200*K);
	set("daoxing", 2000*K);

	set("max_force", 1500);

	set("chat_msg",({
		"猪八戒乐呵呵地说道：西天归来，老猪便是天下美食家也。\n",
		"猪八戒想想说：乡下发大水灾了，老猪该当救济饥民。\n",
		"猪八戒说道：老猪要寻遍天下美酒佳肴，再请世人来俺帅府品尝品尝。\n",
		"猪八戒说道：不是老猪贪嘴，俺老猪想凑个美宴，请平民百姓也能尝个新鲜。\n",
		"猪八戒自言自语地说：俺老猪不是为自己，老猪想收集世上美食，让大唐人都能来尝尝。\n",
		"猪八戒扭过身去捧起澡盆大的金饭盆吧嗒吧嗒大嚼了起来。\n",
		"猪八戒弯腰捧起水桶大的银酒壶咕咚咕咚地灌了下去。\n",
	}));
	set("inquiry", ([
		"here":   "此乃天蓬帅府也，老猪西天归来后唐太宗御赐在此开府，专事饮食慈善业。\n",
		"name":   "猪八戒，谁人不知也。\n",
	]));

	set("rank_info/self", "俺");

	set_task(TASK_GET("quest", "food"), 
		({"food", "美食", "美酒", "美宴", "佳肴", "食物", "饮水", "吃", "喝"}),
		([				
			"task"		:
				"$N略有所思地点点头对$n说道：$S老猪想给大唐人凑个美宴，正缺%s，\n"
				"这位$r可否赏老猪个大脸设法子去给弄来？\n",
			"repeat"	:
				"$N对$n说道：这位$r，$S还等着请您帮忙找的%s呢！\n",
			"done"		:
				"$N对$n说道：多谢这位$r为唐人美宴寻得%s，真是为大唐天下民众造福哇！\n",
			"name_err"	:
				"$N对$n说道：这位$r，$S等着请您帮忙找的%s，您却给俺%s，这……\n",
			"id_err"	:
				"$N对$n说道：这位$r，俺等着您的%s，东西倒挺象，但不是同一个货；\n"
				"俺要的是(%s)，您给的是(%s)！\n",
		])
	);

	setup();
	
	carry_object("/d/kaifeng/obj/jiuchipa")->wield();
	carry_object("/d/obj/armor/tongjia")->wear();
}

