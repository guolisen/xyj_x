// firefox 11/21/2009

inherit NPC;

#include <ansi.h>
#include <xyj_x.h>

#define NAME			"谛听"
#define CD				5

int test_player();

object_f _task = TASK_GET("mieyao", "mieyao");

void create()
{
	set_name(NAME, ({ "di ting", "diting" }) );

	set("title", "万兽征物");
	set("gender", "雄性" );
	set("race", "野兽");
	set("can_speak", 1);
	set("age", 15);
	set("per", 120);
	set("long", "

谛听是地藏菩萨经案下伏的一神兽。他若伏在地下，一霎时，将四大部
洲山川社稷，洞天福地之间，蠃虫、麟虫、毛虫、羽虫、昆虫、天仙、
地仙、神仙、人仙、鬼仙可以照鉴善恶，察听贤愚。可明辨六耳猕猴与
孙悟空者，除了如来佛祖，就只有它了。

");     

	set("limbs", ({ "头部", "身体", "前脚", "后脚", "尾巴" }) );
	set("verbs", ({ "bite", "claw" }) );

	set("chat_chance", 1);
	set("chat_msg", ({	NAME"用后腿抓了抓自己的耳朵。\n" }) );
	set("inquiry", ([
		"mieyao":   (: test_player() :),
	]));

	setup();
}


int test_player()
{
	object me = this_object();
	object who = this_player();
	object ob = _task->query_guai(who);

	if(!cd_start(me, "answer", CD)) {
		msvx(CYN"$N闭上眼睛假装睡着了...\n"NOR, me);
		return 1;
	}

	if(ob) {
		object env = environment(ob);
		if(env) {
			string map = MISC_D->find_place(env);
			string room = env->query("short");
			if(map != room) room = map + "的" + room;

			msvx(CYN"$N俯伏在地，须臾抬起头来，对$n说道：那妖怪正在%s。\n"NOR, me, who, room);
			return 1;
		}
	}

	msvx(CYN"$N俯伏在地，须臾抬起头来，对$n说道：世间无此怪。\n"NOR, me, who);
	return 1;
}

void die()
{
	set("eff_kee", 2200);
	set("eff_sen", 2200);
	set("kee", 2200);
	set("sen", 2200);
}

void unconcious()
{
	die ();
}