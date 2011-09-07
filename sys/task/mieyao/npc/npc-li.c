// by firefox 04/20/2010

#include <xyj_x.h>

inherit EMPLOYER;

void create()
{
	set_name("李靖", ({ "li jing", "jing", "li" }) );
	set("gender", "男性" );
	set("long", "托塔李天王乃是天界元帅，麾下十万天兵天将，法力无边。\n");	
	set("title", "托塔天王");
	set("age",40);
	set("str", 40);

	set("chat_chance", 1);
	set("chat_msg", ({ name() + "说道：哪位大仙可愿去下界灭妖？\n",}) );

	seteuid(getuid());
	FAMILY->quick_setup(_this, "方寸山三星洞", 180);

	set_task(TASK_GET("mieyao", "mieyao"),
		({"mieyao", "kill", "灭妖"}),
		([
			"task"		: "$N将手中照妖镜朝下界一晃！\n"
				+ "$N对$n说道：近有%s在%s为非作歹，请速去降服！\n",
			"repeat"	: "$N说道：老夫不是派你去降服%s吗？\n",
			"cd"		: "$N对手中照妖镜一看，说：这位$r,妖魔已除尽,不妨先去歇息。\n",
		])
	);

	setup();
	carry_object("/d/obj/fabao/huangjin-baota");
	carry_object("/d/obj/armor/jinjia")->wear();
	carry_object("/d/sky/obj/zhanyaojian")->wield();
}

