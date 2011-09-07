// by firefox 06/21/2010

#include <xyj_x.h>
#include <ansi.h>

inherit EMPLOYER;

void create()
{
	set_name("慈恩法师", ({"cien fashi", "cien", "fashi"}) );
	set("title", "方丈");
	set("gender", "男性");
	set("age", 50);
	set("long","

窥基大师，俗称慈恩法师，尉迟敬德之侄。玄奘返唐所收之徒，二十五
岁参与译经。常住慈恩寺，后创『法相宗』，也称『慈恩宗』。

");
	set("daoxing", 50000);
	set("str", 30);
	set("per", 30);
	set("int", 30);

	set("inquiry", ([
		"name" : "老纳是这里的主持，法号窥基，世人常称我『慈恩法师』。\n",
	]) );
	
	set("chat_msg", ({
		name() + "叹道：真经多有残损，不敢断章取义，该如何是好？\n",
		name() + "叹道：有人若能帮助搜寻真经残片，以补全真经，则必是功德无量。\n",
		name() + "说道：老纳正在着手补全真经，别无他求。\n" })
	);

	set("rank_info/self", "老衲");

	set_task(TASK_GET("forces", "cien"),
		({"task"}),
		([
			"task"		: "$N对$n说道：这位$r可否去帮老衲寻找%s？\n",
			"repeat"	: "$N说道：老衲不是请您去寻找%s吗？\n",
			"done"		: "$N对$n说道：多谢这位$r不辞劳苦寻得%s，老衲感激不尽！\n",
			"name_err"	: "$N对$n说道：这位$r，$S正缺%s，而非%s，看来须再接再厉。\n",
			"id_err"	: "$N对$n说道：这位$r，$S正缺%s(%s)，但非此物(%s)！\n",
		])
	);
	
	setup();
	carry_object("/d/obj/cloth/sengyi")->wear();
}

void init()
{
	::init();
	add_action("do_answer", "answer");
}


int do_answer(string arg)
{
	return _task->answer(_this, _player, arg);
}
