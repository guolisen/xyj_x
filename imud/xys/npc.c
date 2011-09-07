// by firefox 10/01/2010
// 西游杀-报名NPC

inherit NPC;

#include <xys.h>

int do_join();

void create()
{
	set_name("绛珠仙子", ({"jiangzhu xianzi", "xianzi", "girl", }));
	set("long", @LONG

两弯似蹙非蹙凝烟眉，一双似喜非喜含情目。态生两靥之愁，娇袭一
身之病。泪光点点，娇喘微微。闲静时如姣花照水。行动处似弱柳扶
风。心较比干多一窍，病如西子胜三分。

LONG);

	set("title", HIY"幻境使者"NOR);
	set("gender", "女性");
	set("age", 18);
	set("per", 30);

	set("inquiry", ([
		"西行幻境": (: do_join :),
	]));

	setup();
	carry_object("/d/moon/obj/luoyi")->wear();

}
int do_join()
{
	return XYS->do_join(_this, _player);
}

void die ()
{
	set("kee", 200);
	set("eff_kee", 200);
	set("sen", 200);
	set("eff_sen", 200);
}

void unconcious()
{
	die();
}
