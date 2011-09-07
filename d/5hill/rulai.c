

#include <ansi.h>

inherit NPC;

#define DNTG11	"dntg11"	//dtng 11关标记

int work_me();

void create()
{
	set_name("如来佛", ({ "rulai fo", "rulai", "fo" }));
	set("title", "佛祖多陀阿伽陀");
	set("long", "大慈大悲灵山雷音古刹佛祖多陀阿伽陀如来佛爷。\n");
	set("gender", "男性");
	set("age", 10000);
	set("attitude", "peaceful");
	set("rank_info/self", "贫僧");
	set("rank_info/respect", "佛祖爷爷");
	//set("class", "bonze");
	set("str",100);
	set("per",100);
	set("max_kee", 10000);
	set("max_gin", 10000);
	set("max_sen", 10000);
	set("force", 10000);
	set("max_force", 10000);
	set("force_factor", 500);
	set("max_mana", 10000);
	set("mana", 10000);
	set("mana_factor", 500);
	set("combat_exp", 4000000);
	set("daoxing", 10000000);

	set_skill("literate", 300);
	set_skill("spells", 300);
	set_skill("buddhism", 300);
	set_skill("unarmed", 300);
	set_skill("jienan-zhi", 300);
	set_skill("dodge", 300);
	set_skill("lotusmove", 300);
	set_skill("parry", 300);
	set_skill("force", 300);
	set_skill("lotusforce", 300);
	set_skill("staff", 300);
	set_skill("lunhui-zhang", 300);
	map_skill("spells", "buddhism");
	map_skill("unarmed", "jienan-zhi");
	map_skill("dodge", "lotusmove");
	map_skill("force", "lotusforce");
	map_skill("parry", "lunhui-zhang");
	map_skill("staff", "lunhui-zhang");
	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: cast_spell, "bighammer" :),
	}) );

	set("inquiry", ([
		"天宫"			: (: work_me :),
		"玉帝"			: (: work_me :),
		"皇帝"			: (: work_me :),
		"让位"			: (: work_me :),
	]) );

	setup();
	carry_object("/d/obj/cloth/jia_sha")->wear();
}

void init()
{
	add_action("do_say", "say");
}

int work_me()
{
	object me = this_object();
	object who = this_player();

	object shanding = load_object(__DIR__"shanding");

	//todo:检查条件
	if( who->query("combat_exp") < 300000 ) {
		message_vision("$N对$n说道：条件不满足。\n", me, who);
		return 1;
	}
	if(shanding->query("short") != "莲花五行山顶峰") {	//山已经塌了
		message_vision("$N对$n说道：稍安毋躁。\n", me, who);
		return 1;
	}

	message_vision(CYN"$N对$n说道：你是想叫玉帝搬出去，将天宫让与你吗？\n"NOR, me, who);
	who->set_temp("dadu/stage", ({1, ({"是", "对", "轮流"})}));
	return 1;
}

int say(object who, string msg)
{
	message_vision(CYN"$N说道：" + msg + "\n"NOR, who);
}

int do_say(string arg)
{
	object me = this_object();
	object who = this_player();
	mixed* stage = who->query_temp("dadu/stage");
	int answer_ok = 0;

	if(!arg || !stage) return 0;

	//判断时候正确的回答了指定的关键字
	foreach(string word in stage[1]) {
		if(strsrch(arg, word) >= 0) answer_ok = 1;
	}
	if(!answer_ok) return 0;
	if(wizardp(who)) printf("[bebug]:stage[0]:%d\n", stage[0]);

	switch(stage[0]) {
	case 1:		
		say(who, "对，皇帝轮流做，明年到我家。若还不让，定要搅乱，永不清平！");
		say(me, "你除了生长变化之法，在有何能，敢占天宫胜境？");
		who->set_temp("dadu/stage", ({2, ({"手段", "十万", "八千", "腾云"})}));
		break;
	case 2:
		say(who, "我的手段甚多，一纵就能十万八千里。如何坐不得天位？");
		me->command("shake");
		say(me, "我与你打个赌赛；你若有本事打出我右手掌，算你赢，玉帝让出天宫。");
		say(me, "若不能打出手掌，你还下界为妖，再修几劫，却来争吵。");
		who->set_temp("dadu/stage", ({3, ({"好"})}));
		break;
	case 3:
		say(who, "好！");
		message_vision("$n说罢纵身跳上$N手心，道声：去也！一路云光，无影无形去了。\n", me, who);		
		who->set_temp("dadu/stage", ({4, ({"天尽头", "让", "记号"})}));
		who->move(__DIR__"finger");
		break;
	case 4:
		say(who, "我已去到天尽头，留了记号，速教玉帝让天宫与我！");
		say(me, "你这个尿精！你只自低头看看。");
		message_vision(CYN"$N伸出右手，中指写着『齐天大圣，到此一游』，指丫里还有尿臊气。\n"NOR, me, who);
		say(who, "有这等事！有这等事！我决不信！不信！等我再去来！");
		message_vision(HIR"$n纵身欲飞，$N翻掌一扑推出西天门外，五指化作五行山轻轻压住。\n"NOR, me, who);
		who->set(DNTG11, "done");		//todo:标记第十一关完成，第十二关开始
		who->delete_temp("dadu");		
		who->move(__DIR__"shandi");		
		break;
	}		
	return 1;
}
